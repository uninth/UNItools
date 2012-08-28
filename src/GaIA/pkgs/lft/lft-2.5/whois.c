/*  
 *  Handle communication with whois servers. 
 *
 *  Includes:
 *		- simplified access to regular expressions
 *		- tokenizer
 *		- lookup functions for AS, NETNAME, ORGNAME 
 *              - works with the following sources:
 *		  ARIN, RIPE, APNIC, RADB, CYMRU, PWHOIS, RISwhois
 *              - will do recursive lookups
 *		- convenient framework for further whois digging
 *
 * 	To compile the standalone client:
 *		cc -o w whob.c -DSTANDALONE
 *      To use the standalone client:
 *		./whob <hostname | ip>
 *
 *      Portions (c) 2005 Victor Oppleman (lft@oppleman.com)
 *	Portions (c) 2002 Ugen Antsilevitch (ugen@xonix.com)
 *
 *  This file is part of LFT.
 *
 *  The full text of our legal notices is contained in the file called
 *  COPYING, included with this Distribution.
 *
 */

#define PORT_WHOIS	43

#ifdef WIN32
#include <windows.h>
#include <stdio.h>
#include <string.h>
#define read(a, b, c)	recv(a, b, c, 0)
#define write(a, b, c)  send(a, b, c, 0)
#define close(s) closesocket(s)
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#ifdef sun
#include <strings.h>
#endif
#endif
#include "whois.h"

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

#define ASSERT(x)       if (!(x)) { fprintf(stderr, "Assertion ("#x") failed\n"); exit(1); }

/* OPTIONS and variable initialization */

static const char *version = "1.5";             /* set version string for library and client */
static int w_noisy = 0;                         /* Don't show debug msgs by default */
static char pw_serv[256];                       /* User can specify his own pwhois server */
static char *consolidated_asn = "?";		/* ASN returned from pwhois */
static char *consolidated_asp = "?";		/* AS-PATH returned from pwhois */
static char *consolidated_route = "?";		/* Prefix returned from pwhois */
static const char *appname = "WhoB";            /* set application name */

static char *pwhois_server = "whois.pwhois.org";
static char *radb_server = "whois.ra.net";
static char *cymru_server = "whois.cymru.com";
static char *arin_server = "whois.arin.net";
static char *apnic_server = "whois.apnic.net";
static char *ripe_server = "whois.ripe.net";
static char *ripe_ris_server = "riswhois.ripe.net";

#ifdef STANDALONE
static int use_cymru = 0;                       /* Don't use Cymru by default */
static int use_riperis = 0; 			/* Don't use RIPE NCC RIS by default */
static int display_orgname = 0;                 /* Display orgname by default */
static int display_aspath = 0;                  /* Don't display AS-PATH by default */
static int display_netname = 0;                 /* Don't display netname by default */
static int display_radb_as = 0;                 /* Don't display RADB Origin-AS by default */
static int show_routes_byasn = 0;		/* Don't show all advertisements by default */
static int show_routes_byprefix = 0;		/* Don't show all routes by prefix by default */
static int show_server_status = 0;		/* Don't show pwhois server status by default */
static int show_cache_date = 0;			/* Don't show pwhois cache date by default */
static const int max_hostname_input = 200;      /* Maximum length of input from user */
static char hostname[256];
#endif

/* END of OPTIONS and variable initialization */

char tbuf[1024];
time_t tval;

#ifdef WIN32
char *
index(char *s, char c)
{
	char *t;
	if (!s)
		return NULL;

	for (t = s; *t; t++)
		if (*t == c) {
			return t;
		}

	/* Return terminating \0 if 
	   specifically requested */
	if (c == '\0')
		return t;

	return NULL;
}
#endif

char *
lft_strndup(char *s, int len)
{
char *rs;

	if (!s || len < 0)
		return NULL;

	if ((int)strlen(s) <= len)
		return(strdup(s));

	if (!(rs = malloc(len + 1)))
		return NULL;

	if (len > 0)
		strncpy(rs, s, len);
	rs[len] = 0;

	return rs;
}

#ifdef WIN32
int
inet_aton(const char *cp, struct in_addr *pin)
{
	if (!pin)
		return -1;

	pin->s_addr = inet_addr(cp);
	return (pin->s_addr != -1) ? 1 : 0;
}
#endif

char *
strskip(char *buf, char *sep)
{
char *c;

	c = buf;
	while (*c != '\0') {
		if (index(sep, *c)) 
			c++;
		else
			break;
	}

	return c;
}

typedef struct token_s {
	char	*ptr;
} token_t;

token_t *
tokens(char *buf, char *sep)
{
char *c, *c1;
int size, cur;
token_t *rt;

	if (!buf || !sep)
		return NULL;

	size = 1;
	for (c = buf; *c ; c++) 
		if (index(sep, *c)) {
			size++;
			while (*c && index(sep, *c)) 
					c++;
		}

	size++; /* for the NULL */

	if (!(rt = (token_t *)malloc(size * sizeof(token_t))))
		return NULL;

	memset(rt, 0, size * sizeof(token_t));

	rt[0].ptr = buf;
	cur = 0;

	for (c = buf; *c ; c++) {
		if (index(sep, *c)) {
			c1 = c;
			while (*c && index(sep, *c)) 
					c++;
			if (*c) 
				rt[++cur].ptr = c;

			*c1 = '\0';
		} 
	}

	rt[++cur].ptr = NULL;

	return rt;
}

typedef struct ip_blk_s {
	unsigned int	start;
	unsigned int	end;
} ip_blk_t;

