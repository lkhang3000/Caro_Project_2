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

        switch (menuChoice) {
        case 1: // Chế độ
        {
            int choice = modeChoosing(window);
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
        case 2: // Mới / Tiếp tục Game (SFML Loop)
        {
			//Chọn PvP hay PvE
			int opponent = opponentChoosing(window);   
			if (opponent == -1) break;
			if (opponent == 1) {
			    _isPvE = true;  
			}
			else {
			    _isPvE = false; 
			}
            // === 1. Tải Font và Assets cho Game Play ===
            sf::Font font;
            if (!font.loadFromFile("Assets/font/regular.ttf")) {
                std::cerr << "Không thể tải font!\n";
            }

            // Tải Texture cho nút Setting và Pause/Play
            sf::Texture settingOffT, settingOnT, pauseOffT, pauseOnT, playOnT, backOnT, backOffT;
            // Đảm bảo bạn có các file này trong Assets/button/
            if (!settingOffT.loadFromFile("Assets/button/setting2_button_off.png")) { /* handle error */ }
            if (!settingOnT.loadFromFile("Assets/button/setting2_button_on.png")) { /* handle error */ }
            if (!pauseOffT.loadFromFile("Assets/button/pause_button_off.png")) { /* handle error */ }
            if (!pauseOnT.loadFromFile("Assets/button/pause_button_on.png")) { /* handle error */ }
            if (!playOnT.loadFromFile("Assets/button/play_button_on.png")) { /* handle error */ }
			if (!backOnT.loadFromFile("Assets/button/exit.png")) { /* handle error */ }
			if (!backOffT.loadFromFile("Assets/button/exit_dark.png")) { /* handle error */ }

            sf::Sprite settingButton(settingOffT);
            sf::Sprite pauseButton(pauseOffT);
            sf::Sprite backButton(backOffT);

            // Vị trí và Scale nút
            float buttonScale = 4.26875f - 1.5;
            float margin = 4.267f - 1.5;
            float btnWidth = settingOffT.getSize().x * buttonScale;

            // Tính toán vị trí các nút ở góc phải trên
            // Setting ở ngoài cùng bên phải
            float settingX = 1366.f - margin - btnWidth;
            // Pause ở bên trái Setting
            float pauseX = settingX;
            float settingY = margin;
            float pauseY = margin;
            settingButton.setPosition(settingX, settingY);
            pauseButton.setPosition(pauseX, pauseY);

            settingButton.setScale(buttonScale, buttonScale);
            pauseButton.setScale(buttonScale, buttonScale);
			backButton.setScale(buttonScale, buttonScale);
            settingButton.setPosition(settingX, settingY);
            pauseButton.setPosition(pauseX, pauseY);
			backButton.setPosition(10.f, 10.f);

            // === 2. Khởi tạo Trạng thái Game ===
            StartGame();
            int result = 2; // 2: Đang chơi, -1: X thắng, 1: O thắng, 0: Hòa

            // enum GameState { BOARD_ACTIVE, PAUSE_FOCUSED, SETTING_FOCUSED, BACK_FOCUSED }; (Nên khai báo trong Globals.h)
            enum GameState { BOARD_ACTIVE, PAUSE_FOCUSED, SETTING_FOCUSED, BACK_FOCUSED }; // Khai báo tạm nếu chưa có
            GameState gameState = BOARD_ACTIVE;
            bool isPaused = false;

            // === 3. Vòng lặp Game Play ===
            while (window.isOpen()) {
				if (_isPvE && !_TURN && result == 2 && !isPaused) {
				    sf::sleep(sf::milliseconds(300)); 
				    _POINT botMove = GetBotMove();                     
				    _currentRow = botMove.x;
				    _currentCol = botMove.y;
				    if (PlacePiece()) {
				        result = TestBoard(rule); 
				        _TURN = !_TURN;           
				    }
				}
				// ==========================================================
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        return 0;
                    }
                    if (event.type == sf::Event::KeyPressed) {
						// Nếu là PvE + Lượt Máy (O) + Game chưa xong -> Bỏ qua mọi phím bấm
						if (_isPvE && !_TURN && result == 2) {
						    continue;
						}

                        // 1. Xử lý khi Game đã kết thúc (result != 2)
                        if (result != 2) {
                            if (event.key.code == sf::Keyboard::Enter) {
                                StartGame();
                                goto main_menu;
                            }
                            continue;
                        }

                        // 2. Ngăn chặn input khi đang trong Menu Pause
                        if (isPaused) {
                            continue;
                        }

                        // 3. Xử lý Input chính khi Game Active/Focus nút
                        switch (event.key.code) {
                        case sf::Keyboard::A:
                            if (gameState == BOARD_ACTIVE) MoveLeft();
                            else if (gameState == PAUSE_FOCUSED) gameState = BOARD_ACTIVE; // Từ Pause về Board (hoặc vòng)
                            else if (gameState == SETTING_FOCUSED) gameState = PAUSE_FOCUSED; // Từ Setting về Pause
                            else if (gameState == PAUSE_FOCUSED) gameState = BACK_FOCUSED;
                            break;
                        case sf::Keyboard::D:
                            if (gameState == BOARD_ACTIVE) MoveRight();
                            else if (gameState == BACK_FOCUSED) gameState = PAUSE_FOCUSED; // Back sang phải là Pause
                            else if (gameState == PAUSE_FOCUSED) gameState = SETTING_FOCUSED;
                            break;
                        case sf::Keyboard::W:
                            // LOGIC MỚI: Chỉ cần MoveUp một lần từ hàng 0 sẽ chuyển focus
                            if (gameState == BOARD_ACTIVE) {
                                if (_currentRow == 0) { // Kiểm tra nếu đang ở hàng đầu tiên
                                    // Từ hàng trên cùng của bàn cờ
                                    // Logic thông minh: Nếu ở bên trái bàn cờ -> lên Back, bên phải -> lên Pause
                                    if (_currentCol < BOARD_SIZE / 2) gameState = BACK_FOCUSED;
                                    else gameState = PAUSE_FOCUSED;
                                }
                                else {
                                    MoveUp();
                                }
                            }
                            else {
                                // Khi đang focus nút, W đưa về focus bàn cờ
                                gameState = BOARD_ACTIVE;
                            }
                            break;
                        case sf::Keyboard::S:
                            if (gameState == BOARD_ACTIVE) {
                                MoveDown();
                            }
                            else {
                                // Khi đang focus nút, S đưa về focus bàn cờ
                                gameState = BOARD_ACTIVE;
                            }
                            break;
                        case sf::Keyboard::Enter:
                        {
                            if (gameState == BOARD_ACTIVE) {
                                if (PlacePiece()) {

                                    // moves already incremented inside PlacePiece()
                                    result = TestBoard(rule);

                                    // update wins when the game ends (TestBoard returns -1 for X, 1 for O, 0 for draw)
                                    if (result == -1) {
                                        ++_winsX;
                                    } else if (result == 1) {
                                        ++_winsO;
                                    }

                                    _TURN = !_TURN;

                                    if (result != 2) {
                                        // existing game-over handling (keep as before)
                                    }
                                }
                            }
                            else if (gameState == BACK_FOCUSED) {
                                // Xử lý Back -> Về Main Menu
                                goto main_menu;
                            }
                            else if (gameState == SETTING_FOCUSED) {
                                handleSettings(window, font);
                                gameState = BOARD_ACTIVE; // Quay lại bàn cờ sau khi thoát Settings
                            }
                            else if (gameState == PAUSE_FOCUSED) {
                                isPaused = true;

                                int pauseResult = handlePauseMenu(window, font);

                                isPaused = false;
                                gameState = BOARD_ACTIVE; // Luôn quay lại bàn cờ sau khi thoát menu

                                if (pauseResult == 1) { /* Tiếp tục */ }
                                else if (pauseResult == 2) {
                                    StartGame();
                                    result = 2;
                                }
                                else if (pauseResult == 3) { /* Lưu game */ }
                                else if (pauseResult == 4) {
                                    goto main_menu;
                                }
                            }
                            break;
                        }
                        case sf::Keyboard::Escape:
                            goto main_menu; // ESC thoát về Main Menu
                        default:
                            break;
                        }
                    }
                }

                // === 4. Render Game ===
                window.clear();
                DrawBoard(window, BOARD_SIZE, result);

                // Cập nhật trạng thái và vẽ nút
                settingButton.setTexture(settingOffT);
                pauseButton.setTexture(pauseOffT);
				backButton.setTexture(backOffT);

                // Khi focus Setting
                if (gameState == SETTING_FOCUSED) {
                    settingButton.setTexture(settingOnT);
                    pauseButton.setTexture(pauseOffT);
                    backButton.setTexture(backOffT);
                }
                // Khi focus Pause
                else if (gameState == PAUSE_FOCUSED) {
                    pauseButton.setTexture(pauseOnT);
                    settingButton.setTexture(settingOffT);
                    backButton.setTexture(backOffT);
                }
                else if (gameState == BACK_FOCUSED) { 
                    backButton.setTexture(backOnT);
                    pauseButton.setTexture(pauseOffT);
                    settingButton.setTexture(settingOffT);
                }

                window.draw(settingButton);
                window.draw(pauseButton);
                window.draw(backButton);
                window.display();
            }

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
