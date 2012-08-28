#include <cassert>
#include <unistd.h>
#include "IPv4TCPPacket.h"
#include "TCPPacket.h"
#include "headers.h"

IPv4TCPPacket::IPv4TCPPacket( const u_char *data, unsigned int data_len )
	: IPv4Packet( data, data_len )
{
	assert(theproto==IPPROTO_TCP);
	tcppkt=new TCPPacket(data+IP_HEADER_LEN,data_len-IP_HEADER_LEN);
}

IPv4TCPPacket::IPv4TCPPacket( const IPv4TCPPacket & orig )
	: IPv4Packet( orig )
{
	tcppkt = new TCPPacket( orig.tcp() );
}

IPv4TCPPacket::~IPv4TCPPacket()
{
	delete tcppkt;
}
