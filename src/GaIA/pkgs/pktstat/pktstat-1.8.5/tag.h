/* David Leonard, 2002. Public domain. */
/* $Id: tag.h 1172 2006-11-11 13:32:14Z d $ */

/*
 * Tag functions return a string tag depending on the packet payload.
 * The string represents a display category.
 * The design philosophy here is that the tags should be short enough
 * and descriptive enough not to overwhelm an operator on a relatively
 * quiet business network, with the presumption that if the operator
 * is interested enough, they can always run tcpdump to look closer.
 */

extern int combine;

#if _AIX
#define ip6_hdr ipv6    /* AIX uses RFC 1883 instead of RFC2460 */
#define ip6_nxt ip6_nh
#endif

struct ip;
struct in_addr;
struct in6_addr;
struct ip6_hdr;

const char *ppp_tag(const char *, const char *);
const char *ether_tag(const char *, const char *);
const char *loop_tag(const char *, const char *);
const char *sll_tag(const char *, const char *);

const char *ip_tag(const char *, const char *);
const char *ip6_tag(const char *, const char *);

const char *ip_lookup(const struct in_addr *);
const char *ip6_lookup(const struct in6_addr *);

const char *tcp_tag(const char *, const char *, const struct ip *, const struct ip6_hdr *);
const char *udp_tag(const char *, const char *, const struct ip *, const struct ip6_hdr *);
const char *icmp_tag(const char *, const char *, const struct ip *);

const char *ipx_tag(const char *, const char *);

const char *tag_combine(const char *, const char *);

const char *ether_wol(const char *, const char *, const char *);

/* Ethernet-like tagging helper */
const char *ether_tagx(unsigned int type, const char *p, const char *end);

/* Flush hostname and port lookup caches */
void ip_reset(void);
void tcp_reset(void);
void udp_reset(void);
