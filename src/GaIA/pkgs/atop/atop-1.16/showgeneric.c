/*
** ATOP - System & Process Monitor 
**
** The program 'atop' offers the possibility to view the activity of
** the system on system-level as well as process-level.
** 
** This source-file contains the print-functions to visualize the calculated
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
** $Log: showgeneric.c,v $
** Revision 1.41  2006/04/03 05:42:35  gerlof
** *** empty log message ***
**
** Revision 1.40  2006/02/07 08:28:26  gerlof
** Improve screen-handling (less flashing) by exchanging clear()
** by werase() (contribution Folkert van Heusden).
**
** Revision 1.39  2005/11/04 14:16:16  gerlof
** Minor bug-solutions.
**
** Revision 1.38  2005/10/28 09:52:03  gerlof
** All flags/subcommands are defined as macro's.
** Subcommand 'p' has been changed to 'z' (pause).
**
** Revision 1.37  2005/10/24 06:12:17  gerlof
** Flag -L modified into -l.
**
** Revision 1.36  2005/10/21 09:50:46  gerlof
** Per-user accumulation of resource consumption.
** Possibility to send signal to process.
**
** Revision 1.35  2004/12/14 15:06:41  gerlof
** Implementation of patch-recognition for disk and network-statistics.
**
** Revision 1.34  2004/09/27 11:01:13  gerlof
** Corrected usage-info as suggested by Edelhard Becker.
**
** Revision 1.33  2004/09/13 09:19:14  gerlof
** Modify subcommands (former 's' -> 'v', 'v' -> 'V', new 's').
**
** Revision 1.32  2004/08/31 09:52:47  root
** information about underlying threads.
**
** Revision 1.31  2004/06/01 11:57:58  gerlof
** Regular expressions for selections on process-name and user-name.
**
** Revision 1.30  2003/07/07 09:27:24  gerlof
** Cleanup code (-Wall proof).
**
** Revision 1.29  2003/07/03 11:16:42  gerlof
** Implemented subcommand `r' (reset).
**
** Revision 1.28  2003/06/30 11:29:49  gerlof
** Handle configuration file ~/.atoprc
**
** Revision 1.27  2003/06/24 06:21:57  gerlof
** Limit number of system resource lines.
**
** Revision 1.26  2003/02/07 10:19:18  gerlof
** Possibility to show the version number and date.
**
** Revision 1.25  2003/01/17 07:32:16  gerlof
** Show the full command-line per process (option 'c').
**
** Revision 1.24  2002/10/30 13:47:20  gerlof
** Generate notification for statistics since boot.
**
** Revision 1.23  2002/10/08 12:00:30  gerlof
** *** empty log message ***
**
** Revision 1.22  2002/09/26 14:17:39  gerlof
** No beep when resizing the window.
**
** Revision 1.21  2002/09/26 13:52:26  gerlof
** Limit header lines by not showing disks.
**
** Revision 1.20  2002/09/18 07:15:59  gerlof
** Modified viewflag to rawreadflag.
**
** Revision 1.19  2002/09/17 13:17:39  gerlof
** Allow key 'T' to be pressed to view previous sample in raw file.
**
** Revision 1.18  2002/08/30 07:11:50  gerlof
** Minor changes to support viewing of raw atop data.
**
** Revision 1.17  2002/08/27 12:10:12  gerlof
** Allow raw data file to be written and to be read (with compression).
**
** Revision 1.16  2002/07/24 11:12:46  gerlof
** Changed to ease porting to other UNIX-platforms.
**
** Revision 1.15  2002/07/11 09:12:05  root
** Some minor updates.
**
** Revision 1.14  2002/07/10 05:00:37  root
** Counters pin/pout renamed to swin/swout (Linux conventions).
**
** Revision 1.13  2002/07/08 09:29:49  root
** Limitation for username and groupname (8 characters truncate).
**
** Revision 1.12  2002/07/02 07:14:02  gerlof
** More positions for the name of the disk-unit in the DSK-line.
**
** Revision 1.11  2002/01/22 13:40:42  gerlof
** Support for number of cpu's.
** Check if the window is large enough for the system-statistics.
**
** Revision 1.10  2001/11/30 09:09:36  gerlof
** Cosmetic chnage.
**
** Revision 1.9  2001/11/29 10:41:44  gerlof
** *** empty log message ***
**
** Revision 1.8  2001/11/29 10:38:16  gerlof
** Exit-code correctly printed.
**
** Revision 1.7  2001/11/26 11:18:45  gerlof
** Modified generic output in case that the kernel-patch is not installed.
**
** Revision 1.6  2001/11/13 08:24:50  gerlof
** Show blank columns for sockets and disk I/O when no kernel-patch installed.
**
** Revision 1.5  2001/11/07 09:19:28  gerlof
** Use /proc instead of /dev/kmem for process-level statistics.
**
** Revision 1.4  2001/10/05 13:46:32  gerlof
** Implemented paging through the process-list
**
** Revision 1.3  2001/10/04 08:47:27  gerlof
** Improved handling of error-messages
**
** Revision 1.2  2001/10/03 08:57:53  gerlof
** Improved help-screen shown in scrollable window
**
** Revision 1.1  2001/10/02 10:43:34  gerlof
** Initial revision
**
*/

