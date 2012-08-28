/*

  This file is part of LFT.

  The LFT software provided in this Distribution is
  Copyright 2005 VOSTROM Holdings, Inc.

  The full text of our legal notices is contained in the file called
  COPYING, included with this Distribution.

  Authors:

  -  Victor Oppleman <lft@oppleman.com>
  -  Eugene Antsilevitch <ugen@xonix.com>

  Other copyrights and former authors:

  -  Portions copyright (c) Genuity, Inc. 
  -  Portions copyright (c) Nils McCarthy

*/


#include "acconfig.h"
#include <assert.h>

#ifdef __CYGWIN__
#define __USE_W32_SOCKETS
#include "windows.h"
#include <ws2tcpip.h>
#include <sys/types.h>
#define LITTLE_ENDIAN 1
#define BYTE_ORDER 1
typedef signed long n_long;
typedef signed short n_short;
typedef signed long n_time;
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <getopt.h>
#include "include/net/if_arp.h"
#include "include/netinet/if_ether.h"
#include "include/netinet/ip.h"
#include "include/netinet/ip_icmp.h"
#include "include/netinet/tcp.h"
#else
#include <sys/types.h>
#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif
#include <stdio.h>
#include <math.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/if_ether.h>
#include <assert.h>
#include <netdb.h>
#include <pcap.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#ifdef BSD
#include <machine/limits.h>
#endif
#ifdef BSD_IP_STACK
#include <errno.h>
#include <sys/ioctl.h>
#ifndef DARWIN
#include <net/bpf.h>
#include <pcap-int.h>
#endif
#endif

#ifdef sun
#include <limits.h>
#include <strings.h>
#endif

#endif

#include "lft_ifname.h"
#include "lft_lsrr.h"
#include "whois.h"

#include "lft_queue.h"

static char *version = "2.5";  	/* set version string */
static char *version_date = "(9/2005)";	/* date of this version */
static char *appname = "LFT";
static char *hostname = NULL;
static char *hostname_lsrr[9];
static int hostname_lsrr_size = 0;
static int dflag = 0;
static int hop_info_size = 0;
static int hop_info_length = 0;

static int seq_start = 0; 	/* generate ISN internally by default */
static int dport = 80;          /* set default destination to tcp/80 HTTP */
static int sport = 53;		/* set default source to tcp/53 dns-xfer */
static int auto_ports = 1;	/* enable port autoselection by default */
static int random_source = 0;   /* disable random source port by default */

static int win_len = 32768;

static int timeout_ms = 1000;	/* timeout between retries */
static int retry_max = 2;	/* number of retries before giving up */
static int retry_min = 1;	/* minimum number of checks per hop */
static double scatter_ms = 20;	/* milleseconds between sends */
static int ahead_limit = 5;	/* number of probes we can send
				 * without replies if we don't know
				 * the number of hops */
static int ttl_limit = 30;	/* max # hops to traverse (highest TTL) */
static int ttl_min = 0;	  	/* user may request to start at a higher TTL */
static int break_on_icmp = 1;	/* break on icmp other than time exceeded */
static int noisy = 0;		/* disable verbose debug by default */
static int nostatus = 0;	/* print status bar by default */
static int userdevsel = 0;	/* by default, we'll select the device */
static int resolve_names = 1;   /* dns resolution enabled by default */
static int hostnames_only = 0;	/* disable printing of IP addresses */
static int timetrace = 0;  	/* disable tracer timing by default */
static int max_net_dev_input = 64; /* only take this much input */
static int adaptive = 0;		/* disable state engine by default */
static int do_netlookup = 0;    /* disable netname lookup by default */
static int do_aslookup = 0;	/* disable asn lookup by default */
static int use_radb = 0;	/* use RADB instead of pwhois */
static int use_cymru = 0;	/* use Cymru instead of pwhois */
static int use_ris = 0;         /* use RIPE NCC RIS instead of pwhois */

struct in_addr local_address;
struct in_addr remote_address;

struct timeval ts_last_sent, now, begin_time, trace_done_time;

int send_sock;
int skip_header_len;

#ifdef __CYGWIN__
int recv_sock;
static int sock = -1;
#endif

unsigned short ip_id;
unsigned char tcp_flags = TH_SYN;

int num_hops = 0;
int num_sent = 0;
int num_rcvd = 0;

static char *icmp_messages[] = {
  "endpoint",
  "net unreachable",
  "host unreachable",
  "protocol unreachable",
  "port unreachable",
  "need fragment",
  "source fail",
  "net unknown",
  "host unknown",
  "src isolated",
  "net prohib",
  "host prohib",
  "bad tos/net",
  "bad tos/hst",
  "prohibited",
  "precedence violation",
  "precedence cutoff"
};

/* The actual packet data */
struct trace_packet_s
{
  struct ip ip_hdr;
  struct ip_lsrr lsrr;		/* must go here for ip checksum to work */
  struct tcphdr tcp_hdr;
  int size;
}
trace_packet;


/* Packet container with additional info */
struct trace_packet_info_s
{
  int icmp_type;		/* ICMP_UNREACH code, -1 if RST reply */
  int is_done;			/* is this a final hop? */
  short hopno;
  unsigned int   seq;
  struct timeval sent;
  struct timeval recv;		/* 0 if unreceived */
  struct in_addr hopaddr;	/* IP address of router */
  struct trace_packet_s	packet;
  SLIST_ENTRY(trace_packet_info_s) next_by_hop;
  SLIST_ENTRY(trace_packet_info_s) next;
}
*trace_packet_info;		/* indexed by dport - dport */

/* list of packet containers */
static SLIST_HEAD(packets_s, trace_packet_info_s) trace_packets;
static int trace_packets_num = 0;

/* hop information, by ttl */
struct hop_info_s
{
  int num_sent;
  int all_sent, all_rcvd;
  struct timeval ts_last_sent;
  struct timeval ts_last_recv;	
  unsigned short state;
  unsigned short flags;
  SLIST_HEAD(hop_packets_s, trace_packet_info_s) packets;
}
*hop_info;

/* As the trace progresses, each hope will attempt
   to work through the states one by one until it
   receives an answer (2 attempts per state).
   Whatever state "works" - will be then set up on 
   following hops to continue from.
*/
#define HS_SEND_FIN		0x00
#define HS_SEND_SYN		0x01
#define HS_SEND_SYN_FIN		0x02
#define HS_MAX			(HS_SEND_SYN)

#define HF_ENDPOINT		0x01


#if defined(BSD_IP_STACK) && !defined(OPENBSD)
#define SCREWED_IP_LEN
#endif

#ifndef SCREWED_IP_LEN
static u_int32_t
ip_cksum (const struct ip *ip)
{
  register const u_short *sp = (u_short *) ip;
  register u_int32_t sum = 0; 
  register int count;

  /*
   * No need for endian conversions.
   */
  for (count = ip->ip_hl * 2; --count >= 0;)
    sum += *sp++;
  while (sum > 0xffff)
    sum = (sum & 0xffff) + (sum >> 16);
  sum = ~sum & 0xffff;

  return (sum);
}
#endif

