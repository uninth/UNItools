/** \file Config.h
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief Config class header
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

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "Main.h"

class Config
{
public:
	
	Config();
	virtual ~Config();

	static Config * Instance(void);

	bool Load(void);
	void LoadHomePath(void);

	bool Save(bool bForce = false);

	string & getValue(char * pOption);
	string & getValue(string & strOption);

	void setValue(char * pOption, char * pValue);
	void setValue(string & strOption, string & strValue);

	string & getHomePath(void) { return m_strHomePath; }

private:

	void LoadDefaultConfig(void);

private:

	static Config * m_pConfig;
	static string m_strConfigFile;

	bool m_bChanged;

	string m_strHomePath;

	map<string, string> m_mapConfig;	
};

#endif