static const char rcsid[] = "$Id$";

#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>
#include <stdarg.h>
#include <curses.h>
#include <pwd.h>
#include <grp.h>
#include <regex.h>

#include "atop.h"
#include "photoproc.h"
#include "photosyst.h"
#include "showgeneric.h"

extern unsigned long	interval;
extern int		deviatonly;
extern char		rawreadflag;
extern struct utsname	utsname;
extern char		flaglist[];

struct selection procsel = {"", {USERSTUB, }, "", 0, { 0, }};

static void	showhelp(int);

static int	screen;     	/* boolean: screen control-codes needed */
static int	paused;     	/* boolean: currently in pause-mode     */
static int	fixedhead;	/* boolean: fixate header-lines         */
static int	avgval;		/* boolean: average values i.s.o. total */

static int	(*curcompar)(const void *, const void *) = compcpu;
static char	*sortorder = "CPU", showtype = MPROCGEN;

static int	maxcpulines = 999;  /* maximum cpu       lines          */
static int	maxdsklines = 999;  /* maximum disk      lines          */
static int	maxintlines = 999;  /* maximum interface lines          */

char    	*genhdr = "ATOP - %-18.18s "
                          "%s  %s     %12ld seconds elapsed\n";

static int	cumusers(struct pstat *, struct pstat *, int);
static int	cumprocs(struct pstat *, struct pstat *, int);
static long	getnumval(char *, long, int);

