#ifndef Globals_h
#define Globals_h
#include "View.h"
#include <SFML/Audio.hpp>

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
extern bool _isPvE;

extern int _winsX;  
extern int _winsO;  
extern int _movesX;  
extern int _movesO;  

extern int _matchCount;

extern sf::String _playerXName;
extern sf::String _playerOName;

extern sf::Sound _sfx;
extern sf::SoundBuffer _buttonBuffer;
extern sf::SoundBuffer _moveBuffer;
extern sf::SoundBuffer _winBuffer;
extern sf::SoundBuffer _loseBuffer;
extern sf::Music _bgm;
extern bool _playedResultSfx;
void PlayMoveSFX();
void PlayClickSFX();
#endif
