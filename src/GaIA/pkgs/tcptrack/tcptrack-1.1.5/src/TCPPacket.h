#ifndef TCPPACKET_H
#define TCPPACKET_H 1
#define __FAVOR_BSD 1

#include <netinet/in.h>

/* 
 * If you're wondering why this doesn't inherit from IPv4Packet: TCP over
 * IPv4 is the same as over IPv6. A packet containing a TCP header isn't
 * neccessarily a kind of IPv4 Packet. tcptrack doesn't do IPv6 yet, but it
 * will at some point. When it does this class will be used by IPv4Packet
 * and IPv6Packet.
 */

using namespace std;

typedef unsigned short portnum_t;
typedef unsigned int   seq_t;

#define FIN 0x01
#define SYN 0x02
#define RST 0x04
#define PSH 0x08
#define ACK 0x10
#define URG 0x20
#define ECE 0x40
#define CWR 0x80

class TCPPacket
{
public:
	TCPPacket::TCPPacket( const u_char *data, unsigned int data_len );
	TCPPacket::TCPPacket( TCPPacket & orig );
	seq_t TCPPacket::getSeq() const;
	seq_t TCPPacket::getAck() const;
	bool isFlagSet(unsigned int);
	unsigned short headerLen() const { return header_len; };

	portnum_t srcPort() const;
	portnum_t dstPort() const;

	bool TCPPacket::fin() const;
	bool TCPPacket::syn() const;
	bool TCPPacket::rst() const;
	bool TCPPacket::psh() const;
	bool TCPPacket::ack() const;
	bool TCPPacket::urg() const;
	bool TCPPacket::ece() const;
	bool TCPPacket::cwr() const;

	friend ostream & operator<<( ostream &, const TCPPacket &);
private:

	seq_t seqn;
	seq_t ackn;
	portnum_t src;
	portnum_t dst;
	unsigned char flags;
	unsigned short header_len;
};

#endif