/*
** print the deviation-counters on process- and system-level
*/
char
generic_samp(time_t curtime, int nsecs,
           struct sstat *sstat, struct pstat *pstat,
           int nact, int nproc, int nzomb, int nexit, char bootflag)
{
	static int	callnr = 0;

	register int	i, curline, statline;
	int		firstproc = 0, plistsz, alistsz, killpid, killsig;
	int		lastchar;
	char		format1[16], format2[16];
	char		*statmsg = NULL;
	struct passwd 	*pwd;
	struct syscap	syscap;

	struct pstat	*save_pstat = NULL;
	int		 save_nact = 0;

	if (callnr == 0)	/* first call ? */
	{
		/*
		** check if default sortorder and/or showtype are overruled
		** by commando-line flags
		*/
		for (i=0; flaglist[i]; i++)
		{
			switch (flaglist[i])
			{
			   case MSORTCPU:
				curcompar = compcpu;
				sortorder = "CPU";
				break;

			   case MSORTMEM:
				curcompar = compmem;
				sortorder = "MEM";
				break;

			   case MSORTDSK:
				curcompar = compdsk;
				sortorder = "DSK";
				break;

			   case MSORTNET:
				curcompar = compnet;
				sortorder = "NET";
				break;

			   case MPROCGEN:
				showtype  = MPROCGEN;
				curcompar = compcpu;
				sortorder = "CPU";
				break;

			   case MPROCMEM:
				showtype  = MPROCMEM;
				curcompar = compmem;
				sortorder = "MEM";
				break;

			   case MPROCSCH:
				showtype  = MPROCSCH;
				curcompar = compcpu;
				sortorder = "CPU";
				break;

			   case MPROCDSK:
				if ( !(kernpatch & PATCHSTAT) )
				{
					fprintf(stderr,
						"No kernel-patch installed "
						"(no disk-statistics)\n");
					sleep(3);
					break;
				}

				showtype  = MPROCDSK;
				curcompar = compdsk;
				sortorder = "DSK";
				break;

			   case MPROCNET:
				if ( !(kernpatch & PATCHSTAT) )
				{
					fprintf(stderr,
						"No kernel-patch installed "
						"(no network-statistics)\n");
					sleep(3);
					break;
				}

				showtype  = MPROCNET;
				curcompar = compnet;
				sortorder = "NET";
				break;

			   case MPROCVAR:
				showtype  = MPROCVAR;
				break;

			   case MPROCARG:
				showtype  = MPROCARG;
				break;

			   case MAVGVAL:
				if (avgval)
					avgval=0;
				else
					avgval=1;
				break;

			   case MCUMUSER:
				showtype  = MCUMUSER;
				break;

			   case MCUMPROC:
				showtype  = MCUMPROC;
				break;

			   case MSYSFIXED:
				if (fixedhead)
					fixedhead=0;
				else
					fixedhead=1;
				break;

			   case MSYSLIMIT:
				maxcpulines = 0;
				maxdsklines = 5;
				maxintlines = 3;
				break;

			   case MVERSION:
				printf("%s\n", getversion());
				cleanstop(0);

			   default:
				prusage("atop");
			}
		}

        	/*
        	** set stdout output on line-basis
        	*/
        	setvbuf(stdout, (char *)0, _IOLBF, BUFSIZ);

        	/*
        	** check if STDOUT is related to a tty or
        	** something else (file, pipe)
        	*/
        	if ( isatty(1) )
                	screen = 1;
        	else
                	screen = 0;

        	/*
        	** install catch-routine to finish in a controlled way
		** and activate cbreak-mode
        	*/
        	if (screen)
		{
			/*
			** initialize screen-handling via curses
			*/
			initscr();
			cbreak();
			noecho();

			if (COLS  < 80)
			{
				printw("Not enough columns "
				       "(need at least %d columns)\n", 80);
				refresh();
				sleep(3);
				cleanstop(1);
			}
		} 
                signal(SIGINT,   cleanstop);
                signal(SIGTERM,  cleanstop);
	}

	callnr++;

	/*
	** compute the total capacity of this system for the 
	** four main resources
	*/
	totalcap(&syscap, sstat, pstat, nact);

	/*
	** loop in which the system resources and the list of active
	** processes is shown; the loop will be preempted by receiving
	** a timer-signal or when the trigger-button is pressed.
	*/
	while (1)
	{
		curline = 1;

	        /*
       	 	** prepare screen or file output for new sample
        	*/
        	if (screen)
               	 	werase(stdscr);
        	else
                	printf("\n\n");

        	/*
        	** print general headerlines
        	*/
        	convdate(curtime, format1);       /* date to ascii string   */
        	convtime(curtime, format2);       /* time to ascii string   */

		if (screen)
			attron(A_REVERSE);

       		printg(genhdr, utsname.nodename, format1, format2, nsecs);

		if (screen)
			attroff(A_REVERSE);

		/*
		** print cumulative system- and user-time for all processes
		*/
		pricumproc(pstat, nact, nproc, nzomb, nexit, avgval, nsecs);

		curline++;

		/*
		** sort per-cpu       statistics on busy percentage
		** sort per-disk      statistics on busy percentage
		** sort per-interface statistics on transferred packages
		*/
		if (sstat->cpu.nrcpu > 1)
			qsort(sstat->cpu.cpu, sstat->cpu.nrcpu,
		 	               sizeof sstat->cpu.cpu[0], cpucompar);

		if (sstat->xdsk.nrxdsk > 1)
			qsort(sstat->xdsk.xdsk, sstat->xdsk.nrxdsk,
				       sizeof sstat->xdsk.xdsk[0], diskcompar);

		if (sstat->intf.nrintf > 1)
			qsort(sstat->intf.intf, sstat->intf.nrintf,
			  	       sizeof sstat->intf.intf[0], intfcompar);

		/*
		** print other lines of system-wide statistics
		*/
		curline = prisyst(sstat, curline, nsecs, avgval, fixedhead,
				maxcpulines, maxdsklines, maxintlines);

		if (screen && curline+2 > LINES)
		{
			move(0, 0);
			clrtobot();
			move(0, 0);
			printw("Not enough screen-lines available "
			       "(need at least %d lines)\n", curline+2);
			move(1, 0);
			printw("Resize window or start atop with the -l flag"
		       	       "to limit system-resources");

			refresh();
			sleep(4);
			cleanstop(1);
		}

		statline = curline;

		if (statmsg)
		{
			clrtoeol();
			printg(statmsg);
			statmsg = NULL;
		}
		else
		{
			if (bootflag)
			{
				if (screen)
					attron(A_BLINK);

       				printg("                *** system and "
				       "process activity since boot ***");

				if (screen)
					attroff(A_BLINK);
			}
		}

		if (screen)
			plistsz = LINES-curline-2;
		else
			plistsz = nact;

		/*
		** if cumulative figures required, save the current
		** list of processes and accumulate resource consumption
		** of all processes in the current list
		*/
		if (showtype == MCUMUSER || showtype == MCUMPROC)
		{
			/*
			** remember info based on individual processes
			*/
			save_pstat = pstat;
			save_nact  = nact;

			/*
			** allocate space for new (temporary) list with
			** one entry per user/program (list has worst-case size)
			*/
			pstat = calloc(sizeof(struct pstat), nact);

			/*
			** accumulate all processes
			** return-value nact contains number of new entries
			*/ 
			switch (showtype)
			{
			   case MCUMUSER:
				nact = cumusers(save_pstat, pstat, save_nact);
				break;
			   case MCUMPROC:
				nact = cumprocs(save_pstat, pstat, save_nact);
				break;
			}

			if (screen)
				plistsz = LINES-curline-2;
			else
				plistsz = nact;
		}

		/*
		** sort the list in required order 
		** (default CPU-consumption) and print the list
		*/
		if (nact > 0 && plistsz > 0)
		{
			qsort(pstat, nact, sizeof(struct pstat), curcompar);

			if (screen)
				attron(A_REVERSE);

			/*
			** print the header
			*/
			priphead(firstproc/plistsz+1, (nact-1)/plistsz+1,
			        			sortorder, showtype);

			if (screen)
			{
				attroff(A_REVERSE);
				clrtobot();
			}

			/*
			** print the list
			*/
			priproc(pstat, firstproc, nact, curline+2,
			        firstproc/plistsz+1, (nact-1)/plistsz+1,
			        sortorder, &syscap, showtype, 
				&procsel, screen, nsecs, avgval);
		}

		alistsz = nact;		/* preserve size of active list */

		/*
		** if cumulative figures per user shown,
		** release temporary space and restore per-process values
		*/
		if (showtype == MCUMUSER || showtype == MCUMPROC)
		{
			free(pstat);

			pstat = save_pstat;
			nact  = save_nact;
		}

		/*
		** in case of writing to a terminal, the user can also enter
		** a character to switch options, etc
		*/
		if (screen)
		{
			/*
			** show blinking pause-indication if necessary
			*/
			if (paused)
			{
				move(statline, 73);
				attron(A_BLINK);
				attron(A_REVERSE);
				printw("PAUSED");
				attroff(A_REVERSE);
				attroff(A_BLINK);
			}

			/*
			** await input-character or interval-timer expiration
			*/
			switch ( (lastchar = mvgetch(statline, 0)) )
			{
			   /*
			   ** timer expired
			   */
			   case ERR:
			   case 0:
				return lastchar;	

			   /*
			   ** stop it
			   */
			   case MQUIT:
				move(LINES-1, 0);
				clrtoeol();
				refresh();
				cleanstop(0);

			   /*
			   ** manual trigger for next sample
			   */
			   case MSAMPNEXT:
				if (paused)
					break;

				getalarm(0);
				return lastchar;

			   /*
			   ** manual trigger for previous sample
			   */
			   case MSAMPPREV:
				if (!rawreadflag)
				{
					statmsg = "Only allowed when viewing "
					          "raw file!";
					beep();
					break;
				}

				if (paused)
					break;

				return lastchar;

			   /*
			   ** sort in cpu-activity order
			   */
			   case MSORTCPU:
				curcompar = compcpu;
				sortorder = "CPU";
				firstproc = 0;
				break;

			   /*
			   ** sort in memory-consumption order
			   */
			   case MSORTMEM:
				curcompar = compmem;
				sortorder = "MEM";
				firstproc = 0;
				break;

			   /*
			   ** sort in disk-activity order
			   */
			   case MSORTDSK:
				curcompar = compdsk;
				sortorder = "DSK";
				firstproc = 0;
				break;

			   /*
			   ** sort in network-activity order
			   */
			   case MSORTNET:
				curcompar = compnet;
				sortorder = "NET";
				firstproc = 0;
				break;

			   /*
			   ** general figures per process
			   */
			   case MPROCGEN:
				showtype  = MPROCGEN;
				curcompar = compcpu;
				sortorder = "CPU";
				firstproc = 0;
				break;

			   /*
			   ** memory-specific figures per process
			   */
			   case MPROCMEM:
				showtype  = MPROCMEM;
				curcompar = compmem;
				sortorder = "MEM";
				firstproc = 0;
				break;

			   /*
			   ** disk-specific figures per process
			   */
			   case MPROCDSK:
				if ( !(kernpatch & PATCHSTAT) )
				{
					statmsg = "No kernel-patch installed; "
					          "request ignored!";
					break;
				}
				showtype  = MPROCDSK;
				curcompar = compdsk;
				sortorder = "DSK";
				firstproc = 0;
				break;

			   /*
			   ** network-specific figures per process
			   */
			   case MPROCNET:
				if ( !(kernpatch & PATCHSTAT) )
				{
					statmsg = "No kernel-patch installed; "
					          "request ignored!";
					break;
				}
				showtype  = MPROCNET;
				curcompar = compnet;
				sortorder = "NET";
				firstproc = 0;
				break;

			   /*
			   ** various info per process
			   */
			   case MPROCVAR:
				showtype  = MPROCVAR;
				firstproc = 0;
				break;

			   /*
			   ** command-line per process
			   */
			   case MPROCARG:
				showtype  = MPROCARG;
				firstproc = 0;
				break;

			   /*
			   ** scheduling-values per process
			   */
			   case MPROCSCH:
				showtype  = MPROCSCH;
				curcompar = compcpu;
				sortorder = "CPU";
				firstproc = 0;
				break;

			   /*
			   ** accumulated resource consumption per user
			   */
			   case MCUMUSER:
				statmsg = "Consumption per user; use 'a' to "
				          "toggle between all/active processes";

				showtype  = MCUMUSER;
				firstproc = 0;
				break;

			   /*
			   ** accumulated resource consumption per program
			   */
			   case MCUMPROC:
				statmsg = "Consumption per program; use 'a' to "
				          "toggle between all/active processes";

				showtype  = MCUMPROC;
				firstproc = 0;
				break;

			   /*
			   ** help wanted?
			   */
			   case MHELP1:
			   case MHELP2:
				alarm(0);	/* stop the clock         */

				move(1, 0);
				clrtobot();	/* blank the screen */
				refresh();

				showhelp(2);

				move(statline, 0);

				if (interval && !paused && !rawreadflag)
					alarm(3); /* force new sample     */

				firstproc = 0;
				break;

			   /*
			   ** send signal to process
			   */
			   case MKILLPROC:
				if (rawreadflag)
				{
					statmsg = "Not possible when viewing "
					          "raw file!";
					beep();
					break;
				}

				alarm(0);	/* stop the clock */

				killpid = getnumval("Pid of process: ",
						     0, statline);

				switch (killpid)
				{
				   case 0:
				   case -1:
					break;

				   case 1:
					statmsg = "Sending signal to pid 1 not "
					          "allowed!";
					beep();
					break;

				   default:
					clrtoeol();
					killsig = getnumval("Signal [%d]: ",
						     15, statline);

					if ( kill(killpid, killsig) == -1)
					{
						statmsg = "Not possible to "
						     "send signal to this pid!";
						beep();
					}
				}

				if (!paused)
					alarm(3); /* set short timer */

				firstproc = 0;
				break;

			   /*
			   ** change interval timeout
			   */
			   case MINTERVAL:
				if (rawreadflag)
				{
					statmsg = "Not possible when viewing "
					          "raw file!";
					beep();
					break;
				}

				alarm(0);	/* stop the clock */

				interval = getnumval("New interval in seconds "
						     "(now %d): ",
						     interval, statline);

				if (interval)
				{
					if (!paused)
						alarm(3); /* set short timer */
				}
				else
				{
					statmsg = "No timer set; waiting for "
					          "manual trigger ('t').....";
				}

				firstproc = 0;
				break;

			   /*
			   ** focus on specific user
			   */
			   case MSELUSER:
				alarm(0);	/* stop the clock */
				echo();

				move(statline, 0);
				clrtoeol();
				printw("Username as regular expression "
				       "(enter=all users): ");

				procsel.username[0] = '\0';
				scanw("%255s\n", procsel.username);

				noecho();

				if (procsel.username[0]) /* data entered ? */
				{
					regex_t		userregex;
					int		u = 0;

					regcomp(&userregex, procsel.username,
								    REG_NOSUB);

					while ( (pwd = getpwent()))
					{
						if (regexec(&userregex,
						    pwd->pw_name, 0, NULL, 0))
							continue;

						if (u < MAXUSERSEL-1)
						{
							procsel.userid[u] =
								pwd->pw_uid;
							u++;
						}
					}
					endpwent();

					procsel.userid[u] = USERSTUB;

					if (u == 0)
					{
						statmsg = "No user-names "
						    "matching this pattern!";
						beep();
					}
				}
				else
				{
					procsel.userid[0] = USERSTUB;
				}

				if (interval && !paused && !rawreadflag)
					alarm(3);  /* set short timer */

				firstproc = 0;
				break;

			   /*
			   ** focus on specific process-name
			   */
			   case MSELPROC:
				alarm(0);	/* stop the clock */
				echo();

				move(statline, 0);
				clrtoeol();
				printw("Process-name as regular "
				       "expression (enter=no specific name): ");

				procsel.procnamesz  = 0;
				procsel.procname[0] = '\0';

				scanw("%63s\n", procsel.procname);
				procsel.procnamesz = strlen(procsel.procname);

				if (procsel.procnamesz)
					regcomp(&procsel.procregex,
					         procsel.procname, REG_NOSUB);

				noecho();

				move(statline, 0);

				if (interval && !paused && !rawreadflag)
					alarm(3);  /* set short timer */

				firstproc = 0;
				break;

			   /*
			   ** toggle pause-state
			   */
			   case MPAUSE:
				if (paused)
				{
					paused=0;
					clrtoeol();
					refresh();

					if (!rawreadflag)
						alarm(1);
				}
				else
				{
					paused=1;
					clrtoeol();
					refresh();
					alarm(0);	/* stop the clock */
				}
				break;

			   /*
			   ** toggle between modified processes and
			   ** all processes
			   */
			   case MALLPROC:
				if (rawreadflag)
				{
					statmsg = "Process-list from raw file "
					          "will be shown anyhow!";
					break;
				}

				if (deviatonly)
				{
					deviatonly=0;
					statmsg = "All processes will be "
					          "shown/accumulated......";
				}
				else
				{
					deviatonly=1;
					statmsg = "Only active processes will"
					          " be shown/accumulated.....";
				}

				if (interval && !paused && !rawreadflag)
					alarm(3);  /* set short timer */

				firstproc = 0;
				break;

			   /*
			   ** toggle average or total values
			   */
			   case MAVGVAL:
				if (avgval)
					avgval=0;
				else
					avgval=1;
				break;

			   /*
			   ** system-statistics lines:
			   **	         toggle fixed or variable
			   */
			   case MSYSFIXED:
				if (fixedhead)
				{
					fixedhead=0;
					statmsg = "Only active system-resources"
					          " will be shown ......";
				}
				else
				{
					fixedhead=1;
					statmsg = "Also inactive "
					  "system-resources will be shown.....";
				}

				firstproc = 0;
				break;

			   /*
			   ** system-statistics lines:
			   **	         toggle no or all active disk
			   */
			   case MSYSLIMIT:
				alarm(0);	/* stop the clock */

				maxcpulines =
				  getnumval("Maximum lines for per-cpu "
				            "statistics (now %d): ",
				            maxcpulines, statline);

				maxdsklines =
				  getnumval("Maximum lines for disk "
				            "statistics (now %d): ",
				            maxdsklines, statline);

				maxintlines =
				  getnumval("Maximum lines for interface "
				            "statistics (now %d): ",
					    maxintlines, statline);

				if (interval && !paused && !rawreadflag)
					alarm(3);  /* set short timer */

				firstproc = 0;
				break;

			   /*
			   ** reset statistics 
			   */
			   case MRESET:
				getalarm(0);	/* restart the clock */
				paused = 0;
				return lastchar;

			   /*
			   ** show version info
			   */
			   case MVERSION:
				statmsg = getversion();
				break;

			   /*
			   ** handle forward
			   */
			   case MLISTFW:
				if (alistsz-firstproc > plistsz)
					firstproc += plistsz;
				break;

			   /*
			   ** handle backward
			   */
			   case MLISTBW:
				if (firstproc >= plistsz)
					firstproc -= plistsz;
				break;

			   /*
			   ** handle screen resize
			   */
			   case KEY_RESIZE:
				statmsg = "Window has been resized....";
				break;

			   /*
			   ** unknown key-stroke
			   */
			   default:
			        beep();
			}
		}
		else	/* no screen */
		{
			return '\0';
		}
	}
}

