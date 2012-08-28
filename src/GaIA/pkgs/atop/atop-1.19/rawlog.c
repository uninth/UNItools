/*
** ATOP - System & Process Monitor
**
** The program 'atop' offers the possibility to view the activity of 
** the system on system-level as well as process-level.
**
** This source-file contains the 
** ==========================================================================
** Author:      Gerlof Langeveld - AT Computing, Nijmegen, Holland
** E-mail:      gerlof@ATComputing.nl
** Date:        September 2002
** --------------------------------------------------------------------------
** Copyright (C) 2000-2005 Gerlof Langeveld
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
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
** --------------------------------------------------------------------------
**
** $Log: rawlog.c,v $
** Revision 1.15  2006/01/30 09:12:34  gerlof
** Minor bug-fix.
**
** Revision 1.14  2005/10/21 09:50:36  gerlof
** Per-user accumulation of resource consumption.
**
** Revision 1.13  2004/12/14 15:06:23  gerlof
** Implementation of patch-recognition for disk and network-statistics.
**
** Revision 1.12  2004/05/06 09:47:36  gerlof
** Ported to kernel-version 2.6.
**
** Revision 1.11  2003/07/07 09:26:48  gerlof
** Cleanup code (-Wall proof).
**
** Revision 1.10  2003/07/03 12:04:11  gerlof
** Implemented subcommand `r' (reset).
**
** Revision 1.9  2003/06/27 12:32:48  gerlof
** Removed rawlog compatibility.
**
** Revision 1.8  2003/02/06 14:08:33  gerlof
** Cosmetic changes.
**
** Revision 1.7  2003/01/17 07:33:39  gerlof
** Modified process statistics: add command-line.
** Implement compatibility for old pstat-structure read from logfiles.
**
** Revision 1.6  2002/10/30 13:46:11  gerlof
** Generate notification for statistics since boot.
** Adapt interval from ushort to ulong (bug-solution);
** this results in incompatible logfile but old logfiles can still be read.
**
** Revision 1.5  2002/10/24 12:22:25  gerlof
** In case of writing a raw logfile:
** If the logfile already exists, append new records to the existing file.
** If the logfile does not yet exist, create it.
**
** Revision 1.4  2002/10/08 11:35:22  gerlof
** Modified storage of raw filename.
**
** Revision 1.3  2002/10/03 10:41:51  gerlof
** Avoid end-less loop when using end-time specification (flag -e).
**
** Revision 1.2  2002/09/17 13:17:01  gerlof
** Allow key 'T' to be pressed to view previous sample in raw file.
**
**
*/

static const char rcsid[] = "$Id$";

#include <sys/types.h>
#include <sys/param.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <sys/utsname.h>
#include <string.h>
#include <zlib.h>

#include "atop.h"
#include "photoproc.h"
#include "photosyst.h"

#define	BASEPATH	"/var/log/atop/"  

/*
** argument values and global variables
*/
extern unsigned long	interval;
extern struct utsname	utsname;
extern char		rawname[];

extern int		osrel;
extern int		osvers;
extern int		ossub;

/*
** structure which describes the raw file contents
**
** layout raw file:    rawheader
**
**                     rawrecord                           \
**                     compressed system-level statistics   | sample 1
**                     compressed process-level statistics /
**
**                     rawrecord                           \
**                     compressed system-level statistics   | sample 2
**                     compressed process-level statistics /
**
** etcetera .....
*/
#define	MYMAGIC		(unsigned int) 0xfeedbeef

struct rawheader {
	unsigned int	magic;
	unsigned short	sstatlen;
	unsigned short	pstatlen;
	unsigned short	rawreclen;
	char		acctfd;
	char		kernpatch;
	int		osrel;
	int		osvers;
	int		ossub;
	char		node[32];
	char		reserved[16];
};

struct rawrecord {
	time_t		curtime;	/* current time (epoch)         */
	unsigned int	interval;	/* interval (number of seconds) */
	unsigned short	flags;		/* various flags                */
	unsigned short	nlist;		/* number of processes in list  */
	unsigned short	npresent;	/* total number of processes    */
	unsigned short	nexit;		/* number of exited processes   */
	unsigned short	nzombie;	/* number of zombie processes   */
	unsigned short	scomplen;	/* length of compressed sstat   */
	unsigned int	pcomplen;	/* length of compressed pstat's */
	unsigned char	reserved[4];	/* future extensions            */
};

#define	RRBOOT	0x0001	/* rawrecord.flags				*/

