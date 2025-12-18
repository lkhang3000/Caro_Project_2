#include "Globals.h"
#include <SFML/System.hpp>
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
sf::SoundBuffer _switchBuffer;
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

void PlaySwitchSFX() {
    if (_buttonBuffer.getSampleCount() == 0) return;

    _sfx.stop();
    _sfx.setBuffer(_switchBuffer);
    _sfx.play();
}

void DuckBGM(float duckVolume, int durationMs)
{
    if (!_bgm.getStatus() == sf::Music::Playing) return;

    _bgmNormalVolume = _bgm.getVolume();
    _bgm.setVolume(duckVolume);

    _bgmDuckDurationMs = durationMs;
    _bgmDuckClock.restart();
    _isBgmDucked = true;
}

bool _isBgmDucked = false;
float _bgmNormalVolume = 40.f;
sf::Clock _bgmDuckClock;
int _bgmDuckDurationMs = 0;