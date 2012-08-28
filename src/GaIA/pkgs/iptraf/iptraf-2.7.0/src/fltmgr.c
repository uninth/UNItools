 
/***

fltmgr.c - filter list management routines

Copyright (c) Gerard Paul Java 1998

This software is open source; you can redistribute it and/or modify
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
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <listbox.h>
#include <labels.h>
#include <input.h>
#include <menurt.h>
#include <msgboxes.h>
#include "attrs.h"
#include "deskman.h"
#include "dirs.h"
#include "fltdefs.h"
#include "fltmgr.h"
#include "instances.h"
#include "error.h"

extern int daemonized;

void makestdfiltermenu(struct MENU *menu)
{
    tx_initmenu(menu, 9, 31, (LINES - 8) / 2, (COLS - 31) / 2 + 15,
        BOXATTR, STDATTR, HIGHATTR, BARSTDATTR, BARHIGHATTR, DESCATTR);
    tx_additem(menu, " ^D^efine new filter...",
	    "Defines a new set of filter parameters");
    tx_additem(menu, " ^A^pply filter...",
	    "Applies a defined filter");
    tx_additem(menu, " Detac^h^ filter",
	    "Removes the currently applied filter");
    tx_additem(menu, " ^E^dit filter...",
	    "Modifies existing filter data");
    tx_additem(menu, " Dele^t^e filter...",
	    "Removes a TCP filter from the filter list");
    tx_additem(menu, NULL, NULL);
    tx_additem(menu, " E^x^it menu", "Returns to the main menu");
}

void makeudpfiltermenu(struct MENU *menu)
{
    tx_initmenu(menu, 10, 38, (LINES - 11) / 2 + 1, (COLS - 38) / 2 + 18,
        BOXATTR, STDATTR, HIGHATTR, BARSTDATTR, BARHIGHATTR, DESCATTR);
    tx_additem(menu, " Show ^a^ll UDP packets",
	    "Permits display of all UDP packets");
    tx_additem(menu, " Show ^n^o UDP packets",
	    "Omits all UDP packets from display");
    tx_additem(menu, " ^D^efine custom UDP filter...",
	    "Defines a custom UDP filter");
    tx_additem(menu, " Apply ^c^ustom UDP filter...",
	    "Applies a custom UDP filter");
    tx_additem(menu, " ^E^dit custom UDP filter...",
	    "Modifies a custom UDP filter");
    tx_additem(menu, " Dele^t^e custom UDP filter...",
	    "Removes a custom UDP filter");
    tx_additem(menu, NULL, NULL);
    tx_additem(menu, " E^x^it menu", "Returns to the main menu");
}

void makemainfiltermenu(struct MENU *menu)
{
    tx_initmenu(menu, 10, 15, (LINES - 8) / 2, (COLS - 15) / 2 - 5,
        BOXATTR, STDATTR, HIGHATTR, BARSTDATTR, BARHIGHATTR, DESCATTR);
    tx_additem(menu, " ^T^CP...", "Transmission Control Protocol");
    tx_additem(menu, " ^U^DP...", "User Datagram Protocol");
    tx_additem(menu, " ^O^ther IP...", "Other IP protocols");
    tx_additem(menu, " ^A^RP", "Address Resolution Protocol");
    tx_additem(menu, " RAR^P^ ", "Reverse Address Resolution Protocol");
    tx_additem(menu, " ^N^on-IP", "Non-IP packets");
    tx_additem(menu, NULL, NULL);
    tx_additem(menu, " E^x^it menu", "Return to main menu");
}

/*
 * Generate a string representation of a number to be used as a name.
 */

void genname(unsigned long n, char *m)
{
    sprintf(m, "%lu", n);
}