static int	getrawrec  (int, struct rawrecord *, int);
static int	getrawsstat(int, struct sstat *, int, int);
static int	getrawpstat(int, struct pstat *, int, int, int);
static int	rawwopen(void);
static int	lookslikedatetome(char *);

/*
** write a raw record to file
** (file is opened/created during the first call)
*/
char
rawwrite(time_t curtime, int numsecs, 
	 struct sstat *ss, struct pstat *ps,
	 int nlist, int npresent, int nzombie,
	 int nexit, char bootflag)
{
	static int		rawfd = -1;
	struct rawrecord	rr;

	Byte			scompbuf[sizeof(struct sstat)], *pcompbuf;
	unsigned long		scomplen = sizeof scompbuf;
	unsigned long		pcomplen = sizeof(struct pstat) * nlist;

	/*
	** first call:
	**	take care that the log file is opened
	*/
	if (rawfd == -1)
		rawfd = rawwopen();

	/*
	** compress system- and process-level statistics
	*/
	(void) compress(scompbuf, &scomplen,
				(Byte *)ss, (unsigned long)sizeof *ss);

	pcompbuf = malloc(pcomplen);

	(void) compress(pcompbuf, &pcomplen,
				(Byte *)ps, (unsigned long)pcomplen);

	/*
	** fill record header and write to file
	*/
	rr.curtime	= curtime;
	rr.interval	= numsecs;
	rr.flags	= 0;
	rr.nlist	= nlist;
	rr.npresent	= npresent;
	rr.nzombie	= nzombie;
	rr.nexit	= nexit;
	rr.scomplen	= scomplen;
	rr.pcomplen	= pcomplen;

	memset(rr.reserved, 0, sizeof rr.reserved);

	if (bootflag)
		rr.flags |= RRBOOT;

	if ( write(rawfd, &rr, sizeof rr) == -1)
	{
		fprintf(stderr, "%s - ", rawname);
		perror("write raw record");
		cleanstop(7);
	}

	/*
	** write compressed system status structure to file
	*/
	if ( write(rawfd, scompbuf, scomplen) == -1)
	{
		fprintf(stderr, "%s - ", rawname);
		perror("write raw status record");
		cleanstop(7);
	}

	/*
	** write compressed list of process status structures to file
	*/
	if ( write(rawfd, pcompbuf, pcomplen) == -1)
	{
		fprintf(stderr, "%s - ", rawname);
		perror("write raw process record");
		cleanstop(7);
	}

	free(pcompbuf);

	return '\0';
}


/*
** open a raw file for writing
**
** if the raw file exists already:
**    - read and validate the header record (be sure it is an atop-file)
**    - seek to the end of the file
**
** if the raw file does not yet exist:
**    - create the raw file
**    - write a header record
**
** return the filedescriptor of the raw file
*/
static int
rawwopen()
{
	struct rawheader	rh;
	extern int		acctfd;
	int			fd;

	/*
	** check if the file exists already
	*/
	if ( (fd = open(rawname, O_RDWR)) >= 0)
	{
		/*
		** read and verify header record
		*/
		if ( read(fd, &rh, sizeof rh) < sizeof rh)
		{
			fprintf(stderr, "%s - cannot read header\n", rawname);
			cleanstop(7);
		}

		if ( rh.magic		!= MYMAGIC			||
		     rh.sstatlen	!= sizeof(struct sstat)		||
		     rh.pstatlen	!= sizeof(struct pstat)		||
		     rh.rawreclen	!= sizeof(struct rawrecord)	||
		     rh.acctfd		!= acctfd			||
		     rh.kernpatch	!= kernpatch			  )
		{
			fprintf(stderr,
				"%s exists and has incompatible header\n",
				rawname);
			cleanstop(7);
		}

		(void) lseek(fd, (off_t) 0, SEEK_END);

		return fd;
	}

	/*
	** file does not exist already (or can not be opened)
	*/
	if ( (fd = creat(rawname, 0666)) == -1)
	{
		fprintf(stderr, "%s - ", rawname);
		perror("create raw file");
		cleanstop(7);
	}

	rh.magic	= MYMAGIC;
	rh.sstatlen	= sizeof(struct sstat);
	rh.pstatlen	= sizeof(struct pstat);
	rh.rawreclen	= sizeof(struct rawrecord);
	rh.acctfd	= acctfd;
	rh.kernpatch	= kernpatch;
	rh.osrel	= osrel;
	rh.osvers	= osvers;
	rh.ossub	= ossub;

	strncpy(rh.node, utsname.nodename, sizeof rh.node);
	rh.node[sizeof rh.node -1] = '\0';

	memset(rh.reserved, 0, sizeof rh.reserved);

	if ( write(fd, &rh, sizeof rh) == -1)
	{
		fprintf(stderr, "%s - ", rawname);
		perror("write raw header");
		cleanstop(7);
	}

	return fd;
}

