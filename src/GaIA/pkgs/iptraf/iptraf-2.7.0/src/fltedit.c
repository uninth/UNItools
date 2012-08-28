/***

fltedit.c	- TCP/UDP Filter Editing Facility

Copyright (c) Gerard Paul Java 1999, 2001

This software is open-source; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License in the included COPYING file for
details.

***/

#include <curses.h>
#include <panel.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>  
#include <menurt.h>
#include <winops.h>
#include <labels.h>
#include <msgboxes.h>
#include "fltdefs.h"
#include "fltmgr.h"
#include "othipflt.h"
#include "utfilter.h"
#include "dirs.h"
#include "getpath.h"
#include "attrs.h"
#include "deskman.h"
#include "error.h"

extern int daemonized;

/*
 * Union to hold both TCP/UDP and other IP filter parameters
 */
 
union hp_un {
    struct hostparams ut_hp;
    struct othipfltdata othip_data;
};

void init_filter_table(struct filterlist *fl)
{
    fl->head = fl->tail = NULL;
}

void definefilter(int protocol, int *aborted)
{
    struct filterfileent ffile;
    struct filterent fe;
    char fntemp[14];

    int pfd;
    int bw;
    int resp;

    /*
     * Lock facility
     */

    if (!mark_filter_change(protocol))
	return;

    get_filter_description(ffile.desc, aborted, "");

    if (*aborted) {
	clear_flt_tag(protocol);
	return;
    }
    genname(time((time_t *) NULL), fntemp);

    pfd =
	open(get_path(T_WORKDIR, fntemp), O_CREAT | O_WRONLY | O_TRUNC,
	     S_IRUSR | S_IWUSR);
    if (pfd < 0) {
	tx_errbox("Cannot create filter data file", ANYKEY_MSG,
	       &resp);
	*aborted = 1;
	clear_flt_tag(protocol);
	return;
    }
    do {
        if (protocol != F_OTHERIP)
	    gethostparams(&(fe.un.hp), aborted, "", "", "", "0.0.0.0", "0.0.0.0", "0",
		          "I");
	else {
	    bzero(&(fe.un.othipdata), sizeof(struct othipfltdata));
	    get_othip_hostparams(&(fe.un.othipdata), "", "", "0.0.0.0", "0.0.0.0", aborted);
        }
        
	if (!(*aborted)) {
	    if (protocol != F_OTHERIP)
	        bw = write(pfd, &(fe.un.hp), sizeof(struct hostparams));
	    else
	        bw = write(pfd, &(fe.un.othipdata), sizeof(struct othipfltdata));

	    if (bw < 0) {
		tx_errbox("Unable to write filter data", ANYKEY_MSG,
		       &resp);
		close(pfd);
		clear_flt_tag(protocol);
		return;
	    }
	}
    } while (!(*aborted));

    close(pfd);

    if (protocol == F_TCP)
	pfd =
	    open(TCPFLNAME, O_CREAT | O_WRONLY | O_APPEND,
		 S_IRUSR | S_IWUSR);
    else if (protocol == F_UDP)
	pfd =
	    open(UDPFLNAME, O_CREAT | O_WRONLY | O_APPEND,
		 S_IRUSR | S_IWUSR);
    else if (protocol == F_OTHERIP)
        pfd = 
            open(OTHIPFLNAME, O_CREAT | O_WRONLY | O_APPEND,
                 S_IRUSR | S_IWUSR);
                 
    if (pfd < 0) {
	listfileerr(1);
	clear_flt_tag(protocol);
	return;
    }
    strcpy(ffile.filename, fntemp);
    bw = write(pfd, &ffile, sizeof(struct filterfileent));
    if (bw < 0)
	listfileerr(2);

    close(pfd);

    clear_flt_tag(protocol);
}

/* 
 * Loads the filter from the filter file
 */

