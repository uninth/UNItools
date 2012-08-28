/*
** ATOP - System & Process Monitor 
** 
** The program 'atop' offers the possibility to view the activity of
** the system on system-level as well as process-level.
** 
** This source-file contains functions to read all relevant system-level
** figures.
** ==========================================================================
** Author:      Gerlof Langeveld - AT Computing, Nijmegen, Holland
** E-mail:      gerlof@ATComputing.nl
** Date:        November 1996
** LINUX-port:  June 2000
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
** $Log: photosyst.c,v $
** Revision 1.21  2006/01/30 09:14:16  gerlof
** Extend memory counters (a.o. page scans).
**
** Revision 1.20  2005/10/21 09:50:08  gerlof
** Per-user accumulation of resource consumption.
**
** Revision 1.19  2004/10/28 08:31:23  gerlof
** New counter: vm committed space
**
** Revision 1.18  2004/09/24 10:02:35  gerlof
** Wrong cpu-numbers for system level statistics.
**
** Revision 1.17  2004/05/07 05:27:37  gerlof
** Recognize new disk-names and support of diskname-modification.
**
** Revision 1.16  2004/05/06 09:53:31  gerlof
** Skip statistics of ram-disks.
**
** Revision 1.15  2004/05/06 09:46:14  gerlof
** Ported to kernel-version 2.6.
**
** Revision 1.14  2003/07/08 13:53:21  gerlof
** Cleanup code.
**
** Revision 1.13  2003/07/07 09:27:06  gerlof
** Cleanup code (-Wall proof).
**
** Revision 1.12  2003/06/30 11:30:37  gerlof
** Enlarge counters to 'long long'.
**
** Revision 1.11  2003/06/24 06:21:40  gerlof
** Limit number of system resource lines.
**
** Revision 1.10  2003/01/17 14:23:05  root
** Change-directory to /proc to optimize opening /proc-files
** via relative path-names i.s.o. absolute path-names.
**
** Revision 1.9  2003/01/14 07:50:26  gerlof
** Consider IPv6 counters on IP and UDP level (add them to the IPv4 counters).
**
** Revision 1.8  2002/07/24 11:13:38  gerlof
** Changed to ease porting to other UNIX-platforms.
**
** Revision 1.7  2002/07/11 09:12:41  root
** Parsing of /proc/meminfo made 2.5 proof.
**
** Revision 1.6  2002/07/10 05:00:21  root
** Counters pin/pout renamed to swin/swout (Linux conventions).
**
** Revision 1.5  2002/07/08 09:31:11  gerlof
** *** empty log message ***
**
** Revision 1.4  2002/07/02 07:36:45  gerlof
** *** empty log message ***
**
** Revision 1.3  2002/07/02 07:08:36  gerlof
** Recognize more disk driver types via regular expressions
**
** Revision 1.2  2002/01/22 13:40:11  gerlof
** Support for number of cpu's.
**
** Revision 1.1  2001/10/02 10:43:31  gerlof
** Initial revision
**
*/

static const char rcsid[] = "$Id$";

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

#include "atop.h"
#include "photosyst.h"

#define	MAXCNT	64

static int	isrealdisk(char *, char *, int);

extern int	osrel;
extern int	osvers;

