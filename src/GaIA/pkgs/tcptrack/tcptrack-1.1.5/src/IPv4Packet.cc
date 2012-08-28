#include <cassert>
#include <iostream>
#include <unistd.h>
#include "IPv4Packet.h"
#include "headers.h"
#include "util.h"
#include "TCPPacket.h"
#include "IPv4TCPPacket.h"

IPv4Packet::IPv4Packet( const u_char *data, unsigned int data_len )
{
	struct sniff_ip *ip = (struct sniff_ip *)data;

	assert( ip->ip_v == 4 ); // this class only handles v4, v6 elsewhere.

	// make sure that the various length fields are long enough to contain
	// an IPv4 header (at least 20 bytes).
	assert( data_len >= 20 ); 
	assert( ntohs(ip->ip_len) >= 20 ); // TODO: is this right?
	assert( ip->ip_hl >= 5 );

	total_len=ntohs(ip->ip_len);
	theproto=ip->ip_p;
	src=new IPv4Address(ip->ip_src);
	dst=new IPv4Address(ip->ip_dst);
	header_len=ip->ip_hl*4;
	
}

IPv4Packet::IPv4Packet( const IPv4Packet &orig )
{
	src = new IPv4Address( orig.srcAddr() );
	dst = new IPv4Address( orig.dstAddr() );
	total_len = orig.total_len;
	header_len = orig.header_len;
	theproto = orig.theproto;
}

IPv4Packet::~IPv4Packet()
{
	delete src;
	delete dst;
}


proto_t IPv4Packet::proto() const { return theproto; }
unsigned int IPv4Packet::totalLen() const { return total_len; }
IPv4Address & IPv4Packet::srcAddr() const { return *src; }
IPv4Address & IPv4Packet::dstAddr() const { return *dst; }
version_t IPv4Packet::version() const { return 4; }

ostream & operator<<( ostream &out, const IPv4Packet &ipv4p )
{
	out << "IP: ";
	out << "src=" << ipv4p.srcAddr();
	out << " dst=" << ipv4p.dstAddr();
	out << " len=" << ipv4p.totalLen();
	return out;
}

unsigned int IPv4Packet::payloadLen() const
{
	return total_len-header_len;
}

IPv4Packet * IPv4Packet::newPacket( const u_char *data, unsigned int data_len )
{
	struct sniff_ip *ip = (struct sniff_ip *)data;
	if( ip->ip_p == IPPROTO_TCP ) 
		return new IPv4TCPPacket(data,data_len);
	else
		return new IPv4Packet(data,data_len);	
}