int loadfilter(int protocol, char *filename, struct filterlist *fl, int resolve)
{
    struct filterent *fe;
    int pfd;
    unsigned int idx = 0;
    int br;
    int resolv_err = 0;
    char protocol_str[10];
    char err_msg[80];
    
    init_filter_table(fl);

    pfd = open(filename, O_RDONLY);

    if (pfd < 0) {
        bzero(err_msg, 80);
        if (protocol == F_TCP)
            strcpy(protocol_str, "TCP");
        else if (protocol == F_UDP)
            strcpy(protocol_str, "UDP");
        else
            strcpy(protocol_str, "misc IP");
        
        snprintf(err_msg, 80, "Error opening %s filter data file", protocol_str);     
	write_error(err_msg, daemonized);
	fl->head = NULL;
	return 1;
    }
    do {
	fe = malloc(sizeof(struct filterent));
	if (protocol != F_OTHERIP)
	    br = read(pfd, &(fe->un.hp), sizeof(struct hostparams));
        else
            br = read(pfd, &(fe->un.othipdata), sizeof(struct othipfltdata));
            
	if (br > 0) {
	    fe->index = idx;
	    if (resolve) {
		fe->saddr = nametoaddr(fe->un.hp.s_fqdn, &resolv_err);
		fe->daddr = nametoaddr(fe->un.hp.d_fqdn, &resolv_err);

		if (resolv_err) {
		    free(fe);
		    continue;
		}

		fe->smask = inet_addr(fe->un.hp.s_mask);
		fe->dmask = inet_addr(fe->un.hp.d_mask);
	    }
	    if (fl->head == NULL) {
		fl->head = fe;
		fe->prev_entry = NULL;
	    } else {
		fl->tail->next_entry = fe;
		fe->prev_entry = fl->tail;
	    }
	    fe->next_entry = NULL;
	    fl->tail = fe;
	    idx++;
	} else {
	    free(fe);
	}
    } while (br > 0);

    if (br == 0)
	close(pfd);

    return 0;
}

void savefilter(unsigned int protocol, char *filename,
		struct filterlist *fl)
{
    struct filterent *fe = fl->head;
    int pfd;
    int bw;
    int resp;

    pfd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

    while (fe != NULL) {
        if (protocol != F_OTHERIP)
	    bw = write(pfd, &(fe->un.hp), sizeof(struct hostparams));
	else
	    bw = write(pfd, &(fe->un.othipdata), sizeof(struct othipfltdata));
	
	if (bw < 0) {
	    tx_errbox("Unable to save filter changes", ANYKEY_MSG, &resp);
	    clear_flt_tag(protocol);
	    return;
	}
	fe = fe->next_entry;
    }

    close(pfd);
}

/* 
 * Remove a currently applied filter from memory
 */

void destroyfilter(struct filterlist *fl)
{
    struct filterent *fe;
    struct filterent *cfe;

    if (fl->head != NULL) {
	fe = fl->head;
	cfe = fl->head->next_entry;

	do {
	    free(fe);
	    fe = cfe;
	    if (cfe != NULL)
		cfe = cfe->next_entry;
	} while (fe != NULL);

	fl->head = fl->tail = NULL;
    }
}

void print_hostparam_line(int protocol, struct filterent *fe, int idx, WINDOW * win, 
                          int attr)
{
    wattrset(win, attr);

    scrollok(win, 0);
    mvwprintw(win, idx, 0, "%78c", ' ');

    if (protocol != F_OTHERIP) {
        mvwaddnstr(win, idx, 2, fe->un.hp.s_fqdn, 15);
        wprintw(win, "/");
        waddnstr(win, fe->un.hp.s_mask, 12);
        wprintw(win, ":%u", fe->un.hp.sport);
        mvwaddnstr(win, idx, 38, fe->un.hp.d_fqdn, 15);
        wprintw(win, "/");
        waddnstr(win, fe->un.hp.d_mask, 12);
        wprintw(win, ":%u", fe->un.hp.dport);
        mvwprintw(win, idx, 76, "%c", toupper(fe->un.hp.reverse));
    } else {
        mvwaddnstr(win, idx, 2, fe->un.othipdata.hp.s_fqdn, 15);
        wprintw(win, "/");
        waddnstr(win, fe->un.othipdata.hp.s_mask, 15);
        mvwaddnstr(win, idx, 38, fe->un.othipdata.hp.d_fqdn, 15);
        wprintw(win, "/");
        waddnstr(win, fe->un.othipdata.hp.d_mask, 15);
        mvwprintw(win, idx, 76, "%c", toupper(fe->un.othipdata.hp.reverse));
    }
}

