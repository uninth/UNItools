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

int main(){

	sg_mem_stats *mem_stats;
	sg_swap_stats *swap_stats;

	long long total, free;

	/* Initialise statgrab */
	sg_init();

	/* Drop setuid/setgid privileges. */
	if (sg_drop_privileges() != 0) {
		perror("Error. Failed to drop privileges");
		return 1;
	}

	if( ((mem_stats=sg_get_mem_stats()) != NULL) && (swap_stats=sg_get_swap_stats()) != NULL){
		printf("Total memory in bytes : %lld\n", mem_stats->total);
		printf("Used memory in bytes : %lld\n", mem_stats->used);
		printf("Cache memory in bytes : %lld\n", mem_stats->cache);
		printf("Free memory in bytes : %lld\n", mem_stats->free);

		printf("Swap total in bytes : %lld\n", swap_stats->total);
		printf("Swap used in bytes : %lld\n", swap_stats->used);	
		printf("Swap free in bytes : %lld\n", swap_stats->free);

		total = mem_stats->total + swap_stats->total;
		free = mem_stats->free + swap_stats->free;

		printf("Total VM usage : %5.2f%%\n", 100 - (((float)total/(float)free)));

	}
	else {
		printf("Unable to get VM stats: %s\n", sg_str_error(sg_get_error()));
		exit(1);
	}
	exit(0);
}