static int
lft_resolve_port (const char *strport)
{

  struct servent *se;

  if ((se = getservbyname (strport, "tcp")))
    return (ntohs (se->s_port));

  return atoi (strport);
}

static u_int32_t
tcp_cksum (struct ip *ip, struct tcphdr *tcp)
{
  u_int32_t sum = 0; 
  register int count;
  u_short *sp;
  int old_ttl;

  sp = (u_short *) tcp;
  for (count = sizeof (struct tcphdr) / 2; --count >= 0;)
    sum += *sp++;

  sp = (u_short *) & ip->ip_src;
  for (count = 2; --count >= 0;)
    sum += *sp++;

  sp = (u_short *) & ip->ip_dst;
  for (count = 2; --count >= 0;)
    sum += *sp++;

  old_ttl = ip->ip_ttl;
  ip->ip_ttl = 0;
  sp = (u_short *) & ip->ip_ttl;	/* protocol comes right after this */
  for (count = 1; --count >= 0;)
    sum += *sp++;
  ip->ip_ttl = old_ttl;

  sum += htons (sizeof (struct tcphdr));

  while (sum > 0xffff)
    sum = (sum & 0xffff) + (sum >> 16);
  sum = ~sum & 0xffff;

  return (sum);
}

void
do_auto_ports (char *hostname, int init_dport)
{
 /*
  *  Provides rudimentary auto-select of source and destination ports
  *  based on parsing the hostname supplied by the user
  *
  *  EXPECTS a string like "mail.example.com" and RETURNS the 
  *  auto-selected src and dst ports if changed or NULL if unchanged
  *
  *  currently operates on user's input only as a call to
  *  gethostbyaddr() before tracing could slow us down too much
  */

  if (strlen(hostname) > 5) {

    char *mailservers[] = { "mail", "smtp", "mx", "relay", "inbound" };
    int cnt = 0;
    hostname = (char *) tolower(hostname);

  for (cnt = 0 ; cnt < 5 ; cnt++)
   {
    if (strstr(hostname,mailservers[cnt]))
    {
      dport = 25;
      sport = 25;
      break;
    }
   }

   if (strncmp (hostname,"ftp",3) == 0) {
      dport = 21;
      sport = 19021;
    } else if (strncmp (hostname,"whois",5) == 0) {
      dport = 43;
      sport = 19043;
    } else if (strncmp (hostname,"imap",4) == 0) {
      dport = 143;
      sport = 19143;
    } else if (strncmp (hostname,"pop",3) == 0) {
      dport = 110;
      sport = 19110;
    } else if ((strncmp (hostname,"dns",3) == 0) || (strncmp (hostname,"ns",2) == 0)) {
      dport = 53;
      sport = 53;
    } else if ((strncmp (hostname,"ntp",3) == 0) || (strncmp (hostname,"clock",5) == 0)) {
      dport = 123;
      sport = 123;
    }

   if (noisy && (dport != init_dport)) 
	printf ("Autoconfigured to source tcp/%d, destination tcp/%d.\n",sport, dport);
  }
}

void
print_host (struct in_addr addr)
{
  struct hostent *h;

  if (!resolve_names) {
    printf ("%s", inet_ntoa (addr));
  } else {
    h = gethostbyaddr ((void *) &addr, 4, AF_INET);
    if (h) {
        printf ("%s", h->h_name);
        if (!hostnames_only) 
            printf(" (%s)", inet_ntoa (addr));
    } else
      printf ("%s", inet_ntoa (addr));
  }
}

unsigned int
get_address(char *host)
{
  struct hostent *h;
  struct in_addr *addr;

  h = gethostbyname (host);
  if (!h) {
    fprintf (stderr, "LFT: Unknown host: %s\n", host);
    exit (1);
  }
  addr = (struct in_addr *) h->h_addr;
  return addr->s_addr;
}

#ifdef __CYGWIN__
/*
The Windows/Cygwin version of this function uses the winsock built-in 
WSAIoctl SIO_ROUTING_INTERFACE_QUERY to find the appropriate interface.
*/
char *
lft_getifforremote(const char *remote)
{
  struct hostent *h;
	struct sockaddr_in in, out;
	unsigned long nBytesReturned;

	/* Only do this once of course */
	if (sock < 0) {
		if ((sock = socket (AF_INET, SOCK_DGRAM, 0)) < 0) {
			perror ("socket"); 
			return NULL;
		}
	}

	/* Ask what i/f  the packet should go out on */
	in.sin_family = AF_INET;
	in.sin_port = 0;
	in.sin_addr.s_addr = get_address((char *)remote);
	if (SOCKET_ERROR != WSAIoctl(sock, SIO_ROUTING_INTERFACE_QUERY, &in, sizeof(in), &out, sizeof(out), &nBytesReturned, NULL, NULL))
		return lft_getifname(out.sin_addr);

	/* not found */
	return NULL;
}
#else
/* 
The non-Windows version of this function uses connect() to 
acquire a socket to the target and uses the OS's decision 
as to what interface is appropriate. 
*/
char *
lft_getifforremote(const char *remote)
{
        int sd;
        struct sockaddr_in sock;
        uint32_t socklen = sizeof(struct sockaddr_in);
        uint16_t p1;

        /* TODO: fill with a better RANDOM */

        p1 = rand() % 33525 + 32525;

        if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
                {perror("LFT: Socket trouble; unable to determine interface"); return 0;}
        sock.sin_family = AF_INET;
        sock.sin_addr.s_addr = get_address((char *) remote);
        sock.sin_port = htons(p1);
        if (connect(sd, (struct sockaddr *) &sock, sizeof(struct sockaddr_in)) == -1)
        {
                perror("LFT: UDP connect(); unable to determine interface");
                close(sd);
                return NULL;
        }

        memset(&sock, 0, sizeof(sock));
        if (getsockname(sd, (struct sockaddr*) &sock, &socklen) == -1) {
                perror("getsockname");
                close(sd);
                return NULL;
        }

        close(sd);

        return lft_getifname(sock.sin_addr);
}
#endif

static void
init_address (char *remote, char *pcap_dev)
{

  struct hostent *h;

  local_address.s_addr = lft_getifaddr (pcap_dev);	

  if (noisy) {
    print_host (local_address);
    if (random_source) {
        printf (":%d (pseudo-random)\n", sport);
    } else 
        printf (":%d\n", sport);
  }

  h = gethostbyname (remote);
  if (!h) {
    fprintf (stderr, "LFT: Unknown host: %s\n", remote);
    exit (1);
  }
  remote_address = *(struct in_addr *) h->h_addr;
}

