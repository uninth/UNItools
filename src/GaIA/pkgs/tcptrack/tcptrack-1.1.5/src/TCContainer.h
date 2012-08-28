/* 
 *  Ths code in this file is part of tcptrack. For more information see
 *    http://www.rhythm.cx/~steve/devel/tcptrack
 *
 *     Copyright (C) Steve Benson - 2003
 *
 *  tcptrack is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your
 *  option) any later version.
 *   
 *  tcptrack is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *   
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *  
 */
#ifndef TCCONTAINER_H
#define TCCONTAINER_H 1

#define _BSD_SOURCE 1
#define _REENTRANT
#include <sys/types.h>
#include <pthread.h>
#include <list>
#ifdef HAVE_HASH_MAP
#include <hash_map>
#elif HAVE_EXT_HASH_MAP
#include <ext/hash_map>
#endif
#include "headers.h"
#include "TCPConnection.h"
#include "Guesser.h"
#include "Collector.h"
#include "TCPConnection.h"
#include "SortedIterator.h"
#include "util.h"
#include "IPv4Packet.h"
#include "IPv4TCPCapture.h"
#include "SocketPair4.h"

#define TSTATE_IDLE 1
#define TSTATE_RUNNING 2
#define TSTATE_STOPPING 3
#define TSTATE_DONE 4

#ifdef GNU_CXX_NS
using namespace __gnu_cxx;
#endif


/////

class TCCEqFunc : public unary_function<SocketPair4,bool>
{
public:
	bool operator()( const SocketPair4 &sp1, const SocketPair4 &sp2 ) 
	{
		if( sp1==sp2 )
			return true;
		else
			return false;
	}
};

// TODO: banged out off the top of my head... could be improved.
class TCCHashFunc : public unary_function<SocketPair4, size_t>
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

typedef hash_map<SocketPair4, TCPConnection *, TCCHashFunc, TCCEqFunc> tccmap;

////



class TCContainer
{
	friend class SortedIterator;
	friend class TCCSnapshot;
public:
	TCContainer();
	~TCContainer();

	bool processPacket( IPv4TCPCapture &p );
	unsigned int numConnections();

	void stop();

	void lock();
	void unlock();

	// do not call. only called from maint_thread_func.
	void maint_thread_run();
	
	SortedIterator * getSortedIteratorPtr();

	// remove closed connections?
	void purge(bool npurgeflag);
private:
	// this Collector thing gets closed connections after a certain 
	// delay. Right now it just deletes them. It could log their stats
	// or something...
	Collector collector;
	
	// this is a hash table that stores all the connections we're 
	// currently tracking.
	tccmap conhash2;	
	pthread_mutex_t conlist_lock; 

	// this is for the maintenence thread, which runs regularly to
	// recalculate averages and anything else like that.
	pthread_t maint_thread_tid;
	bool run_maint_thread;

	// This thing takes stray packets (TCP packets for connections that
	// we're not tracking) and keeps track of them and tries to determine
	// the characteristics of connections that we're not keeping track of
	// (ie, connections that have no entry in conhash2). When it knows
	// a connection exists, it feeds it to TCContainer which keeps
	// track of it as usual.
	Guesser guesser;
	
	// for starting up, shutting down the maint thread.
	int state;
	pthread_mutex_t state_mutex;

	// remove closed connections? 
	bool purgeflag;
};

// maint thread main function.
void *maint_thread_func( void * arg );

#endif

