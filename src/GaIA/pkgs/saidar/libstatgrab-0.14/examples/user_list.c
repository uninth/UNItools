/*
 * i-scream libstatgrab
 * http://www.i-scream.org
 * Copyright (C) 2000-2004 i-scream
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id$
 */

#include <stdio.h>
#include <statgrab.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){

	extern char *optarg;
	int c;

	int delay = 1;
	sg_user_stats *users;

	while ((c = getopt(argc, argv, "d:")) != -1){
		switch (c){
			case 'd':
				delay = atoi(optarg);
				break;
		}
	}

	/* Initialise statgrab */
	sg_init();

	/* Drop setuid/setgid privileges. */
	if (sg_drop_privileges() != 0) {
		perror("Error. Failed to drop privileges");
		return 1;
	}

	if( (users = sg_get_user_stats()) != NULL){
		printf("Users : %s\n", users->name_list);
		printf("Number of users : %d\n", users->num_entries);
	}

	exit(0);
}