static void
open_sockets ()
{
#ifdef __CYGWIN__
  int optval = 1;
  DWORD dwBytesRet = 2048;
#endif
#ifdef IP_HDRINCL
  int on = 1;
#endif
  int i;
#if defined(sun) || defined(__CYGWIN__)
  struct sockaddr_in local_bind;
#endif

#if defined(sun)
  send_sock = socket (PF_INET, SOCK_RAW, IPPROTO_IP);
#elif defined(BSD_IP_STACK)
  send_sock = socket (PF_INET, SOCK_RAW, IPPROTO_TCP);
#elif defined(__CYGWIN__)
  send_sock = socket (PF_INET, SOCK_RAW, IPPROTO_RAW);
  recv_sock = socket (PF_INET, SOCK_RAW, IPPROTO_IP);
  
  if (recv_sock < 0) {
    perror ("LFT: raw socket");
    exit (1);
  }
  local_bind.sin_addr = local_address;
  local_bind.sin_port = 0;
  local_bind.sin_family = AF_INET;
  if (bind(recv_sock, (struct sockaddr *)&local_bind, sizeof(local_bind)) < 0) {
    perror("winsock bind");
  }
  /* apparently the cygwin include files don't define this: */
# define SIO_RCVALL 0x98000001
  if (WSAIoctl(recv_sock, SIO_RCVALL, &optval, sizeof(optval), NULL, 0, &dwBytesRet, NULL, NULL) < 0)
    perror("LFT: WSAIoctl");
#else
  send_sock = socket (PF_INET, SOCK_RAW, IPPROTO_RAW);
#endif
  if (send_sock < 0) {
    perror ("LFT: raw socket");
    exit (1);
  }
#ifdef IP_HDRINCL
  if (setsockopt (send_sock, IPPROTO_IP, IP_HDRINCL, (char *) &on,
		  sizeof (on)) < 0) {
    perror ("LFT: IP_HDRINCL");
    exit (1);
  }
#endif
#ifdef sun
  local_bind.sin_addr = local_address;
  local_bind.sin_port = 0;
  local_bind.sin_family = AF_INET;
  if (bind (send_sock, (struct sockaddr *)&local_bind, sizeof (local_bind)) < 0) {
    perror ("LFT: bind");
    exit (1);
  }
#endif

  /* set up initial ip headers, etc. */
  memset (&trace_packet, 0, sizeof (trace_packet));

  if (hostname_lsrr_size > 0) {
    for (i = 0; i < hostname_lsrr_size; i++) {
      trace_packet.lsrr.data[i] = get_address(hostname_lsrr[i]);
    }
    trace_packet.lsrr.ipl_code = IPOPT_LSRR;
    trace_packet.lsrr.ipl_len = hostname_lsrr_size * 4 + 3;
    trace_packet.lsrr.ipl_ptr = 4;
  }
  trace_packet.ip_hdr.ip_v = 4;
  if (hostname_lsrr_size > 0) {
    trace_packet.ip_hdr.ip_hl = 6 + hostname_lsrr_size; /* 5 + 3byte lsrr + addresses + padding */
    trace_packet.ip_hdr.ip_len = sizeof (struct ip) + sizeof(struct tcphdr) + trace_packet.lsrr.ipl_len + 1;
  } else {
    trace_packet.ip_hdr.ip_hl = 5;
    trace_packet.ip_hdr.ip_len = sizeof (struct ip) + sizeof(struct tcphdr);
  }

#ifdef SCREWED_IP_LEN
  /*  trace_packet.ip_hdr.ip_len = sizeof (struct ip) + sizeof(struct tcphdr); */
#else
  trace_packet.ip_hdr.ip_len = htons (trace_packet.ip_hdr.ip_len);
#endif
#ifndef IPDEFTTL
#define IPDEFTTL 64
#endif
  trace_packet.ip_hdr.ip_ttl = IPDEFTTL;
  trace_packet.ip_hdr.ip_p = IPPROTO_TCP;

  trace_packet.tcp_hdr.th_win = htons (win_len);
  trace_packet.tcp_hdr.th_off = sizeof (struct tcphdr) / 4;

  /* 
   * Init hop storage (array)
   * Init global packet info storage (SLIST)
   * Init per-hop packet info storage (SLIST)
   */
  hop_info_size = 255; /* can't be more then this */
  hop_info = malloc (sizeof (struct hop_info_s) * hop_info_size);
  for (i = 0; i < 255; i++) {
    bzero(&hop_info[i], sizeof(struct hop_info_s));
    hop_info[i].state = 0;
    SLIST_INIT(&(hop_info[i].packets));
  }

  SLIST_INIT(&trace_packets);
}

static unsigned int
new_seq()
{
  if (adaptive) {
    return rand();
  } else {
    return seq_start + trace_packets_num;
  }
}
	

static unsigned int
send_packet (short nhop, unsigned short ttl, unsigned int seq, unsigned char flags)
{
  struct sockaddr_in dest;
  unsigned int tseq;
  unsigned short tttl;
  char buf[sizeof(struct trace_packet_s) + 2], *bptr;
  int blen;

  struct trace_packet_info_s	*pinfo;
  struct trace_packet_s *packet;

  if (!(pinfo = malloc(sizeof(struct trace_packet_info_s)))) {
    perror("malloc");
    exit(1);
  }

  bzero(pinfo, sizeof(struct trace_packet_info_s));
  packet = &(pinfo->packet);
  memcpy(packet, &trace_packet, sizeof(struct trace_packet_s));

  /*
   * XXX change sequence generation method here
   */
  if (seq == 0)
    tseq = new_seq();
  else
    tseq = seq;

  if (nhop == -1)
    tttl = ttl;
  else
    tttl = nhop + 1;

  /* XXX DO NOT INSERT ANY CODE HERE THAT IS NOT DIRECTLY  *
   * RELATED TO PACKET GENERATION!!!!                      */

  num_sent++;

  ts_last_sent = now;

  packet->ip_hdr.ip_ttl = tttl;
  packet->ip_hdr.ip_src = local_address;
  packet->ip_hdr.ip_dst = remote_address;

  if (noisy) {
    printf("SENT TTL=%d SEQ=%u FLAGS=%#x ( ", nhop, tseq, flags);
    if (flags & TH_RST)
      printf ("RST ");
    if (flags & TH_ACK)
      printf ("ACK ");
    if (flags & TH_SYN)
      printf ("SYN ");
    if (flags & TH_FIN)
      printf ("FIN ");
    printf(")\n");
  }
  else {
  /*  if (!nostatus)
      printf(">"); */
  }

  packet->ip_hdr.ip_sum = 0;
#if !defined(SCREWED_IP_LEN)
  packet->ip_hdr.ip_sum = ip_cksum (&(packet->ip_hdr));
#endif

  packet->tcp_hdr.th_dport = htons (dport);
  /*
    trace_packet.tcp_hdr.th_seq = htonl (seq_start + trace_packet_info_length);
  */
  packet->tcp_hdr.th_seq = htonl (tseq);
  packet->tcp_hdr.th_sport = htons (sport);
  packet->tcp_hdr.th_flags = flags;

#if defined(SOLARIS_LENGTH_IN_CHECKSUM)
  packet->tcp_hdr.th_sum = htons (sizeof (struct tcphdr));
#else
  packet->tcp_hdr.th_sum = 0;
  packet->tcp_hdr.th_sum = tcp_cksum (&(packet->ip_hdr), &(packet->tcp_hdr));
#endif

  dest.sin_family = AF_INET;
  dest.sin_addr = remote_address;
  dest.sin_port = 0;

  bptr = buf;
  memcpy(bptr, &(packet->ip_hdr), sizeof(struct ip));
  bptr += sizeof(struct ip);
  if (packet->lsrr.ipl_len > 0) {
    memcpy(bptr, &(packet->lsrr), packet->lsrr.ipl_len + 1);
    bptr += (packet->lsrr.ipl_len + 1); /* PADDING !!! */
  }
  memcpy(bptr, &(packet->tcp_hdr), sizeof(struct tcphdr));
  blen = sizeof(struct ip) + packet->lsrr.ipl_len + sizeof(struct tcphdr);

  if (sendto (send_sock, buf, blen, 0, (struct sockaddr *)&dest, sizeof (dest)) < 0) {
    perror ("sendto");
    exit (1);
  }
 
  pinfo->hopno = nhop;
  pinfo->seq = tseq;
  pinfo->sent = now;
  SLIST_INSERT_HEAD(&trace_packets, pinfo, next);
  trace_packets_num++;

  if (nhop != -1) {
    SLIST_INSERT_HEAD(&hop_info[nhop].packets, pinfo, next_by_hop);
    hop_info[nhop].num_sent++;
    hop_info[nhop].all_sent++;
    hop_info[nhop].ts_last_sent = now;
  }

  return tseq;
}

