#ifndef IPV4PACKET_H
#define IPV4PACKET_H 1
#define __FAVOR_BSD 1

#include <netinet/in.h> // neeeded 
#include "IPv4Address.h"
#include "TCPPacket.h"
#include "NetworkPacket.h"
//#include "IPv4TCPPacket.h"

typedef unsigned char  proto_t;
typedef unsigned char  version_t;

class IPv4TCPPacket;

class IPv4Packet : public NetworkPacket
{
public:
	/* stuff to do in constructor:
	 *  ensure data_len >= ip header len field
	 *  ensure version is 4
	 *  ensure total len >= ip header len
	 *  verify checksum
	 */
	IPv4Packet( const u_char *data, unsigned int data_len );
	IPv4Packet( const IPv4Packet &orig );
	~IPv4Packet();
	unsigned int totalLen() const;
	proto_t proto() const;
	version_t version() const; // always return 4
	unsigned long len() const { return total_len; };
	unsigned int payloadLen() const;
	IPv4Address & srcAddr() const;
	IPv4Address & dstAddr() const;
	

	friend ostream & operator<<( ostream &, const IPv4Packet &);

	// public methods below here = unimplemented
	
	/*
	unsigned int getHeaderLen(); // in bytes
	unsigned int getTOS();
	unsigned short getID();
	unsigned int getTTL();
	bool isMoreSet();
	bool isNoFragSet();
	bool isUnusedSet();
	*/

	static IPv4Packet * newPacket( const u_char *data, unsigned int data_len );

//private:
protected:
	unsigned int total_len;
	unsigned short header_len;
	proto_t theproto;
	
	// these are pointers because the IPv4Address class is not modifiable
	// after initialization. The constructor of this class can not 
	// immediately set them.
	IPv4Address *src;
	IPv4Address *dst;
	
};


#endif
