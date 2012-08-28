/** \file Config.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief Config class implementation
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
#include "Config.h"
#include "Util.h"

Config * Config::m_pConfig = NULL;
string Config::m_strConfigFile = "ifstatus.cfg";

Config::Config()
{
	m_mapConfig.clear();

	LoadHomePath();
	LoadDefaultConfig();

	m_bChanged = false;
}

Config::~Config()
{
	m_mapConfig.clear();
	
	if(m_pConfig)
		delete m_pConfig;
	
	m_pConfig = NULL;
}

Config * Config::Instance(void)
{
	if(!m_pConfig)
		m_pConfig = new Config;
	
	return m_pConfig;
}

bool Config::Load(void)
{
	ifstream ifConfig;
	string strSeparator = "=";
	string strLine;
	string strFile;
	
	strFile = m_strHomePath + m_strConfigFile;

	ifConfig.open(strFile.c_str());
	
	if(ifConfig.is_open())
	{
		vector<string> vctData;
		
		while(getline(ifConfig, strLine)) 
		{
			int iPosition = strLine.find_first_of("#;/", 0);
			
			if(iPosition != -1)
				strLine.erase(iPosition, strLine.length()-iPosition);
			
			while((iPosition = strLine.find_first_of("\t", 0)) != -1)
				strLine.erase(iPosition, 1);

			Util::Trim(strLine);

			if(!strLine.length())
				continue;
			
			vctData.clear();
			
			if(Util::Split(strLine, strSeparator, vctData) != 2)
				continue;
			
			Util::Trim(vctData[0]);
			Util::Trim(vctData[1]);
			
			setValue(vctData[0], vctData[1]);
		}
		
		m_bChanged = false;
		
		ifConfig.close();
	}
	else
	{
		Save();
		
		return false;
	}
	
	return true;
}

void Config::LoadHomePath(void)
{
	char * pTemp = NULL;
	
	if((pTemp = getenv("HOME")))
	{
		m_strHomePath = pTemp;
		m_strHomePath += "/.ifstatus/";

		Util::CreateDirectory(m_strHomePath);
	}
	else
		m_strHomePath = "/etc/";
}

void Config::LoadDefaultConfig(void)
{
	char * pUser = getenv("USER");
	
	m_mapConfig["Interfaces"] = "ALL";
        m_mapConfig["Information"] = "ON";
	m_mapConfig["GraphDataSource"] = "BOTH";
	m_mapConfig["GraphPeriod"] = "1";
	m_mapConfig["GraphScaleInfo"] = "ON";
	m_mapConfig["EmailCheck"] = "ON";
	m_mapConfig["Help"] = "OFF";

	if(pUser)
		m_mapConfig["User"] = pUser;
}

bool Config::Save(bool bForce)
{
	fstream fConfig;
	string strLine;
	string strFile;
	
	strFile = m_strHomePath + m_strConfigFile;
	
	if(!bForce && !m_bChanged)
		return false;
			
	fConfig.open(strFile.c_str(), ios::out | ios::trunc);
	
	if(fConfig.is_open())
	{
		map<string, string>::iterator itConfig;
		string strLine;

		strLine = "# IFStatus ";
		strLine += VERSION;
		strLine += " configuration file.";
		
		fConfig << strLine << endl << endl;
		
		for(itConfig = m_mapConfig.begin(); itConfig != m_mapConfig.end(); itConfig++)
		{
			strLine = (*itConfig).first;
			strLine += " = ";
			strLine += (*itConfig).second;
			
			if((*itConfig).first == "Interfaces")
				strLine += "\t\t# ALL, eth0, eth1, ppp0...";
			else if((*itConfig).first == "GraphDataSource")
				strLine += "\t\t# BOTH, RX or TX.";
			else if((*itConfig).first == "GraphPeriod")
				strLine += "\t\t\t# Period in seconds to update the graph.";
			else if((*itConfig).first == "GraphScaleInfo")
				strLine += "\t\t# ON or OFF.";
			else if((*itConfig).first == "EmailCheck")
				strLine += "\t\t\t# ON or OFF.";
			else if((*itConfig).first == "Information")
				strLine += "\t\t# ON or OFF.";
			else if((*itConfig).first == "Help")
				strLine += "\t\t\t# ON or OFF.";
			else 
				continue;
				
			fConfig << strLine << endl;
		}
		
		fConfig.close();

		return true;
	}

	return false;
}

string & Config::getValue(char * pOption)
{
	string strOption = pOption;
	
	return m_mapConfig[strOption];
}

string & Config::getValue(string & strOption)
{
	return m_mapConfig[strOption];
}

void Config::setValue(char * pOption, char * pValue)
{
	if(pOption)
	{
		string strOption = pOption;
		string strValue = pValue ? pValue : "";
	
		setValue(strOption, strValue);
	}
}

void Config::setValue(string & strOption, string & strValue)
{
	string strTemp = m_mapConfig[strOption];
	
	if(strTemp != strValue)
	{
		m_mapConfig[strOption] = strValue;
		m_bChanged = true;
	}
}
