/** \file Interface.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief Interface class implementation
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

#include "Interface.h"
#include "Config.h"

InterfaceData::InterfaceData()
{ 
	memset((unsigned long long *)&m_ullReceived, 0, eTotalTypes * sizeof(unsigned long long));  
	memset((unsigned long long *)&m_ullSent, 0, eTotalTypes * sizeof(unsigned long long));
}

InterfaceData & InterfaceData::operator=(InterfaceData & rInterfaceData)
{
	// Bytes
	setReceivedBytes(rInterfaceData.getReceivedBytes());
	setSentBytes(rInterfaceData.getSentBytes());
	
	// Packets
	setReceivedPackets(rInterfaceData.getReceivedPackets());
	setSentPackets(rInterfaceData.getSentPackets());
	
	// Errors
	setReceivingErrors(rInterfaceData.getReceivingErrors());
	setSendingErrors(rInterfaceData.getSendingErrors());
	
	return *this;
}

InterfaceData InterfaceData::operator-(InterfaceData & rInterfaceData)
{
	InterfaceData cData;
	
	cData.setSentBytes(getSentBytes() - rInterfaceData.getSentBytes());
	cData.setReceivedBytes(getReceivedBytes() - rInterfaceData.getReceivedBytes());
	
	cData.setSentPackets(getSentPackets() - rInterfaceData.getSentPackets());
	cData.setReceivedPackets(getReceivedPackets() - rInterfaceData.getReceivedPackets());

	cData.setSendingErrors(getSendingErrors() - rInterfaceData.getSendingErrors());
	cData.setReceivingErrors(getReceivingErrors() - rInterfaceData.getReceivingErrors());
	
	return cData;
}

Interface::Interface(string & strInterface)
{
	Initialize(strInterface.c_str());
}

Interface::Interface(char * pInterface)
{
	Initialize((const char *)pInterface);
}

Interface::~Interface()
{
	m_deqHistory.clear();	
}

void Interface::Initialize(const char * pInterface)
{
	m_strInterface = pInterface;
	m_strOnlineTime = "0d 00:00:00";

	m_ulTopBytesSecond = m_ulTopPacketsSecond = 0;
	m_ulPeriodBytes = m_ulPeriodPackets = 0;

	m_bFirst = true;
	m_bOnlineTime = false;
	m_bDrawn = false;
	
	ResolveIPAddress();
	
	m_deqHistory.clear();

	setInactive();
}

void Interface::Update(void)
{
	InterfaceData cDiference =  getData() - getPreviousData();
	setPreviousData(getData());
	
        if(m_deqHistory.size() > ((unsigned)Window::ScreenColumns() * 10))
	{
		Config * pConfig = Config::Instance();
		int iPeriod = atoi((pConfig->getValue("GraphPeriod")).c_str());
		int iErase;

		for(iErase = 0; iErase < iPeriod; iErase++)
	                m_deqHistory.erase(m_deqHistory.begin());
	}

	m_deqHistory.push_back(cDiference);

	setPeriodBytes(cDiference.getSentBytes() + cDiference.getReceivedBytes());
	setPeriodPackets(cDiference.getSentPackets() + cDiference.getReceivedPackets());

	if(getPeriodBytes() > getTopBytesSecond())
		setTopBytesSecond(getPeriodBytes());
	
	if(getPeriodPackets() > getTopPacketsSecond())
		setTopPacketsSecond(getPeriodPackets());
	
	UpdateOnlineTime();
	
	setDrawn(false);
}

void Interface::UpdateOnlineTime(void)
{
	struct stat sStat;
	time_t tCurrentTime = time(NULL);
	time_t tOnlineTime;
	
	string strFile = "/var/run/" + m_strInterface + ".pid";
	
	if(!stat(strFile.c_str(), &sStat))
	{
		int iDays, iHours, iMinutes, iSeconds;
		char cTime[12] = { 0 };
		
		m_bOnlineTime = true;
		
		tOnlineTime = tCurrentTime - sStat.st_mtime;
		
		iSeconds = tOnlineTime % 60;
		iMinutes = (tOnlineTime / 60) % 60; 
		iHours = (tOnlineTime / 3600) % 24;
		iDays = (tOnlineTime / (3600 * 24)) % 365;
		
		sprintf(cTime, "%dd %.2d:%.2d:%.2d", iDays, iHours, iMinutes, iSeconds);
		
		m_strOnlineTime = cTime;
	}
	else
	{
		m_bOnlineTime = false;
	}
}

void Interface::ResolveIPAddress(void)
{
	struct ifreq sIFReq;
	struct sockaddr_in * pSocketAddress;
	int iSocket;
	
	if((iSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		m_strIPAddress = "Unknown";
		return;
	}
	
	strcpy(sIFReq.ifr_name, m_strInterface.c_str());
	
	if(ioctl(iSocket, SIOCGIFADDR, &sIFReq) < 0);
	
	pSocketAddress = (struct sockaddr_in *)&sIFReq.ifr_addr;
	
	if(pSocketAddress->sin_addr.s_addr)
		m_strIPAddress =  inet_ntoa(pSocketAddress->sin_addr);
	else
		m_strIPAddress = "Unknown";
	
}
