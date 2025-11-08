#pragma once
#ifndef View_h
#define View_h
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
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
int modeChoosing(sf::RenderWindow& window);
//Load game
int loadGameScreen(sf::RenderWindow& window);
#endif

// Console versions