ip_blk_t *
w_blk2range(char *s_start, char *s_end)
{
struct in_addr in;
unsigned int s, e;
ip_blk_t *r;

	if (!s_start || !s_end)
		return NULL;

	if (!inet_aton(s_start, &in))
		return NULL;

	s = ntohl(in.s_addr);

	if (!inet_aton(s_end, &in))
		return NULL;

	e = ntohl(in.s_addr);

	if (!(r = malloc(sizeof(ip_blk_t))))
		return NULL;

	r->start = s;
	r->end = e;
	return r;
}

ip_blk_t *
w_mask2range(char *addr, char *mask)
{
struct in_addr in;
unsigned int s, m;
ip_blk_t *r;

	if (!addr || !mask)
		return NULL;

	m = atoi(mask);
	if ((m < 0) || (m > 32))
		return NULL;

	if (!inet_aton(addr, &in))
		return NULL;

	s = ntohl(in.s_addr);

	if (!(r = malloc(sizeof(ip_blk_t))))
		return NULL;

	r->start = s &~ (((unsigned)0xffffffff) >> m);
	r->end = s | (((unsigned)0xffffffff) >> m);
	return r;
}

int rm_spaces(char* str)
{
/* Remove spaces (isspace()) from anywhere within a string
   ONLY operates on a null-terminated (\0) string!  */

   int j = -1;
   int i;     
   
   if (!str) return 0;  

   for (i=0; i<=strlen(str); i++)
       if (!(isspace(*(str+i))))
           *(str+(++j)) = *(str+i);
       else
           continue;

   return 1;     
}
	
char *match_prefix(const char *prefix, const char *target)
{
  /* Target will be something like "origin:        AS22773" and prefix will be "origin:" and
   * we return a pointer to "AS22773" */
  while (*prefix) {
    if (tolower(*prefix) != tolower(*target))
      return NULL;
    prefix++;
    target++;
  }
  while (isspace(*target))
    target++;
  /* strip out the leading AS from the number */
  if (strncmp(target,"AS",2) == 0)
    target += 2;
  return strdup(target);
}

ip_blk_t *match_iprange(char *target)
{
  /* matches something like "1.2.3.4-5.6.7.8" */
  char *pos, *dash, *beforedash;
  ip_blk_t *out;

  while (isspace(*target))
    target++;
  pos = target;
  while (*pos && !isspace(*pos))
	pos++;

  beforedash = strdup(target);
  beforedash[pos-target] = 0;

  dash = strchr(target, '-');
  if (!dash)
    return NULL;
  dash++;
  while (isspace(*dash))
    dash++;

  return w_blk2range(beforedash, dash);
}

ip_blk_t *match_ipprefix(char *target)
{
  /* matches something like 1.2.3.0/24 */
  char *slash, *pos;
  char *beforeslash;
  ip_blk_t *out;

  while (isspace(*target))
    target++;
  pos = target;
  while (*pos && !isspace(*pos) && *pos != '/')
    pos++;
  beforeslash = strdup(target);
  beforeslash[pos - target] = 0;

  slash = strchr(target, '/');
  if (!slash) return NULL;

  slash++;

  return w_mask2range(beforeslash, slash);
}

char *match_inparens(char *target)
{
  /* matches something like "    (HELLO)" and returns "HELLO" */
  char *end, *res;

  target = strchr(target, '(');
  if (!target)
    return NULL;
  
  target++;
  end = strchr(target, ')');
  if (!end)
    return NULL;

  res = strdup(target);
  res[end - target] = 0;
  return res;
}

char *match_afterparens(char *target)
{
  /* matches something like "   (HELLO) xxx" and returns a pointer to "xxx" */
  target = strchr(target, '(');
  if (!target) return NULL;
  target = strchr(target, ')');
  if (!target) return NULL;
  target++;
  while(*target && isspace(*target)) target++;
  if (*target) return strdup(target);
  else return NULL;
}

void
w_init()
{
int e;

#ifdef WIN32
WORD wVersionRequested;
WSADATA wsaData;
	wVersionRequested = MAKEWORD( 2, 2 );
	WSAStartup( wVersionRequested, &wsaData );
#endif
}

char *
w_ask(char *serv, char *q, char *port)
{
int s;
struct sockaddr_in sin;
struct hostent *hp;
char *br;
int q_s, br_s, cur, n, myport;
char buf[128];


	if (!serv || !q)
		return NULL;

	if (!(hp = gethostbyname(serv)))
		return NULL;

	sin.sin_family = AF_INET;
        if (port) {
          if (!(myport = atoi(port))) 
                return NULL;
          sin.sin_port = htons(myport);
        } else {
          sin.sin_port = htons(PORT_WHOIS);
        }
	memcpy((void *)&sin.sin_addr, hp->h_addr, hp->h_length);

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		return NULL;

	if (connect(s, (struct sockaddr *)&sin, sizeof (sin)) < 0) 
		return NULL;

	br_s = 512;
	if (!(br = malloc(br_s)))
		return NULL;

	q_s = strlen(q);
	if (write(s, q, q_s) != q_s || write(s, "\r\n", 2) != 2)
		return NULL;

	cur = 0;
	while ((n = read(s, buf, sizeof(buf))) > 0) {
		if ((cur + n) >= br_s) {
			br_s = br_s * 2;
			if (!(br = realloc(br, br_s)))
				return NULL;
		}
		strncpy((char *)&br[cur], buf, n);
		cur += n;	
	}
	br[cur] = 0;

	close(s);

	return br;
}