static double
timediff_ms (struct timeval prior, struct timeval latter)
{
  return
    (latter.tv_usec - prior.tv_usec) / 1000. +
    (latter.tv_sec - prior.tv_sec) * 1000.;
}

static unsigned int
send_hop (short nhop)
{
  struct hop_info_s *h = &hop_info[nhop];

  if (!adaptive)
    return send_packet (nhop , 0, 0, tcp_flags);

  if (h->state == HS_SEND_FIN) {
    return send_packet(nhop, 0, 0, TH_FIN);
  }

  if (h->state == HS_SEND_SYN) {
    return send_packet(nhop, 0, 0, TH_SYN);
  }

  printf("Bad state %d for hop %d\n", h->state, nhop);
  return -1;
}

static int
hop_state_up (short nhop)
{
  struct hop_info_s *h = &hop_info[nhop];

  if (h->state == HS_MAX)
    return -1;

  h->state++;
  h->num_sent = 0; /* for this state that is */
  return 0;
}

static int
hop_state_copy(short nhop)
{
  int i;
	
  if (noisy > 2)
    printf("Upping states of the hops following %d\n", nhop);
  for (i = (nhop+1); i <= 255; i++)
    if (hop_info[i].state < hop_info[nhop].state) {
      hop_info[i].state = hop_info[nhop].state;
      hop_info[i].num_sent = 0;
    }

  return 0;
}

