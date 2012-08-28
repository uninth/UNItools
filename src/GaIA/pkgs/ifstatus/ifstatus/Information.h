/** \file Information.h
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief Information class header
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

#ifndef _INFORMATION_H
#define _INFORMATION_H


// Include files

#include "Display.h"

class Information : public Display
{
public:
	Information();
	virtual ~Information();

	virtual void Draw(Interfaces & rInterfaces, bool bForce = false);

private:

	void ShowLabels(Interface & rInterface);
	void ShowData(Interface & rInterface, bool bForce);

	void FormatSize(unsigned long ulBytes, string & strOutput, bool bPerSecond);

private:
	string m_strLastInterface;
	string m_strLastIPAddress;
	string m_strLastOnlineTime;

	unsigned long m_ulLastTopPacketsSecond;
	unsigned long m_ulLastTopBytesSecond;

	int m_iUnreadEmail;

	InterfaceData m_cLastData;
		
	string strData[12];
	int iLastDataSize[12];

	bool m_bEmailCheck;
	bool m_bLabelsDrawn;

	bool m_bChanged;
};

#endif