int 
w_lookup_all_pwhois(char *addr)
{
        token_t *ls;
        char *serv, *reply, *format;
        int i;

        if (!addr)
                return -1;

        if (strlen(pw_serv) > 0)
		serv = pw_serv;
	else 
		serv = pwhois_server;

        reply = w_ask(serv, addr, NULL);
        if (!reply) {
		if (w_noisy) fprintf(stderr,"No reply from %s.\n",serv);
                return -1;
	}

        ls = tokens(reply, "\n");

        for (i = 0; ls[i].ptr; i++) {
                char *value = NULL;
                if ((value = match_prefix("origin-as:", ls[i].ptr))) {
			if (strncmp(consolidated_asn,"?",1) == 0) consolidated_asn = value;
                }
                if ((value = match_prefix("prefix:", ls[i].ptr))) {
			if (strncmp(consolidated_route,"?",1) == 0) consolidated_route = value;
                }
                if ((value = match_prefix("as-path:", ls[i].ptr))) {
			if (strncmp(consolidated_asp,"?",1) == 0) consolidated_asp = value;
                }
		if ((value = match_prefix("cache-date:", ls[i].ptr))) {
			if (tval = atol(value)) {
				format = "%d-%b-%y %H:%M:%S %Z";
				(void)strftime(tbuf, sizeof(tbuf), format, localtime(&tval));
                        }
                }
        }

        free(ls); free(reply); 
	return 0;
}

int 
w_lookup_all_riperis(char *addr)
{
        token_t *ls;
        char *serv, *reply;
        const char *risopts = "-1 -M ";  /* 1 object/prefix, Most specific */
        char *risquery = malloc(strlen(risopts) + strlen(addr) + 1);
        int i;

        if (!addr)
                return -1;

        /* prepare the text-string-based query */
        strcat(risquery,risopts);
        strcat(risquery,addr);

        reply = w_ask(ripe_ris_server, risquery, NULL);
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",serv);
                return -1;
        }

        ls = tokens(reply, "\n");

        for (i = 0; ls[i].ptr; i++) {
                char *value = NULL;
                if ((value = match_prefix("origin:", ls[i].ptr))) {
                        if (strncmp(consolidated_asn,"?",1) == 0) consolidated_asn = value;
                }
                if ((value = match_prefix("route:", ls[i].ptr))) {
                        if (strncmp(consolidated_route,"?",1) == 0) consolidated_route = value;
                }
        }

        free(ls); free(reply); free(risquery);
        return 0;
}

int
w_lookup_as_pwhois(char *addr)
{
        token_t *ls;
        char *reply = NULL, *value = NULL;
        int i, ans = 0;

        if (!addr)
                return 0;

        reply = w_ask(pwhois_server, addr, NULL);
        if (!reply) {
		if (w_noisy) fprintf(stderr,"No reply from %s.\n",pwhois_server);
                return 0;
	}
        ls = tokens(reply, "\n");

        for (i = 0; ls[i].ptr; i++) {
                if ((value = match_prefix("origin-as:", ls[i].ptr)))
                        break;
        }

        free(ls); free(reply);

	if (!value)
		return 0;

	rm_spaces(value);

        for (i = 0; i < strlen(value); i++) {
               if (!isdigit(value[i])) {
                        return 0;
                }
        }

        if (ans = atoi(value))
                       return ans;
        else return 0;
}

int
w_lookup_as_riswhois(char *addr)
{
        token_t *ls;
        char *reply = NULL, *value = NULL;
        const char *risopts = "-1 -M ";  /* 1 object/prefix, Most specific */
        char *risquery = malloc(strlen(risopts) + strlen(addr) + 1);
        int i, ans = 0;

        if (!addr)
                return 0;

        /* prepare the text-string-based query */
        strcat(risquery,risopts);
        strcat(risquery,addr);

        reply = w_ask(ripe_ris_server, risquery, NULL);
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",ripe_ris_server);
                return 0;
        }
        ls = tokens(reply, "\n");

        for (i = 0; ls[i].ptr; i++) {
                if ((value = match_prefix("origin:", ls[i].ptr)))
                        break;
        }

        free(ls); free(reply); free(risquery);

        if (!value)
                return 0;

        rm_spaces(value);

        for (i = 0; i < strlen(value); i++) {
               if (!isdigit(value[i])) {
                        return 0;
                }
        }

        if (ans = atoi(value))
                       return ans;
        else return 0;
}

int
w_lookup_as_riswhois_bulk(struct ip_list_array *iplist)
{

        token_t *responses;
        char *reply;
        const char *bulk_begin = "-k -1 -M\n";  /* Keepalive, 1 object/prefix, Most specific */
        const char *bulk_end = "-k";
        char *bulk_ip_query = malloc(strlen(bulk_begin) + strlen(bulk_end) + (16 * (*iplist).numItems));
        int i,j,k = 0;
	int numlines = 0;
        char *value = NULL;

        if (!iplist)
                return -1;

        /* clean up the response data set in case the caller doesn't (and we return error) */
        for (i = 0; i <= (*iplist).numItems; i++)
                (*iplist).asn[(i)] = 0;

        /* prepare the text-string-based query */
        strcat(bulk_ip_query,bulk_begin);
        for (i = 0; i < ((*iplist).numItems); i++) {
                strcat(bulk_ip_query,inet_ntoa((*iplist).ipaddr[i]));
                strcat(bulk_ip_query,"\n");
        }
        strcat(bulk_ip_query,bulk_end);

        reply = w_ask(ripe_ris_server, bulk_ip_query, NULL);
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",ripe_ris_server);
                /* clean up the response data set in case the caller doesn't */
                for (i = 0; i <= (*iplist).numItems; i++)
                        (*iplist).asn[(i)] = 0;
                return -1;
        }
        responses = tokens(reply, "\n");

        for (i = 0; responses[i].ptr; i++) {
	  /* numlines++; printf("%d: ",numlines); */
          if (value = match_prefix("origin:", responses[i].ptr)) {
            rm_spaces(value);       /* strip out any spaces from the ASN */
            for (j = 0; j < strlen(value); j++) {
                   if (!isdigit(value[j])) {
                            if (w_noisy) printf("Parse error at \'%c\': non-numeric value at position %d of %s).\n",value[i],i,value);
                            break;
                    }
            }
           if (atoi(value)) {
                       (*iplist).asn[(k)] = atoi(value);
                       /* printf("** MATCHED %d for hop %d inside '%s'\n",atoi(value),k+1,responses[i].ptr); */
                       k++; 
                } else printf("Skipping additional object for same query.\n");
          } else {
                 if (value = match_prefix("% ", responses[i].ptr)) {
                       if (i > 5) {   /* Weed out up to 5 header lines from RIPE NCC RIS */
                         /* printf("%% MATCHED on '%s'\n",responses[i].ptr); */
                         (*iplist).asn[(k)] = 0;
                         k++;
                       } /* else printf("'%s'\n",responses[i].ptr); */
                 } /* else printf("'%s'\n",responses[i].ptr); */
          }
          if ((k+1) > (*iplist).numItems)
             break;
        }

        free(responses); free(reply); free(bulk_ip_query);

        return 0;
}