/*
** accumulate all processes per user in new list
*/
static int
cumusers(struct pstat *curprocs, struct pstat *curusers, int numprocs)
{
	register int	i, numusers;

	/*
	** sort list of active processes in order of uid (increasing)
	*/
	qsort(curprocs, numprocs, sizeof(struct pstat), compusr);

	/*
	** accumulate all processes per user in the new list
	*/
	for (numusers=i=0; i < numprocs; i++, curprocs++)
	{
		if ( curusers->gen.ruid != curprocs->gen.ruid )
		{
			if (curusers->gen.pid)
			{
				numusers++;
				curusers++;
			}
			curusers->gen.ruid = curprocs->gen.ruid;
		}

		curusers->gen.pid++;		/* misuse as counter */

		curusers->gen.nthr   += curprocs->gen.nthr;
		curusers->cpu.utime  += curprocs->cpu.utime;
		curusers->cpu.stime  += curprocs->cpu.stime;

		curusers->dsk.rio    += curprocs->dsk.rio;
		curusers->dsk.wio    += curprocs->dsk.wio;
			
		curusers->net.tcpsnd += curprocs->net.tcpsnd;
		curusers->net.tcprcv += curprocs->net.tcprcv;
		curusers->net.udpsnd += curprocs->net.udpsnd;
		curusers->net.udprcv += curprocs->net.udprcv;
		curusers->net.rawsnd += curprocs->net.rawsnd;
		curusers->net.rawrcv += curprocs->net.rawrcv;

		if (curprocs->gen.state != 'E')
		{
			curusers->mem.rmem   += curprocs->mem.rmem;
			curusers->mem.vmem   += curprocs->mem.vmem;
			curusers->mem.rgrow  += curprocs->mem.rgrow;
			curusers->mem.vgrow  += curprocs->mem.vgrow;
		}
	}

	if (curusers->gen.pid)
		numusers++;

	return numusers;
}

