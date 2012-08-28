/*
** ATOP - System & Process Monitor
**
** The program 'atop' offers the possibility to view the activity of
** the system on system-level as well as process-level.
**
** Include-file describing system-level counters maintained.
** ================================================================
** Author:      Gerlof Langeveld - AT Computing, Nijmegen, Holland
** E-mail:      gerlof@ATComputing.nl
** Date:        November 1996
** LINUX-port:  June 2000
**
** This program is free software; you can redistribute it and/or modify it
** under the terms of the GNU General Public License as published by the
** Free Software Foundation; either version 2, or (at your option) any
** later version.
**
** This program is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
*/
#define	MAXCPU		64
#define	MAXDSK		128
#define	MAXDKNAM	32
#define	MAXINTF		32

/************************************************************************/

struct	memstat {
	count_t	physmem;	/* number of physical pages 	*/
	count_t	freemem;	/* number of free     pages	*/
	count_t	buffermem;	/* number of buffer   pages	*/
	count_t	slabmem;	/* number of slab     pages	*/
	count_t	cachemem;	/* number of cache    pages	*/
	count_t	committed;	/* number of reserved pages	*/

	count_t	swouts;		/* number of pages swapped out	*/
	count_t	swins;		/* number of pages swapped in	*/

	count_t	totswap;	/* number of pages in swap	*/
	count_t	freeswap;	/* number of free swap pages	*/
	count_t	pgscans;	/* number of page scans		*/
	count_t	commitlim;	/* commit limit 		*/
	count_t	allocstall;	/* try to free pages forced	*/
	count_t	future1;	/* reserved for future use	*/
	count_t	future2;	/* reserved for future use	*/
	count_t	future3;	/* reserved for future use	*/
};

/************************************************************************/

struct	netstat {
	count_t	tcpin;	/* TCP received packets			*/
	count_t	tcpout;	/* TCP transmitted packets		*/

	count_t	udpin;	/* UDP received packets			*/
	count_t	udpout;	/* UDP transmitted packets		*/

	count_t	ipin;	/* IP  received packets			*/
	count_t	ipout;	/* IP  transmitted packets		*/
	count_t	ipindel;/* IP  locally delivered packets	*/
	count_t	ipfrw;	/* IP  forwarded packets		*/
	count_t	future1;	/* reserved for future use	*/
	count_t	future2;	/* reserved for future use	*/
	count_t	future3;	/* reserved for future use	*/
};

/************************************************************************/

struct percpu {
	int	cpunr;
	count_t	stime;	/* system  time in clock ticks		*/
	count_t	utime;	/* user    time in clock ticks		*/
	count_t	ntime;	/* nice    time in clock ticks		*/
	count_t	itime;	/* idle    time in clock ticks		*/
	count_t	wtime;	/* iowait  time in clock ticks		*/
	count_t	Itime;	/* irq     time in clock ticks		*/
	count_t	Stime;	/* softirq time in clock ticks		*/
	count_t	future1;	/* reserved for future use	*/
	count_t	future2;	/* reserved for future use	*/
	count_t	future3;	/* reserved for future use	*/
};

struct	cpustat {
	count_t	devint;	/* number of device interrupts 		*/
	count_t	csw;	/* number of context switches		*/
	count_t	nrcpu;	/* number of cpu's 			*/
	float	lavg1;	/* load average last    minute          */
	float	lavg5;	/* load average last  5 minutes         */
	float	lavg15;	/* load average last 15 minutes         */
	count_t	future1;	/* reserved for future use	*/
	count_t	future2;	/* reserved for future use	*/
	count_t	future3;	/* reserved for future use	*/

	struct percpu   all;
	struct percpu   cpu[MAXCPU];
};

/************************************************************************/

struct	perxdsk {
        char	name[MAXDKNAM];	/* empty string for last        */
        count_t	nread;	/* number of read  transfers            */
        count_t	nrblk;	/* number of sectors read               */
        count_t	nwrite;	/* number of write transfers            */
        count_t	nwblk;	/* number of sectors written            */
        count_t	io_ms;	/* number of millisecs spent for I/O    */
        count_t	avque;	/* average queue length                 */
	count_t	future1;	/* reserved for future use	*/
	count_t	future2;	/* reserved for future use	*/
	count_t	future3;	/* reserved for future use	*/
};

struct xdskstat {
	int		nrxdsk;
	struct perxdsk	xdsk[MAXDSK];
};

/************************************************************************/

struct	perintf {
        char	name[16];	/* empty string for last        */
        count_t	rbyte;	/* number of read bytes                 */
        count_t	rpack;	/* number of read packets               */
        count_t	sbyte;	/* number of written bytes              */
        count_t	spack;	/* number of written packets            */
	long 	speed;	/* interface speed in megabits/second	*/
	char	duplex;	/* full duplex (boolean) 		*/
	count_t	future2;	/* reserved for future use	*/
	count_t	future3;	/* reserved for future use	*/
};

struct intfstat {
	int		nrintf;
	struct perintf	intf[MAXINTF];
};


/************************************************************************/
/************************************************************************/

struct	sstat {
	struct cpustat	cpu;
	struct memstat	mem;
	struct netstat	net;
	struct intfstat	intf;
	struct xdskstat xdsk;
};

/*
** prototypes
*/
void	photosyst (struct sstat *);
void	deviatsyst(struct sstat *, struct sstat *, struct sstat *);