void update_hp_screen(int protocol, struct filterlist *fl,
		      struct filterent *firstvisible, WINDOW * win)
{
    struct filterent *ftmp = firstvisible;
    int i;

    wattrset(win, STDATTR);
    if (firstvisible == NULL) {
	mvwprintw(win, 0, 0, "%78c", ' ');
	return;
    }

    scrollok(win, 0);
    for (i = 0; i <= 12; i++) {
	if (ftmp != NULL) {
	    print_hostparam_line(protocol, ftmp, i, win, STDATTR);
	    ftmp = ftmp->next_entry;
	} else {
	    mvwprintw(win, i, 0, "%78c", ' ');
	}
    }
    scrollok(win, 1);
}

int new_hp_entry(struct filterent **ftemp)
{
    int resp;
    *ftemp = malloc(sizeof(struct filterent));
    if (*ftemp == NULL) {
	tx_errbox("No memory for new filter entry", ANYKEY_MSG, &resp);
	return 0;
    }
    
    bzero(*ftemp, sizeof(struct filterent));
    return 1;
}

void show_matched_protocols(WINDOW *win, struct filterent *fe)
{
    char protocols[80];
    
    bzero(protocols, 80);
    strcpy(protocols, "Matches: ");
    
    if (fe->un.othipdata.filters[F_ICMP])
        strcat(protocols, "ICMP  ");
    if (fe->un.othipdata.filters[F_IGMP])
        strcat(protocols, "IGMP  ");
    if (fe->un.othipdata.filters[F_OSPF])
        strcat(protocols, "OSPF  ");
    if (fe->un.othipdata.filters[F_IGP])
        strcat(protocols, "IGP  ");
    if (fe->un.othipdata.filters[F_IGRP])
        strcat(protocols, "IGRP  ");
    if (fe->un.othipdata.filters[F_GRE])
        strcat(protocols, "GRE  ");
    if (fe->un.othipdata.filters[F_OTHERIP])
        strcat(protocols, "Other IP");

    mvwprintw(win, 0, 0, "%80c", ' ');        
    mvwprintw(win, 0, 1, protocols);
}

