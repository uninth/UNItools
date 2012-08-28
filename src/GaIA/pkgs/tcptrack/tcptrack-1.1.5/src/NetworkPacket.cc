#include <cassert>
#include <unistd.h>
#include "NetworkPacket.h"
#include "IPv4Packet.h"
#include "util.h"

// given the raw packet as sniffed off the wire (minus link layer header,
// that was parsed off in Sniffer),
// return an appropriate NetworkPacket which is the network layer packet.
// NetworkPacket is an abstract class which has children IPv4Packet and 
// IPv6Packet (todo).
NetworkPacket *NetworkPacket::newPacket( const u_char *data, 
                                         unsigned int data_len,
                                         int proto )
{
	// in the future, there will be an NLP_IPv6...
	// but for now, only IPv4 is supported.
	// asserting this because Sniffer should have dopped any
	// non-IPv4 packets. If they made it this far, it must be a bug.
	assert( proto==NLP_IPV4 );

	NetworkPacket *p = IPv4Packet::newPacket(data,data_len);
	return p;
}

