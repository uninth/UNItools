/** \file Email.cc
 * \author Gabriel Montenegro
 * \date 11-19-04
 * \brief E-mail Check class implementation
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

#include "Email.h"
#include "Config.h"

Email * Email::m_pEmail = NULL;

Email::Email()
{
	m_iUnread = 0;
}

Email::~Email()
{
	if(m_pEmail)
		delete m_pEmail;
	
	m_pEmail = NULL;
}

Email * Email::Instance(void)
{
	if(!m_pEmail)
		m_pEmail = new Email;
	
	return m_pEmail;
}

bool Email::Check(void)
{
	char cMailFile[64];
	char * pUser = NULL;
	string strUser;
	
	if((pUser = getenv("USER")))
		strUser = pUser;
		
	m_iUnread = 0;
	
	if(strUser.length())
	{
		string strLine;
		
		sprintf(cMailFile, "/var/mail/%s", strUser.c_str());
	
		ifstream ifMails(cMailFile);
		
		if(ifMails.is_open())
		{
			while(getline(ifMails, strLine, '\n')) 
			{
				if(!strncmp(strLine.c_str(), "From ", 5))
					m_iUnread++; 				
			}
			
			return true;
		}
	}
	
	return false;
}
