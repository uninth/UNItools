/*
** ATOP - System & Process Monitor
**
** The program 'atop' offers the possibility to view the activity of
** the system on system-level as well as process-level.
**
** This source-file contains functions to calculate the differences for
** the system-level and process-level counters since the previous sample.
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
** $Log: deviate.c,v $
** Revision 1.27  2007/01/18 10:43:18  gerlof
** Support for network-interface busy-percentage (speed and duplex).
**
** Revision 1.26  2006/11/13 13:47:26  gerlof
** Implement load-average counters, context-switches and interrupts.
**
** Revision 1.25  2006/02/07 06:45:33  gerlof
** Removed swap-counter.
**
** Revision 1.24  2006/01/30 09:13:33  gerlof
** Extend memory counters (a.o. page scans).
**
** Revision 1.23  2005/10/31 12:45:29  gerlof
** Support account-record version 3 (used by Mandriva).
**
** Revision 1.22  2005/10/21 09:49:38  gerlof
** Per-user accumulation of resource consumption.
**
** Revision 1.21  2004/12/14 15:05:47  gerlof
** Implementation of patch-recognition for disk and network-statistics.
**
** Revision 1.20  2004/10/28 08:30:51  gerlof
** New counter: vm committed space
**
** Revision 1.19  2004/09/24 10:02:01  gerlof
** Wrong cpu-numbers for system level statistics.
**
** Revision 1.18  2004/09/02 10:49:18  gerlof
** Added sleep-average to process-info.
**
** Revision 1.17  2004/08/31 13:27:04  gerlof
** Add new info for threading.
**
** Revision 1.16  2004/05/07 05:49:40  gerlof
** *** empty log message ***
**
** Revision 1.15  2004/05/06 09:46:55  gerlof
** Ported to kernel-version 2.6.
**
** Revision 1.14  2003/07/07 09:26:33  gerlof
** Cleanup code (-Wall proof).
**
** Revision 1.13  2003/07/03 11:17:49  gerlof
** Corrected calculations for exited processes.
**
** Revision 1.12  2003/06/30 11:30:57  gerlof
** Enlarge counters to 'long long'.
**
** Revision 1.11  2003/06/24 06:21:12  gerlof
** Limit number of system resource lines.
**
** Revision 1.10  2003/01/24 14:20:16  gerlof
** If possible, also show commandline when process has exited.
**
** Revision 1.9  2002/09/16 08:58:08  gerlof
** Add indicator for newly created processes.
**
** Revision 1.8  2002/08/27 04:47:46  gerlof
** Minor comment updates.
**
** Revision 1.7  2002/07/24 11:12:20  gerlof
** Redesigned to ease porting to other UNIX-platforms.
**
** Revision 1.6  2002/07/10 04:59:37  root
** Counters pin/pout renamed to swin/swout (Linux conventions).
**
** Revision 1.5  2002/01/22 13:39:20  gerlof
** Support for number of cpu's.
**
** Revision 1.4  2001/11/22 08:33:10  gerlof
** Add priority per process.
**
** Revision 1.3  2001/11/07 09:18:22  gerlof
** Use /proc instead of /dev/kmem for process-level statistics.
**
** Revision 1.2  2001/10/03 08:58:41  gerlof
** Improved subtraction which is overflow-proof
**
** Revision 1.1  2001/10/02 10:43:23  gerlof
** Initial revision
**
*/

static const char rcsid[] = "$Id$";

#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <memory.h>
#include <string.h>

#include "atop.h"
#include "ifprop.h"
#include "photoproc.h"
#include "photosyst.h"

extern time_t	pretime;	/* previous sample time 	 */

#define	MAX32BITVAL	0x100000000LL

/*
** calculate the process-activity during the last sample
*/
int
deviatproc(struct pstat *aproc, int npresent,
           struct pstat *eproc, int nexit, int deviatonly,
	   struct pstat *dproc, int *nzombie)
{
	register int		c, d;
	register struct pstat	*curstat, *devstat;
	struct pstat		prestat;
	struct pinfo		*pinfo;

