/** \file Window.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief Window class implementation
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


#include "Window.h"


Window::Window()
{
	m_pWindow = newwin(0, 0, 0, 0);	
}

Window::~Window()
{
	if(m_pWindow)
		delwin(m_pWindow);
}

void Window::Clear(void)
{
	ChangeColor(TextBlack);
	
	for(int y = 0; y < Window::ScreenLines(); y++)
	{
		MoveCursor(y, 0);
		HorizontalLine(' ', Window::ScreenColumns());
	}
}

void Window::FadeToBlack(void)
{
	ChangeColor(TextBlack);
	
	for(int y = 0; y < Window::ScreenLines(); y++)
	{
		MoveCursor(y, 0);
		HorizontalLine(' ', Window::ScreenColumns());
		Refresh();
		usleep(5000L);
	}
}

void Window::ChangeColor(eColors eColor, int iModes)
{
	wattrset(m_pWindow, COLOR_PAIR(eColor) | iModes);
}

void Window::ChangeColor(int iPair, int iModes)
{
	wattrset(m_pWindow, COLOR_PAIR(iPair) | iModes);
}

void Window::MoveCursor(int iX, int iY)
{
	wmove(m_pWindow, iX, iY);	
}

void Window::PutChar(char cChar)
{
	waddch(m_pWindow, cChar);
}

void Window::PutString(char * pString)
{
	waddstr(m_pWindow, pString);
}

void Window::PutString(string & strString)
{
	waddnstr(m_pWindow, strString.c_str(), strString.length());
}

void Window::PutUnsignedLong(unsigned long ulData)
{
	char cData[32] = { 0 };
	
	sprintf(cData, "%ld", ulData);
	
	waddnstr(m_pWindow, cData, strlen(cData));
}

void Window::PutInt(int iData)
{
	char cData[32] = { 0 };
	
	sprintf(cData, "%d", iData);
	
	waddnstr(m_pWindow, cData, strlen(cData));
}

void Window::HorizontalLine(char cChar, int iLines)
{
	whline(m_pWindow, cChar, iLines);
	
}

void Window::VerticalLine(char cChar, int iLines)
{
	wvline(m_pWindow, cChar, iLines);
}

void Window::Refresh(void)
{
	wrefresh(m_pWindow);
}

void Window::Redraw(void)
{
	redrawwin(m_pWindow);
}

void Window::Border(void)
{
	wborder(m_pWindow, 0, 0, 0, 0, 0, 0, 0, 0);
}
