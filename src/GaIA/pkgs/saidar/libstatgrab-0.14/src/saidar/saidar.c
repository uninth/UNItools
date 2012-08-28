/*
 * i-scream libstatgrab
 * http://www.i-scream.org
 * Copyright (C) 2000-2004 i-scream
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/termios.h>
#include <signal.h>
#include <errno.h>
#include <statgrab.h>
#include <sys/times.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#ifdef HAVE_NCURSES_H
#define COLOR_SUPPORT
#endif
#include CURSES_HEADER_FILE

#define THRESHOLD_LOAD 1.0

#define THRESHOLD_WARN_ZMB 0

#define THRESHOLD_WARN_CPU 60.0
#define THRESHOLD_ALERT_CPU 90.0

#define THRESHOLD_WARN_SWAP 75.0
#define THRESHOLD_ALERT_SWAP 90.0

#define THRESHOLD_WARN_MEM 75.0
#define THRESHOLD_ALERT_MEM 90.0

#define THRESHOLD_WARN_DISK 75.0
#define THRESHOLD_ALERT_DISK 90.0

int sig_winch_flag = 0;

typedef struct{
	sg_cpu_percents *cpu_percents;
	sg_mem_stats *mem_stats;
	sg_swap_stats *swap_stats;
	sg_load_stats *load_stats;
	sg_process_count *process_count;
	sg_page_stats *page_stats;

	sg_network_io_stats *network_io_stats;
	int network_io_entries;

	sg_disk_io_stats *disk_io_stats;
	int disk_io_entries;

	sg_fs_stats *fs_stats;
	int fs_entries;

	sg_host_info *host_info;
	sg_user_stats *user_stats;
}stats_t;

stats_t stats;

char *size_conv(long long number){
	char type[] = {'B', 'K', 'M', 'G', 'T'};
	int x=0;
	int sign=1;
	static char string[10];

	if(number < 0){
		sign=-1;
		number=-number;
	}

	for(;x<5;x++){
		if( (number/1024) < (100)) {
			break;
		}
		number = (number/1024);
	}

	number = number*sign;

	snprintf(string, 10, "%lld%c", number, type[x]);
	return string;

}

char *hr_uptime(time_t time){
	int day = 0, hour = 0, min = 0;
	static char uptime_str[25];
	int sec = (int) time;

	day = sec / (24*60*60);
	sec = sec % (24*60*60);
	hour = sec / (60*60);
	sec = sec % (60*60);
	min = sec / 60;
	sec = sec % 60;

	if(day){
		snprintf(uptime_str, 25, "%dd %02d:%02d:%02d", day, hour, min, sec);
	}else{
		snprintf(uptime_str, 25, "%02d:%02d:%02d", hour, min, sec);
	}
	return uptime_str;
}

void display_headings(){
	int line;

	move(0,0);
	printw("Hostname  :");
	move(0,27);
	printw("Uptime : ");
	move(0,54);
	printw("Date : ");

	/* Load */
	move(2,0);
	printw("Load 1    :");
	move(3,0);
	printw("Load 5    :");
	move(4,0);
	printw("Load 15   :");

	/* CPU */
	move(2,21);
	printw("CPU Idle  :");
	move(3,21);
	printw("CPU System:");
	move(4,21);
	printw("CPU User  :");

	/* Process */
	move(2, 42);
	printw("Running   :");
	move(3, 42);
	printw("Sleeping  :");
	move(4, 42);
	printw("Stopped   :");
	move(2, 62);
	printw("Zombie    :");
	move(3, 62);
	printw("Total     :");
	move(4, 62);
	printw("No. Users :");

	/* Mem */
	move(6, 0);
	printw("Mem Total :");
	move(7, 0);
	printw("Mem Used  :");
	move(8, 0);
	printw("Mem Free  :");

	/* Swap */
	move(6, 21);
	printw("Swap Total:");
	move(7, 21);
	printw("Swap Used :");
	move(8, 21);
	printw("Swap Free :");

	/* VM */
	move(6, 42);
	printw("Mem Used  :");
	move(7, 42);
	printw("Swap Used :");
	move(8, 42);
	printw("Total Used:");

	/* Paging */
	move(6, 62);
	printw("Paging in :");
	move(7, 62);
	printw("Paging out:");

	/* Disk IO */
	move(10,0);
	printw("Disk Name");
	move(10,15);
	printw("Read");
	move(10,28);
	printw("Write");

	line = 10;
	if (stats.network_io_stats != NULL) {
		/* Network IO */
		move(line, 42);
		printw("Network Interface");
		move(line, 67);
		printw("rx");
		move(line, 77);
		printw("tx");
		line += 2 + stats.network_io_entries;
	}

	move(line, 42);
	printw("Mount Point");
	move(line, 65);
	printw("Free");
	move(line, 75);
	printw("Used");

	refresh();
}

