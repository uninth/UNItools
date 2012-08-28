/** \file Graph.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 09-23-04
 * \brief Graph class implementation
 *
 * Class implementation
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
#include "Graph.h"


Graph::Graph()
{
	m_uiX = m_uiY = m_uiWidth = m_uiHeight = 0;
	lstData.clear();
}


Graph::Graph(unsigned int uiX, unsigned int uiY, unsigned int uiWidth, unsigned int uiHeight)
{
	setPosition(uiX, uiY);
	setArea(uiWidth, uiHeight);
	lstData.clear();
}


Graph::~Graph()
{
	lstData.clear();
}


void Graph::setPosition(unsigned int uiX, unsigned int uiY)
{
	m_uiX = uiX;
	m_uiY = uiY;
}


void Graph::setArea(unsigned int uiWidth, unsigned int uiHeight)
{
	m_uiWidth = uiWidth;
	m_uiHeight = uiHeight;
}


void Graph::Draw(Window * pWindow, eGraphUses eData)
{
	list< pair< unsigned long, unsigned long > >::iterator itTemp, itData;
	unsigned long ulTop = 0;
	char cSpeed[2][16] = { 0 };
	int iLen[2];
	int iColunm = 0, iSpeedLegth = 0;
	
	itData = lstData.begin();
	
	if(!lstData.size())
		return;

	if(lstData.size() < m_uiWidth)
	{
		iColunm = m_uiWidth - lstData.size();
	}
	else if(lstData.size() > m_uiWidth)
	{
		int iOut = lstData.size() - m_uiWidth;

		for(; iOut; iOut--, itData++);
	}
	
	// Take the maximum value
	for(itTemp = itData; itTemp != lstData.end(); itTemp++)
	{
		if(eData == LeftData || eData == BothData)
		{
			if((*itTemp).first > ulTop)
				ulTop = (*itTemp).first;
		}

		if(eData == RightData || eData == BothData)
		{
			if((*itTemp).second > ulTop)
				ulTop = (*itTemp).second;
		}
	}
	
	// Clear all the graphic

	pWindow->ChangeColor(m_iClearColor);
	
	for(unsigned int uiHeight = 0; uiHeight < m_uiHeight; uiHeight++)
	{
		pWindow->MoveCursor(m_uiY + uiHeight, m_uiX);
		pWindow->HorizontalLine(32, m_uiWidth);
	}
	
	// Scale Info
	
	if(m_bScaleInfo)
	{
		if((ulTop / m_uiPeriod) >= 1048576)
			sprintf(cSpeed[0], "%.2f MBps", ((float)ulTop / m_uiPeriod) / 1048576);
		else if((ulTop / m_uiPeriod) >= 1024 && (ulTop / m_uiPeriod) < 1048576)
			sprintf(cSpeed[0], "%.2f KBps", ((float)ulTop / m_uiPeriod) / 1024);
		else
			sprintf(cSpeed[0], "%ld Bps", (ulTop / m_uiPeriod));

		iLen[0] = strlen(cSpeed[0]);
		
		if(((ulTop / m_uiPeriod) / 2) >= 1048576)
			sprintf(cSpeed[1], "%.2f MBps", (((float)ulTop / m_uiPeriod) / 2) / 1048576);
		else if(((ulTop / m_uiPeriod) / 2) >= 1024 && ((ulTop / m_uiPeriod) / 2) < 1048576)
			sprintf(cSpeed[1], "%.2f KBps", (((float)ulTop / m_uiPeriod) / 2) / 1024);
		else
			sprintf(cSpeed[1], "%ld Bps", ((ulTop / m_uiPeriod) / 2));

		iLen[1] = strlen(cSpeed[1]);
		
		iLen[0] >= iLen[1] ? iSpeedLegth = iLen[0] : iSpeedLegth = iLen[1];
		
		pWindow->ChangeColor(m_iTextColor);
		pWindow->MoveCursor(m_uiY, m_uiX + (iSpeedLegth - iLen[0]));
		pWindow->HorizontalLine(32, iSpeedLegth);
		pWindow->PutString(cSpeed[0]);
		
		pWindow->MoveCursor((m_uiY) + (int)(m_uiHeight / 2), m_uiX + (iSpeedLegth - iLen[1]));
		pWindow->HorizontalLine(32, iSpeedLegth);
		pWindow->PutString(cSpeed[1]);

		pWindow->MoveCursor((m_uiY - 1)+ m_uiHeight, m_uiX + (iSpeedLegth - 5));
		pWindow->HorizontalLine(32, iSpeedLegth);
		pWindow->PutString("0 Bps");
	}
	
	// Plota na tela
	for(itTemp = itData; itTemp != lstData.end(); itTemp++, iColunm++)
	{
		unsigned int uiAllX = m_uiX + iColunm;
		
		if(m_bScaleInfo && (uiAllX <= (m_uiX + iSpeedLegth)))
			continue;

		if(ulTop)
		{
			int iLeftHeight = ((*itTemp).first * m_uiHeight) / ulTop;
			int iRightHeight = ((*itTemp).second * m_uiHeight) / ulTop;
			int iIntersectionHeight;
			
			if((*itTemp).first && !iLeftHeight)
				iLeftHeight = 1;
			
			if((*itTemp).second && !iRightHeight)
				iRightHeight = 1;
			
			iIntersectionHeight = iLeftHeight <= iRightHeight ? iLeftHeight : iRightHeight;
			
			// Draw Left Data
			if(eData == LeftData || (eData == BothData && iLeftHeight && (iLeftHeight > iRightHeight)))
			{
				pWindow->ChangeColor(m_iLeftDataColor, A_BOLD);
				
				for(int iHeight = 1; iHeight <= iLeftHeight; iHeight++)
				{
					pWindow->MoveCursor(m_uiY + m_uiHeight - iHeight, uiAllX);
					pWindow->PutChar('#');
				}
			}

			// Draw Right Data
			if(eData == RightData || (eData == BothData && iRightHeight && (iRightHeight > iLeftHeight)))
			{
				pWindow->ChangeColor(m_iRightDataColor);

				for(int iHeight = 1; iHeight <= iRightHeight; iHeight++)
				{
					pWindow->MoveCursor(m_uiY + m_uiHeight - iHeight, uiAllX);
					pWindow->PutChar('#');
				}
			}
			
			// Intersection
			if(eData == BothData && iIntersectionHeight)
			{
				pWindow->ChangeColor(m_iIntersectionColor);

				for(int iHeight = 1; iHeight <= iIntersectionHeight; iHeight++)
				{
					pWindow->MoveCursor(m_uiY + m_uiHeight - iHeight, uiAllX);
					pWindow->PutChar('#');
				}
			}
		}
	}
}
