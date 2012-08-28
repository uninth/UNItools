/** \file Util.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-22-04
 * \brief Util class implementation
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
 

#include "Util.h"


int Util::Split(string & strText, string strSeparators, vector<string> & vctWords)
{
	int iWords = 0;
	int iTextLen = strText.length();
	int iStart = strText.find_first_not_of(strSeparators, 0);

	while((iStart >= 0) && (iStart < iTextLen))
	{
		int iStop = strText.find_first_of(strSeparators, iStart);

		if((iStop < 0) || (iStop > iTextLen))
			iStop = iTextLen;

		vctWords.push_back(strText.substr(iStart, iStop - iStart));

		iStart = strText.find_first_not_of(strSeparators, iStop+1);

		iWords++;
	}

	return iWords;
}

string & Util::TrimRight(string & strText)
{
	char * pBegin = new char[strText.length() + 1];
	char * pTmp = pBegin;
	
	strcpy(pBegin, strText.c_str());

	pTmp = pBegin + (strText.length() - 1);

	while(*pTmp == 32)
		*pTmp-- = 0;

	strText = pBegin;
	
	delete [] pBegin;
	
	return strText;
}

string & Util::TrimLeft(string & strText)
{
	char * pBegin = new char[strText.length() + 1];
	char * pInitA = pBegin;
	char * pInitB = pBegin;

	strcpy(pBegin, strText.c_str());
	
	while(*pInitB == 32)
		pInitB++;

	if(pInitA != pInitB)
	{
		while((*(pInitA++) = *(pInitB++)));
		
		strText = pBegin;
	}
	
	delete [] pBegin;

	return strText;
}

string & Util::Trim(string & strText)
{
	return TrimLeft(TrimRight(strText));
}

void Util::CreateDirectory(string & strDirectory)
{
	struct stat sStat;
	mode_t mMode = 00755;
	
	if(!stat(strDirectory.c_str(), &sStat))
		return;
	
	mkdir(strDirectory.c_str(), mMode);
}