int
w_lookup_as(char *addr)
{
	token_t *ls;
	ip_blk_t *a = NULL, *b = NULL;
	char *sa, *sb;
	char *reply, *value = NULL;
	int i, ans = 0;
	int use_this = 1;

	if (!addr)
		return 0;

	reply = w_ask(radb_server, addr, NULL);
	if (!reply) {
		if (w_noisy) fprintf(stderr,"No reply from %s.\n",radb_server);
		return 0;
	}
	ls = tokens(reply, "\n");

	for (i = 0; ls[i].ptr; i++) {
		if ((value = match_prefix("local-as:", ls[i].ptr))) {
			break;
		}
		if ((value = match_prefix("route:", ls[i].ptr))) {
			a = match_ipprefix(value);

			if (b) {
				if (((b->end - b->start) > (a->end - a->start))) {
					use_this = 1;
					free(b);
					b = a;
					a = NULL;
				} else {
					use_this = 0;
					free(a);
					a = NULL;
				}
			} else {
				use_this = 1;
				b = a;
				a = NULL;
			}
		}
		if (use_this && (value = match_prefix("origin:", ls[i].ptr))) {
			break;
		}
	}

	free(ls); free(reply); if (b) free(b);

	if (!value)
		return 0;

	rm_spaces(value);

        for (i = 0; i < strlen(value); i++) {
               if (!isdigit(value[i])) {
                        return 0;
                }
        }

        if (ans = atoi(value))
                        return ans;
        else return 0;
}

int
w_lookup_as_cymru(char *addr)
{
/*
 *   Look up the ASN at the prefix-based Cymru whois server
 */
        token_t *ls;
        char *reply;
        int i;
        char value[6];
        int ans = 0;
        memset(&value, 0, sizeof(value));

        if (!addr)
                return 0;

        reply = w_ask(cymru_server, addr, NULL);
        if (!reply) {
		if (w_noisy) fprintf(stderr,"No reply from %s.\n",cymru_server);
                return 0;
	}
        ls = tokens(reply, "\n");

        /* Set i to 1 to skip the first/header line of reply from cymru */
        strncpy(value,ls[1].ptr,5);
        rm_spaces(value);       /* strip out any spaces from the ASN */

        for (i = 0; i < strlen(value); i++) {
               if (!isdigit(value[i])) {
                        return 0;
                }
        }

        free(ls); free(reply);
        if (ans = atoi(value))
                        return ans;
        else return 0;
}

int
w_lookup_as_cymru_bulk(struct ip_list_array *iplist)
{

	token_t *responses;
	char *reply;
	const char *bulk_begin = "begin\n";
	const char *bulk_end = "end\n";
	char *bulk_ip_query = malloc(strlen(bulk_begin) + strlen(bulk_end) + (16 * (*iplist).numItems));
	int i,j;
	char value[6];
	memset(&value, 0, sizeof(value));

	if (!iplist)
		return -1;

        /* clean up the response data set in case the caller doesn't (and we return error) */
        for (i = 0; i <= (*iplist).numItems; i++)
                (*iplist).asn[(i)] = 0; 

	/* prepare the text-string-based query */
	strcat(bulk_ip_query,bulk_begin);
	for (i = 0; i < ((*iplist).numItems); i++) {
		strcat(bulk_ip_query,inet_ntoa((*iplist).ipaddr[i]));
		strcat(bulk_ip_query,"\n");
	}
	strcat(bulk_ip_query,bulk_end);

        reply = w_ask(cymru_server, bulk_ip_query, NULL);
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",cymru_server);
                return -1;
        }
        responses = tokens(reply, "\n");

        /* Set i to 1 to skip the first/header line of reply from cymru */
	for (i = 1; responses[i].ptr; i++) {
          strncpy(value,responses[i].ptr,5);
          rm_spaces(value);       /* strip out any spaces from the ASN */
          for (j = 0; j < strlen(value); j++) {
                 if (!isdigit(value[j])) {
			  if (w_noisy) printf("Parse error at \'%c\': non-numeric value at position %d of %s).\n",value[i],i,value);
			  break;
                  }
          }
         if (atoi(value)) { 
	    (*iplist).asn[(i-1)] = atoi(value);
	 } else {
  	      (*iplist).asn[(i-1)] = 0;
           }
         if ((i+1) > (*iplist).numItems) 
              break;
	}

        free(responses); free(reply); free(bulk_ip_query); 

	return 0;
}

