#include <SFML/Graphics.hpp>
#include "View.h"
#include "Model.h"
#include "Control.h"
#include "Globals.h"
#include <iostream>
#include <cctype>
using namespace std;

GameRule rule = GameRule::FREESTYLE;
GameRule _rule = GameRule::FREESTYLE;

int main() {
    FixConsoleWindow();

    sf::RenderWindow window(sf::VideoMode(1366, 768), "Caro", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        int menuChoice = mainScreen(window);

        switch (menuChoice) {
        case 1: // Chế độ
        {
            int choice = modeChoosing(window);
            switch (choice) {
            case 2:
                rule = GameRule::FREESTYLE;
                _backgroundForBoard = 1;
                break;
            case 3:
                rule = GameRule::STANDARD;
                _backgroundForBoard = 2;
                break;
            case 4:
                rule = GameRule::BLOCKED_TWO_ENDS;
                _backgroundForBoard = 3;
                break;
            default: continue;
            }
            break;
        }
        case 2: // Mới
        {
            // ======= BẮT ĐẦU GAME =======
            StartGame();
            int result = 2;

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return 0;
                    }

                    if (event.type == sf::Event::KeyPressed) {
                        if (result != 2) {
                            if (event.key.code == sf::Keyboard::Enter) {
                                goto main_menu;
                            }
                            continue;
                        }
                        switch (event.key.code) {
                        case sf::Keyboard::A:
                            MoveLeft();
                            break;
                        case sf::Keyboard::W:
                            MoveUp();
                            break;
                        case sf::Keyboard::S:
                            MoveDown();
                            break;
                        case sf::Keyboard::D:
                            MoveRight();
                            break;
                        case sf::Keyboard::Enter:
                        {
                            if (PlacePiece()) {
                                result = TestBoard(rule);

                                if (result != 2) {

                                }

                                _TURN = !_TURN;
                            }
                            break;
                        }
                        case sf::Keyboard::Escape:
                            goto main_menu;
                        default:
                            break;
                        }
                    }
                }

                // Render game
                window.clear();
                DrawBoard(window, BOARD_SIZE, result);
                window.display();
            }
        main_menu:
            break;
        }
        case 3:
        {
            int slot = loadGameScreen(window);
            if (slot == 0) break; // 0 = thoát hoặc quay lại menu chính

            window.close();
            std::cout << u8"Đang tải slot " << slot << "...\n";

            // ======= LOAD GAME =======
            if (!LoadFromFile(slot)) {
                std::cout << u8"Không thể tải file slot " << slot << ". Bắt đầu game mới.\n";
                StartGame();
            }

            bool validEnter = true;
            _rule = rule;

            while (true)
            {
                _COMMAND = toupper(_getch());
                if (_COMMAND == 27) // ESC để thoát
                {
                    ExitGame();
                    return 0;
                }
                else {
                    if (_COMMAND == 'A') MoveLeft();
                    else if (_COMMAND == 'W') MoveUp();
                    else if (_COMMAND == 'S') MoveDown();
                    else if (_COMMAND == 'D') MoveRight();
                    else if (_COMMAND == 13) // ENTER
                    {
                        switch (CheckBoard(_X, _Y)) {
                        case -1: cout << "X"; break;
                        case 1:  cout << "O"; break;
                        case 0:  validEnter = false;
                        }
                        if (validEnter == true) {
                            int result = 2;
                            switch (_rule)
                            {
                            case GameRule::FREESTYLE:
                                result = TestBoard_Freestyle(); break;
                            case GameRule::STANDARD:
                                result = TestBoard_Standard(); break;
                            case GameRule::BLOCKED_TWO_ENDS:
                                result = TestBoard_BlockedTwoEnds(); break;
                            }

                            switch (ProcessFinish(result)) {
                            case -1: case 1: case 0:
                                if (AskContinue() != 'Y') {
                                    ExitGame();
                                    return 0;
                                }
                                else {
                                    StartGame();
                                }
                            }
                        }
                        validEnter = true;
                    }
                }
            }

            break;
        }
            
        case 4: // Thoát
            ExitGame();
            window.close();
            return 0;
        default:
            continue;
        }
        
    }
    return 0;
}
