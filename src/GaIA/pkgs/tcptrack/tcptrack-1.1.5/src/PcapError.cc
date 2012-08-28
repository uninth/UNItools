#include <string>
#include <cassert>
#include <iostream>
#include "PcapError.h"

using namespace std;

PcapError::PcapError( char *func, char *errbuf )
{
	f=func;
	e=errbuf;
}

PcapError::PcapError( const PcapError &oe )
{
	f=oe.f;
	e=oe.e;
}

string PcapError::msg() const
{
	return f+": "+e;
}
