/** \file Window.h
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-23-04
 * \brief Window class header
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
 
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Main.h"

class Window
{
	
public:
	
	Window();
	virtual ~Window();

	void ChangeColor(eColors eColor, int iModes = A_NORMAL);
	void ChangeColor(int iPair, int iModes = A_NORMAL);
	
	void MoveCursor(int iX, int iY);

	void PutString(char * pString);
	void PutString(string & strString);

	void PutChar(char cChar);

	void PutInt(int iData);
	void PutUnsignedLong(unsigned long ulData);

	void HorizontalLine(char cChar, int iLines);
	void VerticalLine(char cChar, int iLines);
	
	void Refresh(void);
	void Redraw(void);
	
	void Border(void);
	
	void Clear(void);
	void FadeToBlack(void);
	
	static int ScreenLines(void) { return LINES; }
	static int ScreenColumns(void) { return COLS; }

protected:

	WINDOW * m_pWindow;
	
};


#endif
