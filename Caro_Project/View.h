#pragma once
#ifndef View_h
#define View_h
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <string>

#define BOARD_SIZE 12 
const int BOARD_LEFT = 2;
const int BOARD_TOP = 1;

using namespace std;
void GotoXY(int x, int y);
void FixConsoleWindow();
void DrawBoard(sf::RenderWindow& window, int n, int result = 2);
int mainScreen(sf::RenderWindow& window);
int AskContinue();
int ProcessFinish(int pWhoWin);

// Xử lý các màn hình chức năng
void handleSettings(sf::RenderWindow& window, sf::Font& font);
int handlePauseMenu(sf::RenderWindow& window, sf::Font& font);
int modeChoosing(sf::RenderWindow& window);
int opponentChoosing(sf::RenderWindow& window);
//Load game
int loadGameScreen(sf::RenderWindow& window);
//Save game
// Trong View.h
// Trong View.h
int handleSaveSuccessScreen(sf::RenderWindow& window, sf::Font& font, bool askContinue = true);
int handleSaveScreen(sf::RenderWindow& window, sf::Font& font, const sf::View& gameView);
std::string GetInputString(sf::RenderWindow& window, sf::Font& font, const sf::View& gameView, std::string initialText = "");
#endif

// Console versions

