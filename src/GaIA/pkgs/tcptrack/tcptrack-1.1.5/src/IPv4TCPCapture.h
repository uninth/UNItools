#ifndef IPV4TCPCAPTURE_H
#define IPV4TCPCAPTURE_H 1

#include <sys/time.h>
#include "NetworkPacket.h"
#include "IPv4Packet.h"
#include "IPv4TCPPacket.h"

/* An IPv4TCPCapture is a packet captured off the wire that is known to be
 * an IPv4/TCP packet
 */
// TODO: Make this properly extend CapturedPacket
class IPv4TCPCapture
{
public:
	IPv4TCPCapture( const u_char *data,
	                unsigned int data_len,
	                struct timeval nts );
	IPv4TCPCapture( const IPv4TCPCapture &orig );
	~IPv4TCPCapture();
	IPv4TCPPacket & ipv4() const;
	struct timeval timestamp() const { return ts; };
private:
	IPv4TCPPacket *p;	
	struct timeval ts;
};

#endif
