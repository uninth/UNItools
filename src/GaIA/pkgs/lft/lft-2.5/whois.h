#ifndef WHOIS_H
#define WHOIS_H

struct ip_list_array {
	struct in_addr ipaddr[512];
	int asn[512];
	int numItems;
        char *application;
};

/* must be called BEFORE making any queries */
void w_init(void);

/* return the origin-asn according to the RADB in "3356" format */
int w_lookup_as(char *);

/* return the origin-asn according to Cyrmu in "3356" format */
int w_lookup_as_cymru(char *);

/* return the origin-asn according to the RIPE RIS in "3356" format */
int w_lookup_as_riswhois(char *);

/* return the origin-asn according to pwhois in "3356" format */
int w_lookup_as_pwhois(char *);

/* return the network name from the registrar in a string */
char *w_lookup_netname(char *);

/* return the organization name from the registrar in a string */
char *w_lookup_orgname(char *);

/* return a pointer to an ip_list_array (see above) containing
   an 'asn' to each corresponding 'ipaddr' according to Cymru   */
int w_lookup_as_cymru_bulk(struct ip_list_array*);

/* return a pointer to an ip_list_array (see above) containing
   an 'asn' to each corresponding 'ipaddr' according to pwhois   */
int w_lookup_as_pwhois_bulk(struct ip_list_array*);

/* return a pointer to an ip_list_array (see above) containing
   an 'asn' to each corresponding 'ipaddr' according to RIS whois   */
int w_lookup_as_riswhois_bulk(struct ip_list_array*);

#endif