/*
** accumulate all processes with the same name (i.e. same program)
** into a new list
*/
static int
cumprocs(struct pstat *curprocs, struct pstat *curprogs, int numprocs)
{
	register int	i, numprogs;

	/*
	** sort list of active processes in order of process-name
	*/
	qsort(curprocs, numprocs, sizeof(struct pstat), compnam);

	/*
	** accumulate all processes with same name in the new list
	*/
	for (numprogs=i=0; i < numprocs; i++, curprocs++)
	{
		if ( strcmp(curprogs->gen.name, curprocs->gen.name) != 0)
		{
			if (curprogs->gen.pid)
			{
				numprogs++;
				curprogs++;
			}
			strcpy(curprogs->gen.name, curprocs->gen.name);
		}

		curprogs->gen.pid++;		/* misuse as counter */

		curprogs->gen.nthr   += curprocs->gen.nthr;
		curprogs->cpu.utime  += curprocs->cpu.utime;
		curprogs->cpu.stime  += curprocs->cpu.stime;

		curprogs->dsk.rio    += curprocs->dsk.rio;
		curprogs->dsk.wio    += curprocs->dsk.wio;
			
		curprogs->net.tcpsnd += curprocs->net.tcpsnd;
		curprogs->net.tcprcv += curprocs->net.tcprcv;
		curprogs->net.udpsnd += curprocs->net.udpsnd;
		curprogs->net.udprcv += curprocs->net.udprcv;
		curprogs->net.rawsnd += curprocs->net.rawsnd;
		curprogs->net.rawrcv += curprocs->net.rawrcv;

		if (curprocs->gen.state != 'E')
		{
			curprogs->mem.rmem   += curprocs->mem.rmem;
			curprogs->mem.vmem   += curprocs->mem.vmem;
			curprogs->mem.rgrow  += curprocs->mem.rgrow;
			curprogs->mem.vgrow  += curprocs->mem.vgrow;
		}
	}

	if (curprogs->gen.pid)
		numprogs++;

	return numprogs;
}

