#ifndef IPV4TCPPACKET_H
#define IPV4TCPPACKET_H 1

#include "IPv4Packet.h"
#include <netinet/in.h> // neeeded
#include "TCPPacket.h"
#include "SocketPair4.h"

// an IPv4TCPPacket is a specific kind of IPv4Packet which is known to have
// a TCP payload.
class IPv4TCPPacket : public IPv4Packet
{
public:
	IPv4TCPPacket( const u_char *data, unsigned int data_len );
	IPv4TCPPacket( const IPv4TCPPacket & orig );
	TCPPacket & tcp() const { return *tcppkt; };
	~IPv4TCPPacket();
	SocketPair4 sockpair() const { return SocketPair4(srcAddr(),tcp().srcPort(),dstAddr(),tcp().dstPort()); };
private:
	TCPPacket *tcppkt;
};


#endif
