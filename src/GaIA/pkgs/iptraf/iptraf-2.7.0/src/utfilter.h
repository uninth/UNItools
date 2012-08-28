void gethostparams(struct hostparams *hp, int *aborted,
                   char *isrc, char *ismask, char *isport,
                   char *idst, char *idmask, char *idport, char *iinex);
void tcpfilterselect(struct filterlist *fl, unsigned int *filtered,
		     char *filename, int *aborted);
void udpfilterselect(struct filterlist *fl, unsigned int *filtercode,
		     char *filename, int *aborted);
void loadsavedtcpfilter(struct filterlist *fl, int *filtered);
int utfilter(struct filterlist *fl, unsigned long source, unsigned long dest,
	     unsigned int sport, unsigned int dport, unsigned int protocol);
