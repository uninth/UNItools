/* David Leonard, 2002. Public domain. */
/* $Id$ */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#if STDC_HEADERS
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#endif
#if HAVE_NETDB_H
# include <netdb.h>
#endif
#if HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#if HAVE_SYS_TIME_H
# include <sys/time.h>
#endif
#if defined(__linux__) || defined(__GLIBC__)
# define __FAVOR_BSD
#endif
#if HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
#if HAVE_NETINET_IN_SYSTM_H
# include <netinet/in_systm.h>
#endif
#if HAVE_NETINET_IP_H
# include <netinet/ip.h>
#endif
#if HAVE_NETINET_IP6_H
# include <netinet/ip6.h>
#endif
#if HAVE_NETINET_TCP_H
# include <netinet/tcp.h>
#endif
#if HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif

#include "compat.h"
#include "tag.h"
#include "hash.h"
#include "flow.h"
#include "main.h"
#include "tcp.h"
#include "display.h"

static void link_ftp_eport(const char *, const char *, const char *, 
	const struct in_addr *, const struct in6_addr *);
static void link_ftp_port(const char *, const char *, const char *);

/* a hack to remember recent FTP port commands */
static struct {
    char ctltag[TAGLEN];
    char datatag[DESCLEN];
    struct in_addr addr;
#if HAVE_NETINET_IP6_H
    struct in6_addr addr6;
#endif
    u_int16_t port;
} ftp;

static int
tcp_cmp(a, b)
	const void *a;
	const void *b;
{
	const u_int16_t*ia = (const u_int16_t*)a;
	const u_int16_t*ib = (const u_int16_t*)b;

	return *ia - *ib;
}

static unsigned int
tcp_hash(a)
	const void *a;
{
	const u_int16_t*ia = (const u_int16_t*)a;

	return *ia;
}

static struct hash tcp_hashtab = { 
	tcp_cmp,		/* cmp */
	tcp_hash,		/* hashfn */
	(free_t)free,		/* freekey */
	(free_t)free 		/* freedata */
};

void
tcp_reset()
{
	hash_clear(&tcp_hashtab);
}

/* Look up a TCP port's symbolic name */
const char *
tcp_lookup(port)
	u_int16_t port;
{
	const char *result;
	static int oldnflag = -1;

	if (oldnflag != nflag) {
		tcp_reset();
		oldnflag = nflag;
	}

	result = (const char *)hash_lookup(&tcp_hashtab, &port);
	if (result == NULL) {
		struct servent *se;
		u_int16_t *a2;
		char buf[TAGLEN];

		if (nflag)
			se = NULL;
		else if (port > IPPORT_USERRESERVED)
			se = NULL;
		else {
#if HAVE_GETSERVBYPORT
			display_message("resolving tcp port %u", port);
			se = getservbyport(htons(port), "tcp");
			display_message("");
#else
			se = NULL;
#endif
		}
		if (se == NULL) {
			snprintf(buf, sizeof buf, "%u", port);
			result = buf;
		} else
			result = se->s_name;
		result = strdup(result);
		a2 = (u_int16_t *)malloc(sizeof (u_int16_t));
		if (a2 == NULL)
			errx(1, "malloc");
		*a2 = port;
		hash_store(&tcp_hashtab, a2, result);
	}
	return result;
}