void display_data(int colors){
	char cur_time[20];
	struct tm *tm_time;
	time_t epoc_time;
	int counter, line;
	long long r,w;
	long long rt, wt;
	sg_disk_io_stats *disk_io_stat_ptr;
	sg_network_io_stats *network_stat_ptr;
	sg_fs_stats *disk_stat_ptr;
	/* Size before it will start overwriting "uptime" */
	char hostname[15];
	char *ptr;

	if (stats.host_info != NULL) {
		move(0,12);
		strncpy(hostname, stats.host_info->hostname, (sizeof(hostname) - 1));
		/* strncpy does not NULL terminate.. If only strlcpy was on all platforms :) */
		hostname[14] = '\0';
		ptr=strchr(hostname, '.');
		/* Some hosts give back a FQDN for hostname. To avoid this, we'll
		 * just blank out everything after the first "."
		 */
		if (ptr != NULL){
			*ptr = '\0';
		}
		if (colors) {
			attron(COLOR_PAIR(1));
		}
		printw("%s", hostname);
		move(0,36);
		printw("%s", hr_uptime(stats.host_info->uptime));
		epoc_time=time(NULL);
		tm_time = localtime(&epoc_time);
		strftime(cur_time, 20, "%Y-%m-%d %T", tm_time);
		move(0,61);
		printw("%s", cur_time);
		if (colors) {
			attroff(COLOR_PAIR(1));
		}
	}

	if (stats.load_stats != NULL) {
		/* Load */
		if (colors) {
			attron(COLOR_PAIR(6));
		}
		move(2,12);
		if (colors && fabs(stats.load_stats->min1 - stats.load_stats->min5) > THRESHOLD_LOAD) {
			attron(A_BOLD);
		}
		printw("%6.2f", stats.load_stats->min1);
		if (colors) {
			attroff(A_BOLD);
		}
		move(3,12);
		if (colors && fabs(stats.load_stats->min5 - stats.load_stats->min15) > THRESHOLD_LOAD) {
			attron(A_BOLD);
		}
		printw("%6.2f", stats.load_stats->min5);
		if (colors) {
			attroff(A_BOLD);
		}
		move(4,12);
		if (colors && fabs(stats.load_stats->min1 - stats.load_stats->min15) > THRESHOLD_LOAD) {
			attron(A_BOLD);
		}
		printw("%6.2f", stats.load_stats->min15);
		if (colors) {
			attroff(A_BOLD);
		}
	}

	if (stats.cpu_percents != NULL) {
		/* CPU */
		move(2,33);
		printw("%6.2f%%", stats.cpu_percents->idle);
		move(3,33);
		printw("%6.2f%%", (stats.cpu_percents->kernel + stats.cpu_percents->iowait + stats.cpu_percents->swap));
		move(4,33);
		if (colors && stats.cpu_percents->user + stats.cpu_percents->nice > THRESHOLD_ALERT_CPU) {
			attron(A_STANDOUT);
			attron(A_BOLD);
		}
		else if (colors && stats.cpu_percents->user + stats.cpu_percents->nice > THRESHOLD_WARN_CPU) {
			attron(A_BOLD);
		}
		printw("%6.2f%%", (stats.cpu_percents->user + stats.cpu_percents->nice));
		if(colors) {
			attroff(A_BOLD);
			attroff(A_STANDOUT);
			attron(COLOR_PAIR(6));
		}
	}

	if (stats.process_count != NULL) {
		/* Process */
		move(2, 54);
		printw("%5d", stats.process_count->running);
		move(2,74);
		if (colors && stats.process_count->zombie > THRESHOLD_WARN_ZMB) {
			attron(A_STANDOUT);
			attron(A_BOLD);
		}
		printw("%5d", stats.process_count->zombie);
		if(colors) {
			attroff(A_STANDOUT);
			attroff(A_BOLD);
		}
		move(3, 54);
		printw("%5d", stats.process_count->sleeping);
		move(3, 74);
		printw("%5d", stats.process_count->total);
		move(4, 54);
		printw("%5d", stats.process_count->stopped);
	}
	if (stats.user_stats != NULL) {
		move(4,74);
		printw("%5d", stats.user_stats->num_entries);
	}

	if(colors) {
		attroff(COLOR_PAIR(6));
		attron(COLOR_PAIR(5));
	}
	if (stats.mem_stats != NULL) {
		/* Mem */
		move(6, 12);
		printw("%7s", size_conv(stats.mem_stats->total));
		move(7, 12);
		printw("%7s", size_conv(stats.mem_stats->used));
		move(8, 12);
		printw("%7s", size_conv(stats.mem_stats->free));
	}

	if (stats.swap_stats != NULL) {
		/* Swap */
		move(6, 32);
		printw("%8s", size_conv(stats.swap_stats->total));
		move(7, 32);
		printw("%8s", size_conv(stats.swap_stats->used));
		move(8, 32);
		printw("%8s", size_conv(stats.swap_stats->free));
	}

	/* VM */
	if (stats.mem_stats != NULL && stats.mem_stats->total != 0) {
		float f = 100.00 * (float)(stats.mem_stats->used)/stats.mem_stats->total;
		if (colors && f > THRESHOLD_ALERT_MEM) {
			attron(A_STANDOUT);
			attron(A_BOLD);
		}
		else if (colors && f > THRESHOLD_WARN_MEM) {
			attron(A_BOLD);
		}
		move(6, 54);
		printw("%5.2f%%", f);
		if (colors) {
			attroff(A_STANDOUT);
			attroff(A_BOLD);
			attron(COLOR_PAIR(5));
		}
	}
	if (stats.swap_stats != NULL && stats.swap_stats->total != 0) {
		float f = 100.00 * (float)(stats.swap_stats->used)/stats.swap_stats->total;
		if (colors && f > THRESHOLD_ALERT_SWAP) {
			attron(A_STANDOUT);
			attron(A_BOLD);
		}
		else if (colors && f > THRESHOLD_WARN_SWAP) {
			attron(A_BOLD);
		}
		move(7, 54);
		printw("%5.2f%%", f);
		if (colors) {
			attroff(A_STANDOUT);
			attroff(A_BOLD);
			attron(COLOR_PAIR(5));
		}
	}
	if (stats.mem_stats != NULL && stats.swap_stats != NULL &&
	    stats.mem_stats->total != 0 && stats.swap_stats->total != 0) {
		move(8, 54);
		printw("%5.2f%%", (100.00 * (float)(stats.mem_stats->used+stats.swap_stats->used)/(stats.mem_stats->total+stats.swap_stats->total)));
	}

	if (stats.page_stats != NULL) {
		/* Paging */
		move(6, 74);
		printw("%5d", (stats.page_stats->systime)? (stats.page_stats->pages_pagein / stats.page_stats->systime): stats.page_stats->pages_pagein);
		move(7, 74);
		printw("%5d", (stats.page_stats->systime)? (stats.page_stats->pages_pageout / stats.page_stats->systime) : stats.page_stats->pages_pageout);
	}
	if (colors) {
		attroff(COLOR_PAIR(5));
	}

	line = 11;
	if (stats.disk_io_stats != NULL) {
		/* Disk IO */
		disk_io_stat_ptr = stats.disk_io_stats;
		r=0;
		w=0;
		for(counter=0;counter<stats.disk_io_entries;counter++){
			char name[12];
			strncpy(name, disk_io_stat_ptr->disk_name, sizeof(name));
			name[sizeof(name)-1] = '\0'; /* strncpy doesn't terminate longer strings */
			move(line, 0);
			printw("%s", name);
			move(line, 12);
			rt = (disk_io_stat_ptr->systime)? (disk_io_stat_ptr->read_bytes/disk_io_stat_ptr->systime): disk_io_stat_ptr->read_bytes;
			if(colors) {
				attron(COLOR_PAIR(4));
			}
			printw("%7s", size_conv(rt));
			r+=rt;
			move(line, 26);
			wt = (disk_io_stat_ptr->systime)? (disk_io_stat_ptr->write_bytes/disk_io_stat_ptr->systime): disk_io_stat_ptr->write_bytes;
			printw("%7s", size_conv(wt));
			w+=wt;
			disk_io_stat_ptr++;
			line++;
			if(colors) {
				attroff(COLOR_PAIR(4));
			}
		}
		line++;
		move(line, 0);
		printw("Total");
		move(line, 12);
		if(colors) {
			attron(COLOR_PAIR(4));
		}
		printw("%7s", size_conv(r));
		move(line, 26);
		printw("%7s", size_conv(w));
		if(colors) {
			attroff(COLOR_PAIR(4));
		}
	}

	line = 11;
	if (stats.network_io_stats != NULL) {
		/* Network */
		network_stat_ptr = stats.network_io_stats;
		for(counter=0;counter<stats.network_io_entries;counter++){
			char name[20];
			strncpy(name, network_stat_ptr->interface_name, sizeof(name));
			name[sizeof(name)-1] = '\0'; /* strncpy doesn't terminate longer strings */
			move(line, 42);
			printw("%s", name);
			move(line, 62);
			rt = (network_stat_ptr->systime)? (network_stat_ptr->rx / network_stat_ptr->systime): network_stat_ptr->rx;
			if(colors) {
				attron(COLOR_PAIR(4));
			}
			printw("%7s", size_conv(rt));
			move(line, 72);
			wt = (network_stat_ptr->systime)? (network_stat_ptr->tx / network_stat_ptr->systime): network_stat_ptr->tx;
			printw("%7s", size_conv(wt));
			network_stat_ptr++;
			line++;
			if(colors) {
				attroff(COLOR_PAIR(4));
			}
		}
		line += 2;
	}

	if (stats.fs_stats != NULL) {
		/* Disk */
		disk_stat_ptr = stats.fs_stats;
		for(counter=0;counter<stats.fs_entries;counter++){
			char name[20];
			strncpy(name, disk_stat_ptr->mnt_point, sizeof(name));
			name[sizeof(name)-1] = '\0'; /* strncpy doesn't terminate longer strings */
			move(line, 42);
			printw("%s", name);
			move(line, 62);
			if(colors) {
				attron(COLOR_PAIR(2));
			}
			printw("%7s", size_conv(disk_stat_ptr->avail));
			move(line, 73);
			if(colors && 100.00 * ((float) disk_stat_ptr->used / (float) (disk_stat_ptr->used + disk_stat_ptr->avail)) > THRESHOLD_ALERT_DISK) {
				attron(A_STANDOUT);
				attron(A_BOLD);
			} else if (colors && 100.00 * ((float) disk_stat_ptr->used / (float) (disk_stat_ptr->used + disk_stat_ptr->avail)) > THRESHOLD_WARN_DISK) {
				attron(A_BOLD);
			}
			printw("%6.2f%%", 100.00 * ((float) disk_stat_ptr->used / (float) (disk_stat_ptr->used + disk_stat_ptr->avail)));
			disk_stat_ptr++;
			line++;
			if(colors) {
				attroff(COLOR_PAIR(2));
				attroff(A_STANDOUT);
				attroff(A_BOLD);
			}
		}
	}

	refresh();
}