void
photosyst(struct sstat *si)
{
	register int	i, nr, nlines;
	count_t		cnts[MAXCNT];
	FILE 		*fp;
	char		linebuf[1024], nam[64], origdir[1024];
	static char	part_stats = 1; /* per-partition statistics ? */
	unsigned int	pgsz = getpagesz();

	memset(si, 0, sizeof(struct sstat));

	getcwd(origdir, sizeof origdir);
	chdir("/proc");

	/*
	** gather various general statistics from the file /proc/stat and
	** store them in binary form
	*/
	if ( (fp = fopen("stat", "r")) != NULL)
	{
		while ( fgets(linebuf, sizeof(linebuf), fp) != NULL)
		{
			nr = sscanf(linebuf,
			 "%s   %lld %lld %lld %lld %lld %lld %lld %lld %lld "
			 "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
			 "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
			 "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
			 "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
			 "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
			 "%lld %lld %lld %lld %lld ",
			  	nam,
			  	&cnts[0],  &cnts[1],  &cnts[2],  &cnts[3],
			  	&cnts[4],  &cnts[5],  &cnts[6],  &cnts[7],
			  	&cnts[8],  &cnts[9],  &cnts[10], &cnts[11],
			  	&cnts[12], &cnts[13], &cnts[14], &cnts[15],
			  	&cnts[16], &cnts[17], &cnts[18], &cnts[19],
			  	&cnts[20], &cnts[21], &cnts[22], &cnts[23],
			  	&cnts[24], &cnts[25], &cnts[26], &cnts[27],
			  	&cnts[28], &cnts[29], &cnts[30], &cnts[31],
			  	&cnts[32], &cnts[33], &cnts[34], &cnts[35],
			  	&cnts[36], &cnts[37], &cnts[38], &cnts[39],
			  	&cnts[40], &cnts[41], &cnts[42], &cnts[43],
			  	&cnts[44], &cnts[45], &cnts[46], &cnts[47],
			  	&cnts[48], &cnts[49], &cnts[50], &cnts[51],
			  	&cnts[52], &cnts[53], &cnts[54], &cnts[55],
			  	&cnts[56], &cnts[57], &cnts[58], &cnts[59],
			  	&cnts[60], &cnts[61], &cnts[62], &cnts[63]);

			if (nr < 2)		/* headerline ? --> skip */
				continue;

			if ( strcmp("cpu", nam) == EQ)
			{
				si->cpu.all.utime	= cnts[0];
				si->cpu.all.ntime	= cnts[1];
				si->cpu.all.stime	= cnts[2];
				si->cpu.all.itime	= cnts[3];

				if (nr > 5)	/* 2.6 kernel? */
				{
					si->cpu.all.wtime	= cnts[4];
					si->cpu.all.Itime	= cnts[5];
					si->cpu.all.Stime	= cnts[6];
				}
				continue;
			}

			if ( strncmp("cpu", nam, 3) == EQ)
			{
				i = atoi(&nam[3]);

				si->cpu.cpu[i].cpunr	= i;
				si->cpu.cpu[i].utime	= cnts[0];
				si->cpu.cpu[i].ntime	= cnts[1];
				si->cpu.cpu[i].stime	= cnts[2];
				si->cpu.cpu[i].itime	= cnts[3];

				if (nr > 5)	/* 2.6 kernel? */
				{
					si->cpu.cpu[i].wtime	= cnts[4];
					si->cpu.cpu[i].Itime	= cnts[5];
					si->cpu.cpu[i].Stime	= cnts[6];
				}

				si->cpu.nrcpu++;
				continue;
			}

			if ( strcmp("ctxt", nam) == EQ)
			{
				si->cpu.csw	= cnts[0];
				continue;
			}

			if ( strcmp("intr", nam) == EQ)
			{
				si->cpu.devint	= cnts[0];
				continue;
			}

			if ( strcmp("swap", nam) == EQ)   /* < 2.6 */
			{
				si->mem.swins	= cnts[0];
				si->mem.swouts	= cnts[1];
				continue;
			}
		}

		fclose(fp);

		if (si->cpu.nrcpu == 0)
			si->cpu.nrcpu = 1;
	}

	/*
	** gather virtual memory statistics from the file /proc/vmstat and
	** store them in binary form (>= kernel 2.6)
	*/
	if ( (fp = fopen("vmstat", "r")) != NULL)
	{
		int	nrfields = 9;	/* number of fields to be filled */

		while ( fgets(linebuf, sizeof(linebuf), fp) != NULL &&
								nrfields > 0)
		{
			nr = sscanf(linebuf, "%s %lld", nam, &cnts[0]);

			if (nr < 2)		/* headerline ? --> skip */
				continue;

			if ( strcmp("pswpin", nam) == EQ)
			{
				si->mem.swins   = cnts[0];
				nrfields--;
				continue;
			}

			if ( strcmp("pswpout", nam) == EQ)
			{
				si->mem.swouts  = cnts[0];
				nrfields--;
				continue;
			}

			if ( strcmp("allocstall", nam) == EQ)
			{
				si->mem.allocstall = cnts[0];
				nrfields--;
				continue;
			}

			if ( strncmp("pgscan_", nam, 7) == EQ)
			{
				si->mem.pgscans += cnts[0];
				nrfields--;
				continue;
			}
		}

		fclose(fp);
	}

	/*
	** gather memory-related statistics from the file /proc/meminfo and
	** store them in binary form
	**
	** in the file /proc/meminfo a 2.4 kernel starts with two lines
	** headed by the strings "Mem:" and "Swap:" containing all required
	** fields, except proper value for page cache
        ** if these lines are present we try to skip parsing the rest
	** of the lines; if these lines are not present we should get the
	** required field from other lines
	*/
	si->mem.physmem	 	= (count_t)-1; 
	si->mem.freemem		= (count_t)-1;
	si->mem.buffermem	= (count_t)-1;
	si->mem.cachemem  	= (count_t)-1;
	si->mem.slabmem		= (count_t) 0;
	si->mem.totswap  	= (count_t)-1;
	si->mem.freeswap 	= (count_t)-1;
	si->mem.committed 	= (count_t) 0;

	if ( (fp = fopen("meminfo", "r")) != NULL)
	{
		int	nrfields = 9;	/* number of fields to be filled */

		while ( fgets(linebuf, sizeof(linebuf), fp) != NULL && 
								nrfields > 0)
		{
			nr = sscanf(linebuf,
				"%s %lld %lld %lld %lld %lld %lld %lld "
			        "%lld %lld %lld\n",
				nam,
			  	&cnts[0],  &cnts[1],  &cnts[2],  &cnts[3],
			  	&cnts[4],  &cnts[5],  &cnts[6],  &cnts[7],
			  	&cnts[8],  &cnts[9]);

			if (nr < 2)		/* headerline ? --> skip */
				continue;

			if ( strcmp("Mem:", nam) == EQ)
			{
				si->mem.physmem	 	= cnts[0] / pgsz; 
				si->mem.freemem		= cnts[2] / pgsz;
				si->mem.buffermem	= cnts[4] / pgsz;
				nrfields -= 3;
			}
			else	if ( strcmp("Swap:", nam) == EQ)
				{
					si->mem.totswap  = cnts[0] / pgsz;
					si->mem.freeswap = cnts[2] / pgsz;
					nrfields -= 2;
				}
			else	if (strcmp("Cached:", nam) == EQ)
				{
					if (si->mem.cachemem  == (count_t)-1)
					{
						si->mem.cachemem  =
							cnts[0]*1024/pgsz;
						nrfields--;
					}
				}
			else	if (strcmp("MemTotal:", nam) == EQ)
				{
					if (si->mem.physmem  == (count_t)-1)
					{
						si->mem.physmem  =
							cnts[0]*1024/pgsz;
						nrfields--;
					}
				}
			else	if (strcmp("MemFree:", nam) == EQ)
				{
					if (si->mem.freemem  == (count_t)-1)
					{
						si->mem.freemem  =
							cnts[0]*1024/pgsz;
						nrfields--;
					}
				}
			else	if (strcmp("Buffers:", nam) == EQ)
				{
					if (si->mem.buffermem  == (count_t)-1)
					{
						si->mem.buffermem  =
							cnts[0]*1024/pgsz;
						nrfields--;
					}
				}
			else	if (strcmp("SwapTotal:", nam) == EQ)
				{
					if (si->mem.totswap  == (count_t)-1)
					{
						si->mem.totswap  =
							cnts[0]*1024/pgsz;
						nrfields--;
					}
				}
			else	if (strcmp("SwapFree:", nam) == EQ)
				{
					if (si->mem.freeswap  == (count_t)-1)
					{
						si->mem.freeswap  =
							cnts[0]*1024/pgsz;
						nrfields--;
					}
				}
			else	if (strcmp("Slab:", nam) == EQ)
				{
					si->mem.slabmem = cnts[0]*1024/pgsz;
					nrfields--;
				}
			else	if (strcmp("Committed_AS:", nam) == EQ)
				{
					si->mem.committed = cnts[0]*1024/pgsz;
					nrfields--;
				}
			else	if (strcmp("CommitLimit:", nam) == EQ)
				{
					si->mem.commitlim = cnts[0]*1024/pgsz;
					nrfields--;
				}
		}

		fclose(fp);
	}

	/*
	** gather network-related statistics
 	** 	- IPv4      stats from the file /proc/net/snmp
 	** 	- IPv6      stats from the file /proc/net/snmp6
 	** 	- interface stats from the file /proc/net/dev
	*/
	if ( (fp = fopen("net/snmp", "r")) != NULL)
	{
		nlines = 3;

		while ( fgets(linebuf, sizeof(linebuf), fp) != NULL &&
		                                               nlines > 0)
		{
			nr = sscanf(linebuf,
			 "%s   %lld %lld %lld %lld %lld %lld %lld %lld %lld "
			 "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
			 "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
			 "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
			 "%lld\n",
				nam,
				&cnts[0],  &cnts[1],  &cnts[2],  &cnts[3],
				&cnts[4],  &cnts[5],  &cnts[6],  &cnts[7],
				&cnts[8],  &cnts[9],  &cnts[10], &cnts[11],
				&cnts[12], &cnts[13], &cnts[14], &cnts[15],
				&cnts[16], &cnts[17], &cnts[18], &cnts[19],
				&cnts[20], &cnts[21], &cnts[22], &cnts[23],
				&cnts[24], &cnts[25], &cnts[26], &cnts[27],
				&cnts[28], &cnts[29], &cnts[30], &cnts[31],
				&cnts[32], &cnts[33], &cnts[34], &cnts[35],
				&cnts[36], &cnts[37], &cnts[38], &cnts[39]);

			if (nr < 2)		/* headerline ? --> skip */
				continue;

			if ( strcmp("Ip:", nam) == EQ)
			{
				si->net.ipin	= cnts[2];
				si->net.ipout	= cnts[9];
				si->net.ipindel	= cnts[8];
				si->net.ipfrw	= cnts[5];
				nlines--;
				continue;
			}

			if ( strcmp("Tcp:", nam) == EQ)
			{
				si->net.tcpin	= cnts[9];
				si->net.tcpout	= cnts[10];
				nlines--;
				continue;
			}

			if ( strcmp("Udp:", nam) == EQ)
			{
				si->net.udpin	= cnts[0];
				si->net.udpout	= cnts[3];
				nlines--;
				continue;
			}
		}

		fclose(fp);
	}

	if ( (fp = fopen("net/snmp6", "r")) != NULL)
	{
		count_t	countval;

		/*
		** one name-value pair per line
		*/
		while ( fgets(linebuf, sizeof(linebuf), fp) != NULL)
		{
		   	nr = sscanf(linebuf, "%s %lld", nam, &countval);

			if (nr < 2)		/* unexpected line ? --> skip */
				continue;

			if ( memcmp("Icmp6", nam, 5) == EQ)
				continue;

			if ( memcmp("Ip6", nam, 3) == EQ)
			{
				if      ( strcmp("Ip6InReceives", nam) == EQ)
					si->net.ipin	+= countval;
				else if ( strcmp("Ip6OutRequests", nam) == EQ)
					si->net.ipout	+= countval;
				else if ( strcmp("Ip6InDelivers", nam) == EQ)
					si->net.ipindel	+= countval;
				else if (strcmp("Ip6OutForwDatagrams",nam)==EQ)
					si->net.ipfrw	+= countval;

				continue;
			}

			if ( memcmp("Udp6", nam, 4) == EQ)
			{
				if      ( strcmp("Udp6InDatagrams", nam) == EQ)
					si->net.udpin  += countval;
				else if ( strcmp("Udp6OutDatagrams", nam) ==EQ)
					si->net.udpout += countval;

				continue;
			}
		}

		fclose(fp);
	}

	if ( (fp = fopen("net/dev", "r")) != NULL)
	{
		char *cp;

		i = 0;

		while ( fgets(linebuf, sizeof(linebuf), fp) != NULL)
		{
			if ( (cp = strchr(linebuf, ':')) != NULL)
				*cp = ' ';      /* substitute ':' by space */

			nr = sscanf(linebuf,
		 	    "%15s  %lld %lld %*d %*d %*d %*d %*d "
			    "%*d %lld %lld %*d %*d %*d %*d %*d %*d",
				  si->intf.intf[i].name,
				&(si->intf.intf[i].rbyte),
				&(si->intf.intf[i].rpack),
				&(si->intf.intf[i].sbyte),
				&(si->intf.intf[i].spack));

			if (nr == 5)	/* skip header & lines without stats */
			{
				if (++i >= MAXINTF-1)
					break;
			}
		}

		si->intf.intf[i].name[0] = '\0'; /* set terminator for table */
		si->intf.nrintf = i;

		fclose(fp);
	}

	/*
	** check if extended partition-statistics are provided < kernel 2.6
	*/
	if ( part_stats && (fp = fopen("partitions", "r")) != NULL)
	{
		char diskname[256];

		i = 0;

		while ( fgets(linebuf, sizeof(linebuf), fp) )
		{
			nr = sscanf(linebuf,
			      "%*d %*d %*d %255s %lld %*d %lld %*d "
			      "%lld %*d %lld %*d %*d %lld %lld",
			        diskname,
				&(si->xdsk.xdsk[i].nread),
				&(si->xdsk.xdsk[i].nrblk),
				&(si->xdsk.xdsk[i].nwrite),
				&(si->xdsk.xdsk[i].nwblk),
				&(si->xdsk.xdsk[i].io_ms),
				&(si->xdsk.xdsk[i].avque) );

			/*
			** check if this line concerns the entire disk
			** or just one of the partitions of a disk (to be
			** skipped)
			*/
			if (nr == 7)	/* full stats-line ? */
			{
				if ( !isrealdisk(diskname,
				                 si->xdsk.xdsk[i].name,
						 MAXDKNAM) )
				       continue;
			
				if (++i >= MAXDSK-1)
					break;
			}
		}

		si->xdsk.xdsk[i].name[0] = '\0'; /* set terminator for table */
		si->xdsk.nrxdsk = i;

		fclose(fp);

		if (i == 0)
			part_stats = 0;	/* do not try again for next cycles */
	}


	/*
	** check if disk-statistics are provided (kernel 2.6 onwards)
	*/
	if ( (fp = fopen("diskstats", "r")) != NULL)
	{
		char diskname[256];
		i = 0;

		while ( fgets(linebuf, sizeof(linebuf), fp) )
		{
			nr = sscanf(linebuf,
			      "%*d %*d %255s %lld %*d %lld %*d "
			      "%lld %*d %lld %*d %*d %lld %lld",
				diskname,
				&(si->xdsk.xdsk[i].nread),
				&(si->xdsk.xdsk[i].nrblk),
				&(si->xdsk.xdsk[i].nwrite),
				&(si->xdsk.xdsk[i].nwblk),
				&(si->xdsk.xdsk[i].io_ms),
				&(si->xdsk.xdsk[i].avque) );

			/*
			** check if this line concerns the entire disk
			** or just one of the partitions of a disk (to be
			** skipped)
			*/
			if (nr == 7)	/* full stats-line ? */
			{
				if ( !isrealdisk(diskname,
				                 si->xdsk.xdsk[i].name,
						 MAXDKNAM) )
				       continue;
			
				if (++i >= MAXDSK-1)
					break;
			}
		}

		si->xdsk.xdsk[i].name[0] = '\0'; /* set terminator for table */
		si->xdsk.nrxdsk = i;

		fclose(fp);
	}

	chdir(origdir);
}