const char *
tcp_tag(p, end, ip, ip6)
	const char *p;
	const char *end;
	const struct ip *ip;
	const struct ip6_hdr *ip6;
{
	static char src[TAGLEN], dst[TAGLEN];
	static char tag[TAGLEN];
	struct tcphdr *tcp = (struct tcphdr *)p;
	struct flow *f = NULL;
	u_int16_t sport, dport;
	const char *data, *d;
	int direction;

	sport = ntohs(tcp->th_sport);	/* Same for both tcp and tcp6 */
	dport = ntohs(tcp->th_dport);
	if (ip) {
		snprintf(src, sizeof src, "%s:%s", 
			ip_lookup(&ip->ip_src), tcp_lookup(sport));
		snprintf(dst, sizeof dst, "%s:%s", 
			ip_lookup(&ip->ip_dst), tcp_lookup(dport));
		snprintf(tag, sizeof tag, "tcp %s", tag_combine(src, dst));
	}
#if HAVE_NETINET_IP6_H
	if (ip6) {
		snprintf(src, sizeof src, "%s,%s", 
			ip6_lookup(&ip6->ip6_src), tcp_lookup(sport));
		snprintf(dst, sizeof src, "%s,%s", 
			ip6_lookup(&ip6->ip6_dst), tcp_lookup(dport));
		snprintf(tag, sizeof tag, "tcp6 %s", tag_combine(src, dst));
	}
#endif

	direction = (strcmp(src, dst) > 0 ? 0 : 1);

	f = findflow(tag);

	/* mark some flows as long-lived so we can preserve desc state */
	if ((tcp->th_flags & (TH_SYN|TH_FIN|TH_RST)) != 0) {
		if ((tcp->th_flags & TH_SYN) != 0) {
			f->dontdel = 1;
			f->seq[direction] = (ntohl(tcp->th_seq) + 1) 
						& 0xffffffffUL;
		}
		if ((tcp->th_flags & (TH_FIN|TH_RST)) != 0) {
			f->dontdel = 0;	/* can reclaim now */
			/* f->desc[0] = '\0'; */ /* keep the url around */
		}
	}

	/* Keep track of the sequence numbers, ignoring dups */
	if (ntohl(tcp->th_seq) != f->seq[direction])
		return tag;
	data = p + (tcp->th_off << 2);
	f->seq[direction] = (f->seq[direction] + (end - data))
				& 0xffffffffUL;

	switch (dport) {
	case 25:
		tcp_smtp(f, data, end, 1);
		break;
	case 80:
	case 8080:
	case 3127:
	case 3128:
		tcp_http(f, data, end, 1);
		break;
#if 0 /* tcp_sup is too unstable! */
	case 871:
		tcp_sup(f, data, end, 1);
		break;
#endif
	case 6000:
	case 6001:
	case 6002:
	case 6003:
	case 6010:
		/* X11 protocol */
		tcp_x11(f, data, end);
		break;
	}

	switch (sport) {
	case 80:
	case 8080:
	case 3127:
	case 3128:
		tcp_http(f, data, end, 0);
		break;
#if 0 /* tcp_sup is too unstable! */
	case 871:
		tcp_sup(f, data, end, 0);
		break;
#endif
	}

	/* 
	 * XXX FTP - RFC2428
	 *
	 * FTP is handled here because we want to associate the
	 * control stream with the data stream at the TCP layer.
	 */
	if (dport == 21) {
		if (memcmp(data, "RETR ", 5) == 0 ||
		    memcmp(data, "STOR ", 5) == 0 ||
		    memcmp(data, "NLST ", 5) == 0 ||
		    memcmp(data, "ABOR ", 5) == 0 ||
		    memcmp(data, "LIST ", 5) == 0)
		{
			for (d = data; d < end && *d != '\r' && *d != '\n'; d++)
				;
			snprintf(f->desc, sizeof f->desc, "%.*s",
				 (int)(d - data), data);
			/* Copy the desc to the data flow if it is known */
			if (ftp.datatag[0] != '\0'  &&
			    strcmp(ftp.ctltag, tag) == 0)
			{
			    struct flow *f2 = findflow(ftp.datatag);
			    snprintf(f2->desc, sizeof f2->desc,
				"ftp-data: %.*s", 
                                (int)(d - data) - 5, data + 5);
			    ftp.ctltag[0] = '\0';
			    ftp.datatag[0] = '\0';
			}
	        }
		if (memcmp(data, "PORT ", 5) == 0) 
			link_ftp_port(data + 5, tag, end);
		if (memcmp(data, "EPRT ", 5) == 0) 
			link_ftp_eport(data + 5, tag, end,
				 ip ? &ip->ip_src : NULL,
#if HAVE_NETINET_IP6_H
				 ip6 ? &ip6->ip6_src : NULL
#else
				 NULL
#endif
			);
	}

	if (sport == 21) {
	    d = data;
	    if (memcmp(d, "227 ", 4) == 0) {
		while (d < end && *d != '(')
			d++;
		if (++d < end)
			link_ftp_port(d, tag, end);
	    }
	    else if (memcmp(d, "229 ", 4) == 0) {
		while (d < end && *d != '(')
			d++;
		if (++d < end)
			link_ftp_eport(d, tag, end,
				 ip ? &ip->ip_src : NULL,
#if HAVE_NETINET_IP6_H
				 ip6 ? &ip6->ip6_src : NULL
#else
				 NULL
#endif
			);
	    }
	}

	/* Try to complete an FTP association */
	if (ftp.datatag[0] == '\0'
	    && ftp.ctltag[0] != '\0' 
	    && (ip ? ip->ip_dst.s_addr == ftp.addr.s_addr
#if HAVE_NETINET_IP6_H
		   : memcmp(&ip6->ip6_src, &ftp.addr6, sizeof ftp.addr6) == 0
#else
		   : 0
#endif
	       )
	    && dport == ftp.port)
	{
		/* Complete association so that future descs are copied */
		strlcpy(ftp.datatag, tag, sizeof ftp.datatag);
	}

	return tag;
}