#ifdef STANDALONE
int w_display_rvbyasn_pwhois(char *asn)
{
        char *reply;
        const char *query_begin = "routeview source-as=";
        char *whob_query = NULL;
        char *serv;
  
        if (!asn) 
           return -1;

        if (strlen(pw_serv) > 0)
                serv = pw_serv;
        else
                serv = pwhois_server;

        whob_query = malloc((strlen(appname)+10) + strlen(version) + strlen(query_begin) + strlen(asn));

        /* prepare the text-string-based query */
        strcat(whob_query,"app=\"");
        strcat(whob_query,appname);
        strcat(whob_query," ");
        strcat(whob_query,version);
        strcat(whob_query,"\" ");
        strcat(whob_query,query_begin);
        strcat(whob_query,asn);

        strcat(whob_query,"\n");

        reply = w_ask(serv, whob_query, NULL);
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",serv);
                return -1;
        }

        printf("%s",reply);

        free(reply); free(whob_query);

        return 0;
}

int w_display_rvbyprefix_pwhois(char *prefix)
{
        char *reply;
        const char *query_begin = "routeview prefix=";
        char *whob_query = NULL;
        char *serv;
  
        if (!prefix) 
           return -1;

        if (strlen(pw_serv) > 0)
                serv = pw_serv;
        else
                serv = pwhois_server;

        whob_query = malloc((strlen(appname)+10) + strlen(version) + strlen(query_begin) + strlen(prefix));

        /* prepare the text-string-based query */
        strcat(whob_query,"app=\"");
        strcat(whob_query,appname);
        strcat(whob_query," ");
        strcat(whob_query,version);
        strcat(whob_query,"\" ");
        strcat(whob_query,query_begin);
        strcat(whob_query,prefix);

        strcat(whob_query,"\n");

        reply = w_ask(serv, whob_query, NULL);  
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",serv);
                return -1;
        }

        printf("%s",reply);

        free(reply); free(whob_query);

        return 0;
}
int w_display_pwhois_version()
{
        char *reply;
        char *serv;

        if (strlen(pw_serv) > 0)
                serv = pw_serv;
        else
                serv = pwhois_server;

	if (w_noisy)
                printf("Querying Prefix WhoIs Server %s for version/status...\n",serv);

        reply = w_ask(serv, "version\n", NULL);
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",serv);
                return -1;
        }

        printf("%s",reply);

        free(reply); 

        return 0;
}
#endif

int
w_lookup_as_pwhois_bulk(struct ip_list_array *iplist)
{

        token_t *responses;
        char *reply;
        const char *bulk_begin = "begin\n";     
        const char *bulk_end = "end\n";         
        char *bulk_ip_query = NULL;
        int i,j,k = 0;
        char *value = NULL;

        if (!iplist)
                return -1;

	if ((*iplist).application) {
           bulk_ip_query = malloc((strlen((*iplist).application)+10) + strlen(bulk_begin) + strlen(bulk_end) + (16 * (*iplist).numItems));
        } else bulk_ip_query = malloc((strlen(appname)+10) + strlen(version) + strlen(bulk_begin) + strlen(bulk_end) + (16 * (*iplist).numItems));

        /* clean up the response data set in case the caller doesn't (and we return error) */
        for (i = 0; i <= (*iplist).numItems; i++)
                (*iplist).asn[(i)] = 0;        

        /* prepare the text-string-based query */
        strcat(bulk_ip_query,bulk_begin);
        if ((*iplist).application) {
           strcat(bulk_ip_query,"app=\"");
           strcat(bulk_ip_query,(*iplist).application);
           strcat(bulk_ip_query,"\"\n");
        } else {
           strcat(bulk_ip_query,"app=\"");
           strcat(bulk_ip_query,appname);
           strcat(bulk_ip_query," ");
           strcat(bulk_ip_query,version);
           strcat(bulk_ip_query,"\"\n");
        }

        for (i = 0; i < ((*iplist).numItems); i++) {
                strcat(bulk_ip_query,inet_ntoa((*iplist).ipaddr[i]));
                strcat(bulk_ip_query,"\n");
        }
        strcat(bulk_ip_query,bulk_end);

        reply = w_ask(pwhois_server, bulk_ip_query, NULL);
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",pwhois_server);
		/* clean up the response data set in case the caller doesn't */
		for (i = 0; i <= (*iplist).numItems; i++) 
			(*iplist).asn[(i)] = 0;
                return -1;
        }
        responses = tokens(reply, "\n");
                        
        for (i = 0; responses[i].ptr; i++) {
          if (value = match_prefix("origin-as:", responses[i].ptr)) {
            rm_spaces(value);       /* strip out any spaces from the ASN */
            for (j = 0; j < strlen(value); j++) {
                   if (!isdigit(value[j])) {
                            if (w_noisy) printf("Parse error at \'%c\': non-numeric value at position %d of %s).\n",value[i],i,value);
                            break;
                    }
            }
           if (atoi(value)) {
              (*iplist).asn[(k)] = atoi(value);
              k++;
           } else {
                (*iplist).asn[(k)] = 0;
              k++;
             }
          }
          if ((k+1) > (*iplist).numItems) 
             break;
     	}

        free(responses); free(reply); free(bulk_ip_query); 

        return 0;
}

