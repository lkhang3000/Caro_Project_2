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
bool _isPvE = false;

int _winsX = 0;
int _winsO = 0;
int _movesX = 0;
int _movesO = 0;

int _matchCount = 1;

sf::Music _bgm;
sf::SoundBuffer _winBuffer;
sf::SoundBuffer _loseBuffer;
sf::SoundBuffer _buttonBuffer;
sf::SoundBuffer _moveBuffer;
sf::Sound _sfx;
bool _playedResultSfx = false;

void PlayMoveSFX() {
    if (_moveBuffer.getSampleCount() == 0) return;

    _sfx.stop();
    _sfx.setBuffer(_moveBuffer);
    _sfx.play();
}

void PlayClickSFX() {
    if (_buttonBuffer.getSampleCount() == 0) return;

    _sfx.stop();
    _sfx.setBuffer(_buttonBuffer);
    _sfx.play();
}