int mark_filter_change(int protocol)
{
    int resp;

    if (protocol == F_TCP) {
	if (!facility_active(TCPFLTIDFILE, ""))
	    mark_facility(TCPFLTIDFILE, "TCP filter change", "");
	else {
	    tx_errbox("TCP filter data file in use; try again later",
		   ANYKEY_MSG, &resp);
	    return 0;
	}
    } else if (protocol == F_UDP) {
	if (!facility_active(UDPFLTIDFILE, ""))
	    mark_facility(UDPFLTIDFILE, "UDP filter change", "");
	else {
	    tx_errbox("UDP filter data file in use; try again later",
		   ANYKEY_MSG, &resp);
	    return 0;
	}
    } else {
        if (!facility_active(OTHIPFLTIDFILE, ""))
            mark_facility(OTHIPFLTIDFILE, "Other IP filter change", "");
        else {
            tx_errbox("Other IP protocol filter data file in use; try again later",
                   ANYKEY_MSG, &resp);
            return 0;
        }
    }
    return 1;
}

void clear_flt_tag(int protocol)
{
    if (protocol == F_TCP)
	unmark_facility(TCPFLTIDFILE, "");
    else if (protocol == F_UDP)
	unmark_facility(UDPFLTIDFILE, "");
    else
        unmark_facility(OTHIPFLTIDFILE, "");
}

void listfileerr(int code)
{
    if (code == 1)
	write_error("Error loading filter list file", daemonized);
    else
	write_error("Error writing filter list file", daemonized);
}

unsigned long int nametoaddr(char *ascname, int *err)
{
    unsigned long int result;
    struct hostent *he;
    char imsg[45];
    struct in_addr inp;
    int resolv_err = 0;

    resolv_err = inet_aton(ascname, &inp);
    if (resolv_err == 0) {
	snprintf(imsg, 45, "Resolving %s", ascname);
	indicate(imsg);
	he = gethostbyname(ascname);
	if (he != NULL)
	    bcopy((he->h_addr_list)[0], &result, he->h_length);
	else {
	    snprintf(imsg, 45, "Unable to resolve %s", ascname);
	    write_error(imsg, daemonized);
	    *err = 1;
	    return (-1);
	}
    } else
	result = inp.s_addr;

    return (result);
    *err = 0;
}

int loadfilterlist(unsigned int protocol, struct ffnode **fltfile)
{
    int pfd = 0;
    int result = 0;

    struct ffnode *ffiles = NULL;
    struct ffnode *ptemp;
    struct ffnode *tail = NULL;

    int br;

    if (protocol == F_TCP)
	pfd = open(TCPFLNAME, O_RDONLY);
    else if (protocol == F_UDP)
	pfd = open(UDPFLNAME, O_RDONLY);
    else if (protocol == F_OTHERIP)
        pfd = open(OTHIPFLNAME, O_RDONLY);

    if (pfd < 0) {
	*fltfile = NULL;
	return 1;
    }
    do {
	ptemp = malloc(sizeof(struct ffnode));
	br = read(pfd, &(ptemp->ffe), sizeof(struct filterfileent));

	if (br > 0) {
	    if (ffiles == NULL) {
		ffiles = ptemp;
		ffiles->prev_entry = NULL;
	    } else {
		tail->next_entry = ptemp;
		ptemp->prev_entry = tail;
	    }

	    ptemp->next_entry = NULL;
	    tail = ptemp;
	} else {
	    free(ptemp);

	    if (br < 0)
		result = 1;
	}
    } while (br > 0);

    close(pfd);
    *fltfile = ffiles;

    if (ffiles == NULL)
	result = 1;

    return result;
}

void destroyfilterlist(struct ffnode *fltlist)
{
    struct ffnode *fftemp;

    if (fltlist != NULL) {
	fftemp = fltlist->next_entry;

	do {
	    free(fltlist);
	    fltlist = fftemp;
	    if (fftemp != NULL)
		fftemp = fftemp->next_entry;
	} while (fltlist != NULL);
    }
}