	/*
	** make new list of all processes in the process-database;
	** after handling all processes, the left-overs
	** should have disappeared since the previous sample
	*/
	pdb_makeresidue();

	/*
	** calculate deviations per present process
	*/
	for (c=0, d=0, *nzombie=0; c < npresent; c++)
	{
		char	newproc = 0;

		curstat = aproc+c;

		if (curstat->gen.state == 'Z')
			(*nzombie)++;

		/*
		** get previous figures from process-database
		*/
		if ( pdb_getproc(curstat->gen.pid, &pinfo) )
		{
			/*
			** process already present during the previous sample;
			** check differences with previous sample
			*/
			if (deviatonly && memcmp(curstat, &pinfo->pstat, 
					           sizeof(struct pstat)) == EQ)
				continue;

			/*
			** differences detected, so the process was active,
		        ** or its status or memory-occupation has changed;
			** save stats from previous sample (to use for
			** further calculations) and store new statistics
			** in process-database
			*/
			prestat 	= pinfo->pstat;	/* save old	*/
			pinfo->pstat 	= *curstat;	/* overwrite	*/
		}
		else
		{
			/*
			** new process which must have been started during
			** last interval
			*/
			memset(&prestat, 0, sizeof(prestat));

			/*
			** create new process
			*/
			pdb_newproc(&pinfo);

			pinfo->pstat = *curstat;

			/*
			** add new process to process-database
			*/
			pdb_addproc( curstat->gen.pid, pinfo);

			newproc = 1;
		}

		/*
		** now do the calculations
		*/
		devstat = dproc+d;

		devstat->gen        = curstat->gen;

		if (newproc)
			devstat->gen.excode |= ~(LONG_MAX);

		devstat->cpu.nice     = curstat->cpu.nice;
		devstat->cpu.prio     = curstat->cpu.prio;
		devstat->cpu.rtprio   = curstat->cpu.rtprio;
		devstat->cpu.policy   = curstat->cpu.policy;
		devstat->cpu.curcpu   = curstat->cpu.curcpu;
		devstat->cpu.sleepavg = curstat->cpu.sleepavg;

		devstat->cpu.stime  = 
			subcount(curstat->cpu.stime, prestat.cpu.stime);
		devstat->cpu.utime  =
			subcount(curstat->cpu.utime, prestat.cpu.utime);

		devstat->dsk.rio    =
			subcount(curstat->dsk.rio, prestat.dsk.rio);
		devstat->dsk.rsz    =
			subcount(curstat->dsk.rsz, prestat.dsk.rsz);
		devstat->dsk.wio    =
			subcount(curstat->dsk.wio, prestat.dsk.wio);
		devstat->dsk.wsz    =
			subcount(curstat->dsk.wsz, prestat.dsk.wsz);

		devstat->mem.shtext = curstat->mem.shtext;
		devstat->mem.vmem   = curstat->mem.vmem;
		devstat->mem.rmem   = curstat->mem.rmem;
		devstat->mem.vgrow  = curstat->mem.vmem   - prestat.mem.vmem;
		devstat->mem.rgrow  = curstat->mem.rmem   - prestat.mem.rmem;

		devstat->mem.minflt = 
			subcount(curstat->mem.minflt, prestat.mem.minflt);
		devstat->mem.majflt =
			subcount(curstat->mem.majflt, prestat.mem.majflt);

		devstat->net.tcpsnd =
			subcount(curstat->net.tcpsnd, prestat.net.tcpsnd);
		devstat->net.tcpssz =
			subcount(curstat->net.tcpssz, prestat.net.tcpssz);
		devstat->net.tcprcv =
			subcount(curstat->net.tcprcv, prestat.net.tcprcv);
		devstat->net.tcprsz =
			subcount(curstat->net.tcprsz, prestat.net.tcprsz);
		devstat->net.udpsnd =
			subcount(curstat->net.udpsnd, prestat.net.udpsnd);
		devstat->net.udpssz =
			subcount(curstat->net.udpssz, prestat.net.udpssz);
		devstat->net.udprcv =
			subcount(curstat->net.udprcv, prestat.net.udprcv);
		devstat->net.udprsz =
			subcount(curstat->net.udprsz, prestat.net.udprsz);
		devstat->net.rawsnd =
			subcount(curstat->net.rawsnd, prestat.net.rawsnd);
		devstat->net.rawrcv =
			subcount(curstat->net.rawrcv, prestat.net.rawrcv);

		d++;
	}

