/** \file Util.h
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-22-04
 * \brief Util class header
 *
 * Define class structure
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
 
#ifndef _UTIL_H_
#define _UTIL_H_

#include "Main.h"

class Util
{
public:

	static int Split(string & strText, string strSeparators, vector<string> & vctWords);

	static string & Trim(string & strText);
	static string & TrimLeft(string & strText);
	static string & TrimRight(string & strText);

	static void CreateDirectory(string & strDirectory);
};


#endif
