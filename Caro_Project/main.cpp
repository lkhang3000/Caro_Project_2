#include <SFML/Graphics.hpp>
#include "View.h"
#include "Model.h"
#include "Control.h"
#include "Globals.h"
#include <iostream>
#include <cctype>
using namespace std;

GameRule rule = GameRule::FREESTYLE;

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
                        case sf::Keyboard::Left:
                            MoveLeft();
                            break;
                        case sf::Keyboard::W:
                        case sf::Keyboard::Up:
                            MoveUp();
                            break;
                        case sf::Keyboard::S:
                        case sf::Keyboard::Down:
                            MoveDown();
                            break;
                        case sf::Keyboard::D:
                        case sf::Keyboard::Right:
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
            // Mở cửa sổ Setting bằng SFML
            sf::RenderWindow settingsWindow(sf::VideoMode(1366, 768), "Settings", sf::Style::Close);
            sf::Font font;
            if (!font.loadFromFile("Assets/font/regular.ttf")) {
                cerr << "Khong the tai font!\n";
            }
            handleSettings(window, font);
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
