/** \file IFStatus.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief IFStatus class implementation
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

#include "Main.h"
#include "IFStatus.h"
#include "Graph.h"
#include "Email.h"
#include "Config.h"
#include "Curses.h"
#include "Window.h"
#include "Display.h"
#include "Interfaces.h"
#include "Information.h"
#include "GraphDecorator.h"
#include "BorderDecorator.h"

IFStatus::IFStatus()
{
	m_pConfig = Config::Instance();
	m_pDisplay = new BorderDecorator(new GraphDecorator(new Information));
	
	m_iLastHeight = Window::ScreenLines();
	m_iLastWidth = Window::ScreenColumns();
}

IFStatus::~IFStatus()
{
	Finalize();	
}

void IFStatus::Initialize(void)
{
	m_pConfig->Load();
	
	m_cInterfaces.Load();
}

void IFStatus::Finalize(void)
{
	m_pConfig->Save();
}

bool IFStatus::KeyboardOptions(void)
{
	int iWidth = Window::ScreenColumns();
	int iHeight = Window::ScreenLines();
	bool bChanged = false;
	bool bReturn = true;
	char cKey = getch();

	if(iWidth != m_iLastWidth || iHeight != m_iLastHeight)
	{
		bChanged = true;
		
		m_iLastHeight = iHeight;
		m_iLastWidth = iWidth;
	}
	
	if(cKey != ERR)
	{
		switch(cKey)
		{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
			{
				int iTurnActive = (cKey > 48) ? cKey -  48 : 0;
			
				if(m_cInterfaces.setActive(iTurnActive))
					bChanged = true;
			}
				
			
				break;
			
			case 'i':
			case 'I':
				
				if(m_pConfig->getValue("Information") == "ON")
					m_pConfig->setValue("Information", "OFF");
				else
					m_pConfig->setValue("Information", "ON");
				
				bChanged = true;
			
				break;

			case 's':
			case 'S':

				if(m_pConfig->getValue("GraphScaleInfo") == "ON")
					m_pConfig->setValue("GraphScaleInfo", "OFF");
				else
					m_pConfig->setValue("GraphScaleInfo", "ON");
				
				bChanged = true;					
			
				break;
				
			case 'g':
			case 'G':
			{
				string strType = m_pConfig->getValue("GraphDataSource");
				
				if(strType == "RX")
					m_pConfig->setValue("GraphDataSource", "TX");
				else if(strType == "TX")
					m_pConfig->setValue("GraphDataSource", "BOTH");
				else
					m_pConfig->setValue("GraphDataSource", "RX");
			
			}				
				bChanged = true;
			
				break;
				
			case '+':
			{
				char cPeriod[8];
				unsigned int uiGraphPeriod = atoi((m_pConfig->getValue("GraphPeriod")).c_str());
				
				if(uiGraphPeriod < 10)
				{
					uiGraphPeriod++;
				
					sprintf(cPeriod, "%d", uiGraphPeriod);
			
					m_pConfig->setValue("GraphPeriod", cPeriod);
					
					bChanged = true;
				}
			}
			
				break;

			case '-':
			{
				char cPeriod[8];
				unsigned int uiGraphPeriod = atoi((m_pConfig->getValue("GraphPeriod")).c_str());
				
				if(uiGraphPeriod > 1)
				{
					uiGraphPeriod--;
					
					sprintf(cPeriod, "%d", uiGraphPeriod);
					
					m_pConfig->setValue("GraphPeriod", cPeriod);
					
					bChanged = true;
				}
			}
			
				break;
			
			case 'h':
			case 'H':
				
				if(m_pConfig->getValue("Help") == "ON")
					m_pConfig->setValue("Help", "OFF");
				else
					m_pConfig->setValue("Help", "ON");
				
				bChanged = true;
			
				break;
				
			case 'r':
			case 'R':

				bChanged = true;
			
				break;
			
			case 'q':
			case 'Q':
				
				bReturn = false;
			
				m_cInterfaces.getActive().getWindow()->FadeToBlack();
			
				break;
			
			default:
				
				break;
		}
	}

	if(bChanged)
	{
		m_cInterfaces.getActive().getWindow()->Clear();
		m_pDisplay->Draw(m_cInterfaces, true);
	}
	
	return bReturn;	
}

void IFStatus::Start(void)
{
	Config * pConfig = Config::Instance();
	bool bLoop = true;
	time_t tLast[2] = { 0, 0 }, tNow;
	int iGraphPeriod;

	m_cInterfaces.Load();

	if(!m_cInterfaces.getCount())
		return;

	while(bLoop)
	{
		tNow = time(NULL);
		
		iGraphPeriod = atoi((pConfig->getValue("GraphPeriod")).c_str());
	
		if(iGraphPeriod <= 0)
			iGraphPeriod = 1;
	
		if(tLast[0] + 1 <= tNow)
		{
			m_cInterfaces.CheckState();
			m_cInterfaces.UpdateInterfaces();
			
			tLast[0] = tNow;
		}

		if((tLast[2] + 60) <= tNow)
		{
			if(pConfig->getValue("EmailCheck") == "ON")
			{
				Email * pEmail = Email::Instance();
				
				pEmail->Check();
				
				tLast[1] = tNow;
			}
		}
		
		m_cInterfaces.UpdateData();
		m_pDisplay->Draw(m_cInterfaces);

		bLoop = KeyboardOptions();
		
		usleep(100000L);
	}
}