void modify_host_parameters(unsigned int protocol, struct filterlist *fl)
{
    WINDOW *bwin;
    PANEL *bpanel;
    WINDOW *win;
    PANEL *panel;
    WINDOW *swin = NULL;
    PANEL *spanel = NULL;
    struct filterent *fe;
    struct filterent *ftemp;
    
    struct filterent *firstvisible = NULL;    /* cast to struct filterent */
    
    unsigned int idx = 0;
    int endloop_local = 0;
    int ch;
    int gh_aborted = 0;
    char s_portstr[8];
    char d_portstr[8];
    char inexstr[2];
    char sp_buf[10];
    union hp_un hptemp;

    bwin = newwin(15, 80, (LINES - 15) / 2, (COLS - 80) / 2);
    
    bpanel = new_panel(bwin);
    win = newwin(13, 78, (LINES - 13) / 2, (COLS - 78) / 2);
    panel = new_panel(win);
    
    if (protocol == F_OTHERIP) {
        swin = newwin(1, COLS, (LINES - 15) / 2 + 15, 0);
        spanel = new_panel(swin);
        wattrset(swin, DLGTEXTATTR);
        scrollok(swin, 0);
        sprintf(sp_buf, "%%%dc", COLS);
        mvwprintw(swin, 0, 0, sp_buf, ' ');
    }
    
    wattrset(bwin, BOXATTR);
    box(bwin, ACS_VLINE, ACS_HLINE);
    
    if (protocol != F_OTHERIP) {
        mvwprintw(bwin, 0, 2, " First Host/Mask:Port ");
        mvwprintw(bwin, 0, 38, " Second Host/Mask:Port ");
        mvwprintw(bwin, 0, 74, " I/E ");
    } else {
        mvwprintw(bwin, 0, 2, " Source Host/Mask ");
        mvwprintw(bwin, 0, 38, " Destination Host/Mask ");
        mvwprintw(bwin, 0, 74, "I/E");
        wattrset(bwin, BOXATTR);
    }    
    
    wmove(bwin, 14, 1);
    if (protocol == F_TCP)
	wprintw(bwin, " TCP");
    else if (protocol == F_UDP)
	wprintw(bwin, " UDP");
    else
        wprintw(bwin, " Misc IP");

    wprintw(bwin, " Filter Data ");
    tx_stdwinset(win);
    scrollok(win, 0);
    wattrset(win, STDATTR);
    tx_colorwin(win);

    move(LINES - 1, 1);
    tx_printkeyhelp("Up/Down", "-move ptr ", stdscr, HIGHATTR, STATUSBARATTR);
    tx_printkeyhelp("I", "-insert ", stdscr, HIGHATTR, STATUSBARATTR);
    tx_printkeyhelp("A", "-add to list ", stdscr, HIGHATTR, STATUSBARATTR);
    tx_printkeyhelp("D", "-delete ", stdscr, HIGHATTR, STATUSBARATTR);
    tx_printkeyhelp("Enter", "-edit ", stdscr, HIGHATTR, STATUSBARATTR);
    tx_printkeyhelp("X/Ctrl+X", "-exit", stdscr, HIGHATTR, STATUSBARATTR);

    update_panels();
    doupdate();

    firstvisible = fl->head;
    
    update_hp_screen(protocol, fl, firstvisible, win);
    
    idx = 0;
    fe = firstvisible;
    
    update_panels();
    doupdate();
    
    do {
	if (fe != NULL) {
            print_hostparam_line(protocol, fe, idx, win, BARSTDATTR);
	    if (protocol == F_OTHERIP) {
	        show_matched_protocols(swin, fe);
	        update_panels();
	        doupdate();
	    }
	}
	
	ch = wgetch(win);

        if (fe != NULL)
            print_hostparam_line(protocol, fe, idx, win, STDATTR);

	switch (ch) {
	case KEY_UP:
	    if (fl->head != NULL) {
		if (fe->prev_entry != NULL) {
		    if (idx > 0)
			idx--;
		    else {
		        scrollok(win, 1);
			wscrl(win, -1);
			firstvisible = firstvisible->prev_entry;
		    }
		    fe = fe->prev_entry;
		}
	    }
	    break;
	case KEY_DOWN:
	    if (fl->head != NULL) {
		if (fe->next_entry != NULL) {
		    if (idx < 12)
			idx++;
		    else {
		        scrollok(win, 1);
			wscrl(win, 1);
			firstvisible = firstvisible->next_entry;
		    }
		    fe = fe->next_entry;
		}
	    }
	    break;
	case 'i':
	case 'I':
	case KEY_IC:
	    if (!new_hp_entry(&ftemp))
		break;
            
            if (protocol != F_OTHERIP)
	        gethostparams(&(ftemp->un.hp), &gh_aborted, "", "", "", "0.0.0.0",
			  "0.0.0.0", "0", "I");
            else
                get_othip_hostparams(&(ftemp->un.othipdata), "", "", 
                                     "0.0.0.0", "0.0.0.0", &gh_aborted);
            
	    if (gh_aborted) {
		free(ftemp);
		continue;
	    }

	    if (fl->head == NULL) {
		ftemp->next_entry = ftemp->prev_entry = NULL;
		fl->head = fl->tail = ftemp;
		firstvisible = fl->head;
		idx = 0;
	    } else {
		ftemp->next_entry = fe;
		ftemp->prev_entry = fe->prev_entry;

		/*
		 * Point firstvisible at new entry if we inserted at the
		 * top of the list.
		 */

		if (ftemp->prev_entry == NULL) {
		    fl->head = ftemp;
		    firstvisible = ftemp;
		} else
	   	    fe->prev_entry->next_entry = ftemp;

		fe->prev_entry = ftemp;
	    }

	    if (ftemp->next_entry == NULL)
		fl->tail = ftemp;

	    fe = ftemp;
	    update_hp_screen(protocol, fl, firstvisible, win);
	    break;
	case 'a':
	case 'A':
	case 1:
	    if (!new_hp_entry(&ftemp))
		break;
            
            if (protocol != F_OTHERIP)
	        gethostparams(&(ftemp->un.hp), &gh_aborted, "", "", "", "0.0.0.0",
			  "0.0.0.0", "0", "I");
            else
                get_othip_hostparams(&(ftemp->un.othipdata), "", "", "0.0.0.0", "0.0.0.0", &gh_aborted);
                
	    if (gh_aborted) {
		free(ftemp);
		continue;
	    }

	    /*
	     * Add new node to the end of the list (or to the head if the
	     * list is empty.
	     */
	    if (fl->tail != NULL) {
		fl->tail->next_entry = ftemp;
		ftemp->prev_entry = fl->tail;
	    } else {
		fl->head = ftemp;
		fl->tail = ftemp;
		ftemp->prev_entry = ftemp->next_entry = NULL;
		firstvisible = fl->head;
		fe = ftemp;
		idx = 0;
	    }

	    ftemp->next_entry = NULL;
	    fl->tail = ftemp;
	    update_hp_screen(protocol, fl, firstvisible, win);
	    break;
	case 'd':
	case 'D':
	case KEY_DC:
	    if (fl->head != NULL) {
		/*
		 * Move firstvisible down if it's pointing to the target
		 * entry.
		 */

		if (firstvisible == fe)
		    firstvisible = fe->next_entry;

		/*
		 * Detach target node from list.
		 */
		if (fe->next_entry != NULL)
		    fe->next_entry->prev_entry = fe->prev_entry;
		else
		    fl->tail = fe->prev_entry;

		if (fe->prev_entry != NULL)
		    fe->prev_entry->next_entry = fe->next_entry;
		else
		    fl->head = fe->next_entry;

		/*
		 * Move pointer up if we're deleting the last entry.
		 * The list tail pointer has since been moved to the
		 * previous entry.
		 */
		if (fe->prev_entry == fl->tail) {
		    ftemp = fe->prev_entry;

		    /*
		     * Move screen pointer up. Really adjust the index if
		     * the pointer is anywhere below the top of the screen.
		     */
		    if (idx > 0)
			idx--;
		    else {
			/*
			 * Otherwise scroll the list down, and adjust the
			 * firstvisible pointer to point to the entry
			 * previous to the target.
			 */
			if (ftemp != NULL) {
			    firstvisible = ftemp;
			}
		    }
		} else
		    /*
		     * If we reach this point, we're deleting from before
		     * the tail of the list.  In that case, we point the
		     * screen pointer at the entry following the target.
		     */
		    ftemp = fe->next_entry;

		free(fe);
		fe = ftemp;
		update_hp_screen(protocol, fl, firstvisible, win);
	    }
	    break;
	case 13:
	    if (fe != NULL) {
	        if (protocol != F_OTHERIP) {
		    sprintf(s_portstr, "%u", fe->un.hp.sport);
		    sprintf(d_portstr, "%u", fe->un.hp.dport);
		    inexstr[0] = toupper(fe->un.hp.reverse);
		    inexstr[1] = '\0';
		    gethostparams(&(hptemp.ut_hp), &gh_aborted,
			      fe->un.hp.s_fqdn, fe->un.hp.s_mask, s_portstr,
			      fe->un.hp.d_fqdn, fe->un.hp.d_mask, d_portstr,
			      inexstr);

		    if (!gh_aborted)
		        memcpy(&(fe->un.hp), &(hptemp.ut_hp), sizeof(struct hostparams));
                } else {
                    memcpy(&(hptemp.othip_data), &(fe->un.othipdata), sizeof(struct othipfltdata));
                    get_othip_hostparams(&(hptemp.othip_data), 
                        fe->un.othipdata.hp.s_fqdn, fe->un.othipdata.hp.s_mask,
                        fe->un.othipdata.hp.d_fqdn, fe->un.othipdata.hp.d_mask,
                        &gh_aborted);
                        
                    if (!gh_aborted)
                        memcpy(&(fe->un.othipdata), &(hptemp.othip_data), sizeof(struct othipfltdata));
                }             
		update_hp_screen(protocol, fl, firstvisible, win);
	    }

	    break;
	case 'x':
	case 'X':
	case 'q':
	case 'Q':
	case 27:
	case 24:
	    endloop_local = 1;
	    break;
	case 'l':
	case 'L':
	    tx_refresh_screen();
	    break;
	}
	update_panels();
	doupdate();
    } while (!endloop_local);

    if (protocol == F_OTHERIP) {
        del_panel(spanel);
        delwin(swin);
    }
    
    del_panel(panel);
    delwin(win);
    del_panel(bpanel);
    delwin(bwin);
    update_panels();
    doupdate();
}