	/*
	** calculate deviations per exited process
	*/
	for (c=0; c < nexit; c++)
	{
		/*
		** check if this process has been started AND
		** finished since previous sample;
		** if so, it has no use to check if there is still 
		** existing info present in the process-database
		*/
		curstat = eproc+c;

		if (curstat->gen.pid)	/* acctrecord contains pid? */
		{
			if ( pdb_getproc(curstat->gen.pid, &pinfo) )
					prestat = pinfo->pstat;
				else
					memset(&prestat, 0, sizeof(prestat));
		}
		else
		{
			if ( curstat->gen.btime > pretime )
			{
				/*
				** process-start and -finish in same interval
				*/
				memset(&prestat, 0, sizeof(prestat));
			}
			else
			{
				/*
				** process must be known in process-database;
				** try to match one of the remaining processes
				** against this exited one
				*/
				if ( pdb_srchresidue(curstat, &pinfo) )
					prestat = pinfo->pstat;
				else
					memset(&prestat, 0, sizeof(prestat));
		 	}
		}

		/*
		** now do the calculations
		*/
		devstat = dproc+d;

		devstat->gen        = curstat->gen;

		if ( curstat->gen.pid == 0 )
			devstat->gen.pid    = prestat.gen.pid;

		if (!prestat.gen.pid)
			devstat->gen.excode |= ~(LONG_MAX);

		strcpy(devstat->gen.cmdline, prestat.gen.cmdline);

		devstat->cpu.nice     = 0;
		devstat->cpu.prio     = 0;
		devstat->cpu.rtprio   = 0;
		devstat->cpu.policy   = 0;
		devstat->cpu.curcpu   = 0;
		devstat->cpu.sleepavg = 0;

		if (kernpatch & PATCHACCT)
		{
			devstat->net.tcpsnd = curstat->net.tcpsnd -
			                      prestat.net.tcpsnd;
			devstat->net.tcpssz = curstat->net.tcpssz -
			                      prestat.net.tcpssz;
			devstat->net.tcprcv = curstat->net.tcprcv -
			                      prestat.net.tcprcv;
			devstat->net.tcprsz = curstat->net.tcprsz -
			                      prestat.net.tcprsz;
			devstat->net.udpsnd = curstat->net.udpsnd -
			                      prestat.net.udpsnd;
			devstat->net.udpssz = curstat->net.udpssz -
			                      prestat.net.udpssz;
			devstat->net.udprcv = curstat->net.udprcv -
			                      prestat.net.udprcv;
			devstat->net.udprsz = curstat->net.udprsz -
			                      prestat.net.udprsz;
			devstat->net.rawsnd = curstat->net.rawsnd -
			                      prestat.net.rawsnd;
			devstat->net.rawrcv = curstat->net.rawrcv -
			                      prestat.net.rawrcv;
			devstat->dsk.rio    = curstat->dsk.rio    -
			                      prestat.dsk.rio;
			devstat->dsk.rsz    = curstat->dsk.rsz    -
			                      prestat.dsk.rsz;
			devstat->dsk.wio    = curstat->dsk.wio    -
			                      prestat.dsk.wio;
			devstat->dsk.wsz    = curstat->dsk.wsz    -
			                      prestat.dsk.wsz;
			devstat->mem.vmem   = 0;
			devstat->mem.rmem   = 0;
			devstat->mem.vgrow  = -curstat->mem.vmem;
			devstat->mem.rgrow  = -curstat->mem.rmem;
		}
		else
		{
			devstat->net.tcpsnd   = 0;
			devstat->net.tcpssz   = 0;
			devstat->net.tcprcv   = 0;
			devstat->net.tcprsz   = 0;
			devstat->net.udpsnd   = 0;
			devstat->net.udpssz   = 0;
			devstat->net.udprcv   = 0;
			devstat->net.udprsz   = 0;
			devstat->net.rawsnd   = 0;
			devstat->net.rawrcv   = 0;
			devstat->mem.vmem     = 0;
			devstat->mem.rmem     = 0;
			devstat->mem.vgrow    = 0;
			devstat->mem.rgrow    = 0;
			devstat->dsk.wio      = 0;
			devstat->dsk.wsz      = 0;
			devstat->dsk.rsz      = 0;
			devstat->dsk.rio      = curstat->dsk.rio  -
						prestat.dsk.rio   -
						prestat.dsk.wio;
		}

		devstat->cpu.stime  = curstat->cpu.stime  - prestat.cpu.stime;
		devstat->cpu.utime  = curstat->cpu.utime  - prestat.cpu.utime;
		devstat->mem.minflt = curstat->mem.minflt - prestat.mem.minflt;
		devstat->mem.majflt = curstat->mem.majflt - prestat.mem.majflt;
		devstat->mem.shtext = 0;

		/*
		** due to the strange exponent-type storage of values
		** in the process accounting record, the resource-value
		** in the exit-record might have been smaller than the
		** stored value of the last registered sample; in that
		** case the deviation should be set to zero
		*/
		if (devstat->cpu.stime < 0)
			devstat->cpu.stime = 0;
		if (devstat->cpu.utime < 0)
			devstat->cpu.utime = 0;
		if (devstat->dsk.rio    < 0)
			devstat->dsk.rio   = 0;
		if (devstat->dsk.rsz    < 0)
			devstat->dsk.rsz   = 0;
		if (devstat->dsk.wio    < 0)
			devstat->dsk.wio   = 0;
		if (devstat->dsk.wsz    < 0)
			devstat->dsk.wsz   = 0;
		if (devstat->mem.minflt < 0)
			devstat->mem.minflt = 0;
		if (devstat->mem.majflt < 0)
			devstat->mem.majflt = 0;

		if (kernpatch & PATCHACCT)
		{
			if (devstat->net.tcpsnd < 0)
				 devstat->net.tcpsnd = 0;
			if (devstat->net.tcprcv < 0)
				 devstat->net.tcprcv = 0;
			if (devstat->net.udpsnd < 0)
				 devstat->net.udpsnd = 0;
			if (devstat->net.udprcv < 0)
				 devstat->net.udprcv = 0;
			if (devstat->net.rawsnd < 0)
				 devstat->net.rawsnd = 0;
			if (devstat->net.rawrcv < 0)
				 devstat->net.rawrcv = 0;
		}

		d++;

		if (prestat.gen.pid > 0)
			pdb_delproc(prestat.gen.pid);
	}

