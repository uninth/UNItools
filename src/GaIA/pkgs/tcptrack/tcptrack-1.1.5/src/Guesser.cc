#include <iostream>
#include "IPv4TCPCapture.h"
#include "Guesser.h"

Guesser::Guesser()
{
}

Guesser::~Guesser()
{
	for( pktmap::iterator i=hash.begin(); i!=hash.end(); )
	{
		IPv4TCPCapture *cp = (*i).second;
		pktmap::iterator tmp_i = i;
		i++;
		hash.erase(tmp_i);
		delete cp;
	}
}

TCPConnection * Guesser::addPacket( IPv4TCPCapture &p )
{
	// TODO: there should be a thread or something that periodically
	// checks hash for the age of the packets it contains and removes 
	// old stuff.

	// TCP Packets with the following flags set will not trigger the
	// detection of a new connection.
	if( p.ipv4().tcp().syn() )
		return NULL;
	if( p.ipv4().tcp().ece() )
		return NULL;
	if( p.ipv4().tcp().fin() || p.ipv4().tcp().rst() )
	{
		hash.erase(p.ipv4().sockpair());
		return NULL;
	}
	

	if( hash[p.ipv4().sockpair()]==NULL )
	{
		// no packets received yet for this connection
		IPv4TCPCapture *cp = new IPv4TCPCapture(p);
		hash[cp->ipv4().sockpair()]=cp;

		
		return NULL;
	}
	else
	{
		// already received a packet for this connection.
		// replace the old with the new. (remove later)
		// return a connection.

		IPv4TCPCapture *ocp = hash[p.ipv4().sockpair()];
		hash.erase(p.ipv4().sockpair());


		if(    ( ocp->ipv4().srcAddr() == p.ipv4().dstAddr() )
		    && ( ocp->ipv4().tcp().srcPort() == p.ipv4().tcp().dstPort() ) 
		    && ( p.timestamp().tv_sec-ocp->timestamp().tv_sec < 60 ) )
		{
			TCPConnection *nc;
			
			// Currently a TCPConnection expects to be built from a packet
			// that is going from the client to the server. This is because
			// the client initiates the connection and TCPConnection
			// was originally coded to only accept the initial SYN packet
			// to its constructor. At some point this logic may be
			// moved into the TCPConnection constructor.
			
			// crude way to guess at which end is the client:
			// whichever end has the lowest port number.
			// TODO: can this cli/server guessing be made more intelligent?
			if( p.ipv4().tcp().srcPort() > p.ipv4().tcp().dstPort() )
			{
				// this packet might be the one we saw that went from
				// client->server.
				nc=new TCPConnection(p);
			}
			else
			{
				// if not, maybe it was this other packet.
				nc=new TCPConnection(*ocp);
			}

			delete ocp;
			return nc;
		}
		else
		{
			hash[ocp->ipv4().sockpair()] = new IPv4TCPCapture(p);
			delete ocp;
			return NULL;
		}
	}
	
	return NULL;
}