/*
 * Edit an existing filter
 */
void editfilter(unsigned int protocol, int *aborted)
{
    char filename[FLT_FILENAME_MAX];
    struct filterlist fl;
    struct ffnode *flist;
    struct ffnode *ffile;
    struct filterfileent *ffe;

    if (!mark_filter_change(protocol))
	return;

    if (loadfilterlist(protocol, &flist) == 1) {
	listfileerr(1);
	destroyfilterlist(flist);
	clear_flt_tag(protocol);
	return;
    }
    pickafilter(flist, &ffile, aborted);

    clear_flt_tag(protocol);
    if ((*aborted)) {
	destroyfilterlist(flist);
	clear_flt_tag(protocol);
	return;
    }
    ffe = &(ffile->ffe);

    get_filter_description(ffe->desc, aborted, ffe->desc);

    if (*aborted) {
	destroyfilterlist(flist);
	clear_flt_tag(protocol);
	return;
    }
    strncpy(filename, get_path(T_WORKDIR, ffe->filename),
	    FLT_FILENAME_MAX - 1);

    if (loadfilter(protocol, filename, &fl, FLT_DONTRESOLVE))
	return;

    modify_host_parameters(protocol, &fl);

    save_filterlist(protocol, flist);	/* This also destroys it */
    savefilter(protocol, filename, &fl);
    destroyfilter(&fl);
}

/*
 * Delete a filter record from the disk
 */

void delfilter(unsigned int protocol, int *aborted)
{
    struct ffnode *fltfile;
    struct ffnode *fltlist;

    if (!mark_filter_change(protocol))
	return;

    if (loadfilterlist(protocol, &fltlist) == 1) {
	*aborted = 1;
	listfileerr(1);
	destroyfilterlist(fltlist);
	clear_flt_tag(protocol);
	return;
    }
    pickafilter(fltlist, &fltfile, aborted);

    if (*aborted) {
	clear_flt_tag(protocol);
	return;
    }
    unlink(get_path(T_WORKDIR, fltfile->ffe.filename));

    if (fltfile->prev_entry == NULL) {
	fltlist = fltlist->next_entry;
	if (fltlist != NULL)
	    fltlist->prev_entry = NULL;
    } else {
	fltfile->prev_entry->next_entry = fltfile->next_entry;

	if (fltfile->next_entry != NULL)
	    fltfile->next_entry->prev_entry = fltfile->prev_entry;
    }

    free(fltfile);

    save_filterlist(protocol, fltlist);
    clear_flt_tag(protocol);
    *aborted = 0;
}