/*
** set of subroutines to determine which disks should be monitored
** and to translate long name strings into short name strings
*/
static void
nullmodname(char *curname, char *newname, int maxlen)
{
	strncpy(newname, curname, maxlen-1);
	*(newname+maxlen-1) = 0;
}

static void
abbrevname1(char *curname, char *newname, int maxlen)
{
	char	cutype[128];
	int	hostnum, busnum, targetnum, lunnum;

	sscanf(curname, "%[^/]/host%d/bus%d/target%d/lun%d",
			cutype, &hostnum, &busnum, &targetnum, &lunnum);

	snprintf(newname, maxlen, "%c-h%db%dt%d", 
			cutype[0], hostnum, busnum, targetnum);
}

/*
** table contains the names (in regexp format) of valid disks
** to be supported, together a function to modify the name-strings
** (i.e. to abbreviate long strings);
** this table is used in the function isrealdisk()
*/
static struct {
	char 	*regexp;
	regex_t	compreg;
	void	(*modname)(char *, char *, int);
} validdisk[] = {
	{	"^sd[a-z][a-z]*$",			{0}, 	nullmodname, },
	{	"^hd[a-z]$",				{0},	nullmodname, },
	{	"^rd/c[0-9][0-9]*d[0-9][0-9]*$",	{0},	nullmodname, },
	{	"^cciss/c[0-9][0-9]*d[0-9][0-9]*$",	{0},	nullmodname, },
	{ 	"/host.*/bus.*/target.*/lun.*/disc",	{0},	abbrevname1, },
};

