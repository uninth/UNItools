/** \file Main.h
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 09-14-04
 * \brief Main Definitions
 */
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#ifndef _MAIN_H
#define _MAIN_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <memory>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <sys/ioctl.h>

#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <linux/netdevice.h> 
#include <netinet/in.h>

#define VERSION			"v1.1.0"


typedef enum eColors
{
	TextBlack = 1,
	TextRed,
	TextGreen,
	TextYellow,
	TextBlue,
	TextMagenta,
	TextCyan,
	TextWhite,	
	BlockRed,
	BlockGreen,
	BlockYellow,
	BlockBlue,
	BlockMagenta,
	BlockCyan,
	BlockWhite	
};

using namespace std;

#endif
