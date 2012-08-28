#ifndef SOCKETPAIR4_H
#define SOCKETPAIR4_H

#include "IPv4Address.h"
#include "TCPPacket.h"

// a SocketPair4 is the combination of source/dest ports and addrs.
// it is used as a fingerprint to identify connections.

class SocketPair4
{
public:
	SocketPair4( IPv4Address &naddra, portnum_t nporta, 
	             IPv4Address &naddrb, portnum_t nportb );
	SocketPair4( const SocketPair4 & );
	~SocketPair4();
	bool operator==( const SocketPair4 & ) const;
	bool operator!=( const SocketPair4 & ) const;
	IPv4Address & addrA() const { return *addra; };
	IPv4Address & addrB() const { return *addrb; };
	portnum_t portA() const { return porta; };
	portnum_t portB() const { return portb; };
private:
	IPv4Address *addra;
	IPv4Address *addrb;
	portnum_t porta;
	portnum_t portb;
};

#endif