void
finish ()
{
  int hopno;
  int maxhop;
  int reply, noreply;
  int noreply_hop_first = 0;
  int as_for_hop = 0;
  struct trace_packet_info_s 	*tp;
  char *netname; 
  char ind;
  char *myApp = malloc(strlen(version) + 1 + strlen(appname));
  struct ip_list_array ipaslist;
     ipaslist.application = NULL;

  gettimeofday (&trace_done_time, NULL);

  if (noisy >= 3) printf ("Concluding with %d hops.\n", (num_hops+1));
  if (num_hops) {
    maxhop = num_hops;
    /* display all packets we received from this host */
    SLIST_FOREACH(tp, &trace_packets, next)
      if (tp->is_done)
	tp->hopno = maxhop;
  } else {
    maxhop = hop_info_length - 1;
  }

  if (num_hops && !nostatus && !noisy)
    printf ("T\n");
  else if (!noisy && !nostatus)
    printf ("\n");

  /* if user wants ASN resolution from pwhois or Cymru, do it in bulk */
  if (do_aslookup) {
   if (!use_radb) {
     /* populate bulk ip_addr_list structure */
   for (hopno = ttl_min; hopno <= maxhop; hopno++) {
       SLIST_FOREACH(tp, &(hop_info[hopno].packets), next_by_hop)  {
 	ipaslist.ipaddr[as_for_hop] = tp->hopaddr;
         break;
       }
       as_for_hop++;
       ipaslist.numItems = (as_for_hop);
   }
     if (use_cymru) {         /* use cymru bulk service */
         if (noisy > 1) printf ("Using Cymru for bulk AS resolution...\n");
         if (w_lookup_as_cymru_bulk(&ipaslist) != 0)
           if (noisy) printf ("The Cymru lookup failed.\n");
     } else if (use_ris) {    /* using RIPE NCC RIS */
          if (noisy > 1) printf ("Using RIPE NCC RIS for bulk AS resolution...\n");
           if (w_lookup_as_riswhois_bulk(&ipaslist) != 0)
           if (noisy) printf ("The RIPE NCC RIS lookup failed.\n");
     } else {                 /* use pwhois bulk service */
         if (noisy > 1) printf ("Using Prefix WhoIs for bulk AS resolution...\n");
         if (strlen(version) + 1 + strlen(appname) < 254) {
            strcat(myApp,appname); strcat(myApp," "); strcat(myApp,version);
            ipaslist.application = myApp;
         }
         if (w_lookup_as_pwhois_bulk(&ipaslist) != 0)
           if (noisy) printf ("The Prefix WhoIs lookup failed.\n");
     }  
   } else {
        if (noisy > 1) printf ("Using RADB for in-line AS resolution...\n");
     }
  }

  free(myApp);

  printf ("TTL LFT trace to ");

  print_host (remote_address);
  printf(":%d/tcp\n",dport);

  noreply = 0;
  reply = 0;
  as_for_hop = 0;            /* this correlates the hopno to the asn stored in ipaslist */

  
  for (hopno = ttl_min; hopno <= maxhop; hopno++) {
    struct in_addr last_hop;

    if (hop_info[hopno].all_rcvd != 0) {
      if (noreply == 1)
	printf("**  [neglected] no reply packets received from TTL %d\n", hopno);
      if (noreply > 1)
	printf("**  [neglected] no reply packets received from TTLs %d through %d\n", hopno - noreply + 1, hopno);

      noreply_hop_first = 0;
    }

    last_hop.s_addr = 0;
    if ((hop_info[hopno].state == HS_SEND_FIN) && (hop_info[hopno+1].state == HS_SEND_SYN)) {
      printf("**  [firewall] the next gateway may statefully inspect packets\n");
    }

    if ((hop_info[hopno].flags & HF_ENDPOINT) && (noreply >= ((maxhop - ttl_min)/2)) && num_hops > 3) {
      printf("**  [4.2-3 BSD bug?] the next gateway may errantly reply with reused TTLs\n");
    }


    if (hop_info[hopno].all_rcvd == 0) {
      reply = 0;
    } else {

      printf ("%2d ", hopno + 1);
      ind = ' ';

      SLIST_FOREACH(tp, &(hop_info[hopno].packets), next_by_hop) {
	
	if (tp->recv.tv_sec) {
	  reply = 1;
	
	  if (tp->icmp_type < -2 || tp->icmp_type > 17)
	    printf (" [icmp code %d]", tp->icmp_type);
	  else if (tp->icmp_type >= 0)
	    printf (" [%s]", icmp_messages[tp->icmp_type + 1]);
	
	  if (last_hop.s_addr != tp->hopaddr.s_addr) {
	    ind = ' ';
	    if (do_aslookup) {
              int asnumber = 0; 	/* init/clear the ASN */
	      if (use_radb) { 
                  /* using RADB/IRR */
		  asnumber = w_lookup_as(inet_ntoa(tp->hopaddr));
                  if (asnumber)
                    printf(" [%d]", asnumber);
                  else
                    printf(" [AS?]");
                } else if (use_ris) {
                  /* using RIPE NCC RIS */
                  /* asnumber = w_lookup_as_riswhois(inet_ntoa(tp->hopaddr)); */
                  if ((asnumber = ipaslist.asn[as_for_hop]) > 0) 
                  /* if (asnumber) */
                    printf(" [%d]", asnumber);
                  else
                    printf(" [AS?]");
		} else if (use_cymru) {
                  /* using cymru 
		  asnumber = w_lookup_as_cymru(inet_ntoa(tp->hopaddr));  */
                  if ((asnumber = ipaslist.asn[as_for_hop]) > 0)
                    printf(" [%d]", asnumber);
                  else
                    printf(" [AS?]");
		} else {
		  /* using pwhois by default 
                  asnumber = w_lookup_as_pwhois(inet_ntoa(tp->hopaddr));  */
                  if ((asnumber = ipaslist.asn[as_for_hop]) > 0 )
                    printf(" [%d]", asnumber);
                  else
                    printf(" [AS?]");
                }
	    }
			
	    if (do_netlookup) {
	      netname = w_lookup_netname(inet_ntoa(tp->hopaddr));
	      if (netname)
		printf(" [%s]", netname);
	      else
		printf(" [unknown]");
	    }

	    if (tp->icmp_type == -1) {
	      printf(" [target]");
	    }

	    printf(" ");
	    print_host (tp->hopaddr);
	    if (tp->icmp_type == -1) {
	      printf(":%d",dport);
	    }
	  }
	
	  last_hop = tp->hopaddr;
	  printf ("%c%.1f", ind, timediff_ms(tp->sent, tp->recv));
	} else {
	  printf ("%c*", ind);
	}
	ind = '/';
      }
      printf ("ms\n");
    }
    if (reply)
      noreply = 0;
    else
      noreply++;
    reply = 0;
    as_for_hop++;
  }

  if (!num_hops) 
    printf("**  [%d/tcp failed]  Try alternate options or use -V to see packets.\n", dport);
  if (timetrace) {
    gettimeofday (&now, NULL);
    printf ("\nLFT spent %.2fs tracing", 
	    (timediff_ms(begin_time, trace_done_time) / 1000));
    if (resolve_names || do_aslookup || do_netlookup) 
      printf(" and %.2fs resolving names and ASNs", (timediff_ms(trace_done_time, now) / 1000));

    printf(".\n");
  }
  exit (0);
} 

void
check_timeouts ()
{
  int nhop;
  int need_reply = 0;
  int no_reply = 0;
  int last_return = 0;
  unsigned int tseq;

  tseq = 0;

  gettimeofday (&now, NULL);
  if (timediff_ms (ts_last_sent, now) < scatter_ms)
    return;			/* not ready to send another packet yet */

  for (nhop = ttl_min; nhop < hop_info_length; nhop++) {
    if (!hop_info[nhop].num_sent) {
      send_hop(nhop);
      return;
    }
  }

  for (nhop = ttl_min; nhop < hop_info_length; nhop++) {
    if (hop_info[nhop].num_sent <= retry_max && !hop_info[nhop].ts_last_recv.tv_sec) {
      if (noisy >= 3) printf("No reply on TTL %d; ", nhop);
      if (timediff_ms (hop_info[nhop].ts_last_sent, now) >= timeout_ms) {
	/* we timed out waiting for this hop -- retry if we have any
	 * more tries */
	if (hop_info[nhop].num_sent < retry_max) {
	  if (noisy >= 2) printf("TTL %d timed out, RESENDING\n",nhop);
	  send_hop(nhop);
	  return;
	} else {
	  if (!adaptive || hop_state_up(nhop)) {
	    if (noisy >= 2) printf("TTL %d timed out, NO REPLY\n",nhop);
	    no_reply++;
	  }
	}
      } else {
	need_reply++;		/* we have to wait for this one to timeout */
      }
    } else { /* have reply */
      last_return = nhop;
    }
  }

  if (noisy >= 3) {
    printf ("hilength %d, last_return %d\n", hop_info_length, last_return);
    printf ("no_reply %d, ahead_limit %d\n", no_reply, ahead_limit);
    printf ("num_hops %d, need_reply %d\n", num_hops, need_reply);
  }
  if (no_reply >= ahead_limit) {	/* we timed out. */
    if ((last_return + 3) * 2 < hop_info_length) {
      if ((need_reply < 3) && (num_rcvd < 2)) printf("\n\nLFT can\'t reliably round-trip.  Close-proximity filter in the way?\n");
      finish ();
    }
  }

  if ((!num_hops || hop_info_length < num_hops || need_reply) && hop_info_length < ttl_limit) { 
    if (noisy >= 3) printf("I still have unanswered hops.\n");
    if (need_reply >= ahead_limit) {
      if (noisy >= 3) printf("I\'m too far ahead, returning.\n");
      return;			/* wait for some replies before we go on */
    }

    if (num_hops > 0 && hop_info_length >= num_hops) {
      if (noisy >= 3) printf("I know the distance to the target, but I have gaps to fill.  Returning...\n");
      return;			/* we know how long the path is --
				 * wait to fill in the blanks */
    }

    nhop = hop_info_length++;
    send_hop(nhop);
  } else { 
    if (noisy >= 3) printf("Everyone either responded or timed out.  ");
    for (nhop = ttl_min; nhop < hop_info_length; nhop++) {
      if (hop_info[nhop].num_sent < retry_min && hop_info[nhop].num_sent <= retry_max /*&& hop_info[nhop].ts_last_recv.tv_sec*/) {
	send_hop(nhop);
	return;
      }
    }

    finish ();
  } 
}

