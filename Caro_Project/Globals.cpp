#include "Globals.h"
//file lưu biến

_POINT _A[BOARD_SIZE][BOARD_SIZE] = {};
bool _TURN = false;
int _COMMAND = 0;
int _X = 0;
int _Y = 0;

int _currentRow = 0;
int _currentCol = 0;
int _backgroundBoard = 1;

int _winsX = 0;
int _winsO = 0;
int _movesX = 0;
int _movesO = 0;