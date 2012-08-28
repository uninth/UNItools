/* No manual changes in this file */
#include <stdio.h>
#include <string.h>

static const char rcsid[] = "$Id$";

static char atoprevision[] = "$Revision: 1.19 $";
static char atopdate[]     = "$Date: 2007/01/18 11:24:54 $";

char *
getversion(void)
{
	static char vers[256];

	atoprevision[sizeof atoprevision - 3] = '\0';
	atopdate    [sizeof atopdate     - 3] = '\0';

	snprintf(vers, sizeof vers,
		"Version:%s -%s           < gerlof@ATComputing.nl >",
			strchr(atoprevision, ' '),
			strchr(atopdate    , ' '));

	return vers;
}
