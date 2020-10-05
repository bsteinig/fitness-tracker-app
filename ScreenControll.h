// By putting this function in a header file the class member functions were 
//	able to manipulate the windows console cursor as well
#pragma once
// the preprocessor directive is now obsolete, the linker was defining this function each time the header file
// was included, but this was easily solved by adding the static keyword
#ifndef SCREENCONTROLL_H 
#define SCREENCONTROLL_H
#include <Windows.h>

static void placeCursor(HANDLE screen, int row, int col)
{
	COORD pos;
	pos.Y = row;
	pos.X = col;
	SetConsoleCursorPosition(screen, pos);
}

#endif	