void
recv_packet (unsigned int seq, struct in_addr ipaddr, int icmp_type)
{
  double ms;
  struct trace_packet_info_s *tp = NULL;

  gettimeofday (&now, NULL);

  SLIST_FOREACH(tp, &trace_packets, next) {
    if (tp->seq == seq)
      break;
  }

  if (!tp) {
    if (noisy)
      printf("Packet not meant for us?\n");
    else
      if (!nostatus) printf("?");
	
    return;
  }

  if (tp->recv.tv_sec) {
    if (noisy)
      printf ("Duplicate packet?\n");
    else
      if (!nostatus) printf("!");
    return;
  }

  if (noisy) {
    printf ("REF=%u SRC=%s\n", seq, inet_ntoa (ipaddr));
  } else {
    if (!nostatus) printf(".");
  }

  /* increment received packet counter */
  num_rcvd++;

  tp->recv = now;
  if (tp->hopno != -1) {
    hop_info[tp->hopno].ts_last_recv = now;
    hop_info[tp->hopno].all_rcvd++;
    hop_state_copy(tp->hopno);

    if (icmp_type == -1)
      hop_info[tp->hopno].flags |= HF_ENDPOINT;
  }

  tp->hopaddr = ipaddr;
  tp->icmp_type = icmp_type;
  if (icmp_type != -2 && (!num_hops || num_hops > tp->hopno))
    if (break_on_icmp || (icmp_type == -1)) {
      if (tp->hopno != -1) { /* we set fake type -1 when we get actual
			      * tcp packet in return - meaning destination */
      	num_hops = tp->hopno;
      	tp->is_done = 1;
       	if (noisy >= 2) printf ("Looks like we made it.  LFT received a response from the target.\n");
      }
    }

  /* adjust scatter if we have fast reply times */
  ms = timediff_ms (tp->sent, tp->recv);
  scatter_ms = (scatter_ms * (ahead_limit - 1) + ms) / ahead_limit;

}

void process_packet (const u_char *packet)
{
  const struct ip *ip, *orig_ip;
  const struct tcphdr *tcp;
  const struct icmp *icmp;

  if (noisy >= 5) printf("Received new data from packet capture; processing.\n");
  check_timeouts ();

  packet += skip_header_len;
  ip = (void *) packet;

  packet += 4 * ip->ip_hl;
  switch (ip->ip_p) {
  case IPPROTO_ICMP:
    orig_ip = ip;
    icmp = (void *) packet;
    if (icmp->icmp_type != ICMP_UNREACH && icmp->icmp_type != ICMP_TIMXCEED)
      return;
    ip = &icmp->icmp_ip;
    if (ip->ip_p != IPPROTO_TCP)
      return;			/* not a response to our tcp probe */
    packet = (void *) ip;
    packet += 4 * ip->ip_hl;
    tcp = (void *) packet;
    if (ntohs (tcp->th_dport) != dport || ip->ip_src.s_addr != local_address.s_addr || ip->ip_dst.s_addr != remote_address.s_addr)
      return;			/* not for us */
    /*if (ntohl(tcp->th_seq) < seq_start || ntohl(tcp->th_seq) > seq_start + trace_packet_info_length)
      	return; * not for us */


    if (noisy) 
      printf ("RCVD ICMP SEQ=%u ", ntohl (tcp->th_seq));
    recv_packet (ntohl (tcp->th_seq) , orig_ip->ip_src,
		 (icmp->icmp_type == ICMP_TIMXCEED) ? -2 : icmp->icmp_code);
    break;

  case IPPROTO_TCP:
    /* check for RST reply */
    tcp = (void *) packet;
    if (!(tcp->th_flags & TH_RST) && !(tcp->th_flags & TH_ACK) && !(tcp->th_flags & TH_SYN))
      return;			/* not what we're looking rfor */

    if (ntohs (tcp->th_sport) != dport || ip->ip_src.s_addr != remote_address.s_addr || ip->ip_dst.s_addr != local_address.s_addr) {
      return;			/* not the right connection */
    }

    if (noisy) {
      printf("RCVD TCP FLAGS=%#x ( ",tcp->th_flags);

      if (tcp->th_flags & TH_RST)
        printf ("RST ");
      if (tcp->th_flags & TH_ACK)
        printf ("ACK ");
      if (tcp->th_flags & TH_SYN)
        printf ("SYN ");
      if (tcp->th_flags & TH_FIN)
        printf ("FIN ");

      printf (") SEQ=%lu ACK=%lu ", ntohl (tcp->th_seq), ntohl (tcp->th_ack));
    }

    /*if (ntohl(tcp->th_ack) < seq_start || ntohl(tcp->th_ack) > seq_start + trace_packet_info_length + 1)
    	return; * not for us */
    recv_packet (ntohl (tcp->th_ack) - 1, ip->ip_src, -1);
    /*
      send_packet(-1, IPDEFTTL, ntohl(tcp->th_ack) + 1, TH_RST);
    */
    return;
  }
}

#ifndef __CYGWIN__
void
pcap_process_packet (u_char * user_data, const struct pcap_pkthdr *hdr,
		     const u_char * packet)
{
  process_packet(packet);
}
#endif

static void
usage (char *prog)
{
  fprintf (stderr,
	   "\nLayer Four Traceroute (LFT)\n\n    - the alternative traceroute tool for network (reverse) engineers\n\nUsage: %s [<options>] [<gateway> <...>] <target:destport>\n"
	   "\nOptions are:\n"
	   "  -d <dport>       destination port number\n"
	   "  -s <sport>       source port number\n"
	   "  -m <min>         minimum number of probes to send per host\n"
	   "  -M <max>         maximum number of probes to send per host\n"
	   "  -a <ahead>       number of hops forward to query before receiving replies\n"
	   "  -c <scatter ms>  minimum number of milliseconds between subsequent queries\n"
	   "  -t <timeout ms>  maximum RTT before assuming packet was dropped\n"
	   "  -l <min ttl>     minimum TTL to use on outgoing packets\n"
	   "  -q <sequence>    set the initial sequence number (ISN)\n"
           "  -D <device|ip>   network device name or IP address (e.g., \"en1\" or \"1.2.3.4\")\n"
           "  -H <ttl>         maximum number of hops to traverse (max TTL of packets)\n"
           "  -z               use pseudo-random source port number\n"
           "  -i               disable \"stop on ICMP\" other than TTL expired\n"
           "  -n               display hosts numerically; disable use of the DNS resolver\n"
           "  -h               display hosts symbolically; suppress IP address display\n"
           "  -N               enable lookup of network names (whois)\n"
           "  -A               enable lookup of AS numbers using Prefix WhoIs\n"
           "  -r               use RIPE NCC RIS to lookup ASNs instead of Prefix WhoIs\n"
           "  -R               use RADB to lookup ASNs instead of Prefix WhoIs\n"
           "  -C               use Cymru to lookup ASNs instead of Prefix WhoIs\n"
           "  -T               enable display of LFT's execution timer\n"
           "  -S               suppress the status bar (only show the completed trace)\n"
           "  -F               enable use of FIN packets only (defaults are SYN)\n"
           "  -E/-e            enable LFT's stateful Engine to detect firewalls\n"
           "  -V               print debug information; more V\'s = more verbose.\n"
	   "  -v               show version information and exit\n"  "\n"
	   "Default is: %s -d %d -m %d -M %d -a %d -c %.0f -t %d -H %d -s %d\n\n",
	   prog, prog, dport, retry_min, retry_max, ahead_limit,
	   scatter_ms, timeout_ms, ttl_limit, sport);
  exit (1);
}

