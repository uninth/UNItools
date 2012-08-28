/** \file Curses.cc
 * \author Gabriel Montenegro <gmontenegro@users.sourceforge.net>
 * \date 10-14-04
 * \brief Curses class implementation
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

#include <curses.h>
#include "Curses.h"

void Curses::Initialize()
{
	initscr();
	
//	trace(TRACE_MAXIMUM);
	
	start_color();
	
	init_color(1, COLOR_RED, COLOR_GREEN, COLOR_BLUE);
	
	intrflush(stdscr, TRUE);

	curs_set(0);

	nocbreak();
	noecho();
	nonl();
	
	intrflush(stdscr, FALSE);
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

	init_pair(TextBlack, COLOR_BLACK, COLOR_BLACK);
	init_pair(TextRed, COLOR_RED, COLOR_BLACK);
	init_pair(TextGreen, COLOR_GREEN, COLOR_BLACK);
	init_pair(TextYellow, COLOR_YELLOW, COLOR_BLACK);
	init_pair(TextBlue, COLOR_BLUE, COLOR_BLACK);
	init_pair(TextMagenta, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(TextCyan, COLOR_CYAN, COLOR_BLACK);
	init_pair(TextWhite, COLOR_WHITE, COLOR_BLACK);
	
	init_pair(BlockRed, COLOR_RED, COLOR_RED);
	init_pair(BlockGreen, COLOR_GREEN, COLOR_GREEN);
	init_pair(BlockYellow, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(BlockBlue, COLOR_BLUE, COLOR_BLUE);
	init_pair(BlockMagenta, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(BlockCyan, COLOR_CYAN, COLOR_CYAN);
	init_pair(BlockWhite, COLOR_WHITE, COLOR_WHITE);

}

void Curses::Finalize(void)
{
	curs_set(1);
 
	endwin();
}