/*
 * Parse and remember the port address so that we can associate it
 * back to the control flow
 */
static void
link_ftp_port(d, tag, end)
	const char *d;
	const char *tag;
	const char *end;
{
	union {
	    struct in_addr addr;
	    unsigned char a[4];
	} ua;
	union {
	    u_int16_t port;
	    unsigned char a[2];
	} up;
	char buf[TAGLEN], *b;
	unsigned int v[6];

	for (b = buf; d < end && b < buf+1+sizeof buf && 
	    *d != ')' && *d != '\r';)
		*b++ = *d++;
	*b = '\0';

	if (sscanf(buf, "%u,%u,%u,%u,%u,%u", v+0,v+1,v+2,v+3,v+4,v+5) == 6) {
	    ua.a[0] = v[0];
	    ua.a[1] = v[1];
	    ua.a[2] = v[2];
	    ua.a[3] = v[3];
	    up.a[0] = v[4];
	    up.a[1] = v[5];
	    ftp.port = ntohs(up.port);
	    ftp.addr = ua.addr;
	    strlcpy(ftp.ctltag, tag, sizeof ftp.ctltag);
	    ftp.datatag[0] = '\0';
	}
}

/* Same, but for EPRT */
static void
link_ftp_eport(d, tag, end, defaddr, defaddr6)
	const char *d;
	const char *tag;
	const char *end;
	const struct in_addr *defaddr;
	const struct in6_addr *defaddr6;
{
        struct in_addr addr;
	unsigned int port;
	char buf[TAGLEN], *b;
	char delim;

	for (b = buf; d < end && b < buf+1+sizeof buf && 
	    *d != ')' && *d != '\r';)
		*b++ = *d++;
	*b = '\0';

	delim = buf[0];
	if (buf[1] == delim && buf[2] == delim && defaddr) {
		addr.s_addr = defaddr->s_addr;
		if (sscanf(buf + 3, "%u", &port) != 1)
			return;
		goto gotit;
	}

	if (buf[1] != '1' || buf[2] != delim)	/* only handle AF_INET */
		return;

	b = buf+3;
	while (*b && *b != delim)
		b++;
	if (!*b) return;
	*b++ = '\0';
	if (sscanf(b, "%u", &port) != 1)
		return;
	addr.s_addr = inet_addr(buf+3);
gotit:
	ftp.port = port;
	ftp.addr = addr;
	strlcpy(ftp.ctltag, tag, sizeof ftp.ctltag);
	ftp.datatag[0] = '\0';
}
