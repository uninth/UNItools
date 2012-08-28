#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H 1

#include <netinet/in.h>
#include <iostream>

using namespace std;

class IPv4Address
{
public:
	IPv4Address(struct in_addr na) { a=na; }
	IPv4Address(IPv4Address &na) { a=na.toStruct(); }
	bool operator==( const IPv4Address & ) const;
	bool operator!=( const IPv4Address & ) const;
	char * IPv4Address::ptr() const;
	friend ostream & operator<<( ostream &, const IPv4Address &);
	struct in_addr toStruct() const;
private:
	struct in_addr a;
};

#endif
