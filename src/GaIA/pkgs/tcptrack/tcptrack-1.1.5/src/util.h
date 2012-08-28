/* 
 *  Ths code in this file is part of tcptrack. For more information see
 *    http://www.rhythm.cx/~steve/devel/tcptrack
 *
 *     Copyright (C) Steve Benson - 2003
 *
 *  tcptrack is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your
 *  option) any later version.
 *   
 *  tcptrack is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *   
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *  
 */
#ifndef UTIL_H
#define UTIL_H 1
 
#include "../config.h"
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <list>
#ifdef HAVE_PCAP_PCAP_H
#include <pcap/pcap.h>
#elif HAVE_PCAP_H
#include <pcap.h>
#endif
#ifdef HAVE_HASH_MAP
#include <hash_map>
#elif HAVE_EXT_HASH_MAP
#include <ext/hash_map>
#endif
#include "headers.h"
#include "IPv4Address.h"
#include "TCPPacket.h"

char * in_addr2ascii(in_addr addr);

struct config
{
	char *iface; // interface to listen on
	char *fexp;  // filter expression
	unsigned int remto; // timeout to remove closed connections (secs)
	bool fastmode; // faster average recalculation (more than once/sec).
	bool detect; // detect pre-existing connections?
        bool promisc; // enable promisc mode?	        
};

struct avgstat
{
	struct timeval ts;
	unsigned int size;
};

#define NLP_UNKNOWN 0
#define NLP_IPV4 1

struct nlp
{
	u_char *p; // dont forget to free this!
	unsigned int proto;
	unsigned int len;
	struct timeval ts;
};

struct nlp *getnlp( const u_char *p, int dlt, const pcap_pkthdr *pcap );
bool checknlp( struct nlp *n );

#endif