char *
w_lookup_netname_other(char *addr, char *serv)
{
	token_t *ls;
	ip_blk_t *a = NULL, *b = NULL;
	char *reply, *ans = NULL;
	int i;
	int use_this = 1;

	if (!addr || !serv)
		return NULL;

	reply = w_ask(serv, addr, NULL);
	if (!reply) {
		if (w_noisy) fprintf(stderr,"No reply from %s.\n",serv);
		return NULL;
	}
	ls = tokens(reply, "\n");

	for (i = 0; ls[i].ptr; i++) {
		char *value;
		if ((value = match_prefix("inetnum:", ls[i].ptr))) {
			a = match_ipprefix(value);

			if (b) {
				if (((b->end - b->start) > (a->end - a->start))) {
					use_this = 1;
					free(b);
					b = a;
					a = NULL;
				} else {
					use_this = 0;
					free(a);
					a = NULL;
				}
			} else {
				use_this = 1;
				b = a;
				a = NULL;
			}
		}
		if (use_this && (value = match_prefix("netname:", ls[i].ptr))) {
			if (ans)
				free(ans);
			ans = value;
		} 
	}

	free(ls); free(reply); if (b) free(b);
	return ans;
}

char *
w_lookup_netname(char *addr)
{
	token_t *ls;
	ip_blk_t *a = NULL, *b = NULL;
	char *na = NULL, *nb = NULL;
	char *reply, *ans = NULL;
	int i;
	int have_new, have_old;

	if (!addr)
		return NULL;

	reply = w_ask(arin_server, addr, NULL);
	if (!reply) {
		if (w_noisy) fprintf(stderr,"No reply from %s.\n",arin_server);
		return NULL;
	}
	ls = tokens(reply, "\n");

	ans = NULL;
	for (i = 0; ls[i].ptr; i++) {
		char *value;
		if ((value = match_prefix("netname:", ls[i].ptr))) {
			ans = value;
			break;
		}
	}

	if (!ans) {

	for (i = 0; ls[i].ptr; i++) {
		char *value;
		if ((value = match_inparens(ls[i].ptr))) {
			char *after = match_afterparens(ls[i].ptr);
			if (after) {
				na = value;
				a = match_iprange(after);
			} else {
				na = value;
				if (ls[i+1].ptr && (a = match_iprange(ls[i+1].ptr))) {
				  /* successful match */
				} else { /* Bad format */
					free(na); na = NULL;
					continue;
				}
			}
		}

		have_new = (na && a);
		have_old = (nb && b);

		if (have_new) {
			if (have_old) {
				if (((b->end - b->start) > (a->end - a->start))) {
					/* keep new, discard old */
					free(nb); free(b);
					nb = na; na = NULL;
					b = a; a = NULL;
				} else { /* keep old, discard new */
					free(na); free(a);
					na = NULL;
					a = NULL;
				}
			} else { /* nothing old, save new */
				nb = na; na = NULL;
				b = a; a = NULL;
			}
		}
	} /* loop */

	if (na) free(na);
	if (a) free(a);
	if (b) free(b);
	free(ls); free(reply);
	if (!nb)
		return NULL;

	/* Add "!" to the beginning of the question */
	na = malloc(strlen(nb) + 2);
	strcpy(&na[1], nb);
	na[0] = '!';
	free(nb);

	reply = w_ask(arin_server, na, NULL);
	free(na);
	if (!reply) {
		if (w_noisy) fprintf(stderr,"No reply from %s.\n",arin_server);
		return NULL;
	}

	ls = tokens(reply, "\n");

}
	for (i = 0; ls[i].ptr; i++) {
		char *value;
		if ((value = match_prefix("netname:", ls[i].ptr))) {
			ans = value;
			break;
		}
	}

	free(ls); free(reply); 

	{
	  char *other = NULL;
	  if (ans && strstr(ans, "RIPE")) {
	    other = w_lookup_netname_other(addr, ripe_server);
	  }
	  
	  if (ans && !strncmp(ans, "APNIC", 5)) {
	    other = w_lookup_netname_other(addr, apnic_server);
	  }

	  if (other) {
	    char *together = malloc(strlen(ans) + strlen(other) + 2);
	    strcpy(together, ans);
	    strcat(together, "/");
	    strcat(together, other);
	    free(ans);
	    ans = together;
	  }
	}

	return ans;
}

char *
w_lookup_orgname_other(char *addr, char *serv)
{
        token_t *ls;
        ip_blk_t *a = NULL, *b = NULL;
        char *reply, *ans = NULL;
        int i;
        int use_this = 1;

        if (!addr || !serv)
                return NULL;

        reply = w_ask(serv, addr, NULL);
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",serv);
                return NULL;
        }
        ls = tokens(reply, "\n");

        for (i = 0; ls[i].ptr; i++) {
                char *value;
                if ((value = match_prefix("inetnum:", ls[i].ptr))) {
                        a = match_ipprefix(value);

                        if (b) {
                                if (((b->end - b->start) > (a->end - a->start))) {
                                        use_this = 1;
                                        free(b);
                                        b = a;
                                        a = NULL;
                                } else {
                                        use_this = 0;
                                        free(a);
                                        a = NULL;
                                }
                        } else {
                                use_this = 1;
                                b = a;
                                a = NULL;
                        }
                }
                if (use_this && (value = match_prefix("orgname:", ls[i].ptr))) {
                        if (ans)
                                free(ans);
                        ans = value;
                } 
        }

        if (!ans) {
	    for (i = 0; ls[i].ptr; i++) {
		char *value;
                if (use_this && (value = match_prefix("descr:", ls[i].ptr))) {
                        if (ans)
                                free(ans);
                        ans = value;
			break;
                }
            }
	}

        free(ls); free(reply); if (b) free(b);
        return ans;
}