static int
isrealdisk(char *curname, char *newname, int maxlen)
{
	static int	firstcall = 1;
	register int	i;

	if (firstcall)		/* compile the regular expressions */
	{
		for (i=0; i < sizeof validdisk/sizeof validdisk[0]; i++)
			regcomp(&validdisk[i].compreg, validdisk[i].regexp,
								REG_NOSUB);
		firstcall = 0;
	}

	/*
	** try to recognize one of the compiled regular expressions
	*/
	for (i=0; i < sizeof validdisk/sizeof validdisk[0]; i++)
	{
		if (regexec(&validdisk[i].compreg, curname, 0, NULL, 0) == 0)
		{
			/*
			** name-string recognized; modify name-string
			*/
			(*validdisk[i].modname)(curname, newname, maxlen);

			return 1;
		}
	}

	return 0;
}

/*
** LINUX SPECIFIC:
** Determine boot-time of this system (as number of seconds since 1-1-1970).
*/
time_t	getbootlinux(long);

time_t
getbootlinux(long hertz)
{
	int     	cpid;
	char  	  	tmpbuf[1280];
	FILE    	*fp;
	unsigned long 	startticks;
	time_t		boottime = 0;

	/*
	** dirty hack to get the boottime, since the
	** Linux 2.6 kernel (2.6.5) does not return a proper
	** boottime-value with the times() system call :-(
	*/
	if ( (cpid = fork()) == 0 )
	{
		/*
		** child just waiting to be killed by parent
		*/
		pause();
	}
	else
	{
		/*
		** parent determines start-time (in clock-ticks since boot) 
		** of the child and calculates the boottime in seconds
		** since 1-1-1970
		*/
		snprintf(tmpbuf, sizeof tmpbuf, "/proc/%d/stat", cpid);

		if ( (fp = fopen(tmpbuf, "r")) != NULL)
		{
			if ( fscanf(fp, "%*d (%*[^)]) %*c %*d %*d %*d %*d "
			                "%*d %*d %*d %*d %*d %*d %*d %*d "
			                "%*d %*d %*d %*d %*d %*d %lu",
			                &startticks) == 1)
			{
				boottime = time(0) - startticks / hertz;
			}

			fclose(fp);
		}

		/*
		** kill the child and get rid of the zombie
		*/
		kill(cpid, SIGKILL);
		(void) wait((int *)0);
	}

	return boottime;
}
