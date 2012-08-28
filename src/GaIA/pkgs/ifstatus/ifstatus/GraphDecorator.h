/** \file GraphDecorator.h
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief GraphDecorator class header
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


#ifndef _GRAPHDECORATOR_H
#define _GRAPHDECORATOR_H


// Include files

#include "Main.h"
#include "Decorator.h"
#include "Interface.h"
#include "Display.h"
#include "Graph.h"

class GraphDecorator : public Decorator
{
	
public:
	
	GraphDecorator(Display * pDisplay);
	virtual ~GraphDecorator();

	virtual void Draw(Interfaces & rInterfaces, bool bForce = false);

private:
	
	bool DrawRxTx(Interface & rInterface, bool bForce);
	void DrawStats(Interface & rInterface);
	void DrawGraph(Interface & rInterface, bool bForce);

private:
	
	Graph m_Graph;

	string m_strInformation;

	unsigned long long m_ullLastSent;
	unsigned long long m_ullLastReceived;

	bool bCleanTX;
	bool bCleanRX;
};

#endif