void sig_winch_handler(int dummy){
	sig_winch_flag = 1;
	signal(SIGWINCH, sig_winch_handler);
}

int get_stats(){
	stats.cpu_percents = sg_get_cpu_percents();
	stats.mem_stats = sg_get_mem_stats();
	stats.swap_stats = sg_get_swap_stats();
	stats.load_stats = sg_get_load_stats();
	stats.process_count = sg_get_process_count();
	stats.page_stats = sg_get_page_stats_diff();
	stats.network_io_stats = sg_get_network_io_stats_diff(&(stats.network_io_entries));
	stats.disk_io_stats = sg_get_disk_io_stats_diff(&(stats.disk_io_entries));
	stats.fs_stats = sg_get_fs_stats(&(stats.fs_entries));
	stats.host_info = sg_get_host_info();
	stats.user_stats = sg_get_user_stats();

	return 1;
}

void version_num(char *progname){
	fprintf(stderr, "%s version %s\n", progname, PACKAGE_VERSION);
	fprintf(stderr, "\nReport bugs to <%s>.\n", PACKAGE_BUGREPORT);
	exit(1);
}

void usage(char *progname){
#ifdef COLOR_SUPPORT
	fprintf(stderr, "Usage: %s [-d delay] [-c] [-v] [-h]\n\n", progname);
#else
	fprintf(stderr, "Usage: %s [-d delay] [-v] [-h]\n\n", progname);
#endif
	fprintf(stderr, "  -d    Sets the update time in seconds\n");
#ifdef COLOR_SUPPORT
	fprintf(stderr, "  -c    Enables coloured output\n");
#endif
	fprintf(stderr, "  -v    Prints version number\n");
	fprintf(stderr, "  -h    Displays this help information.\n");
	fprintf(stderr, "\nReport bugs to <%s>.\n", PACKAGE_BUGREPORT);
	exit(1);
}