void save_filterlist(unsigned int protocol, struct ffnode *fltlist)
{
    struct ffnode *fltfile;
    struct ffnode *ffntemp;
    int fd;
    int bw;

    if (protocol == F_TCP)
	fd =
	    open(TCPFLNAME, O_WRONLY | O_CREAT | O_TRUNC,
		 S_IRUSR | S_IWUSR);
    else if (protocol == F_UDP)
	fd =
	    open(UDPFLNAME, O_WRONLY | O_CREAT | O_TRUNC,
		 S_IRUSR | S_IWUSR);
    else
	fd =
	    open(OTHIPFLNAME, O_WRONLY | O_CREAT | O_TRUNC,
		 S_IRUSR | S_IWUSR);
    
    if (fd < 0) {
	listfileerr(2);
	clear_flt_tag(protocol);
	return;
    }
    fltfile = fltlist;
    while (fltfile != NULL) {
	bw = write(fd, &(fltfile->ffe), sizeof(struct filterfileent));

	if (bw < 0) {
	    listfileerr(2);
	    clear_flt_tag(protocol);
	    return;
	}
	ffntemp = fltfile;
	fltfile = fltfile->next_entry;
	free(ffntemp);
    }

    close(fd);
}

void operate_select(struct ffnode *ffiles,
		    struct ffnode **item, int *aborted)
{
    struct ffnode *pptr;
    int ch;
    struct scroll_list list;
    
    tx_listkeyhelp(STDATTR, HIGHATTR);
    update_panels();
    doupdate();
    
    pptr = ffiles;
    
    tx_init_listbox(&list, 60, 10, (COLS - 60) / 2 - 2, (LINES - 10) / 2 - 2,
        STDATTR, BOXATTR, BARSTDATTR, HIGHATTR);
    
    tx_set_listbox_title(&list, "Select Filter", 1);
    
    while (pptr != NULL) {
        tx_add_list_entry(&list, (char *) pptr, pptr->ffe.desc);
        pptr = pptr->next_entry;
    }
    
    tx_show_listbox(&list);
    tx_operate_listbox(&list, &ch, aborted);
    
    if (!(*aborted))     
        *item = (struct ffnode *) list.textptr->nodeptr;
        
    tx_close_listbox(&list);
    tx_destroy_list(&list);
}

void pickafilter(struct ffnode *ffiles,
		 struct ffnode **fltfile, int *aborted)
{
    operate_select(ffiles, fltfile, aborted);

    update_panels();
    doupdate();
}

void selectfilter(unsigned int protocol,
		  struct filterfileent *ffe, int *aborted)
{
    struct ffnode *fltfile;
    struct ffnode *ffiles;

    if (loadfilterlist(protocol, &ffiles) == 1) {
	listfileerr(1);
	*aborted = 1;
	destroyfilterlist(ffiles);
	return;
    }
    pickafilter(ffiles, &fltfile, aborted);

    if (!(*aborted))
	*ffe = fltfile->ffe;

    destroyfilterlist(ffiles);
}


void get_filter_description(char *description, int *aborted,
			    char *pre_edit)
{
    struct FIELDLIST descfield;
    int dlgwintop;
    WINDOW *dlgwin;
    PANEL *dlgpanel;
    int resp = 0;
    
    dlgwintop = (LINES - 9) / 2;
    dlgwin = newwin(7, 42, dlgwintop, (COLS - 42) / 2 - 10);
    dlgpanel = new_panel(dlgwin);
    wattrset(dlgwin, DLGBOXATTR);
    tx_colorwin(dlgwin);
    box(dlgwin, ACS_VLINE, ACS_HLINE);
    wattrset(dlgwin, DLGTEXTATTR);
    wmove(dlgwin, 2, 2);
    wprintw(dlgwin, "Enter a description for this filter");
    wmove(dlgwin, 5, 2);
    stdkeyhelp(dlgwin);
    update_panels();
    doupdate();

    tx_initfields(&descfield, 1, 35, dlgwintop + 3, (COLS - 42) / 2 - 8,
        DLGTEXTATTR, FIELDATTR);
    tx_addfield(&descfield, 33, 0, 0, pre_edit);
    
    do {
        tx_fillfields(&descfield, aborted);
    
        if ((descfield.list->buf[0] == '\0') && (!(*aborted)))
            tx_errbox("Enter an appropriate description for this filter", ANYKEY_MSG, &resp);
    } while ((descfield.list->buf[0] == '\0') && (!(*aborted)));
    
    if (!(*aborted))
        strcpy(description, descfield.list->buf);

    tx_destroyfields(&descfield);
    del_panel(dlgpanel);
    delwin(dlgwin);
    update_panels();
    doupdate();
}