char *
w_lookup_orgname(char *addr)
{
        token_t *ls;
        ip_blk_t *a = NULL, *b = NULL;
        char *na = NULL, *nb = NULL;
        char *reply, *ans = NULL;
        int i;
        int have_new, have_old;

        if (!addr)
                return NULL;

        reply = w_ask(arin_server, addr, NULL);
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",arin_server);
                return NULL;
        }
        ls = tokens(reply, "\n");

        for (i = 0; ls[i].ptr; i++) {
                char *value;
                if ((value = match_prefix("netname:", ls[i].ptr))) {
                        ans = value;
			break;
                } 
        }

        if (!ans) {

        for (i = 0; ls[i].ptr; i++) {
                char *value;
                if ((value = match_inparens(ls[i].ptr))) {
                        char *after = match_afterparens(ls[i].ptr);
                        if (after) {
                                na = value;
                                a = match_iprange(after);
                        } else {
                                na = value;
                                if (ls[i+1].ptr && (a = match_iprange(ls[i+1].ptr))) {
                                  /* successful match */
                                } else { /* Bad format */
                                        free(na); na = NULL;
                                        continue;
                                }
                        }
                }

                have_new = (na && a);
                have_old = (nb && b);

                if (have_new) {
                        if (have_old) {
                                if (((b->end - b->start) > (a->end - a->start))) {
                                        /* keep new, discard old */
                                        free(nb); free(b);
                                        nb = na; na = NULL;
                                        b = a; a = NULL;
                                } else { /* keep old, discard new */
                                        free(na); free(a);
                                        na = NULL;
                                        a = NULL;
                                }
                        } else { /* nothing old, save new */
                                nb = na; na = NULL;
                                b = a; a = NULL;
                        }
                }
        } /* loop */

        if (na) free(na);
        if (a) free(a);
        if (b) free(b);
        free(ls); free(reply);
        if (!nb)
                return NULL;

        /* Add "!" to the beginning of the question */
        na = malloc(strlen(nb) + 2);
        strcpy(&na[1], nb);
        na[0] = '!';
        free(nb);

        reply = w_ask(arin_server, na, NULL);
        free(na);
        if (!reply) {
                if (w_noisy) fprintf(stderr,"No reply from %s.\n",arin_server);
                return NULL;
        }

        ls = tokens(reply, "\n");

}
        for (i = 0; ls[i].ptr; i++) {
                char *value;
                if ((value = match_prefix("orgname:", ls[i].ptr))) {
                        ans = value;
                        break;
                }
        }

        free(ls); free(reply);

        {
          char *other = NULL;
          if (ans && strstr(ans, "RIPE")) {
            other = w_lookup_orgname_other(addr, ripe_server);
          }

          if (ans && (!strncmp(ans, "APNIC", 5) || strstr(ans, "Asia Pacific Net") )) {
            other = w_lookup_orgname_other(addr, apnic_server);
          }

          if (other) {
/*            char *together = malloc(strlen(ans) + strlen(other) + 4);
            strcpy(together, other);
            strcat(together, " (");
            strcat(together, ans);
            strcat(together, ")");
*/
            free(ans);
            ans = other;
          }
        }

        return ans;
}

#ifdef STANDALONE

static void
usage (char *prog)
{
  fprintf (stderr,
           "\nWhoB - version %s\n\n     - a no-frills whois client for internetwork engineers\n"
           "\nUsage: %s [<options>] <hostname>\n"
           "\nOptions:\n\n"
           "  -a         Display all routes announced by the respective ASN (pwhois-only)\n"
           "  -P         Display all routes announced respective to a prefix (pwhois-only)\n"
           "  -R         Display the Origin-AS on file at the RADB/IRR also\n"
           "  -o         Display the organization\'s name on file at the registrar\n"
           "  -p         Display the AS-Path learned by the pwhois server (pwhois-only)\n"
           "  -n         Display the network name on file at the registrar also\n"
           "  -t         Display the date the route was last updated (pwhois-only)\n"
           "  -c/-C      Use Cymru\'s whois server instead of pwhois\n"
           "  -r         Use RIPE NCC\'s RIS whois server instead of pwhois\n"
           "  -h <host>  Specify your own pwhois-compatible server to query\n"
           "  -V         Display verbose/debug output.  Use more \'V\'s for additional verbosity\n"
           "  -v         Display WhoB\'s version information and exit(1)\n"  "\n"
           ,version,prog);
           printf("Example:    $ ./%s -nop 1.2.3.4\n",prog);
           printf("Returns:    IP | ASN-by-prefix (prefix) | AS-Path | NetName | OrgName\n\n"); 
  exit (1);
}

static void
show_startup_msgs ()
{
  if (w_noisy) {
	printf("WhoB version %s firing up...",version);
        if (w_noisy > 1) printf(" (verbosity level %d)\n",w_noisy); else printf ("\n");
	printf("Data sources:");
	if ((strlen(pw_serv) > 0) && (!use_cymru)) printf(" %s (pwhois)",pw_serv); 
           else if (!use_cymru && !use_riperis) printf(" %s (pwhois)", pwhois_server);
           else if (!use_cymru) printf(" %s (RIPE NCC)", ripe_ris_server);
        if (use_cymru) printf(" %s (Cymru)",cymru_server);
	if (display_radb_as) printf(", %s (RADB)",radb_server);
	printf(", and registrars.\n");
        if (show_routes_byprefix == 1 && show_routes_byasn == 1) {
           fprintf(stderr,"You may only perform routeviews one at a time.  Using by ASN.\n");
           show_routes_byprefix = 0;
        } 
  }
}

