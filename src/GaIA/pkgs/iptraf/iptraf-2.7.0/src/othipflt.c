/***

othipflt.c - user interface and filter function for non-TCP and non-UDP
IP packets

Written by Gerard Paul Java
Copyright (c) Gerard Paul Java 2001

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
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <input.h>
#include <menurt.h>
#include <msgboxes.h>
#include "addproto.h"
#include "dirs.h" 
#include "deskman.h"
#include "attrs.h"
#include "fltdefs.h"
#include "fltmgr.h"
#include "othipflt.h"
#include "utfilter.h"
#include "fltedit.h"
#include "getpath.h"

extern int daemonized;

void get_othip_hostparams(struct othipfltdata *data, char *init_saddr,
                          char *init_smask, char *init_daddr, char *init_dmask,
			  int *aborted)
{
    WINDOW *dlgwin;
    PANEL *dlgpanel;

    struct FIELDLIST fields;
    struct FIELD *fieldptr;
    char *init_yesno = "Y"; 

    dlgwin = newwin(15, 80, (LINES - 15) / 2, (COLS - 80) / 2);
    dlgpanel = new_panel(dlgwin);

    wattrset(dlgwin, DLGBOXATTR);
    tx_colorwin(dlgwin);
    box(dlgwin, ACS_VLINE, ACS_HLINE);
    
    mvwprintw(dlgwin, 0, 22, " Source ");
    mvwprintw(dlgwin, 0, 52, " Destination ");
    
    wmove(dlgwin, 13, 2);
    tabkeyhelp(dlgwin);
    stdkeyhelp(dlgwin);
    wattrset(dlgwin, DLGTEXTATTR);
    mvwprintw(dlgwin, 2, 2, "IP address");
    mvwprintw(dlgwin, 4, 2, "Wildcard mask");
    mvwprintw(dlgwin, 7, 2, "Protocols to match");
    mvwprintw(dlgwin, 8, 2, "(Enter Y beside each");
    mvwprintw(dlgwin, 9, 2, "protocol to match.)");
    mvwprintw(dlgwin, 11, 2, "Include/Exclude (I/E)");

    tx_initfields(&fields, 12, 55, (LINES - 13) / 2, (COLS - 80) / 2 + 23,
        DLGTEXTATTR, FIELDATTR);
    mvwprintw(fields.fieldwin, 6, 5, "ICMP");
    mvwprintw(fields.fieldwin, 6, 15, "IGMP");
    mvwprintw(fields.fieldwin, 6, 25, "OSPF");
    mvwprintw(fields.fieldwin, 6, 36, "IGP");
    mvwprintw(fields.fieldwin, 6, 45, "IGRP");
    mvwprintw(fields.fieldwin, 8, 6, "GRE");
    mvwprintw(fields.fieldwin, 8, 13, "Oth IP");
    
    tx_addfield(&fields, 25, 1, 0, init_saddr);
    tx_addfield(&fields, 25, 3, 0, init_smask);
    tx_addfield(&fields, 25, 1, 30, init_daddr);
    tx_addfield(&fields, 25, 3, 30, init_dmask);
    
    if (data->filters[F_ICMP])
        init_yesno = "Y";
    else
        init_yesno = "";
    tx_addfield(&fields, 1, 6, 10, init_yesno);

    if (data->filters[F_IGMP])
        init_yesno = "Y";
    else
        init_yesno = "";
    tx_addfield(&fields, 1, 6, 20, init_yesno);
    if (data->filters[F_OSPF])
        init_yesno = "Y";
    else
        init_yesno = "";
    tx_addfield(&fields, 1, 6, 30, init_yesno);
    if (data->filters[F_IGP])
        init_yesno = "Y";
    else
        init_yesno = "";
    tx_addfield(&fields, 1, 6, 40, init_yesno);
    if (data->filters[F_IGRP])
        init_yesno = "Y";
    else
        init_yesno = "";
    tx_addfield(&fields, 1, 6, 50, init_yesno);
    if (data->filters[F_GRE])
        init_yesno = "Y";
    else
        init_yesno = "";
    tx_addfield(&fields, 1, 8, 10, init_yesno);
    if (data->filters[F_OTHERIP])
        init_yesno = "Y";
    else
        init_yesno = "";
    tx_addfield(&fields, 1, 8, 20, init_yesno);
    
    tx_addfield(&fields, 1, 10, 10, "I");
    
    tx_fillfields(&fields, aborted);
    
    if (!(*aborted)) {
        fieldptr = fields.list;
        strcpy(data->hp.s_fqdn, fieldptr->buf);
        fieldptr = fieldptr->nextfield;
        strcpy(data->hp.s_mask, fieldptr->buf);
        fieldptr = fieldptr->nextfield;
        strcpy(data->hp.d_fqdn, fieldptr->buf);
        fieldptr = fieldptr->nextfield;
        strcpy(data->hp.d_mask, fieldptr->buf);
        fieldptr = fieldptr->nextfield;
        
        bzero(&(data->filters), sizeof(data->filters));
        
        if (toupper(fieldptr->buf[0]) == 'Y')
            data->filters[F_ICMP] = 1;
        fieldptr = fieldptr->nextfield;
        if (toupper(fieldptr->buf[0]) == 'Y')
            data->filters[F_IGMP] = 1;
        fieldptr = fieldptr->nextfield;
        if (toupper(fieldptr->buf[0]) == 'Y')
            data->filters[F_OSPF] = 1;
        fieldptr = fieldptr->nextfield;
        if (toupper(fieldptr->buf[0]) == 'Y')
            data->filters[F_IGP] = 1;
        fieldptr = fieldptr->nextfield;
        if (toupper(fieldptr->buf[0]) == 'Y')
            data->filters[F_IGRP] = 1;
        fieldptr = fieldptr->nextfield;
        if (toupper(fieldptr->buf[0]) == 'Y')
            data->filters[F_GRE] = 1;
        fieldptr = fieldptr->nextfield;
        if (toupper(fieldptr->buf[0]) == 'Y')
            data->filters[F_OTHERIP] = 1;

        data->hp.reverse = toupper(fieldptr->nextfield->buf[0]);
    }

    tx_destroyfields(&fields);
    del_panel(dlgpanel);
    delwin(dlgwin);
    update_panels();
    doupdate();
}

void othip_filter_select(struct filterlist *fl, char *filename, int *fltcode)
{
    struct MENU menu;
    int row = 1;
    int aborted;
    struct filterfileent fflist;
    
    makestdfiltermenu(&menu);
        
    do {
        tx_showmenu(&menu);
        tx_operatemenu(&menu, &row, &aborted);
        
        switch(row) {
        case 1:
            definefilter(F_OTHERIP, &aborted);
            break;
        case 2:
            selectfilter(F_OTHERIP, &fflist, &aborted);
            if (!aborted) {
                bzero(filename, FLT_FILENAME_MAX);
                strncpy(filename, get_path(T_WORKDIR, fflist.filename), FLT_FILENAME_MAX - 1);
                if (!loadfilter(F_OTHERIP, filename, fl, FLT_RESOLVE))
                    *fltcode = 1;
                else
                    *fltcode = 0;
            }
            break;
        case 3:
            destroyfilter(fl);
            *fltcode = 0;
            tx_infobox("Misc IP protocol filter deactivated", ANYKEY_MSG);
            break;
        case 4:
            editfilter(F_OTHERIP, &aborted);
            break;
        case 5:
            delfilter(F_OTHERIP, &aborted);
            if (!aborted)
                tx_infobox("Misc IP protocol filter deleted", ANYKEY_MSG);
        }
    } while (row != 7);
    
    tx_destroymenu(&menu);
    update_panels();
    doupdate(); 
}

/*
 * Display/logging filter for other (non-TCP, non-UDP) IP protocols.
 */
