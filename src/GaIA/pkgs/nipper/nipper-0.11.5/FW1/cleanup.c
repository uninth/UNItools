/***************************************************************************
 *   Nipper - The network infrastructure parser                            *
 *   Copyright (C) 2006 - 2008 by Ian Ventura-Whiting                      *
 *   fizz@titania.co.uk                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version. However, there are a number of    *
 *   exceptions listed below.                                              *
 *                                                                         *
 *   EXCEPTIONS TO THE GPL License:                                        *
 *      1. This code cannot be used as part of a commercial product. If a  *
 *         commercial license is required, contact fizz@titania.co.uk for  *
 *         licensing information.                                          *
 *      2. Any code that integrates Nipper MUST display the copyright      *
 *         information below with the programs own copyright information.  *
 *                                                                         *
 *         "Nipper Copyright (C) 2006 - 2008 by Ian Ventura-Whiting"       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

// This file contains the Passport cleanup code


void cleanupFW1(struct nipperConfig *nipper)
{
	// Variables...
	struct host *memberPointer = 0;
	struct policyCollection *policyCollectionPointer;

	// Cleanup Policy Collections
	while (nipper->fw1->policies != 0)
	{
		while (nipper->fw1->policies->targets != 0)
		{
			memberPointer = nipper->fw1->policies->targets->next;
			free(nipper->fw1->policies->targets);
			nipper->fw1->policies->targets = memberPointer;
		}
		policyCollectionPointer = nipper->fw1->policies->next;
		free(nipper->fw1->policies);
		nipper->fw1->policies = policyCollectionPointer;
	}

	// Cleanup Firewall-1 config
	free(nipper->fw1);
}

