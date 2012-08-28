
/***

othfilter.h - declarations for the non-TCP filter module
Written by Gerard Paul Java
Copyright (c) Gerard Paul Java 1997
			
***/

#include <sys/types.h>
#include <netinet/udp.h>
#include "othipflt.h"
#include "utfilter.h"

struct filterstate {
    char tfilename[FLT_FILENAME_MAX];
    char ufilename[FLT_FILENAME_MAX];
    char ofilename[FLT_FILENAME_MAX];
    unsigned int tfiltercode;
    unsigned int ufiltercode;
    unsigned int ofiltercode;
    struct filterlist tfl;
    struct filterlist ufl;
    struct filterlist ofl;

    u_int16_t arp:1, rarp:1, nonip:1, padding:13;
};

void config_filters(struct filterstate *filter);
void loadfilters(struct filterstate *filter);
void savefilters(struct filterstate *filter);
int othfilterok(struct filterstate *filter, unsigned int protocol,
		unsigned long saddr, unsigned long daddr,
		unsigned int sport, unsigned int dport);
