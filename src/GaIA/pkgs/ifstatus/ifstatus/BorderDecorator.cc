/** \file BorderDecorator.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief BorderDecorator class implementation
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

#include "BorderDecorator.h"
#include "Config.h"
#include "Window.h"

BorderDecorator::BorderDecorator(Display * pDisplay) : Decorator(pDisplay)
{
	m_bDrawn = false;
}

BorderDecorator::~BorderDecorator()
{

}

void BorderDecorator::Draw(Interfaces & rInterfaces, bool bForce)
{
	Interface & rInterface = rInterfaces.getActive();
	Config * pConfig = Config::Instance();
	string & rHelp = pConfig->getValue("Help");
	
	if(!m_bDrawn || bForce)
		DrawBorder(rInterface);
	
	if(strLastHelp != rHelp || bForce)
	{
		strLastHelp = rHelp;

		if(rHelp == "ON")
			DrawHelp(rInterface, true);
		else
			DrawHelp(rInterface, false);
	}		
		
	Decorator::Draw(rInterfaces, bForce);
}

void BorderDecorator::DrawBorder(Interface & rInterface)
{
	Window * pWindow = rInterface.getWindow();

	
	string strIFStatus = "[ IFStatus ";
	strIFStatus += VERSION;
	strIFStatus += " ]";
	
	pWindow->ChangeColor(TextWhite);
	pWindow->Border();
	
	if(Window::ScreenLines() >= 2 && Window::ScreenColumns() >= (int)strIFStatus.length() + 4)
	{
		pWindow->MoveCursor(0, (Window::ScreenColumns() / 2) - (strIFStatus.length() / 2));
		pWindow->PutString(strIFStatus);
	}
	
	m_bDrawn = true;
}

void BorderDecorator::DrawHelp(Interface & rInterface, bool bActive)
{
	Window * pWindow = rInterface.getWindow();	
	Config * pConfig = Config::Instance();
	string strHelp;
	
	if(bActive)
		strHelp = "[ (#) ][ (S)cale: " + pConfig->getValue("GraphScaleInfo") +
					  " ][ (G)raph Source: " + pConfig->getValue("GraphDataSource") +
					  " ][ (I)nfo: " + pConfig->getValue("Information") +
					  " ][ (+/-): " + pConfig->getValue("GraphPeriod") + "s" +
					  " ]";
	else
		strHelp = "[ (H)elp ][ Author: Gabriel Montenegro ]";

	if(Window::ScreenLines() >= 2 && Window::ScreenColumns() >= (int)strHelp.length() + 4)
	{
		pWindow->MoveCursor(Window::ScreenLines() - 1, (Window::ScreenColumns() / 2) - (strHelp.length() / 2));
		pWindow->PutString(strHelp);
	}
}


/*
void BorderDecorator::DrawInterfaces(Interfaces & rInterfaces)
{
	Window * pWindow = rInterfaces.getActive().getWindow();
	map<int, Interface *> & rIfaces = rInterfaces.getInterfaces();
	map<int, Interface *>::iterator itInterface;
	string strBlocks;
	int iBegin, iPosition;
	
	iBegin = 2;

	strBlocks = "[ (H)elp ]";

        pWindow->ChangeColor(TextWhite);

        pWindow->MoveCursor(Window::ScreenLines() - 1, iBegin);
        pWindow->PutString(strBlocks);

	iBegin += strBlocks.length();

	for(itInterface = rIfaces.begin(); itInterface != rIfaces.end(); itInterface++)
	{
		strBlocks = "[";

		for(int iSize = 0; iSize < (int)(*itInterface).second->getInterface().length(); iSize++)
			strBlocks += " ";

		strBlocks += "]";

		iPosition = iBegin + 1;

		pWindow->ChangeColor(TextWhite);
		
	        pWindow->MoveCursor(Window::ScreenLines() - 1, iBegin);
        	pWindow->PutString(strBlocks);

		if(((*itInterface).second->getInterface()) == rInterfaces.getActive().getInterface())
	        	pWindow->ChangeColor(TextCyan);

		pWindow->MoveCursor(Window::ScreenLines() - 1, iPosition);
        	pWindow->PutString((*itInterface).second->getInterface());		

		iBegin += strBlocks.length();
	}
	
}

*/
