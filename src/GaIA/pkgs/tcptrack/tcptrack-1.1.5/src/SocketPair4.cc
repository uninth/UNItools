#include <unistd.h>
#include "IPv4Address.h"
#include "TCPPacket.h"
#include "SocketPair4.h"

SocketPair4::SocketPair4( IPv4Address &naddra, portnum_t nporta,  
                          IPv4Address &naddrb, portnum_t nportb )
{
	addra=new IPv4Address(naddra);
	addrb=new IPv4Address(naddrb);
	porta=nporta;
	portb=nportb;
}

SocketPair4::SocketPair4( const SocketPair4 &orig )
{
	addra=new IPv4Address( *(orig.addra) );
	addrb=new IPv4Address( *(orig.addrb) );
	porta=orig.porta;
	portb=orig.portb;
}

SocketPair4::~SocketPair4()
{
	delete addra;
	delete addrb;
}

// a socketpair is equal to another SocketPair4 if their src/dst addrs & ports
// are the same, OR if they are just the opposite (ie, if it were for a 
// packet heading in the opposite direction).
// this is so packets heading in either direction will match the same 
// connection.
bool SocketPair4::operator==( const SocketPair4 &sp ) const
{
	if( *(sp.addra) == *(addra)  &&  *(sp.addrb) == *(addrb) &&
	    sp.porta == porta && sp.portb == portb )
	{
		return true;
	} 
	else if( *(sp.addra) == *(addrb)  &&  *(sp.addrb) == *(addra) &&
	    sp.porta == portb && sp.portb == porta )
	{
		return true;
	}
	else
		return false;
}

bool SocketPair4::operator!=( const SocketPair4 &sp ) const
{
	return !( sp==*this );
}
