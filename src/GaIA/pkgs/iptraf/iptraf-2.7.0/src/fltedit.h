void definefilter(int protocol, int *aborted);
int loadfilter(int protocol, char *filename, struct filterlist *fl, int resolve);
void savefilter(unsigned int protocol, char *filename, struct filterlist *fl);
void destroyfilter(struct filterlist *fl);
void editfilter(unsigned int protocol, int *aborted);
void delfilter(unsigned int protocol, int *aborted);
