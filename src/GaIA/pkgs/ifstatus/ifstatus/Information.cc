/** \file Information.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief Information class implementation
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

#include "Information.h"
#include "Window.h"
#include "Config.h"
#include "Email.h"
#include "Util.h"

Information::Information()
{
	m_bLabelsDrawn = false;
	
	strData[0] = "Interface:";
	strData[1] = "IP Address:";
	strData[2] = "Top Speed:";
	strData[3] = "Received Data:";
	strData[4] = "Received Packets:";
	strData[5] = "Errors on Receiving:";
	
	strData[6] = "On-line Time:";
	strData[7] = "New Email:";
	strData[8] = "Top Packets:";
	strData[9] = "Transmited Data:";
	strData[10] = "Transmited Packets:";
	strData[11] = "Errors on Transmission:";
}

Information::~Information()
{	

}

void Information::Draw(Interfaces & rInterfaces, bool bForce)
{
	Interface & rInterface = rInterfaces.getActive();
	Config * pConfig = Config::Instance();
	m_bChanged = false;

	if(pConfig->getValue("Information") == "ON")
	{
		if(Window::ScreenLines() >= 10 && Window::ScreenColumns() >= 72)
		{
			if(!m_bLabelsDrawn || bForce)
				ShowLabels(rInterface);
		
			ShowData(rInterface, bForce);
		}

		if(m_bChanged || bForce)
			rInterface.getWindow()->Refresh();
		
	}
	else
		m_bLabelsDrawn = false;

	if(m_bChanged || bForce)
		rInterface.getWindow()->Refresh();
}

void Information::FormatSize(unsigned long ulBytes, string & strOutput, bool bPerSecond)
{
	char cData[32];

	if(ulBytes >= 1073741824)
		sprintf(cData, "%.2f GBytes%s", ((float)ulBytes) / 1073741824, bPerSecond ? "/s" : "");
	else if(ulBytes >= 1048576 && ulBytes < 1073741824 )
		sprintf(cData, "%.2f MBytes%s", ((float)ulBytes) / 1048576, bPerSecond ? "/s" : "");
	else if(ulBytes >= 1024 && ulBytes < 1048576)
		sprintf(cData, "%.2f KBytes%s", ((float)ulBytes) / 1024, bPerSecond ? "/s" : "");
	else
		sprintf(cData, "%ld Bytes%s", ulBytes, bPerSecond ? "/s" : "");

	strOutput = cData;
}

void Information::ShowLabels(Interface & rInterface)
{
	Config * pConfig = Config::Instance();
	Window * pWindow = rInterface.getWindow();
	int iX, iY;

	m_bEmailCheck = (pConfig->getValue("EmailCheck") == "ON");
	
	// LEFT LABELS
	
	iY = (int)(Window::ScreenLines() - 8);
	iX = (int)(Window::ScreenColumns() / 10);
	
	pWindow->ChangeColor(TextWhite);

	// Interface	
	pWindow->MoveCursor(iY++, iX);
	pWindow->PutString(strData[0]);
	// IP Address
	pWindow->MoveCursor(iY++, iX);
	pWindow->PutString(strData[1]);
	// Top Speed per Second
	pWindow->MoveCursor(iY++, iX);
	pWindow->PutString(strData[2]);
	// Received Bytes
	pWindow->MoveCursor(iY++, iX);
	pWindow->PutString(strData[3]);
	// Received Packets
	pWindow->MoveCursor(iY++, iX);
	pWindow->PutString(strData[4]);
	// Errors on Receiving
	pWindow->MoveCursor(iY++, iX);
	pWindow->PutString(strData[5]);

	// RIGHT LABELS
	
	iY = (int)(Window::ScreenLines() - 8);
	iX = (int)(Window::ScreenColumns() / 2);

	// Online Time
	if(rInterface.haveOnlineTime())
	{
		if(!m_bEmailCheck)
			iY++;

		pWindow->MoveCursor(iY, iX);
                pWindow->PutString(strData[6]);
	}

	iY++;

	// Email Check
	if(m_bEmailCheck)
	{
		pWindow->MoveCursor(iY, iX);
		pWindow->PutString(strData[7]);
	}
	
	iY++;
	
	// Top Packets per Second
	pWindow->MoveCursor(iY++, iX);
	pWindow->PutString(strData[8]);
	// Transmited Bytes
	pWindow->MoveCursor(iY++, iX);
	pWindow->PutString(strData[9]);
	// Transmited Packets
	pWindow->MoveCursor(iY++, iX);
	pWindow->PutString(strData[10]);
	// Errors on Transmission
	pWindow->MoveCursor(iY++, iX);
	pWindow->PutString(strData[11]);
	
	m_bLabelsDrawn = true;	
}

void Information::ShowData(Interface & rInterface, bool bForce)
{
	Config * pConfig = Config::Instance();
	Window * pWindow = rInterface.getWindow();
	InterfaceData & rData = rInterface.getData();
	int iX, iY;
	int iInitialX = (Window::ScreenColumns() / 10);
	string strBytes;

	m_bEmailCheck = (pConfig->getValue("EmailCheck") == "ON");
	
	// LEFT INFORMATION

	// Interface
	iY = (int)(Window::ScreenLines() - 8);

	pWindow->ChangeColor(TextCyan);

	if(m_strLastInterface != rInterface.getInterface() || bForce)
	{
		iX = iInitialX + strData[0].length() + 1;

		pWindow->MoveCursor(iY, iX);
		pWindow->HorizontalLine(32, iLastDataSize[0]);
		iLastDataSize[0] = rInterface.getInterface().length();
		pWindow->PutString(rInterface.getInterface());

		m_strLastInterface = rInterface.getInterface();
		m_bChanged = true;
	}

	iY++;
	
	// IP Address
	if(m_strLastIPAddress != rInterface.getIPAddress() || bForce)
	{
		iX = iInitialX + strData[1].length() + 1;
	
		pWindow->MoveCursor(iY, iX);
		pWindow->HorizontalLine(32, iLastDataSize[1]);
		iLastDataSize[1] = rInterface.getIPAddress().length();
		pWindow->PutString(rInterface.getIPAddress());

		m_strLastIPAddress = rInterface.getIPAddress();
		m_bChanged = true;
	}

	iY++;

	// Top Bytes per Second
	if(m_ulLastTopBytesSecond != rInterface.getTopBytesSecond() || bForce)
	{
		iX = iInitialX + strData[2].length() + 1;
	
		pWindow->MoveCursor(iY, iX);
		FormatSize(rInterface.getTopBytesSecond(), strBytes, true);
		pWindow->HorizontalLine(32, iLastDataSize[2]);
		iLastDataSize[2] = strBytes.length();
		pWindow->PutString(strBytes);

		m_ulLastTopBytesSecond = rInterface.getTopBytesSecond();
		m_bChanged = true;
	}

	iY++;

	// Received Bytes
	if(m_cLastData.getReceivedBytes() != rData.getReceivedBytes() || bForce)
	{
		iX = iInitialX + strData[3].length() + 1;

		pWindow->MoveCursor(iY, iX);
		FormatSize(rData.getReceivedBytes(), strBytes, false);
		pWindow->HorizontalLine(32, iLastDataSize[3]);
		iLastDataSize[3] = strBytes.length();
		pWindow->PutString(strBytes);

		m_cLastData.setReceivedBytes(rData.getReceivedBytes());
		m_bChanged = true;
	}

	iY++;

	// Received Packets
        if(m_cLastData.getReceivedPackets() != rData.getReceivedPackets() || bForce)
	{
		iX = iInitialX + strData[4].length() + 1;
	
		pWindow->MoveCursor(iY, iX);
		pWindow->PutUnsignedLong(rInterface.getData().getReceivedPackets());

		m_cLastData.setReceivedPackets(rData.getReceivedPackets());
		m_bChanged = true;
	}

	iY++;

	// Receiving Errors
        if(m_cLastData.getReceivingErrors() != rData.getReceivingErrors() || bForce)
	{
		iX = iInitialX + strData[5].length() + 1;
	
		pWindow->MoveCursor(iY, iX);
		pWindow->PutUnsignedLong(rInterface.getData().getReceivingErrors());

		m_cLastData.setReceivingErrors(rData.getReceivingErrors());
		m_bChanged = true;
	}

	iY++;

	// RIGHT INFORMATION

	iInitialX = (Window::ScreenColumns() / 2);

	iY = (int)(Window::ScreenLines() - 8);

	// Online time
	if(rInterface.haveOnlineTime())
	{
		iX = (iInitialX + strData[6].length() + 1);

		if(!m_bEmailCheck)
			iY++;

		if(m_strLastOnlineTime != rInterface.getOnlineTime() || bForce)
		{
			pWindow->MoveCursor(iY, iX);
		        pWindow->PutString(rInterface.getOnlineTime());

			m_strLastOnlineTime = rInterface.getOnlineTime();
			m_bChanged = true;
		}
	}

	iY++;

	// Email Check
	if(m_bEmailCheck)
	{
		Email * pEmail = Email::Instance();

		if(m_iUnreadEmail != pEmail->getUnread() || bForce)
		{
			iX = (iInitialX + strData[7].length() + 1);
			pWindow->MoveCursor(iY, iX);
			pWindow->PutUnsignedLong((unsigned long)pEmail->getUnread());
		
			m_iUnreadEmail = pEmail->getUnread();
			m_bChanged = true;
		}
	}

	iY++;	
	
	// Top Packets per Second

	if(m_ulLastTopPacketsSecond != rInterface.getTopPacketsSecond() || bForce)
	{
		iX = (iInitialX + strData[8].length() + 1);
	
		pWindow->MoveCursor(iY, iX);
		pWindow->PutUnsignedLong(rInterface.getTopPacketsSecond());

		m_ulLastTopPacketsSecond = rInterface.getTopPacketsSecond();
		m_bChanged = true;
	}

	iY++;

	// Sent Bytes
        if(m_cLastData.getSentBytes() != rData.getSentBytes() || bForce)
        {
		iX = (iInitialX + strData[9].length() + 1);
	
		pWindow->MoveCursor(iY, iX);
		FormatSize(rData.getSentBytes(), strBytes, false);
		pWindow->HorizontalLine(32, iLastDataSize[9]);
		iLastDataSize[9] = strBytes.length();
		pWindow->PutString(strBytes);

		m_cLastData.setSentBytes(rData.getSentBytes());
		m_bChanged = true;
	}

	iY++;

	// Sent Packets
	if(m_cLastData.getSentPackets() != rData.getSentPackets() || bForce)
	{
		iX = (iInitialX + strData[10].length() + 1);
	
		pWindow->MoveCursor(iY, iX);
		pWindow->PutUnsignedLong(rInterface.getData().getSentPackets());

		m_cLastData.setSentPackets(rData.getSentPackets());
		m_bChanged = true;
	}

	iY++;

	// Sent Errros
	if(m_cLastData.getSendingErrors() != rData.getSendingErrors() || bForce)
	{
		iX = (iInitialX + strData[11].length() + 1);
	
		pWindow->MoveCursor(iY, iX);
		pWindow->PutUnsignedLong(rInterface.getData().getSendingErrors());

		m_cLastData.setSendingErrors(rData.getSendingErrors());
		m_bChanged = true;
	}
}