/*
** read the contents of a raw file
*/
#define	OFFCHUNK	256

void
rawread(unsigned int begintime, unsigned int endtime)
{
	int			rawfd;
	extern int		acctfd;
	struct rawheader	rh;
	struct rawrecord	rr;
	struct sstat		devsstat;
	struct pstat		*devpstat;

	/*
	** variables to maintain the offsets of the raw records
	** to be able to see previous samples again
	*/
	off_t			*offlist;
	unsigned int		offsize = 0;
	unsigned int		offcur  = 0;
	char			lastcmd = 'X';

	time_t			timenow;
	struct tm		*tp;

	switch ( strlen(rawname) )
	{
	   /*
	   ** if no filename is specified, assemble the name of the raw file
	   */
	   case 0:
		timenow	= time(0);
		tp	= localtime(&timenow);

		snprintf(rawname, RAWNAMESZ, "%s/atop_%04d%02d%02d",
			BASEPATH, 
			tp->tm_year+1900,
			tp->tm_mon+1,
			tp->tm_mday);

		break;

	   /*
	   ** if date specified as filename in format YYYYMMDD, assemble
	   ** the full pathname of the raw file
	   */
	   case 8:
		if ( access(rawname, F_OK) == 0) 
			break;		/* existing file */

		if (lookslikedatetome(rawname))
		{
			char	savedname[RAWNAMESZ];

			strncpy(savedname, rawname, RAWNAMESZ-1);

			snprintf(rawname, RAWNAMESZ, "%s/atop_%s",
				BASEPATH, 
				savedname);
		}
		break;
	}

	/*
	** open raw file
	*/
	if ( (rawfd = open(rawname, O_RDONLY)) == -1)
	{
		char	command[512], tmpname1[RAWNAMESZ], tmpname2[RAWNAMESZ];

		/*
		** check if a compressed raw file is present
		*/
		snprintf(tmpname1, sizeof tmpname1, "%s.gz", rawname);

		if ( access(tmpname1, F_OK|R_OK) == -1)
		{
			fprintf(stderr, "%s - ", rawname);
			perror("open raw file");
			cleanstop(7);
		}

		/*
		** compressed raw file to be decompressed via gunzip
		*/
		fprintf(stderr, "Decompressing logfile ....\n");

		snprintf(tmpname2, sizeof tmpname2, "/tmp/atopwrk%d", getpid());
		snprintf(command,  sizeof command, "gunzip -c %s > %s",
							tmpname1, tmpname2);
		system (command);

		if ( (rawfd = open(tmpname2, O_RDONLY)) == -1)
		{
			fprintf(stderr, "%s - ", rawname);
			perror("open decompressed raw file");
			cleanstop(7);
		}

		unlink(tmpname2);
	}

	/*
	** read the raw header and verify the magic number and version
	*/
	if ( read(rawfd, &rh, sizeof rh) < sizeof rh)
	{
		fprintf(stderr, "can not read raw file header\n");
		cleanstop(7);
	}

	if (rh.magic != MYMAGIC)
	{
		fprintf(stderr, "file %s does not contain raw atop output "
				"(wrong magic number)\n", rawname);
		cleanstop(7);
	}

	strncpy(utsname.nodename, rh.node, sizeof utsname.nodename);
	utsname.nodename[sizeof utsname.nodename -1] = '\0';

	kernpatch = rh.kernpatch;
	acctfd    = rh.acctfd;
	osrel     = rh.osrel;
	osvers    = rh.osvers;
	ossub     = rh.ossub;
	interval  = 0;

	/*
	** allocate a list for backtracking of rawrecord-offsets
	*/
	offlist = malloc(sizeof(off_t) * OFFCHUNK);
	offsize = OFFCHUNK;

	*offlist = lseek(rawfd, 0, SEEK_CUR);
	offcur   = 1;

	/*
	** read a raw record header until end-of-file
	*/
	while (lastcmd && lastcmd != 'q')
	{
		while ( getrawrec(rawfd, &rr, rh.rawreclen) == rh.rawreclen)
		{
			unsigned int	secsinday = daysecs(rr.curtime);

			/*
			** store the offset of the raw record in the offset list
			** if case of offset list overflow, extend the list
			*/
			*(offlist+offcur) = lseek(rawfd, 0, SEEK_CUR) -
								rh.rawreclen;

			if ( ++offcur >= offsize )
			{
				offlist = realloc(offlist,
					     (offsize+OFFCHUNK)*sizeof(off_t));
				offsize+= OFFCHUNK;
			}
	
			/*
			** check if this sample is within the time-range
			** specified with the -b and -e flags (if any)
			*/
			if ( (begintime && begintime > secsinday) ||
			     (endtime   && endtime   < secsinday)   )
			{
				lastcmd = '\0';
				lseek(rawfd, rr.scomplen+rr.pcomplen, SEEK_CUR);
				continue;
			}
	
			/*
			** allocate space, read compressed system-level
			** statistics and decompress
			*/
			if ( !getrawsstat(rawfd, &devsstat,
						rr.scomplen, rh.sstatlen) )
				cleanstop(7);

			/*
			** allocate space, read compressed process-level
			** statistics and decompress
			*/
			devpstat  = malloc(sizeof(struct pstat) * rr.nlist);

			if ( !getrawpstat(rawfd, devpstat,
					rr.pcomplen, rh.pstatlen, rr.nlist) )
				cleanstop(7);

			/*
			** activate the installed print-function to visualize
			** the system- and process-level statistics
			*/
			lastcmd = (vis.show_samp)(rr.curtime, rr.interval,
						&devsstat,    devpstat,
					 	rr.nlist,     rr.npresent,
						rr.nzombie,   rr.nexit,
						rr.flags&RRBOOT);
	
			free(devpstat);
	
			switch (lastcmd)
			{
			   case 'T':
				if (offcur >= 2)
					offcur-= 2;
				else
					offcur = 0;
	
				lseek(rawfd, *(offlist+offcur), SEEK_SET);
				break;

			   case 'r':
				lseek(rawfd, *offlist, SEEK_SET);
				offcur = 1;
			}
		}

		if (offcur >= 1)
			offcur--;

		lseek(rawfd, *(offlist+offcur), SEEK_SET);
	}

	close(rawfd);
	cleanstop(0);
}