int othip_filter(unsigned long saddr, unsigned long daddr,
                 unsigned int protocol, struct filterlist *fl)
{
    struct filterent *fe = fl->head;
    int result = 0;
        
    while (fe != NULL) {
        if (((saddr & fe->smask) == (fe->saddr & fe->smask)) &&
           ((daddr & fe->dmask) == (fe->daddr & fe->dmask))) {
    
            switch (protocol) {
            case IPPROTO_ICMP:
                result = fe->un.othipdata.filters[F_ICMP];
                break;
            case IPPROTO_IGMP:
                result = fe->un.othipdata.filters[F_IGMP];
                break;
            case IPPROTO_OSPFIGP:
                result = fe->un.othipdata.filters[F_OSPF];
                break;
            case IPPROTO_IGP:
                result = fe->un.othipdata.filters[F_IGP];
                break;
            case IPPROTO_IGRP:
                result = fe->un.othipdata.filters[F_IGRP];
                break;
            case IPPROTO_GRE:
                result = fe->un.othipdata.filters[F_GRE];
                break;
            default:
                result = fe->un.othipdata.filters[F_OTHERIP];
                break;
            }
            
            if (result) {
                if (toupper(fe->un.othipdata.hp.reverse) == 'E') {
                    return 0;
                }
                
                return 1;
            }
        }
        fe = fe->next_entry;
    }

    return 0;
}
