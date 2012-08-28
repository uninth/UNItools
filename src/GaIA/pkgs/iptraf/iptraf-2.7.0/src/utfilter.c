   
/***

utfilter.c  - UDP/TCP display filter module
Written by Gerard Paul Java
Copyright (c) Gerard Paul Java 1997, 1998

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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <input.h>
#include <menurt.h>
#include <msgboxes.h>
#include "dirs.h"
#include "getpath.h"
#include "deskman.h"
#include "attrs.h"
#include "fltdefs.h"
#include "fltmgr.h"
#include "utfilter.h"
#include "fltedit.h"

extern int daemonized;

void gethostparams(struct hostparams *hp, int *aborted,
		   char *initsrc, char *initsmask, char *initsport,
		   char *initdest, char *initdmask, char *initdport,
		   char *initinex)
{
    struct FIELDLIST fieldlist;
    struct FIELD *dlist;
    WINDOW *dlgwin;
    PANEL *dlgpanel;

    dlgwin = newwin(12, 80, (LINES - 12) / 2, (COLS - 80) / 2);
    dlgpanel = new_panel(dlgwin);

    wattrset(dlgwin, DLGBOXATTR);
    tx_colorwin(dlgwin);
    box(dlgwin, ACS_VLINE, ACS_HLINE);
    wmove(dlgwin, 0, 26);
    wprintw(dlgwin, " First ");

    wmove(dlgwin, 0, 52);
    wprintw(dlgwin, " Second ");

    wattrset(dlgwin, DLGTEXTATTR);
    wmove(dlgwin, 2, 2);
    wprintw(dlgwin, "Host name/IP address:");
    wmove(dlgwin, 4, 2);
    wprintw(dlgwin, "Wildcard mask:");
    wmove(dlgwin, 6, 2);
    wprintw(dlgwin, "Port:");
    wmove(dlgwin, 8, 2);
    wprintw(dlgwin, "Include/Exclude (I/E):");
    wmove(dlgwin, 10, 2);
    tabkeyhelp(dlgwin);
    wmove(dlgwin, 10, 20);
    stdkeyhelp(dlgwin);
    update_panels();
    doupdate();

    tx_initfields(&fieldlist, 8, 52, (LINES - 12) / 2 + 1,
	       (COLS - 80) / 2 + 27, DLGTEXTATTR, FIELDATTR);

    tx_addfield(&fieldlist, 25, 1, 0, initsrc);
    tx_addfield(&fieldlist, 25, 3, 0, initsmask);
    tx_addfield(&fieldlist, 5, 5, 0, initsport);
    tx_addfield(&fieldlist, 25, 1, 26, initdest);
    tx_addfield(&fieldlist, 25, 3, 26, initdmask);
    tx_addfield(&fieldlist, 5, 5, 26, initdport);
    tx_addfield(&fieldlist, 1, 7, 0, initinex);

    dlist = fieldlist.list->nextfield->nextfield->nextfield;

    tx_fillfields(&fieldlist, aborted);

    if (!(*aborted)) {
        strcpy(hp->s_fqdn, fieldlist.list->buf);
        strcpy(hp->s_mask, fieldlist.list->nextfield->buf);
        hp->sport = atoi(fieldlist.list->nextfield->nextfield->buf);

        strcpy(hp->d_fqdn, dlist->buf);
        strcpy(hp->d_mask, dlist->nextfield->buf);
        hp->dport = atoi(dlist->nextfield->nextfield->buf);
        hp->reverse = toupper(dlist->nextfield->nextfield->nextfield->buf[0]);
    }
    
    tx_destroyfields(&fieldlist);
    del_panel(dlgpanel);
    delwin(dlgwin);
    update_panels();
    doupdate();
}

/*
 * The TCP/UDP display filter
 */