/*
** read the next raw record from the raw logfile
*/
static int
getrawrec(int rawfd, struct rawrecord *prr, int rrlen)
{
	int			n;

	switch ( rrlen )
	{
		/*
		** rawrecord layout identical to the one used
		** by this atop-version
		*/
	   case sizeof(struct rawrecord):
		n = read(rawfd, prr, rrlen);
		break;

	   default:
		fprintf(stderr, "raw file contains unrecognized format "
				"of record structure!\n");
		n = 0;
	}

	return n;
}

/*
** read the system-level statistics from the current offset
*/
static int
getrawsstat(int rawfd, struct sstat *sp, int complen, int sslen)
{
	Byte			*compbuf;
	unsigned long		uncomplen;

	compbuf = malloc(complen);

	if ( read(rawfd, compbuf, complen) < complen)
		return 0;

	switch (sslen)
	{
	   case sizeof(struct sstat):
		uncomplen = sslen;
		(void) uncompress((Byte *)sp, &uncomplen, compbuf, complen);
		free(compbuf);
		break;

	   default:
		fprintf(stderr, "raw file contains unrecognized format "
				"of system statistics!\n");
		free(compbuf);
		return 0;
	}

	return 1;
}

/*
** read the process-level statistics from the current offset
*/
static int
getrawpstat(int rawfd, struct pstat *pp, int complen, int pslen, int nlist)
{
	Byte			*compbuf;
	unsigned long		uncomplen = pslen * nlist;

	compbuf   = malloc(complen);

	if ( read(rawfd, compbuf, complen) < complen)
		return 0;

	switch (pslen)
	{
	   case sizeof(struct pstat):
		(void) uncompress((Byte *)pp, &uncomplen, compbuf, complen);
		free(compbuf);
		break;

	   default:
		fprintf(stderr, "raw file contains unrecognized format "
				"of process statistics!\n");
		free(compbuf);
		return 0;
	}

	return 1;
}

/* 
** verify if a particular ascii-string is in the format yyyymmdd
*/
static int
lookslikedatetome(char *p)
{
	register int 	i;

	for (i=0; i < 8; i++)
		if ( !isdigit(*(p+i)) )
			return 0;

	if (*p != '2')
		return 0;	/* adapt this in the year 3000 */

	if ( *(p+4) > '1')
		return 0;

	if ( *(p+6) > '3')
		return 0;

	return 1;	/* yes, looks like a date to me */
}
