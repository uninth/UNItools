/** \file Interfaces.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief Interfaces class implementation
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

#include "Interfaces.h"
#include "Config.h"
#include "Util.h"


Interfaces::Interfaces()
{
	m_tLastUpdate = time(NULL);

	m_mapInterfaces.clear();
	m_iActive = 1;
}

Interfaces::~Interfaces()
{
	m_mapInterfaces.clear();
}

int Interfaces::Load(void)
{
	Config * pConfig = Config::Instance();
	vector<string> vctInterfaces;
	vector<string>::iterator itInterface;
	string strInterfaces = pConfig->getValue("Interfaces");
	
	m_mapInterfaces.clear();
	
	Util::Split(strInterfaces, ",", vctInterfaces);
	
	for(itInterface = vctInterfaces.begin(); itInterface != vctInterfaces.end(); itInterface++)
	{
		Util::Trim(*itInterface);
		
		if(*itInterface == "ALL")
		{
			ifstream ifDevices("/proc/net/dev");
			
			if(ifDevices.fail())
				return -1;
			
			if(ifDevices.is_open())
			{
				string strLine;
				vector<string> vctData;
				list<string> lstDevices;
				list<string>::iterator itDevice;
		
				while(getline(ifDevices, strLine, '\n')) 
				{
					if(!strchr(strLine.c_str(), ':'))
						continue;
		
					vctData.clear();
					
					Util::Split(strLine, " :", vctData);
				
					lstDevices.push_back(vctData[0]);
				}
				
				ifDevices.close();
				
				for(itDevice = lstDevices.begin(); itDevice != lstDevices.end(); itDevice++)
				{
					int iSize = (int)m_mapInterfaces.size();
					bool bInsert = true;					
					
					for(int iCounter = 1; iCounter <= iSize; iCounter++)
					{
						if(m_mapInterfaces[iCounter]->getInterface() == *itDevice)
						{
							bInsert = false;
							break;
						}
					}
						
					if(bInsert)
					{
						if(iSize < 9)
							m_mapInterfaces[iSize + 1] = new Interface(*itDevice);
						else if(iSize == 9)
						{
							m_mapInterfaces[0] = new Interface(*itDevice);
							break;
						}
					}
				}
				
				lstDevices.clear();
			}
		}
		else
		{
			int iSize = (int)m_mapInterfaces.size();
			bool bInsert = true;

			printf("Checking for %s... ", (*itInterface).c_str());

			for(int iCounter = 1; iCounter <= iSize; iCounter++)
			{
				if(m_mapInterfaces[iCounter]->getInterface() == *itInterface)
				{
					bInsert = false;
					break;
				}
			}
			
			if(bInsert)
			{
				if(iSize < 9)
					m_mapInterfaces[iSize + 1] = new Interface(*itInterface);
				else if(iSize == 9)
				{
					m_mapInterfaces[0] = new Interface(*itInterface);
					break;
				}
			}	
		}
	}
	
	return m_mapInterfaces.size();
}

Interface & Interfaces::getActive(void)
{
	return *m_mapInterfaces[m_iActive];
}

bool Interfaces::setActive(int iActive)
{
	if(m_mapInterfaces.size() < (unsigned int)iActive || (m_mapInterfaces.size() < 10 && !iActive))
		return false;
	
	m_iActive = iActive;

	return true;
}

void Interfaces::UpdateInterfaces(void)
{
	map<int, Interface *>::iterator itInterfaces;

	for(itInterfaces = m_mapInterfaces.begin(); itInterfaces != m_mapInterfaces.end(); itInterfaces++)
		if((*itInterfaces).second->isActive())
			(*itInterfaces).second->Update();
}

void Interfaces::UpdateData(void)
{
	map<int, Interface *>::iterator itInterfaces;
	string strLine;
	string strSeparators = " :";
	ifstream ifDevices("/proc/net/dev");

	if(ifDevices.is_open())
	{
		vector<string> vctData;
		vector<string>::iterator itData;
		list< vector<string> > lstDevices;
		list< vector<string> >::iterator itDevices;

		while(getline(ifDevices, strLine, '\n')) 
		{
			if(!strchr(strLine.c_str(), ':'))
				continue;

			vctData.clear();
			Util::Split(strLine, strSeparators, vctData);
			lstDevices.push_back(vctData);
		}
		
		ifDevices.close();

		for(itInterfaces = m_mapInterfaces.begin(); itInterfaces != m_mapInterfaces.end(); itInterfaces++)
		{
			Interface * pInterface = (*itInterfaces).second;

			for(itDevices = lstDevices.begin(); itDevices != lstDevices.end(); itDevices++)
			{
				if(pInterface->getInterface() == (*itDevices)[0])
				{
					InterfaceData cData;
					
					cData.setReceivedBytes((unsigned long long)atoll((*itDevices)[1].c_str()));
					cData.setReceivedPackets((unsigned long long)atoll((*itDevices)[2].c_str()));
					cData.setReceivingErrors((unsigned long long)atoll((*itDevices)[3].c_str()));
		
					cData.setSentBytes((unsigned long long)atoll((*itDevices)[9].c_str()));
					cData.setSentPackets((unsigned long long)atoll((*itDevices)[10].c_str()));
					cData.setSendingErrors((unsigned long long)atoll((*itDevices)[11].c_str()));
		
					pInterface->setData(cData);
					
					break;
				}
			}
		}
	}
	
}

void Interfaces::CheckState(void)
{
	map<int, Interface *>::iterator itInterfaces;
	string strLine;
	string strSeparators = "\t";
	ifstream ifDevices("/proc/net/route");

	if(ifDevices.is_open())
	{
		vector<string> vctData;
		vector<string>::iterator itData;
		list< vector<string> > lstDevices;
		list< vector<string> >::iterator itDevices;
		int iLine = 1;

		while(getline(ifDevices, strLine, '\n')) 
		{
			if(iLine++ == 1)
				continue;

			vctData.clear();
			
			Util::Split(strLine, strSeparators, vctData);
			
			lstDevices.push_back(vctData);
		}
		
		ifDevices.close();

		for(itInterfaces = m_mapInterfaces.begin(); itInterfaces != m_mapInterfaces.end(); itInterfaces++)
		{
			Interface * pInterface = (*itInterfaces).second;
			bool bFound = false;

			if( pInterface->getInterface() == "lo" )
			{
				bFound = true;

				if(!pInterface->isActive())
					pInterface->setActive();
			}
			else
			{
				for(itDevices = lstDevices.begin(); itDevices != lstDevices.end(); itDevices++)
				{
					if(pInterface->getInterface() == Util::TrimRight((*itDevices)[0]))
					{
						bFound = true;
					
						if(!pInterface->isActive())
							pInterface->setActive();
					
						break;
					}
				}
			}

			if(!bFound)
			{
				if(pInterface->isActive())
					pInterface->setInactive();
				
				continue;
			}

		}
	}
	
}