int utfilter(struct filterlist *fl,
	     unsigned long source, unsigned long dest,
	     unsigned int sport, unsigned int dport, unsigned int protocol)
{
    struct filterent *fe;
    unsigned long fsaddr, fdaddr;
    unsigned long csaddr, cdaddr;
    unsigned long crsaddr, crdaddr;
    int flt_expr1 = 0;
    int flt_expr2 = 0;

    fe = fl->head;

    while (fe != NULL) {
	fsaddr = fe->saddr & fe->smask;
	fdaddr = fe->daddr & fe->dmask;
	csaddr = source & fe->smask;
	cdaddr = dest & fe->dmask;
	crsaddr = source & fe->dmask;
	crdaddr = dest & fe->smask;

	/*
	 * Just using two variables to make it easier to read
	 */

	flt_expr1 = ((csaddr == fsaddr)
		     && ((fe->un.hp.sport == sport) || (fe->un.hp.sport == 0)))
	    && ((cdaddr == fdaddr)
		&& ((fe->un.hp.dport == dport) || (fe->un.hp.dport == 0)));

	flt_expr2 = ((crsaddr == fdaddr)
		     && ((fe->un.hp.dport == sport) || (fe->un.hp.dport == 0)))
	    && ((crdaddr == fsaddr)
		&& ((fe->un.hp.sport == dport) || (fe->un.hp.sport == 0)));

	if (flt_expr1 || flt_expr2) {
	    if (toupper(fe->un.hp.reverse) == 'E')	/* Exclusive */
		return 0;

	    return 1;
	}
	fe = fe->next_entry;
    }

    return 0;
}


/* display a menu and perform appropriate filter action */

void udpfilterselect(struct filterlist *fl,
		     unsigned int *filtercode,
		     char *filename, int *faborted)
{
    struct MENU fmenu;
    struct filterfileent ffe;
    unsigned int frow;

    makeudpfiltermenu(&fmenu);

    frow = 1;

    do {
	tx_showmenu(&fmenu);
	tx_operatemenu(&fmenu, &frow, faborted);

	switch (frow) {
	case 1:
	    *filtercode = 1;
	    tx_infobox("All UDP packets will be displayed", ANYKEY_MSG);
	    break;
	case 2:
	    if (*filtercode == 2)
		destroyfilter(fl);

	    *filtercode = 0;
	    tx_infobox("No UDP packets will be displayed", ANYKEY_MSG);
	    break;
	case 3:
	    definefilter(F_UDP, faborted);
	    break;
	case 4:
	    selectfilter(F_UDP, &ffe, faborted);
	    if (!(*faborted)) {
		strncpy(filename, get_path(T_WORKDIR, ffe.filename),
			FLT_FILENAME_MAX - 1);
		loadfilter(F_UDP, filename, fl, FLT_RESOLVE);
		*filtercode = 2;
	    }
	    break;
	case 5:
	    editfilter(F_UDP, faborted);
	    break;
	case 6:
	    delfilter(F_UDP, faborted);
	    if (!(*faborted))
	        tx_infobox("Custom UDP filter deleted", ANYKEY_MSG);
	    break;
	}
    } while (frow != 8);

    tx_destroymenu(&fmenu);
    update_panels();
    doupdate();
}


/* 
 * Display a menu and perform appropriate filter operation
 */

void tcpfilterselect(struct filterlist *fl, 
		     unsigned int *filtered, char *filename, int *faborted)
{
    struct MENU fmenu;
    unsigned int frow;
    struct filterfileent ffe;

    makestdfiltermenu(&fmenu);

    frow = 1;
    do {
	tx_showmenu(&fmenu);
	tx_operatemenu(&fmenu, &frow, faborted);

	switch (frow) {
	case 1:
	    definefilter(F_TCP, faborted);
	    break;
	case 2:
	    selectfilter(F_TCP, &ffe, faborted);
	    if (!(*faborted)) {
		strncpy(filename, get_path(T_WORKDIR, ffe.filename),
			FLT_FILENAME_MAX - 1);
		if (!loadfilter(F_TCP, filename, fl, FLT_RESOLVE)) {
		    *filtered = 1;
		}
	    }
	    break;
	case 3:
	    if (*filtered) {
		destroyfilter(fl);
		*filtered = 0;
	    }
	    unlink(TCPFILTERSAVE);
	    tx_infobox("TCP filter deactivated", ANYKEY_MSG);
	    break;
	case 4:
	    editfilter(F_TCP, faborted);
	    break;
	case 5:
	    delfilter(F_TCP, faborted);
	    if (!(*faborted))
	        tx_infobox("TCP filter deleted", ANYKEY_MSG);
	    break;
	}
    } while (frow != 7);

    tx_destroymenu(&fmenu);
    update_panels();
    doupdate();
}
