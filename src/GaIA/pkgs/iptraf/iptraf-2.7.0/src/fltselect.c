
/***
 
fltselect.c - a menu-based module that allows selection of
	other protocols to display
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
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <netinet/udp.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <winops.h>
#include <menurt.h>
#include <msgboxes.h>
#include "addproto.h"
#include "dirs.h"
#include "fltdefs.h"
#include "fltselect.h"
#include "utfilter.h"
#include "fltedit.h"
#include "fltmgr.h"
#include "deskman.h"
#include "attrs.h"
#include "instances.h"

void setfilters(struct filterstate *filter, unsigned int row)
{
    int aborted;
    switch (row) {
    case 1:
        tcpfilterselect(&(filter->tfl), &(filter->tfiltercode),
                        filter->tfilename, &aborted);
        break;
    case 2:
	udpfilterselect(&(filter->ufl), &(filter->ufiltercode),
			filter->ufilename, &aborted);
	break;
    case 3:
        othip_filter_select(&(filter->ofl), filter->ofilename, &(filter->ofiltercode));
	break;
    case 4:
	filter->arp = ~(filter->arp);
	break;
    case 5:
	filter->rarp = ~(filter->rarp);
	break;
    case 6:
	filter->nonip = ~(filter->nonip);
	break;
    }
}

void toggleprotodisplay(WINDOW * win, struct filterstate *filter,
			unsigned int row)
{
    wmove(win, row, 2);
    switch (row) {
    case 1:
        if (filter->tfiltercode == 0)
            wprintw(win, "No TCP filter applied");
        else if (filter->tfiltercode == 1)
            wprintw(win, "TCP filter applied   ");
        break;
    case 2:
        if (filter->ufiltercode == 0)
            wprintw(win, "No UDP packets visible");
        else if (filter->ufiltercode == 1)
            wprintw(win, "All UDP visible       ");
        else if (filter->ufiltercode == 2)
            wprintw(win, "UDP filter applied    ");
        break;
    case 3:
        if (filter->ofiltercode == 0)
            wprintw(win, "No misc IP filter applied");
        else if (filter->ofiltercode == 1)
            wprintw(win, "Misc IP filter applied   ");
        break;
    case 4:
	if (filter->arp)
	    wprintw(win, "ARP visible    ");
	else
	    wprintw(win, "ARP not visible");

	break;
    case 5:
	if (filter->rarp)
	    wprintw(win, "RARP visible    ");
	else
	    wprintw(win, "RARP not visible");

	break;
    case 6:
	if (filter->nonip)
	    wprintw(win, "Non-IP visible    ");
	else
	    wprintw(win, "Non-IP not visible");

	break;
    }
}

int othfilterok(struct filterstate *filter, unsigned int protocol,
		unsigned long saddr, unsigned long daddr,
		unsigned int sport, unsigned int dport)
{
    int result = 0;

    switch (protocol) {
    case IPPROTO_UDP:
	if (filter->ufiltercode == 0)
	    result = 0;
	else if (filter->ufiltercode == 1)
	    result = 1;
	else if (filter->ufiltercode == 2)
	    if (utfilter
		(&(filter->ufl), saddr, daddr, sport, dport,
		 IPPROTO_UDP))
	        result = 1;
	break;
    case ETH_P_ARP:
	result = filter->arp;
	break;
    case ETH_P_RARP:
	result = filter->rarp;
	break;
    case 0:
	result = filter->nonip;
	break;
    default:
        if (filter->ofiltercode == 0)
            result = 1;
        else
            result = othip_filter(saddr, daddr, protocol, &(filter->ofl));
        break;
    }

    return result;
}

void config_filters(struct filterstate *filter)
{
    struct MENU menu;
    WINDOW *statwin;
    PANEL *statpanel;
    WINDOW *infowin;
    PANEL *infopanel;
    int row;
    int aborted;

    statwin = newwin(8, 30, (LINES - 8) / 2, (COLS - 15) / 2 + 10);
    statpanel = new_panel(statwin);
    wattrset(statwin, BOXATTR);
    tx_colorwin(statwin);
    box(statwin, ACS_VLINE, ACS_HLINE);
    tx_stdwinset(statwin);
    wmove(statwin, 0, 1);
    wprintw(statwin, " Filter Status ");
    wattrset(statwin, STDATTR);
    infowin = newwin(2, COLS, LINES - 4, 0);
    infopanel = new_panel(infowin);
    wattrset(infowin, DESKTEXTATTR);
    tx_colorwin(infowin);
    mvwprintw(infowin, 0, 0, " Filters affect the IP traffic monitor, interface statistics, and TCP/UDP");
    mvwprintw(infowin, 1, 0, " protocol breakdown.  The packet size breakdown and LAN monitor are unaffected.");
    update_panels();
    doupdate();

    for (row = 1; row <= 11; row++)
	toggleprotodisplay(statwin, filter, row);

    makemainfiltermenu(&menu);

    row = 1;
    do {
	tx_showmenu(&menu);
	tx_operatemenu(&menu, &row, &aborted);
	if (row <= 6) {
	    setfilters(filter, row);
	    toggleprotodisplay(statwin, filter, row);
	}
    } while (row != 8);

    tx_destroymenu(&menu);
    del_panel(statpanel);
    delwin(statwin);
    del_panel(infopanel);
    delwin(infowin);
    update_panels();
    doupdate();
}

void setodefaults(struct filterstate *filter)
{
    bzero(filter, sizeof(struct filterstate));
    filter->ufiltercode = 1;
}

void loadfilters(struct filterstate *filter)
{
    int pfd;
    int br;

    pfd = open(FLTSTATEFILE, O_RDONLY);	/* open filter state file */

    if (pfd < 0) {
	setodefaults(filter);
	return;
    }
    br = read(pfd, filter, sizeof(struct filterstate));
    if (br < 0)
	setodefaults(filter);

    close(pfd);

    /*
     * Reload TCP filter if one was previously applied
     */
     
    if (filter->tfiltercode != 0)
        loadfilter(F_TCP, filter->tfilename, &(filter->tfl), FLT_RESOLVE);
    
    /* 
     * Reload custom UDP filter if one was previously set
     */

    if (filter->ufiltercode == 2)
	loadfilter(F_UDP, filter->ufilename, &(filter->ufl), FLT_RESOLVE);
	
    /*
     * Reload filter for other IP protocols if one was previously applied
     */
     
    if (filter->ofiltercode != 0)
        loadfilter(F_OTHERIP, filter->ofilename, &(filter->ofl), FLT_RESOLVE);
}

void savefilters(struct filterstate *filter)
{
    int pfd;
    int bw;
    int resp;

    if (!facility_active(OTHFLTIDFILE, ""))
	mark_facility(OTHFLTIDFILE, "Filter configuration change", "");
    else {
	tx_errbox("Filter state file currently in use; try again later",
	       ANYKEY_MSG, &resp);
	return;
    }

    pfd = open(FLTSTATEFILE, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    bw = write(pfd, filter, sizeof(struct filterstate));
    if (bw < 1)
	tx_errbox("Unable to write filter state information", ANYKEY_MSG, &resp);

    close(pfd);

    unmark_facility(OTHFLTIDFILE, "");
}