static void
show_version (void)
{
  fprintf (stderr, "\n"
           "Layer Four Traceroute (LFT) - version %s %s\n\n    - the alternative traceroute tool for network (reverse) engineers\n\n"
	   "    Compile-time options:\n\n"
#if defined(DARWIN)
           "      + Darwin (or MacOS)\n"
#endif
#if defined(OPENBSD)
           "      + OpenBSD\n"
#endif
#if defined(BSD_IP_STACK)
	   "      + BSD IP stack\n"
#endif
#if defined(BSD)
	   "      + BSD platform\n"
#endif
#if defined(linux)
	   "      + Linux platform\n"
#endif
#if defined(sun)
	   "      + SUN platform\n"
#endif
#if !defined(sun) && !defined(linux) && !defined(BSD_IP_STACK) && !defined(OPENBSD)
	   "      (unknown architecture)\n"
#endif
#if defined(SCREWED_IP_LEN)
	   "      + IP length big-endian\n"
#else
	   "      + IP length little-endian\n"
#endif
#if defined(IP_HDRINCL)
	   "      + Full IP headers for raw sockets\n"
#else
	   "      + Without IP header inclusion\n"
#endif
           "      + " HOST_SYSTEM_TYPE "\n"
	   "\n", version, version_date);
  exit (0);
}

#ifdef __CYGWIN__
void cygwin_process()
{
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(recv_sock, &fds);
  struct timeval tm;
  tm.tv_sec = 0;
  tm.tv_usec = 100000;
  if (select(recv_sock+1, &fds, 0, 0, &tm) < 0) {
    perror("select");
    exit(1);
  }
  if (FD_ISSET(recv_sock, &fds)) {
    /* read packet */
    char packetbuf[2048];
    memset(packetbuf, 0, sizeof(packetbuf));
    int nread = recv(recv_sock, packetbuf, sizeof(packetbuf), 0);
    if (nread <= 0) {
      perror("read");
      exit(1);
    }
    process_packet(packetbuf);
  }
}

#endif

extern int
main (int argc, char **argv)
{
#ifndef __CYGWIN__
  char ebuf[PCAP_ERRBUF_SIZE];
  static pcap_t *pd;
#endif
  char *pcap_dev, *userdev = NULL;
  int ch;
  int use_fins = 0;
  char *cp;
  struct timeval tb;
  unsigned int bpfimmflag;

  setbuf (stdout, NULL);

  while ((ch = getopt (argc, argv, "Aa:Cc:D:d:EeFH:hiM:l:m:Nnp:q:RrSs:Tt:Vvw:z")) != EOF)
    switch (ch) {
    case 'F':
      if (adaptive) {
	fprintf (stderr,
		 "LFT warning: TCP flags are selected automatically using (-E) option.\n             Ignoring FINs-only (-F) option and using adaptive Engine.\n\n");
	break;
      } 
      tcp_flags = TH_FIN;
      use_fins = 1;
      dport = 25000;
      auto_ports = 0;
      break;
    case 'h':
      if (!resolve_names) {
              fprintf (stderr,
                 "LFT warning: I can't display hostnames (-h) unless I resolve them.\n             Ignoring your request to display hostnames exclusively.\n\n");
      } else hostnames_only = 1;
      break;
    case 'r':
      if (use_cymru) {
        fprintf (stderr,
                 "LFT warning: Only one ASN lookup source may be used--you selected Cymru.\n             Ignoring your request to use RIPE NCC RIS.\n\n");
        break;
      } else if (use_radb) {
        fprintf (stderr,
                 "LFT warning: Only one ASN lookup source may be used--you selected RADB.\n             Ignoring your request to use RIPE NCC RIS.\n\n");
        break;
      }
      use_radb = 0;
      use_ris = 1;
      use_cymru = 0;
      do_aslookup = 1;
      break;
    case 'R':
      if (use_cymru) {
        fprintf (stderr,
                 "LFT warning: Only one ASN lookup source may be used--you selected Cymru.\n             Ignoring your request to use RADB.\n\n");
        break;
      } else if (use_ris) {
        fprintf (stderr,
                 "LFT warning: Only one ASN lookup source may be used--you selected RIPE NCC RIS.\n             Ignoring your request to use RADB.\n\n");
        break;
      }

      use_radb = 1;
      use_cymru = 0;
      use_ris = 0;
      do_aslookup = 1;
      break;
    case 'C':
      if (use_radb) {
        fprintf (stderr,
                 "LFT warning: Only one ASN lookup source may be used--you selected RADB.\n             Ignoring your request to use Cymru.\n\n");
        break;
      } else if (use_ris) {
        fprintf (stderr,
                 "LFT warning: Only one ASN lookup source may be used--you selected RIPE NCC RIS.\n             Ignoring your request to use Cymru.\n\n");
        break;
      }
      use_cymru = 1;
      use_radb = 0;
      use_ris = 0;
      do_aslookup = 1;
      break;
    case 'd':
      ++dflag;
      dport = atoi (optarg);
      auto_ports = 0;
      break;
    case 'q':
      seq_start = atol (optarg);
      break;
    case 'w':
      win_len = atoi(optarg);
      break;
    case 'm':
      retry_min = atoi (optarg);
      break;
    case 'M':
      retry_max = atoi (optarg);
      break;
    case 'N':
      do_netlookup = 1;
      break;
    case 'A':
      do_aslookup = 1;
      break;
    case 'n':
      if (!hostnames_only) {
	      resolve_names = 0; 
      } else {
              fprintf (stderr,
                 "LFT warning: I can't display hostnames (-h) unless I resolve them.\n             Ignoring your request not to resolve DNS.\n\n");
      }
      break;
    case 'T':
      timetrace = 1;
      break;
    case 's':
      if (random_source) {
        fprintf (stderr,
                 "LFT warning: You already asked to use a random source port.\n             Ignoring request to set specific source port.\n\n");
        break; 
      }
      sport = lft_resolve_port (optarg);
      break;
    case 'E':
      if (use_fins) {
	fprintf (stderr,
		 "LFT warning: TCP flags are selected automatically using (-E) option.\n             Ignoring adaptive Engine (-E) option and using FINs-only (-F).\n\n");
	break;
      }
      adaptive = 1;
      break;
    case 'e':
      if (use_fins) {
        fprintf (stderr,
                 "LFT warning: TCP flags are selected automatically using (-e) option.\n             Ignoring adaptive Engine (-e) option and using FINs-only (-F).\n\n");
        break;
      }
      adaptive = 1;
      break;
    case 'S':
      nostatus = 1;
      break;
    case 'D':
      {
	if (strlen (optarg) > max_net_dev_input) {
	  fprintf (stderr,
		   "Net interface names are limited to %d characters. (e.g., \"eth0\" or \"ppp0\" or \"10.10.10.10\")\n",
		   max_net_dev_input);
	  exit (1);
	}
	userdevsel = 1;
	userdev = optarg;
      }
      break;
    case 'a':
      ahead_limit = atoi (optarg);
      break;
    case 'c':
      scatter_ms = atoi (optarg);
      if (scatter_ms < 1)
	scatter_ms = 1;
      if (scatter_ms > 100)
	scatter_ms = 100;
      break;
    case 't':
      timeout_ms = atoi (optarg);
      break;
    case 'H':
      if (atoi (optarg) > 255) 
	ttl_limit = 255; else
	ttl_limit = atoi (optarg);
      break;
    case 'l':
      ttl_min = atoi(optarg);
      hop_info_length = ttl_min;
      if (ttl_min > 0)
	ttl_min--;
      break;
    case 'i':
      break_on_icmp = 0;
      break;
    case 'v':
      show_version ();
      break;
    case 'V':
      noisy++;
      nostatus = 1; 
      break;
    case 'z':
      random_source = 1;
      sport = rand()%32525+32525;
      break;
    default:
      usage (argv[0]);
    }

  if ((argc - optind) < 1)
    usage (argv[0]);


  if (noisy)
      printf ("Layer Four Traceroute (LFT) version %s", version);
  if (noisy > 1) 
      printf (" ... (verbosity level %d)",noisy);
  if (noisy)    
      printf ("\n");

  gettimeofday (&tb, NULL);
  /* eventually this might want to use /dev/urandom or
   * something on machines that have it.  otherwise,
   * this does a fairly decent job of using the system
   * clock.
   *
   * multiply tv_usec (range 0-1000000) to be in range 0-2^31,
   * and xor to randomize the high bits of tv_sec that don't
   * change very much.
   */
  srand(tb.tv_sec ^ (tb.tv_usec * 2147));

  hostname = argv[optind++];
  hostname_lsrr_size = 0;
  while (optind < argc) {
    hostname_lsrr[hostname_lsrr_size++] = argv[optind++];
    if (hostname_lsrr_size > IP_LSRR_DEST) {
      fprintf(stderr, "Too many LSRR hosts - maximum is 8\n");
      exit(1);
    }
  }
  if (hostname_lsrr_size > 0) {
    hostname_lsrr[hostname_lsrr_size++] = hostname;
    hostname = hostname_lsrr[0];
  }

  /* allow hostname:port if -d not specified */
  if ((cp = strchr (hostname, ':'))) {
    if (!dflag) {
      *cp++ = '\0';
      dport = lft_resolve_port (cp);
      auto_ports = 0;
    }
  }

if (auto_ports) 
	do_auto_ports(hostname, dport);

  if (do_netlookup || do_aslookup)
    w_init();                                                   /* initialize the whois framework */

#ifdef __CYGWIN__
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 1), &wsaData) != 0) {
    perror("WSAStartup");
    exit(1);
  }