int main(int argc, char **argv){
	extern char *optarg;
	int c;
	int colouron = 0;

	time_t last_update = 0;

	WINDOW *window;

	extern int errno;

	int delay=2;

	sg_init();
	if(sg_drop_privileges() != 0){
		fprintf(stderr, "Failed to drop setuid/setgid privileges\n");
		return 1;
	}

#ifdef COLOR_SUPPORT
	while ((c = getopt(argc, argv, "d:cvh")) != -1){
#else
	while ((c = getopt(argc, argv, "d:vh")) != -1){
#endif
		switch (c){
			case 'd':
				delay = atoi(optarg);
				if (delay < 1){
					fprintf(stderr, "Time must be 1 second or greater\n");
					exit(1);
				}
				break;
#ifdef COLOR_SUPPORT
			case 'c':
				colouron = 1;
				break;
#endif
			case 'v':
				version_num(argv[0]);
				break;
			case 'h':
			default:
				usage(argv[0]);
				return 1;
				break;
		}
	}

	signal(SIGWINCH, sig_winch_handler);
	initscr();
#ifdef COLOR_SUPPORT
	/* turn on colour */
	if (colouron) {
		if (has_colors()) {
			start_color();
			use_default_colors();
			init_pair(1,COLOR_RED,-1);
			init_pair(2,COLOR_GREEN,-1);
			init_pair(3,COLOR_YELLOW,-1);
			init_pair(4,COLOR_BLUE,-1);
			init_pair(5,COLOR_MAGENTA,-1);
			init_pair(6,COLOR_CYAN,-1);
		} else {
			fprintf(stderr, "Colour support disabled: your terminal does not support colour.");
			colouron = 0;
		}
	}
#endif
	nonl();
	curs_set(0);
	cbreak();
	noecho();
	timeout(delay * 1000);
	window=newwin(0, 0, 0, 0);
	clear();

	if(!get_stats()){
		fprintf(stderr, "Failed to get all the stats. Please check correct permissions\n");
		endwin();
		return 1;
	}

	display_headings();

	for(;;){
		time_t now;
		int ch = getch();

		if (ch == 'q'){
			break;
		}

		/* To keep the numbers slightly accurate we do not want them
		 * updating more frequently than once a second.
		 */
		now = time(NULL);
		if ((now - last_update) >= 1) {
			get_stats();
		}
		last_update = now;

		if(sig_winch_flag) {
			clear();
			display_headings();
			sig_winch_flag = 0;
		}

		display_data(colouron);
	}

	endwin();
	return 0;
}
