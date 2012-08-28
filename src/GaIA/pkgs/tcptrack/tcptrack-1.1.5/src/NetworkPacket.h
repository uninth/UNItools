#ifndef NETWORKPACKET_H
#define NETWORKPACKET_H 1

#include <stdio.h>
#include <netinet/in.h> // neeeded for u_char

class NetworkPacket
{
public:
	virtual unsigned long len() const = 0;
	//static void f();
	static NetworkPacket * newPacket(const u_char *data,
	                                 unsigned int data_len, 
	                                 int proto);
private:
};

#endif