	/*
	** remove unused entries from RESIDUE chain
	*/
	pdb_cleanresidue();

	return d;
}

/*
** calculate the system-activity during the last sample
*/
void
deviatsyst(struct sstat *cur, struct sstat *pre, struct sstat *dev)
{
	register int	i;

	dev->cpu.devint    = subcount(cur->cpu.devint, pre->cpu.devint);
	dev->cpu.csw       = subcount(cur->cpu.csw,    pre->cpu.csw);
	dev->cpu.nrcpu     = cur->cpu.nrcpu;

	dev->cpu.all.stime = subcount(cur->cpu.all.stime, pre->cpu.all.stime);
	dev->cpu.all.utime = subcount(cur->cpu.all.utime, pre->cpu.all.utime);
	dev->cpu.all.ntime = subcount(cur->cpu.all.ntime, pre->cpu.all.ntime);
	dev->cpu.all.itime = subcount(cur->cpu.all.itime, pre->cpu.all.itime);
	dev->cpu.all.wtime = subcount(cur->cpu.all.wtime, pre->cpu.all.wtime);
	dev->cpu.all.Itime = subcount(cur->cpu.all.Itime, pre->cpu.all.Itime);
	dev->cpu.all.Stime = subcount(cur->cpu.all.Stime, pre->cpu.all.Stime);

	if (dev->cpu.nrcpu == 1)
	{
		dev->cpu.cpu[0] = dev->cpu.all;
	}
	else
	{
		for (i=0; i < dev->cpu.nrcpu; i++)
		{
			dev->cpu.cpu[i].cpunr = cur->cpu.cpu[i].cpunr;
			dev->cpu.cpu[i].stime = subcount(cur->cpu.cpu[i].stime,
						         pre->cpu.cpu[i].stime);
			dev->cpu.cpu[i].utime = subcount(cur->cpu.cpu[i].utime,
					 	         pre->cpu.cpu[i].utime);
			dev->cpu.cpu[i].ntime = subcount(cur->cpu.cpu[i].ntime,
						         pre->cpu.cpu[i].ntime);
			dev->cpu.cpu[i].itime = subcount(cur->cpu.cpu[i].itime,
						         pre->cpu.cpu[i].itime);
			dev->cpu.cpu[i].wtime = subcount(cur->cpu.cpu[i].wtime,
						         pre->cpu.cpu[i].wtime);
			dev->cpu.cpu[i].Itime = subcount(cur->cpu.cpu[i].Itime,
						         pre->cpu.cpu[i].Itime);
			dev->cpu.cpu[i].Stime = subcount(cur->cpu.cpu[i].Stime,
						         pre->cpu.cpu[i].Stime);
		}
	}

	dev->cpu.lavg1		= cur->cpu.lavg1;
	dev->cpu.lavg5		= cur->cpu.lavg5;
	dev->cpu.lavg15		= cur->cpu.lavg15;

	dev->mem.physmem	= cur->mem.physmem;
	dev->mem.freemem	= cur->mem.freemem;
	dev->mem.buffermem	= cur->mem.buffermem;
	dev->mem.slabmem	= cur->mem.slabmem;
	dev->mem.committed	= cur->mem.committed;
	dev->mem.commitlim	= cur->mem.commitlim;
	dev->mem.cachemem	= cur->mem.cachemem;
	dev->mem.totswap	= cur->mem.totswap;
	dev->mem.freeswap	= cur->mem.freeswap;

	dev->mem.swouts		= subcount(cur->mem.swouts,  pre->mem.swouts);
	dev->mem.swins		= subcount(cur->mem.swins,   pre->mem.swins);
	dev->mem.pgscans	= subcount(cur->mem.pgscans, pre->mem.pgscans);
	dev->mem.allocstall	= subcount(cur->mem.allocstall,
				                         pre->mem.allocstall);

	dev->net.ipin 		= subcount(cur->net.ipin,    pre->net.ipin);
	dev->net.ipout 		= subcount(cur->net.ipout,   pre->net.ipout);
	dev->net.ipindel 	= subcount(cur->net.ipindel, pre->net.ipindel);
	dev->net.ipfrw 		= subcount(cur->net.ipfrw,   pre->net.ipfrw);
	dev->net.tcpin 		= subcount(cur->net.tcpin,   pre->net.tcpin);
	dev->net.tcpout		= subcount(cur->net.tcpout,  pre->net.tcpout);
	dev->net.udpin 		= subcount(cur->net.udpin,   pre->net.udpin);
	dev->net.udpout		= subcount(cur->net.udpout,  pre->net.udpout);

	/*
	** calculate deviations for interfaces
	*/
	if (pre->intf.intf[0].name[0] == '\0')	/* first sample? */
	{
		struct ifprop	ifprop;

		for (i=0; cur->intf.intf[i].name[0]; i++)
		{
			strcpy(pre->intf.intf[i].name, cur->intf.intf[i].name);

			strcpy(ifprop.name, cur->intf.intf[i].name);

			getifprop(&ifprop);

			pre->intf.intf[i].speed         = ifprop.speed;
			pre->intf.intf[i].duplex        = ifprop.fullduplex;
 		}
	}
	
	for (i=0; cur->intf.intf[i].name[0]; i++)
	{
		/*
		** check if an interface has been added or removed;
		** in that case, skip further handling for this sample
		*/
		if (strcmp(cur->intf.intf[i].name, pre->intf.intf[i].name) != 0)
		{
			int		j;
			struct ifprop	ifprop;

			/*
			** take care that interface properties are
			** corrected for future samples
			*/
                        seteuid(0);		/* get root privileges      */

		        initifprop();		/* refresh interface info   */

                        seteuid( getuid() );	/* release root privileges  */

			for (j=0; cur->intf.intf[j].name[0]; j++)
			{
				strcpy(ifprop.name, cur->intf.intf[j].name);

				getifprop(&ifprop);

				cur->intf.intf[j].speed  = ifprop.speed;
				cur->intf.intf[j].duplex = ifprop.fullduplex;
			}

			break;
		}

		/*
		** calculate interface deviations for this sample
		*/
		strcpy(dev->intf.intf[i].name, cur->intf.intf[i].name);

		dev->intf.intf[i].rbyte = subcount(cur->intf.intf[i].rbyte,
           	                                  pre->intf.intf[i].rbyte);
		dev->intf.intf[i].rpack = subcount(cur->intf.intf[i].rpack,
		                                  pre->intf.intf[i].rpack);
		dev->intf.intf[i].sbyte = subcount(cur->intf.intf[i].sbyte,
		                                  pre->intf.intf[i].sbyte);
		dev->intf.intf[i].spack = subcount(cur->intf.intf[i].spack,
		                                  pre->intf.intf[i].spack);

		dev->intf.intf[i].speed 	= pre->intf.intf[i].speed;
		dev->intf.intf[i].duplex	= pre->intf.intf[i].duplex;
	
		/*
		** save interface properties for next interval
		*/
		cur->intf.intf[i].speed 	= pre->intf.intf[i].speed;
		cur->intf.intf[i].duplex	= pre->intf.intf[i].duplex;
	}

	dev->intf.intf[i].name[0] = '\0';
	dev->intf.nrintf = i;

	/*
	** calculate deviations for disks
	*/
	for (i=0; cur->xdsk.xdsk[i].name[0]; i++)
	{
		strcpy(dev->xdsk.xdsk[i].name, cur->xdsk.xdsk[i].name);

		dev->xdsk.xdsk[i].nread  = subcount(cur->xdsk.xdsk[i].nread,
		                                   pre->xdsk.xdsk[i].nread);
		dev->xdsk.xdsk[i].nwrite = subcount(cur->xdsk.xdsk[i].nwrite,
		                                   pre->xdsk.xdsk[i].nwrite);
		dev->xdsk.xdsk[i].nrblk  = subcount(cur->xdsk.xdsk[i].nrblk,
		                                   pre->xdsk.xdsk[i].nrblk);
		dev->xdsk.xdsk[i].nwblk  = subcount(cur->xdsk.xdsk[i].nwblk,
		                                   pre->xdsk.xdsk[i].nwblk);
		dev->xdsk.xdsk[i].io_ms  = subcount(cur->xdsk.xdsk[i].io_ms,
		                                   pre->xdsk.xdsk[i].io_ms);
		dev->xdsk.xdsk[i].avque  = subcount(cur->xdsk.xdsk[i].avque,
		                                   pre->xdsk.xdsk[i].avque);
	}

	dev->xdsk.xdsk[i].name[0] = '\0';
	dev->xdsk.nrxdsk = i;
}

/*
** Generic function to subtract two counters taking into 
** account the possibility of overflow of a 32-bit kernel-counter.
*/
count_t
subcount(count_t newval, count_t oldval)
{
	if (newval >= oldval)
		return newval - oldval;
	else
		return MAX32BITVAL + newval - oldval;
}
