#ifndef GUESSER_H
#define GUESSER_H 1

#include "../config.h"
#ifdef HAVE_HASH_MAP
#include <hash_map>
#elif HAVE_EXT_HASH_MAP
#include <ext/hash_map>
#endif
#include "SocketPair4.h"
#include "util.h"
#include "TCPConnection.h"
#include "IPv4TCPCapture.h"

#ifdef GNU_CXX_NS
using namespace __gnu_cxx;
#endif

class GEqFunc : public unary_function<SocketPair4,bool>
{
public:
	bool operator()( const SocketPair4 &sp1, const SocketPair4 & sp2 )
	{
		if( sp1==sp2 )
			return true;
		else
			return false;
	}
};

// TODO: banged out off the top of my head... could be improved.
class GHashFunc : public unary_function<SocketPair4, size_t>
{
public:
	size_t operator()(const SocketPair4 &sp) const
	{
		size_t rv=0;
		if( sp.portB() > 0 )
			rv = sp.addrA().toStruct().s_addr % sp.portB();
		else
			rv = sp.addrA().toStruct().s_addr;
		rv >> 4;
		if( sp.portA() > 0 )
			rv += sp.addrB().toStruct().s_addr % sp.portA();
		else
			rv += sp.addrB().toStruct().s_addr;
		return rv;
	}
};

typedef hash_map<SocketPair4, IPv4TCPCapture *,GHashFunc, GEqFunc> pktmap;

/* Guesser implements the 'detect connections that started before
 * tcptrack was started' functionality.
 * The Guesser takes TCP packets that don't belong to any known 
 * connection and stores them. As it is fed more stray packets, it may
 * detect a TCP connection on the network.
 */

class Guesser
{
public:
	Guesser();
	~Guesser();

	// feed Guesser a stray packet. If it results in a connection
	// detected, it will be returned. If no new connections, NULL 
	// is returned.
	TCPConnection * addPacket( IPv4TCPCapture &p );
private:
	// stray packets that we're keeping track of are stored here.
	// indexed by src/dst addrs and ports.
	pktmap hash;
};

#endif
