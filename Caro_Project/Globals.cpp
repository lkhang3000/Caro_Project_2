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


sf::String _playerXName;
sf::String _playerOName;
sf::Music _bgm;
sf::SoundBuffer _winBuffer;
sf::SoundBuffer _loseBuffer;
sf::SoundBuffer _buttonBuffer;
sf::SoundBuffer _moveBuffer;
sf::SoundBuffer _switchBuffer;
sf::SoundBuffer _typingBuffer;
sf::Sound _uiSfx;
sf::Sound _resultSfx;
bool _playedResultSfx = false;

void PlayMoveSFX() {
    if (_moveBuffer.getSampleCount() == 0) return;
    _uiSfx.stop();
    _uiSfx.setBuffer(_moveBuffer);
    _uiSfx.setVolume(100.f * GetSfxScale());
    _uiSfx.play();
}

void PlayClickSFX() {
    if (_buttonBuffer.getSampleCount() == 0) return;
    _uiSfx.stop();
    _uiSfx.setBuffer(_buttonBuffer);
    _uiSfx.setVolume(100.f * GetSfxScale());
    _uiSfx.play();
}

void PlayTypingSFX() {
    if (_typingBuffer.getSampleCount() == 0) return;
    _uiSfx.stop();
    _uiSfx.setBuffer(_typingBuffer);
    _uiSfx.setVolume(100.f * GetSfxScale());
    _uiSfx.play();
}

void PlaySwitchSFX() {
    if (_switchBuffer.getSampleCount() == 0) return;
    _uiSfx.stop();
    _uiSfx.setBuffer(_switchBuffer);
    _uiSfx.setVolume(100.f * GetSfxScale());
    _uiSfx.play();
}

void DuckBGM(float targetVolume, int durationMs)
{
    _bgmNormalVolume = _bgm.getVolume();   // luôn lấy lại volume
    _bgm.setVolume(targetVolume * GetBgmScale());
    _bgmDuckDurationMs = durationMs;
    _bgmDuckClock.restart();
    _isBgmDucked = true;
}

bool _isBgmDucked = false;
float _bgmNormalVolume = 40.f;
sf::Clock _bgmDuckClock;
int _bgmDuckDurationMs = 0;

SoundQuality _soundQuality = SOUND_HIGH;
SoundQuality _bgmQuality = SOUND_HIGH;
SoundQuality _sfxQuality = SOUND_HIGH;

float GetBgmScale()
{
    switch (_bgmQuality)
    {
    case SOUND_MUTED:  return 0.f;
    case SOUND_LOW:    return 0.3f;
    case SOUND_MEDIUM: return 0.6f;
    case SOUND_HIGH:   return 1.f;
    }
    return 1.f;
}

float GetSfxScale()
{
    switch (_sfxQuality)
    {
    case SOUND_MUTED:  return 0.f;
    case SOUND_LOW:    return 0.3f;
    case SOUND_MEDIUM: return 0.6f;
    case SOUND_HIGH:   return 1.f;
    }
    return 1.f;
}