/*
** get a numerical value from the user and verify 
*/
static long
getnumval(char *ask, long valuenow, int statline)
{
	char numval[16];
	long retval;

	echo();
	move(statline, 0);
	clrtoeol();
	printw(ask, valuenow);

	numval[0] = 0;
	scanw("%15s", numval);

	move(statline, 0);
	noecho();

	if (numval[0])  /* data entered ? */
	{
		if ( numeric(numval) )
		{
			retval = atol(numval);
		}
		else
		{
			beep();
			clrtoeol();
			printw("Value not numeric (current value kept)!");
			refresh();
			sleep(2);
			retval = valuenow;
		}
	}
	else
	{
		retval = valuenow;
	}

	return retval;
}

/*
** generic print-function which checks if printf should be used
** (to file or pipe) or curses (to screen)
*/
void
printg(const char *format, ...)
{
	va_list	args;

	va_start(args, format);

	if (screen)
		vwprintw(stdscr, (char *) format, args);
	else
		vprintf(format, args);

	va_end  (args);
}

/*
** show help information in interactive mode
*/
static struct helptext {
	char *helpline;
	char helparg;
} helptext[] = {
	{"Figures shown for active processes:\n", 		' '},
	{"\t'%c' - generic info (default)\n",			MPROCGEN},
	{"\t'%c' - memory details\n",				MPROCMEM},
	{"\t'%c' - disk details\n",				MPROCDSK},
	{"\t'%c' - network details\n",				MPROCNET},
	{"\t'%c' - scheduling and thread-group info\n",		MPROCSCH},
	{"\t'%c' - various info (user/group, date/time)\n",	MPROCVAR},
	{"\t'%c' - full command-line per process\n",		MPROCARG},
	{"\n",							' '},
	{"Accumulated figures:\n",				' '},
	{"\t'%c' - total resource consumption per user\n", 	MCUMUSER},
	{"\t'%c' - total resource consumption per program (i.e. same "
	 "process name)\n",					MCUMPROC},
	{"\n",							' '},
	{"Sort list of active processes by:\n",			' '},
	{"\t'%c' - cpu activity (default)\n",			MSORTCPU},
	{"\t'%c' - memory consumption\n",			MSORTMEM},
	{"\t'%c' - disk activity\n",				MSORTDSK},
	{"\t'%c' - network activity\n",				MSORTNET},
	{"\n",							' '},
	{"Screen-handling:\n",					' '},
	{"\t^F  - show next     page in the process-list (forward)\n",	' '},
	{"\t^B  - show previous page in the process-list (backward)\n", ' '},
	{"\n",							' '},
	{"Miscellaneous commands:\n",				' '},
	{"\t'%c' - change interval-timer (0 = only manual trigger)\n",
								MINTERVAL},
	{"\t'%c' - manual trigger to finish interval\n",	MSAMPNEXT},
	{"\t'%c' - show previous interval again (raw file viewing)\n",
								MSAMPPREV},
	{"\t'%c' - reset counters to zero (or rewind for raw file viewing)\n",
								MRESET},
	{"\n",							' '},
	{"\t'%c' - focus on specific user name    (regular expression)\n",
								MSELUSER},
	{"\t'%c' - focus on specific process name (regular expression)\n",
								MSELPROC},
	{"\n",							' '},
	{"\t'%c' - active processes only (default) or all processes (toggle)\n",
								MALLPROC},
	{"\t'%c' - pause-button to freeze current sample            (toggle)\n",
								MPAUSE},
	{"\t'%c' - fixate on static range of header-lines           (toggle)\n",
								MSYSFIXED},
	{"\t'%c' - show average-per-second i.s.o. total values      (toggle)\n",
								MAVGVAL},
	{"\t'%c' - limited lines for per-cpu, disk and interface resources\n",
								MSYSLIMIT},
	{"\t'%c' - kill a process (i.e. send a signal)\n",	MKILLPROC},
	{"\n",							' '},
	{"\t'%c' - version-information\n",			MVERSION},
	{"\t'%c' - help-information\n",				MHELP1},
	{"\t'%c' - help-information\n",				MHELP2},
	{"\t'%c' - quit this program\n",			MQUIT},
};

