/** \file Interface.h
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief Interface class header
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

#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "Main.h"
#include "Window.h"

enum eInformationType { eBytes = 0, ePackets, eErrors, eTotalTypes };

class InterfaceData
{

public:

	InterfaceData();
	
	unsigned long long getReceivedBytes(void) const { return m_ullReceived[eBytes]; }
	void setReceivedBytes(unsigned long long ullReceivedBytes) { m_ullReceived[eBytes] = ullReceivedBytes; }

	unsigned long long getReceivedPackets(void) const { return m_ullReceived[ePackets]; }
	void setReceivedPackets(unsigned long long ullReceivedPackets) { m_ullReceived[ePackets] = ullReceivedPackets; }

	unsigned long long getReceivingErrors(void) const { return m_ullReceived[eErrors]; }
	void setReceivingErrors(unsigned long long ullReceivingErrors) { m_ullReceived[eErrors] = ullReceivingErrors; }

	unsigned long long getSentBytes(void) const { return m_ullSent[eBytes]; }
	void setSentBytes(unsigned long long ullSentBytes) { m_ullSent[eBytes] = ullSentBytes; }

	unsigned long long getSentPackets(void) const { return m_ullSent[ePackets]; }
	void setSentPackets(unsigned long long ullSentPackets) { m_ullSent[ePackets] = ullSentPackets; }

	unsigned long long getSendingErrors(void) const { return m_ullSent[eErrors]; }
	void setSendingErrors(unsigned long long ullSendingErrors) { m_ullSent[eErrors] = ullSendingErrors; }

	InterfaceData & operator=(InterfaceData & rInterfaceData);
	InterfaceData operator-(InterfaceData & rInterfaceData);
	
private:

	unsigned long long m_ullReceived[eTotalTypes];
	unsigned long long m_ullSent[eTotalTypes];

};


class Interface
{
public:

	Interface(string & strInterface);
	Interface(char * pInterface);

	~Interface();

	void Update(void);

	void setActive(void) { ResolveIPAddress(); UpdateOnlineTime(); m_bActive = true; }
	void setInactive(void) { m_strIPAddress = "Unknown"; m_strOnlineTime = "0d 00:00:00"; m_bActive = false; }
	
	bool isActive(void) { return m_bActive; };

	string & getInterface(void) { return m_strInterface; }
	string & getIPAddress(void) { return m_strIPAddress; }

	Window * getWindow(void) { return &m_Window; }

	InterfaceData & getData(void) { return m_Data; }
 	void setData(InterfaceData & rInterfaceData) { m_Data = rInterfaceData; if(m_bFirst) { m_bFirst = false; m_PreviousData = rInterfaceData; } }

	void setPeriodBytes(unsigned long ulBytes) { m_ulPeriodBytes = ulBytes; }
	unsigned long getPeriodBytes(void) { return m_ulPeriodBytes; }
	
	void setPeriodPackets(unsigned long ulPackets) { m_ulPeriodPackets = ulPackets; }
	unsigned long getPeriodPackets(void) { return m_ulPeriodPackets; }

	InterfaceData & getPreviousData(void) { return m_PreviousData; }
	void setPreviousData(InterfaceData & rInterfaceData) { m_PreviousData = rInterfaceData; }

	unsigned long getTopPacketsSecond(void) const { return m_ulTopPacketsSecond; }
	void setTopPacketsSecond(unsigned long ulTopPacketsSecond) { m_ulTopPacketsSecond = ulTopPacketsSecond; }
	
	unsigned long getTopBytesSecond(void) const { return m_ulTopBytesSecond; }
	void setTopBytesSecond(unsigned long ulTopBytesSecond) { m_ulTopBytesSecond = ulTopBytesSecond; }
	
	void setDrawn(bool bDrawn) { m_bDrawn = bDrawn; }
	bool isDrawn(void) { return m_bDrawn; }

	bool haveOnlineTime(void) const { return m_bOnlineTime; }
	string & getOnlineTime(void) { return m_strOnlineTime; }
	
	deque<InterfaceData> & getHistory(void) { return m_deqHistory; }
	
private:

	void ResolveIPAddress(void);

	void UpdateOnlineTime(void);

private:

	void Initialize(const char * pInterface);

private:

	Window m_Window;

	string m_strInterface;
	string m_strIPAddress;
	string m_strOnlineTime;

	unsigned long m_ulPeriodBytes;
	unsigned long m_ulPeriodPackets;

	unsigned long m_ulTopPacketsSecond;
	unsigned long m_ulTopBytesSecond;
	
	InterfaceData m_Data;
	InterfaceData m_PreviousData;

	deque<InterfaceData> m_deqHistory;

	bool m_bActive;
	bool m_bDrawn;
	bool m_bOnlineTime;
	bool m_bFirst;
};

#endif
