/***

fltmgr.h - filter list management routine prototypes

Copyright (c) Gerard Paul Java 1998

***/

struct filterfileent {
    char desc[35];
    char filename[40];
};

struct ffnode {
    struct filterfileent ffe;
    struct ffnode *next_entry;
    struct ffnode *prev_entry;
};

void makestdfiltermenu(struct MENU *menu);
void makeudpfiltermenu(struct MENU *menu);
void makemainfiltermenu(struct MENU *menu);
int loadfilterlist(unsigned int protocol, struct ffnode **fltfile);
void save_filterlist(unsigned int protocol, struct ffnode *fltlist);
void pickafilter(struct ffnode *files, struct ffnode **fltfile, int *aborted);
void selectfilter(unsigned int protocol,
		  struct filterfileent *ffe, int *aborted);
void destroyfilterlist(struct ffnode *fltlist);
void get_filter_description(char *description, int *aborted, char *pre_edit);
void genname(unsigned long n, char *m);
unsigned long int nametoaddr(char *ascname, int *err);
void listfileerr(int code);
int mark_filter_change(int protocol);
void clear_flt_tag(int protocol);
