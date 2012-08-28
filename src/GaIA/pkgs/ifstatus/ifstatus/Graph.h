/** \file Graph.h
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-22-04
 * \brief Graph class header
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

#ifndef _GRAPH_H
#define _GRAPH_H

#include "Main.h"
#include "Window.h"

typedef enum eGraphUses
{
	BothData = 0,
	LeftData,
	RightData	
};

class Graph
{
public:
	
	Graph();
	Graph(unsigned int uiX, unsigned int uiY, unsigned int uiWidth, unsigned int uiHeight);
	virtual ~Graph();

	void Draw(Window * pWindow, eGraphUses eData);
	

	void setPosition(unsigned int uiX, unsigned int uiY);

	unsigned int getX() { return m_uiX; }
	unsigned int getY() { return m_uiY; }

	void setArea(unsigned int uiWidth, unsigned int uiHeight);

	unsigned int getWidth() { return m_uiWidth; }
	unsigned int getHeight() { return m_uiHeight; }

	void setScaleInfo(bool bShow) { m_bScaleInfo = bShow; }
	void setPeriod(unsigned int uiPeriod) { m_uiPeriod = uiPeriod; }
	
	void setLeftDataColor(int iPair) { m_iLeftDataColor = iPair; }
	void setRightDataColor(int iPair) { m_iRightDataColor = iPair; }
	void setIntersectionColor(int iPair) { m_iIntersectionColor = iPair; }
	void setClearColor(int iPair) { m_iClearColor = iPair; }
	void setTextColor(int iPair) { m_iTextColor = iPair; }
	
public:
	
	list< pair<unsigned long, unsigned long> > lstData;

protected:

	bool m_bScaleInfo;

	unsigned int m_uiPeriod;

	unsigned int m_uiX;
	unsigned int m_uiY;
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;

	int m_iLeftDataColor;
	int m_iRightDataColor;
	int m_iIntersectionColor;
	int m_iTextColor;
	int m_iClearColor;
};


#endif
