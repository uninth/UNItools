/** \file GraphDecorator.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief GraphDecorator class implementation
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
 
#include "GraphDecorator.h"
#include "Config.h"

GraphDecorator::GraphDecorator(Display * pDisplay) : Decorator(pDisplay)
{	
	m_ullLastReceived = m_ullLastSent = 0;
	
	m_Graph.setIntersectionColor(TextGreen);
	m_Graph.setLeftDataColor(TextGreen);
	m_Graph.setRightDataColor(TextYellow);
	m_Graph.setClearColor(TextBlack);
	
	m_Graph.setPosition(2, 1);
}

GraphDecorator::~GraphDecorator()
{
	
}

void GraphDecorator::Draw(Interfaces & rInterfaces, bool bForce)
{
	Interface & rInterface = rInterfaces.getActive();
	
	if(rInterface.isActive() || bForce)
	{
		bool bDrawn = rInterface.isDrawn();
		bool bRxTxChanged = false;

		if(bForce || !bDrawn)
		{

			if(Window::ScreenLines() >= 15 && Window::ScreenColumns() >= 15)
				DrawGraph(rInterface, bForce);
			
			if(Window::ScreenLines() >= 15 && Window::ScreenColumns() >= 62)
				DrawStats(rInterface);
		}

		if(Window::ScreenLines() >= 15 && Window::ScreenColumns() >= 15)
			bRxTxChanged = DrawRxTx(rInterface, bForce);

		if(!bDrawn || bRxTxChanged || bForce)
		{
			Decorator::Draw(rInterfaces, true);
			return;
		}
	}
	else
	{
		if(Window::ScreenColumns() >= 62)
			DrawStats(rInterface);
	}

	Decorator::Draw(rInterfaces, bForce);
}

void GraphDecorator::DrawStats(Interface & rInterface)
{
	Window * pWindow = rInterface.getWindow();
	unsigned long ulBytes, ulPackets;
	char cFormat[64] = { 0 };

	pWindow->ChangeColor(TextBlack);
	pWindow->MoveCursor(m_Graph.getHeight() + m_Graph.getX() + 2, m_Graph.getY() + 1);
	pWindow->HorizontalLine(32, m_Graph.getWidth());

	if(rInterface.isActive())
	{		
		ulBytes = rInterface.getPeriodBytes();
		ulPackets = rInterface.getPeriodPackets();
		
		if(ulBytes >= 1048576)
			sprintf(cFormat, "[ %.2f MBytes/s  %ld Packets/s ]", ((float)ulBytes / 1048576), ulPackets);
		else if((ulBytes >= 1024) && (ulBytes < 1048576))
			sprintf(cFormat, "[ %.2f KBytes/s  %ld Packets/s ]", ((float)ulBytes / 1024), ulPackets);
		else if((ulBytes > 0) && (ulBytes < 1024))
			sprintf(cFormat, "[ %ld Bytes/s  %ld Packets/s ]", ulBytes, ulPackets);
		else
			sprintf(cFormat, "[ Stalled ]");

		pWindow->ChangeColor(TextCyan);
		pWindow->MoveCursor(m_Graph.getHeight() + m_Graph.getX() + 2, (int)(Window::ScreenColumns() / 2) - (strlen(cFormat) / 2));
		pWindow->PutString(cFormat);
		
		pWindow->ChangeColor(TextGreen, A_BOLD);
		pWindow->MoveCursor(m_Graph.getHeight() + m_Graph.getX(), (int)8);
		pWindow->PutString("[ ON ]");
		
	}
	else
	{
		pWindow->ChangeColor(TextRed, A_BOLD);
		pWindow->MoveCursor(m_Graph.getHeight() + m_Graph.getX(), (int)8);
		pWindow->PutString("[ OFF ]");
		
	}
}

void GraphDecorator::DrawGraph(Interface & rInterface, bool bForce)
{
	Config * pConfig = Config::Instance();
	deque<InterfaceData> & rHistory = rInterface.getHistory();
	string strValue;
	long long llReceivedBytes = 0, llSentBytes = 0;	
	int iPeriodCount = 1;
	unsigned int uiPeriod = atoi((pConfig->getValue("GraphPeriod")).c_str());
	bool bScaleInfo = true;

	if(uiPeriod <= 0)
		uiPeriod = 1;
	
	if((strValue = pConfig->getValue("Information")) != m_strInformation || bForce)
	{
		if(strValue == "OFF")
			m_Graph.setArea(Window::ScreenColumns() - 4, Window::ScreenLines() - 7);
		else
			m_Graph.setArea(Window::ScreenColumns() - 4, Window::ScreenLines() - 14);
		
		m_strInformation = strValue;
	}
	
	m_Graph.lstData.clear();

	for(deque<InterfaceData>::iterator itHistory = rHistory.begin(); itHistory != rHistory.end(); itHistory++)
	{
		llReceivedBytes += (*itHistory).getReceivedBytes();
		llSentBytes += (*itHistory).getSentBytes();
		
		if( iPeriodCount >= uiPeriod )
		{
			pair< unsigned long, unsigned long > pairBytes(llReceivedBytes, llSentBytes);
			m_Graph.lstData.push_back(pairBytes);
			llReceivedBytes = llSentBytes = 0L;
			iPeriodCount = 0;
		}

		iPeriodCount++;
	}
	
	strValue = pConfig->getValue("GraphScaleInfo");
	
	if(strValue == "OFF")
		bScaleInfo = false;
	
	m_Graph.setScaleInfo(bScaleInfo);
	m_Graph.setPeriod(uiPeriod);

	strValue = pConfig->getValue("GraphDataSource");
	
	if(strValue == "RX")
		m_Graph.Draw(rInterface.getWindow(), LeftData);
	else if(strValue == "TX")
		m_Graph.Draw(rInterface.getWindow(), RightData);
	else
		m_Graph.Draw(rInterface.getWindow(), BothData);
	
	rInterface.setDrawn(true);
}

bool GraphDecorator::DrawRxTx(Interface & rInterface, bool bForce)
{
	bool bChanged = false;

	if(m_Graph.getHeight() && m_Graph.getWidth())
	{
		InterfaceData & rActualData = rInterface.getData();
		Window * pWindow = rInterface.getWindow();

		if(bForce)
		{
			m_ullLastReceived = rActualData.getReceivedBytes();
			m_ullLastSent = rActualData.getSentBytes();

			bCleanRX = bCleanTX = false;			
		}
	
		pWindow->MoveCursor(m_Graph.getHeight() + m_Graph.getX(), m_Graph.getY() + 1 + (m_Graph.getWidth() / 2) - 4);
		pWindow->ChangeColor(TextGreen, A_BOLD);

		if(rActualData.getReceivedBytes() != m_ullLastReceived && bCleanRX)
		{
			pWindow->PutString("[RX]");
			bCleanRX = false;
			bChanged = true;
		}
		else
		{
			if(!bCleanRX)
			{
				pWindow->PutString("    ");
				bCleanRX = bChanged = true;
			}
		}
	
		pWindow->MoveCursor(m_Graph.getHeight() + m_Graph.getX(), m_Graph.getY() + 1 + (m_Graph.getWidth() / 2) + 1);
		pWindow->ChangeColor(TextYellow);
		
		if(rActualData.getSentBytes() != m_ullLastSent && bCleanTX)
		{
			pWindow->PutString("[TX]");
			bCleanTX = false;
			bChanged = true;
		}
		else
		{
			if(!bCleanTX)
			{
				pWindow->PutString("    ");
				bCleanTX = bChanged = true;
			}
		}
	
		m_ullLastReceived = rActualData.getReceivedBytes();
		m_ullLastSent = rActualData.getSentBytes();
	}

	return bChanged;
}
