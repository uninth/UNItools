#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "IPv4Address.h"
#include "util.h"

// this function is used for C functions that need a C-style string.
char * IPv4Address::ptr() const
{
	static char ascii[16]; // 12 for octets, 3 dots, 1 null

	unsigned int iaddr = ntohl(a.s_addr);
	int oc1 = (iaddr & 0xFF000000)/16777216;
	int oc2 = (iaddr & 0x00FF0000)/65536;
	int oc3 = (iaddr & 0x0000FF00)/256;
	int oc4 = (iaddr & 0x000000FF);

	sprintf(ascii,"%d.%d.%d.%d",oc1,oc2,oc3,oc4);

	return ascii;	
}

bool IPv4Address::operator==( const IPv4Address & ipv4a ) const
{
	if( ipv4a.a.s_addr == a.s_addr ) 
		return true;
	else
		return false;
}

ostream &operator<<( ostream &out, const IPv4Address &ipv4a )
{
	unsigned int iaddr = ntohl(ipv4a.a.s_addr);
	int oc1 = (iaddr & 0xFF000000)/16777216;
	int oc2 = (iaddr & 0x00FF0000)/65536;
	int oc3 = (iaddr & 0x0000FF00)/256;
	int oc4 = (iaddr & 0x000000FF);
	out << oc1 << "." << oc2 << "." << oc3 << "." << oc4;
}

struct in_addr IPv4Address::toStruct() const
{
	return a;
}
