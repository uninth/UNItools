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
#include "util.h"
#include <stdio.h>
#include "headers.h"
#ifdef HAVE_HASH_MAP
# include <hash_map>
#elif HAVE_EXT_HASH_MAP
# include <ext/hash_map>
#endif

// this takes an IPv4 address (an in_addr struct) and returns it as a
// string in dotted quad form.
// dont forget to free what this returns
char * in_addr2ascii(in_addr addr)
{
	char *ascii = (char *) malloc(16); // 12 for octets, 3 dots, 1 null
	unsigned int iaddr = ntohl(addr.s_addr);

	int oc1 = (iaddr & 0xFF000000)/16777216;
	int oc2 = (iaddr & 0x00FF0000)/65536;
	int oc3 = (iaddr & 0x0000FF00)/256;
	int oc4 = (iaddr & 0x000000FF);
	sprintf(ascii,"%d.%d.%d.%d",oc1,oc2,oc3,oc4);
	return ascii;
}

/*
 * getnlp takes a raw packet (with link level header) sniffed from an 
 * interface whose type is dlt (values for dlt are the DLT_* macros in
 * net/bpf.h).
 * It returns a struct nlp, which contains a pointer to the beginning 
 * of the network layer protocol (in *p) and a value to identify the network
 * layer protocol
 */
struct nlp *getnlp( const u_char *p, int dlt, const pcap_pkthdr *pcap )
{
	struct nlp *n = (struct nlp *) malloc( sizeof(struct nlp) );
	
	n->p=NULL;
	n->proto=NLP_UNKNOWN;
	n->ts = pcap->ts;
	n->len = 0;
	
	if( dlt==DLT_EN10MB )
	{
		if( pcap->caplen < ENET_HEADER_LEN+IP_HEADER_LEN )
			return n;
		
		const struct sniff_ethernet *ethernet;
		ethernet = (struct sniff_ethernet*)(p);
		if( ethernet->ether_type==8 ) // TODO: is this defined somewhere?
		{
			n->proto = NLP_IPV4;
			n->len = pcap->caplen-ENET_HEADER_LEN;
			n->p = (u_char *) malloc( sizeof(u_char) * n->len );
			memcpy( (void *)n->p, (void *)(p+ENET_HEADER_LEN), n->len);
		}
		else
			return n;
	}
	else if( dlt==DLT_LINUX_SLL )
	{
		if( pcap->caplen < SLL_HEADER_LEN+IP_HEADER_LEN )
			return n;

		n->proto=NLP_IPV4;
		//cerr << "pcap->caplen=" << pcap->caplen << endl;
		n->len = pcap->caplen-SLL_HEADER_LEN;
		n->p = (u_char *) malloc( sizeof(u_char) * n->len );
		memcpy( (void *)n->p, (void *)(p+SLL_HEADER_LEN), n->len);
	}
	else if( dlt==DLT_RAW || dlt==DLT_NULL )
	{
		if( pcap->caplen < IP_HEADER_LEN )
			return n;

		n->proto=NLP_IPV4;
		n->len = pcap->caplen;
		n->p = (u_char *) malloc( sizeof(u_char) * n->len );
		memcpy( (void *)n->p, (void *)(p), n->len);
	}

	return n;
}

/* This function performs all kinds of tests on captured packet data to 
 * ensure that it is a valid packet of the given network layer protocol.
 * data is the raw packet, data_len is its length
 * proto is one of the NLP_* values. currently only NLP_IPV4 works.
 * This needs to be run early upon packet reception. Other code assumes it 
 * has. If they detect a bad packet, assertions will fail.
 */
// TODO: this should be split up into smaller functions
bool checknlp( struct nlp *n )
{
	if( n->proto != NLP_IPV4 ) // IPv6 not yet supported
		return false;
	
	// not enough data to do anything with this...
	// we're only interested in IPv4 TCP Packets
	if( n->len < IP_HEADER_LEN+TCP_HEADER_LEN )
		return false;
	
	struct sniff_ip *ip = (struct sniff_ip *)n->p;
	
	if( ntohs(ip->ip_len) < IP_HEADER_LEN+TCP_HEADER_LEN ) 
		return false;

	if( ip->ip_hl < 5 ) 
		return false;
	
	if( ip->ip_p != IPPROTO_TCP ) 
		return false;

	struct sniff_tcp *tcp = (struct sniff_tcp *) (n->p+IP_HEADER_LEN);
	
	if( tcp->th_off < 5 ) // tcp header is at least 20 bytes long.
		return false;

	return true;
}