static int helplines = sizeof(helptext)/sizeof(struct helptext);

static void
showhelp(int helpline)
{
	int	winlines = LINES-helpline, lin;
	WINDOW	*helpwin;

	/*
	** create a new window for the help-info in which scrolling is
	** allowed
	*/
	helpwin = newwin(winlines, COLS, helpline, 0);
	scrollok(helpwin, 1);

	/*
	** show help-lines 
	*/
	for (lin=0; lin < helplines; lin++)
	{
		wprintw(helpwin, helptext[lin].helpline, helptext[lin].helparg);

		/*
		** when the window is full, start paging interactively
		*/
		if (lin >= winlines-2)
		{
			wmove    (helpwin, winlines-1, 0);
			wclrtoeol(helpwin);
			wprintw  (helpwin, "Press any key for next line or "
			                   "'q' to leave help .......");

			if (wgetch(helpwin) == 'q')
			{
				delwin(helpwin);
				return;
			}

			wmove  (helpwin, winlines-1, 0);
		}
	}

	wmove    (helpwin, winlines-1, 0);
	wclrtoeol(helpwin);
	wprintw  (helpwin, "End of help - press any key to continue....");
	(void) wgetch(helpwin);
	delwin   (helpwin);
}

/*
** function to be called to print error-messages
*/
void
generic_error(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end  (args);
}

/*
** function to be called when the program stops
*/
void
generic_end(void)
{
	endwin();
}

