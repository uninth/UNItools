/***

fltdefs.h - declarations for the TCP, UDP, and misc IP filters
Written by Gerard Paul Java
Copyright (c) Gerard Paul Java 1997

***/

#define F_TCP 6
#define F_UDP 17
#define F_OTHERIP 59

#define FLT_FILENAME_MAX 	40

#define FLT_RESOLVE		1
#define FLT_DONTRESOLVE		0

#define F_ICMP		1
#define F_IGMP		2
#define F_OSPF		3
#define F_IGP		4
#define F_IGRP		5
#define F_GRE		7

struct hostparams {
    char s_fqdn[45];
    char d_fqdn[45];
    char s_mask[20];
    char d_mask[20];
    unsigned int sport;
    unsigned int dport;
    char reverse;
};

struct othip_hostparams {
    char s_fqdn[45];
    char d_fqdn[45];
    char s_mask[20];
    char d_mask[20];
    char reverse;
    char reserved[16];
};

struct othipfltdata {
    struct othip_hostparams hp;
    
    int filters[F_OTHERIP + 1];
};

struct filterent {
    union {
        struct hostparams hp;
        struct othipfltdata othipdata;
    } un;
    
    unsigned long saddr;
    unsigned long daddr;
    unsigned long smask;
    unsigned long dmask;
    unsigned int index;
    struct filterent *next_entry;
    struct filterent *prev_entry;
};

struct filterlist {
    struct filterent *head;
    struct filterent *tail;
    unsigned int lastpos;
};
