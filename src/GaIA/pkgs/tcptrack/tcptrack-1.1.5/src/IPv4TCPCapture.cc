#include <typeinfo>
#include <cassert>
#include <typeinfo>
#include <unistd.h>
#include <sys/time.h>
#include "NetworkPacket.h"
#include "IPv4TCPCapture.h"
#include "IPv4Packet.h"
#include "IPv4TCPPacket.h"
#include "util.h"

IPv4TCPCapture::IPv4TCPCapture( const u_char *data,
	                            unsigned int data_len,
                                struct timeval nts )
{
	NetworkPacket *np = NetworkPacket::newPacket(data, data_len, NLP_IPV4);
	assert( typeid(*np)==typeid(IPv4TCPPacket) );
	p=(IPv4TCPPacket *)np;
	ts=nts;
}

IPv4TCPCapture::IPv4TCPCapture( const IPv4TCPCapture & orig )
{
	p = new IPv4TCPPacket( *(orig.p) );
	ts = orig.ts;
}

IPv4TCPCapture::~IPv4TCPCapture()
{
	if( p!=NULL)
		delete p;
}

IPv4TCPPacket & IPv4TCPCapture::ipv4() const
{
	return *p;
}

