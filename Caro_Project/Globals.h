#pragma once
#ifndef Globals_h
#define Globals_h
#include "View.h"

struct _POINT {
	int x, y, c;
};

extern _POINT _A[BOARD_SIZE][BOARD_SIZE];
extern bool _TURN;
extern int _COMMAND;
extern int _X, _Y;
extern int _currentRow;  
extern int _currentCol;
extern int _backgroundBoard;

#endif