int main(int ac, char **av)
{
	struct hostent *he, *pwhost;
	char *addr;
	struct in_addr in, pws;
 	int ch;
        int user_asn = 0;
        char user_asn_buf[10];

	memset(&tbuf, 0, sizeof(tbuf));
        memset(&pw_serv, 0, sizeof(pw_serv));
        memset(&hostname, 0, sizeof(hostname));

	w_init();
	setbuf (stdout, NULL);

    while ((ch = getopt (ac, av, "aCcnropPRstuVvh:w:")) != EOF)
    switch (ch) {
    case 'a':
      show_routes_byasn = 1;
      break;
    case 's':
      show_server_status = 1;
      break;
    case 'P':
      show_routes_byprefix = 1;
      break;
    case 'v':
      usage (av[0]);
      break;
    case 'u':	/* show all times in UTC */
      #if defined(sun)
         fprintf(stderr, "%s: Unable to set TZ to UTC.",appname);
         exit(1);
      #else
      if (setenv("TZ", "GMT0", 1) == -1) {
         fprintf(stderr, "%s: Unable to set TZ to UTC.",appname);
         exit(1);
      }
      #endif
      break;
    case 't':
      show_cache_date = 1;
      break;
    case 'w':
      if (strlen(optarg) > max_hostname_input) {
         fprintf(stderr,"Sorry, the server name you supplied was unreasonably long.\n");
         exit(1);
      }
      if (inet_aton(optarg, &pws)) {
         strncpy(pw_serv,optarg,strlen(optarg));
      } else {
         if (!(pwhost = gethostbyname(optarg))) {
           fprintf(stderr,"Sorry, I cannot resolve \'%s\' to use as your pwhois server.\n", optarg);
           exit(1);
         }
         memcpy(&pws, pwhost->h_addr, pwhost->h_length);
         strncpy(pw_serv,inet_ntoa(pws),strlen(inet_ntoa(pws)));
      }
      break;
    case 'h':
      if (strlen(optarg) > max_hostname_input) {
         fprintf(stderr,"Sorry, the server name you supplied was unreasonably long.\n");
         exit(1);
      }
      if (inet_aton(optarg, &pws)) {
         strncpy(pw_serv,optarg,strlen(optarg));
      } else {
         if (!(pwhost = gethostbyname(optarg))) {
           fprintf(stderr,"Sorry, I cannot resolve \'%s\' to use as your pwhois server.\n", optarg);
           exit(1);
         }
         memcpy(&pws, pwhost->h_addr, pwhost->h_length);
         strncpy(pw_serv,inet_ntoa(pws),strlen(inet_ntoa(pws)));
      }
      break;
    case 'c':
      use_cymru = 1;
      break;
    case 'C':
      use_cymru = 1;
      break;
    case 'n':
      display_netname = 1;
      break;
    case 'r':
      use_riperis = 1;
      break;
    case 'R':
      display_radb_as = 1;
      break;
    case 'o':
      display_orgname = 1;
      break;
    case 'p':
      display_aspath = 1;
      break;
    case 'V':
      w_noisy++;
      break;
    default:
      usage (av[0]);
    }

    if (((ac - optind) < 1) && (show_server_status != 1))
      usage (av[0]);

    /* Show the verbose startup information if verbosity is enabled/requested */
    show_startup_msgs();

    if (show_server_status == 1) {
         w_display_pwhois_version();
         exit(0);
    } else { 
          if (strlen(av[optind]) > max_hostname_input) {
           fprintf(stderr,"Sorry, the host name you supplied was unreasonably long.\n");
           exit(1);
        } else {
           strncpy(hostname,av[optind],strlen(av[optind]));
           optind++;
        }
    }

    if (show_routes_byasn == 1 && (strlen(hostname) <= 5) && atoi(hostname)) {
         user_asn = atoi(hostname);
         if (w_noisy > 1) printf("Using user-supplied ASN %d for advertisement lookup.\n",user_asn);
    } else if (show_routes_byprefix == 1) {
         printf("Displaying all routes for prefix %s.  (be patient)\n",hostname);
    } else {

		if (inet_aton(hostname, &in)) {
			addr = hostname;
		} else {
			if (!(he = gethostbyname(hostname))) {
				fprintf(stderr,"Sorry, I cannot resolve \'%s\'\n", hostname);
				exit(1);
			}
			memcpy(&in, he->h_addr, he->h_length);
			addr = inet_ntoa(in);
		}
    }

    if (show_routes_byasn) {
       if (user_asn > 0) {
          printf("Displaying all routes whose Origin-AS is %d.  (be patient)\n", user_asn);
          snprintf(user_asn_buf,9,"%d",user_asn);
          w_display_rvbyasn_pwhois(user_asn_buf);
       } else {
          w_lookup_all_pwhois(addr);
          if (atoi(consolidated_asn)) {
             printf("Displaying all routes whose Origin-AS is %s.  (be patient)\n", consolidated_asn);
             w_display_rvbyasn_pwhois(consolidated_asn);
          } else {
             printf("Sorry, unable to resolve the ASN for %s (%s) at this time.\n",hostname,addr);
          }
       }
    } else if (show_routes_byprefix) {
                  w_display_rvbyprefix_pwhois(hostname);
    } else {

		printf("%s ", addr);

		if (use_cymru) {
			    printf("| origin-as %d ", w_lookup_as_cymru(addr));
			} else if (use_riperis) {
                            w_lookup_all_riperis(addr);
                            printf("| origin-as %s (%s) ", consolidated_asn, consolidated_route);
                        } else {
			    w_lookup_all_pwhois(addr);
			    printf("| origin-as %s (%s) ", consolidated_asn, consolidated_route);
                            if (show_cache_date && (strlen(tbuf) > 0))
                                 printf("| %s ", tbuf);
			}
		if (display_radb_as) 
			printf("| radb-as %d ", w_lookup_as(addr));
                if ((display_aspath) && (!use_cymru) && (!use_riperis))
                        printf("| as-path %s ", consolidated_asp);
                if (display_netname)
                        printf("| %s ", w_lookup_netname(addr));
		if (display_orgname)
			printf("| %s ", w_lookup_orgname(addr));

    }
		printf("\n");
}
#endif