#endif

  /* if not given network interface, select one automatically */
  if (!userdevsel) {
    pcap_dev = lft_getifforremote(hostname);
#ifndef __CYGWIN__
    if (pcap_dev == NULL) 
      pcap_dev = pcap_lookupdev (ebuf);
    if (pcap_dev == NULL) {
      fprintf (stderr, "LFT: %s\n", ebuf);
      exit (1);
    }
#else 
    if (pcap_dev == NULL) {
      fprintf (stderr, "LFT: Failed to discover an appropriate interface.\n");
      exit (1);
    }
#endif
  } else {
    struct in_addr addr;
    if (inet_aton(userdev, &addr)) {
      /* specified by ip address -- look up device. */
      pcap_dev = lft_getifname(addr);
      if (!pcap_dev) {
	fprintf (stderr, "LFT: Could not find an interface with IP address %s\n", userdev);
	exit(1);
      }
    } else
      pcap_dev = userdev;
  };

#ifdef __CYGWIN__
  skip_header_len = 0;
#else
  /* now, fix pcap's linux implementation */
  if (!strncmp (pcap_dev, "lo:", 3) || !strcmp (pcap_dev, "lo")) {
    pcap_dev = "ppp0";
    skip_header_len = 0;
  } else if (!strncmp (pcap_dev, "ppp", 3))
    skip_header_len = 0;
  else				/* assume ethernet */
    skip_header_len = sizeof (struct ether_header);
#endif
  if (noisy)
    printf ("Using device %s, ", pcap_dev);
#ifndef __CYGWIN__
  pd = pcap_open_live (pcap_dev, 1600, 0, 20, ebuf);
  if (!pd) {
    fprintf (stderr, "\nSorry, that interface isn\'t available to LFT.  Try another or fix:\nERROR: %s\n", ebuf);
    exit (1);
  }
#ifdef BSD_IP_STACK
#ifndef DARWIN
  bpfimmflag = 1;
  if ( ioctl(pd->fd, BIOCIMMEDIATE, &bpfimmflag) < 0) {
    fprintf(stderr, "BIOCIMMEDIATE: %s",
    pcap_strerror(errno));
  }
#endif
#endif
#endif

  init_address (hostname, pcap_dev);

  if (!seq_start) {
     seq_start = rand();
     if (noisy > 1) printf("Setting my ISN = %d\n", seq_start);
  }

  open_sockets ();

#ifndef __CYGWIN__
  setuid (getuid ());
#endif

  if (adaptive) {
    if (retry_min < 2)
      retry_min = 2;
    if (retry_max < retry_min)
      retry_max = retry_min;
  }

  gettimeofday (&begin_time, NULL);
  if (!nostatus && !noisy)
    printf("Tracing ");

#ifdef __CYGWIN__
  for (;;) {
    cygwin_process();
    check_timeouts();
  }
#else
  while (pcap_dispatch (pd, -1, pcap_process_packet, 0) >= 0) {
    if (noisy >= 3) printf("OUTSIDE dispatch \n");
    check_timeouts ();
  }
#endif

  return 0;
}

