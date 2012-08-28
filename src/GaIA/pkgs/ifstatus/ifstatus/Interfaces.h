/** \file Interfaces.h
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief Interfaces class header
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

#ifndef _INTERFACES_H
#define _INTERFACES_H

#include "Main.h"
#include "Interface.h"


class Interfaces
{
public:

	Interfaces();
	~Interfaces();

	int Load(void);

	void UpdateData(void);
	void UpdateInterfaces(void);

	void CheckState(void);

	map<int, Interface *> & getInterfaces(void) { return m_mapInterfaces; }

	int getCount(void) { return m_mapInterfaces.size(); }

	Interface & getActive(void);
	bool setActive(int iActive);

	time_t & getLastUpdate(void) { return m_tLastUpdate; }
	void setLastUpdate(void) { m_tLastUpdate = time(NULL); }

private:

	int m_iActive;

	map<int, Interface *> m_mapInterfaces;

	time_t m_tLastUpdate;
};

#endif
