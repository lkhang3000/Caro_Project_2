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

main_menu:
    while (window.isOpen()) {
        int menuChoice = mainScreen(window);

        
        auto RunGameLoop = [&](bool isLoaded) {
            // === 1. Tải Font và Assets ===
            sf::Font font;
            if (!font.loadFromFile("Assets/font/regular.ttf")) {
                std::cerr << "Không thể tải font!\n";
            }

            sf::Texture settingOffT, settingOnT, pauseOffT, pauseOnT, playOnT;
            if (!settingOffT.loadFromFile("Assets/button/setting2_button_off.png")) {}
            if (!settingOnT.loadFromFile("Assets/button/setting2_button_on.png")) {}
            if (!pauseOffT.loadFromFile("Assets/button/pause_button_off.png")) {}
            if (!pauseOnT.loadFromFile("Assets/button/pause_button_on.png")) {}
            if (!playOnT.loadFromFile("Assets/button/play_button_on.png")) {}

            sf::Sprite settingButton(settingOffT);
            sf::Sprite pauseButton(pauseOffT);

            
            float buttonScale = 4.26875f - 1.5;
            float margin = 4.267f - 1.5;
            float btnWidth = settingOffT.getSize().x * buttonScale;

            
            float settingX = 1366.f - margin - btnWidth;
            float pauseX = settingX; 
            float settingY = margin;
            float pauseY = margin;

            settingButton.setPosition(settingX, settingY);
            pauseButton.setPosition(pauseX, pauseY);

            settingButton.setScale(buttonScale, buttonScale);
            pauseButton.setScale(buttonScale, buttonScale);

            settingButton.setPosition(settingX, settingY);
            pauseButton.setPosition(pauseX, pauseY);
            
            if (!isLoaded) {
                StartGame();
            }
            int result = TestBoard(rule);
            if (isLoaded && result != 2) result = 2; 

            enum GameState { BOARD_ACTIVE, PAUSE_FOCUSED, SETTING_FOCUSED };
            GameState gameState = BOARD_ACTIVE;
            bool isPaused = false;

            
            while (window.isOpen()) {
                if (_isPvE && !_TURN && result == 2 && !isPaused) {
                    sf::sleep(sf::milliseconds(300));
                    _POINT botMove = GetBotMove();
                    _currentRow = botMove.x;
                    _currentCol = botMove.y;
                    if (PlacePiece()) {
                        result = TestBoard(rule);
                        if (result == -1) ++_winsX;
                        else if (result == 1) ++_winsO;
                        _TURN = !_TURN;
                    }
                }

                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return;
                    }
                    if (event.type == sf::Event::KeyPressed) {
                        if (_isPvE && !_TURN && result == 2) continue;

                        if (result != 2) {
                            if (event.key.code == sf::Keyboard::Enter) {
                                StartGame();
                                result = 2; 
                            }
                            else if (event.key.code == sf::Keyboard::Escape) return;
                            continue;
                        }

                        if (isPaused) continue;

                        switch (event.key.code) {
                        case sf::Keyboard::A:
                            if (gameState == BOARD_ACTIVE) MoveLeft();
                            else if (gameState == PAUSE_FOCUSED) gameState = BOARD_ACTIVE;
                            else if (gameState == SETTING_FOCUSED) gameState = PAUSE_FOCUSED;
                            break;
                        case sf::Keyboard::D:
                            if (gameState == BOARD_ACTIVE) MoveRight();
                            else if (gameState == PAUSE_FOCUSED) gameState = SETTING_FOCUSED;
                            break;
                        case sf::Keyboard::W:
                            if (gameState == BOARD_ACTIVE) {
                                if (_currentRow == 0) {
                                    gameState = PAUSE_FOCUSED;
                                }
                                else MoveUp();
                            }
                            else gameState = BOARD_ACTIVE;
                            break;
                        case sf::Keyboard::S:
                            if (gameState == BOARD_ACTIVE) MoveDown();
                            else gameState = BOARD_ACTIVE;
                            break;
                        case sf::Keyboard::Enter:
                        {
                            if (gameState == BOARD_ACTIVE) {
                                if (PlacePiece()) {
                                    result = TestBoard(rule);
                                    if (result == -1) ++_winsX;
                                    else if (result == 1) ++_winsO;
                                    _TURN = !_TURN;
                                }
                            }
                            else if (gameState == SETTING_FOCUSED) {
                                handleSettings(window, font);
                                gameState = BOARD_ACTIVE;
                            }
                            else if (gameState == PAUSE_FOCUSED) {
                                isPaused = true;
                                int pauseResult = handlePauseMenu(window, font);
                                isPaused = false;
                                gameState = BOARD_ACTIVE;

                                if (pauseResult == 2) { // Reset
                                    StartGame();
                                    result = 2;
                                }
                                else if (pauseResult == 3) { // Save
                                    int saveRes = handleSaveScreen(window, font, window.getView());
                                    if (saveRes == 0) return; // Không chơi tiếp -> Về menu
                                }
                                else if (pauseResult == 4) { // Exit
                                    return;
                                }
                            }
                            break;
                        }
                        case sf::Keyboard::Escape:
                            return;
                        default: break;
                        }
                    }
                }

                // === 4. Render Game ===
                window.clear();
                DrawBoard(window, BOARD_SIZE, result);

                
                settingButton.setTexture(settingOffT);
                pauseButton.setTexture(pauseOffT);

                if (gameState == SETTING_FOCUSED) {
                    settingButton.setTexture(settingOnT);
                    pauseButton.setTexture(pauseOffT);
                }
                else if (gameState == PAUSE_FOCUSED) {
                    pauseButton.setTexture(pauseOnT);
                    settingButton.setTexture(settingOffT);
                }

                window.draw(settingButton);
                window.draw(pauseButton);
                window.display();
            }
            };

        switch (menuChoice) {
        case 1: // Chế độ
        {
            int choice = modeChoosing(window);
            if (choice == -1) continue;
            switch (choice) {
            case 2:
                rule = GameRule::FREESTYLE;
                _backgroundBoard = 1;
                break;
            case 3:
                rule = GameRule::STANDARD;
                _backgroundBoard = 2;
                break;
            case 4:
                rule = GameRule::BLOCKED_TWO_ENDS;
                _backgroundBoard = 3;
                break;
            default: continue;
            }
            break;
        }
        case 2: // New Game
        {
            int opponent = opponentChoosing(window);
            if (opponent == -1) break;
            if (opponent == 1) _isPvE = true;
            else _isPvE = false;

            RunGameLoop(false); // Chạy game mới
            break;
        }
        case 3: // Load Game
        {
            int loadResult = loadGameScreen(window);

            if (loadResult == 0) break; 

            rule = _rule;

            if (rule == GameRule::FREESTYLE) _backgroundBoard = 1;
            else if (rule == GameRule::STANDARD) _backgroundBoard = 2;
            else if (rule == GameRule::BLOCKED_TWO_ENDS) _backgroundBoard = 3;

            
            RunGameLoop(true);

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