/*
** function to be called when usage-info is required
*/
void
generic_usage(void)
{
	printf("\t  -%c  show general process-info (default)\n",
			MPROCGEN);
	printf("\t  -%c  show memory-related process-info\n",
			MPROCMEM);
	printf("\t  -%c  show disk-related process-info\n",
			MPROCDSK);
	printf("\t  -%c  show network-related process-info\n",
			MPROCNET);
	printf("\t  -%c  show scheduling-related process-info\n",
			MPROCSCH);
	printf("\t  -%c  show various process-info (user/group, date/time)\n",
			MPROCVAR);
	printf("\t  -%c  show command-line per process\n",
			MPROCARG);
	printf("\t  -%c  show totals per user\n",
			MCUMUSER);
	printf("\t  -%c  show totals per program (i.e. same process name)\n",
			MCUMPROC);
	printf("\t  -%c  sort by cpu-consumption (default)\n",
			MSORTCPU);
	printf("\t  -%c  sort by memory-consumption\n",
			MSORTMEM);
	printf("\t  -%c  sort by disk-activity\n",
			MSORTDSK);
	printf("\t  -%c  sort by network-activity\n",
			MSORTNET);
	printf("\t  -%c  show fixed number of system-statistics\n",
			MSYSFIXED);
	printf("\t  -%c  limited lines for system-resources\n",
			MSYSLIMIT);
	printf("\t  -%c  show average-per-second i.s.o. total values\n",
			MAVGVAL);
}

/*
** functions to handle a particular tag in the .atoprc file
*/
void
do_username(char *val)
{
	struct passwd	*pwd;

	strncpy(procsel.username, val, sizeof procsel.username -1);
	procsel.username[sizeof procsel.username -1] = 0;

	if (procsel.username[0])
	{
		regex_t		userregex;
		int		u = 0;

		regcomp(&userregex, procsel.username, REG_NOSUB);

		while ( (pwd = getpwent()))
		{
			if (regexec(&userregex, pwd->pw_name, 0, NULL, 0))
				continue;

			if (u < MAXUSERSEL-1)
			{
				procsel.userid[u] = pwd->pw_uid;
				u++;
			}
		}
		endpwent();

		procsel.userid[u] = USERSTUB;

		if (u == 0)
		{
			fprintf(stderr,
			        ".atoprc: user-names matching %s do not "
				"exist\n", val);
			exit(1);
		}
	}
	else
	{
		procsel.userid[0] = USERSTUB;
	}
}

void
do_procname(char *val)
{
	strncpy(procsel.procname, val, sizeof procsel.procname -1);
	procsel.procnamesz = strlen(procsel.procname);

	if (procsel.procnamesz)
		regcomp(&procsel.procregex, procsel.procname, REG_NOSUB);
}

void
do_maxcpu(char *val)
{
	if (numeric(val))
	{
		maxcpulines = atoi(val);
	}
	else
	{
		fprintf(stderr, ".atoprc: maxcpu value not numeric\n");
		exit(1);
	}
}

void
do_maxdisk(char *val)
{
	if (numeric(val))
	{
		maxdsklines = atoi(val);
	}
	else
	{
		fprintf(stderr, ".atoprc: maxdisk value not numeric\n");
		exit(1);
	}
}

void
do_maxintf(char *val)
{
	if (numeric(val))
	{
		maxintlines = atoi(val);
	}
	else
	{
		fprintf(stderr, ".atoprc: maxintf value not numeric\n");
		exit(1);
	}
}

void
do_flags(char *val)
{
	int	i;

	for (i=0; val[i]; i++)
	{
		switch (val[i])
		{
		   case '-':
			break;

		   case MSORTCPU:
			curcompar = compcpu;
			sortorder = "CPU";
			break;

		   case MSORTMEM:
			curcompar = compmem;
			sortorder = "MEM";
			break;

		   case MSORTDSK:
			curcompar = compdsk;
			sortorder = "DSK";
			break;

		   case MSORTNET:
			curcompar = compnet;
			sortorder = "NET";
			break;

		   case MPROCGEN:
			showtype  = MPROCGEN;
			curcompar = compcpu;
			sortorder = "CPU";
			break;

		   case MPROCMEM:
			showtype  = MPROCMEM;
			curcompar = compmem;
			sortorder = "MEM";
			break;

		   case MPROCDSK:
			showtype  = MPROCDSK;
			curcompar = compdsk;
			sortorder = "DSK";
			break;

		   case MPROCNET:
			showtype  = MPROCNET;
			curcompar = compnet;
			sortorder = "NET";
			break;

		   case MPROCVAR:
			showtype  = MPROCVAR;
			break;

		   case MPROCSCH:
			showtype  = MPROCSCH;
			curcompar = compcpu;
			sortorder = "CPU";
			break;

		   case MPROCARG:
			showtype  = MPROCARG;
			break;

		   case MCUMUSER:
			showtype  = MCUMUSER;
			break;

		   case MCUMPROC:
			showtype  = MCUMPROC;
			break;

		   case MALLPROC:
			deviatonly  = 0;
			break;

		   case MAVGVAL:
			avgval=1;
			break;

		   case MSYSFIXED:
			fixedhead=1;
			break;
		}
	}
}