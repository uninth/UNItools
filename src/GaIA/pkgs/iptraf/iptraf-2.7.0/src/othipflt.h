void get_othip_hostparams(struct othipfltdata *data, char *init_saddr,
                          char *init_smask, char *init_daddr, char *init_dmask,
			  int *aborted);
void othip_filter_select(struct filterlist *fl, char *filename, int *fltcode);
int othip_filter(unsigned long saddr, unsigned long daddr,
                 unsigned int protocol, struct filterlist *fl);
