#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "dirs.h"

int main(void)
{
    DIR *dir;
    char dirname[80];
    struct dirent *direntry;
    char fullpath1[80];
    char fullpath2[80];
    char *cptr;

    printf("Rearranging filter data files...\n");

    sprintf(dirname, "%s/%s", WORKDIR, "..");	/* parent of the workdir */
    dir = opendir(dirname);

    do {
	direntry = readdir(dir);
	if (direntry != NULL) {
	    if (((strlen(direntry->d_name) > 6)
		 && (strncmp(direntry->d_name, "iptraf", 6) == 0))) {
		cptr = direntry->d_name + 6;
		strcpy(fullpath1, WORKDIR);
		strcpy(fullpath2, WORKDIR);
		strcat(fullpath1, "/../");
		strcat(fullpath2, "/");
		strcat(fullpath1, direntry->d_name);
		strcat(fullpath2, cptr);
		rename(fullpath1, fullpath2);
	    }
	}
    } while (direntry != NULL);

    closedir(dir);
    return 0;
}
