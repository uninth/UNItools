/** \file BorderDecorator.h
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief BorderDecorator class header
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

#ifndef _BORDERDECORATOR_H
#define _BORDERDECORATOR_H

#include "Decorator.h"


class BorderDecorator : public Decorator
{
	
public:

	BorderDecorator(Display * pDisplay);
	virtual ~BorderDecorator();

	virtual void Draw(Interfaces & rInterfaces, bool bForce = false);

private:

	void DrawBorder(Interface & rInterface);
	void DrawHelp(Interface & rInterface, bool bActive);

	//void DrawInterfaces(Interfaces & rInterfaces);

private:
	
	bool m_bDrawn;
	string strLastHelp;
};

#endif
