#include <SFML/Graphics.hpp>
#include <algorithm>
#include "View.h"
#include "Model.h"
#include "Globals.h"

#define scaleX 4.26875f
#define scaleY 4.267f


void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

int mainScreen(sf::RenderWindow& window) {

	window.setVerticalSyncEnabled(true);

	// Khởi tạo font tại đây
	sf::Font font;
	if (!font.loadFromFile("Assets/font/regular.ttf")) {
		std::cerr << "Không thể tải font!\n";
	}

	sf::Texture backgroundT;
	if (!backgroundT.loadFromFile("Assets/background/background_menu.png")) {
	}

	sf::Sprite bg(backgroundT);
	bg.setScale(scaleX, scaleY);

	sf::Texture titleT;
	if (!titleT.loadFromFile("Assets/background/title_menu.png")) {
	}

	sf::Sprite titleS(titleT);
	titleS.setScale(scaleX, scaleY);
	//Tính vị trí title Caro
	double titleWidth = titleT.getSize().x * 4.26875f;
	double titleX = (1366.f - titleWidth) / 2.f;
	titleS.setPosition(titleX, 1.f);

	//Nút được chọn
	sf::Texture modeButtonT;
	sf::Texture newButtonT;
	sf::Texture loadButtonT;
	sf::Texture quitButtonT;
	sf::Texture settingButtonT;

	modeButtonT.loadFromFile("Assets/button/mode_menu.png");
	newButtonT.loadFromFile("Assets/button/new_menu.png");
	loadButtonT.loadFromFile("Assets/button/load_menu.png");
	quitButtonT.loadFromFile("Assets/button/quit_menu.png");
	settingButtonT.loadFromFile("Assets/button/setting.png");

	sf::Sprite modeButton(modeButtonT);
	sf::Sprite newButton(newButtonT);
	sf::Sprite loadButton(loadButtonT);
	sf::Sprite quitButton(quitButtonT);
	sf::Sprite settingButton(settingButtonT);

	modeButton.setScale(scaleX, scaleY);
	newButton.setScale(scaleX, scaleY);
	loadButton.setScale(scaleX, scaleY);
	quitButton.setScale(scaleX, scaleY);
	settingButton.setScale(scaleX - 1, scaleY - 1);

	//Nút màu tối
	sf::Texture darkModeButtonT;
	sf::Texture darkNewButtonT;
	sf::Texture darkLoadButtonT;
	sf::Texture darkQuitButtonT;
	sf::Texture darkSettingButtonT;

	darkModeButtonT.loadFromFile("Assets/button/mode_dark.png");
	darkNewButtonT.loadFromFile("Assets/button/new_dark.png");
	darkLoadButtonT.loadFromFile("Assets/button/load_dark.png");
	darkQuitButtonT.loadFromFile("Assets/button/quit_dark.png");
	darkSettingButtonT.loadFromFile("Assets/button/setting_dark.png");

	sf::Sprite darkModeButton(darkModeButtonT);
	sf::Sprite darkNewButton(darkNewButtonT);
	sf::Sprite darkLoadButton(darkLoadButtonT);
	sf::Sprite darkQuitButton(darkQuitButtonT);
	sf::Sprite darkSettingButton(darkSettingButtonT);

	darkModeButton.setScale(scaleX, scaleY);
	darkNewButton.setScale(scaleX, scaleY);
	darkLoadButton.setScale(scaleX, scaleY);
	darkQuitButton.setScale(scaleX, scaleY);
	darkSettingButton.setScale(scaleX - 1, scaleY - 1);

	//Set vị trí các nút 
	//Nút được chọn
	double ButtonWidth = modeButtonT.getSize().x * 4.26875f;
	double buttonX = (1366.f - ButtonWidth) / 2.f;
	double buttonY = 5.f; //Khoảng cách từ title
	double buttonSpace = 70.f;
	float settingX = 1300.f;
	if (settingButtonT.getSize().x > 0) {
		settingX = 1370.f - settingButtonT.getSize().x * 3.26875f - 20.f; // 20px margin
	}
	else {
		// fallback to previous hardcoded value, but log that texture size was zero
		std::cerr << "Warning: settingButton texture size is zero; using fallback X=1250\n";
		settingX = 1300.f;
	}
	float settingY = 10.f;

	modeButton.setPosition(buttonX, buttonY);
	newButton.setPosition(buttonX, buttonY);
	loadButton.setPosition(buttonX, buttonY);
	quitButton.setPosition(buttonX, buttonY);
	settingButton.setPosition(settingX, settingY);

	// Nút màu tối
	darkModeButton.setPosition(buttonX, buttonY);
	darkNewButton.setPosition(buttonX, buttonY);
	darkLoadButton.setPosition(buttonX, buttonY);
	darkQuitButton.setPosition(buttonX, buttonY);
	darkSettingButton.setPosition(settingX, settingY);

	int choice = 0;
	const int totalOptions = 5;
	//Toggle menu
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0; //Thoát
			}

			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::W:
					choice = (choice - 1 + totalOptions) % totalOptions;
					break;

				case sf::Keyboard::S:
					choice = (choice + 1) % totalOptions;
					break;

				case sf::Keyboard::A:
					choice = (choice - 1 + totalOptions) % totalOptions;
					break;

				case sf::Keyboard::D:
					choice = (choice + 1) % totalOptions;
					break;

				case sf::Keyboard::Enter:
					if (choice == 4) { // Settings
						handleSettings(window, font);
						break;
					}
					return choice + 1;

					//ESC
				case sf::Keyboard::Escape:
					window.close();
					return 0;
				default:
					break;

				}
			}
		}
		window.clear();

		if (backgroundT.getSize().x > 0) {
			window.draw(bg);
		}

		if (titleT.getSize().x > 0) {
			window.draw(titleS);
		}

		switch (choice) {
		case 0:
		{
			window.draw(modeButton);
			window.draw(darkNewButton);
			window.draw(darkLoadButton);
			window.draw(darkQuitButton);
			window.draw(darkSettingButton);
			break;
		}
		case 1:
		{
			window.draw(darkModeButton);
			window.draw(newButton);
			window.draw(darkLoadButton);
			window.draw(darkQuitButton);
			window.draw(darkSettingButton);
			break;
		}
		case 2: {
			window.draw(darkModeButton);
			window.draw(darkNewButton);
			window.draw(loadButton);
			window.draw(darkQuitButton);
			window.draw(darkSettingButton);
			break;
		}
		case 3: {
			window.draw(darkModeButton);
			window.draw(darkNewButton);
			window.draw(darkLoadButton);
			window.draw(quitButton);
			window.draw(darkSettingButton);
			break;
		}
		case 4: { // Setting được chọn
			window.draw(darkModeButton);
			window.draw(darkNewButton);
			window.draw(darkLoadButton);
			window.draw(darkQuitButton);
			window.draw(settingButton); // sáng
			break;
		}
		}

		window.display();
	}
	return 0;
}
// Hàm xử lý màn hình Settings
void handleSettings(sf::RenderWindow& window, sf::Font& font) {
	enum VolumeLevel { MUTED, LOW, MEDIUM, MAX };

	// ==== NÚT EXIT (X) ====
	sf::Texture tabExitT, tabExitDarkT;
	if (!tabExitDarkT.loadFromFile("Assets/button/exit_dark.png")) std::cerr << "Failed load exit_dark\n";
	if (!tabExitT.loadFromFile("Assets/button/exit.png")) std::cerr << "Failed load exit\n";

	sf::Sprite tabExit(tabExitT), tabExitDark(tabExitDarkT);
	tabExitDark.setScale(scaleX, scaleY);
	tabExit.setScale(scaleX, scaleY);

	// CÁC LỰA CHỌN TAB
	const int totalChoices = 5;
	int tabChoice = 0;     // Lựa chọn hiện tại (0-4)
	int lastTabChoice = 0; // Tab cuối cùng được chọn (0-3), dùng để giữ đúng background

	// TẢI ẢNH NỀN CHO CÁC TAB
	vector<sf::Texture> tabBGs(4);
	if (!tabBGs[0].loadFromFile("Assets/background/setting_audio.png")) std::cerr << "Failed load setting_audio\n";
	if (!tabBGs[1].loadFromFile("Assets/background/setting_key.png")) std::cerr << "Failed load setting_key\n";
	if (!tabBGs[2].loadFromFile("Assets/background/setting_rule.png")) std::cerr << "Failed load setting_rule\n";
	if (!tabBGs[3].loadFromFile("Assets/background/setting_info.png")) std::cerr << "Failed load setting_info\n";

	sf::Sprite bg(tabBGs[0]);
	bg.setScale(scaleX, scaleY);
	bg.setPosition(0, 0);

	// CÀI ĐẶT ÂM THANH
	int soundLevel = MEDIUM;
	int affectLevel = MEDIUM;
	int soundChoice = 0; // 0 = sound, 1 = effect
	bool editing = false; // Enter toggles edit mode for the focused control

	// Tải texture cho các mức
	using TexMap = map<string, sf::Texture>;
	TexMap soundLevelT, affectLevelT;
	TexMap soundLevelDarkT, affectLevelDarkT;

	vector<string> levels = { "muted", "low", "medium", "max" };
	for (auto& l : levels) {
		if (!soundLevelT[l].loadFromFile("Assets/button/sound_" + l + ".png")) std::cerr << "Failed load sound_" + l + "\n";
		if (!affectLevelT[l].loadFromFile("Assets/button/affect_" + l + ".png")) std::cerr << "Failed load affect_" + l + "\n";
		if (!soundLevelDarkT[l].loadFromFile("Assets/button/sound_" + l + "_dark.png")) std::cerr << "Failed load sound_" + l + "_dark\n";
		if (!affectLevelDarkT[l].loadFromFile("Assets/button/affect_" + l + "_dark.png")) std::cerr << "Failed load affect_" + l + "_dark\n";
	}

	sf::Sprite soundBar, affectBar;
	// base scale used previously is large; adjust visual scale a bit for highlight when editing
	const float baseScaleX = scaleX;
	const float baseScaleY = scaleY;
	const float editZoom = 0.15f; // slight zoom when editing to indicate state

	soundBar.setScale(baseScaleX, baseScaleY);
	affectBar.setScale(baseScaleX, baseScaleY);
	soundBar.setPosition(3.f, 0.f);
	affectBar.setPosition(0.f, 0.f);

	sf::Texture affectChosenT, soundChosenT;
	if (!affectChosenT.loadFromFile("Assets/background/affect_chosen.png"))
		std::cerr << "Failed load Assets/background/affect_chosen.png\n";
	if (!soundChosenT.loadFromFile("Assets/background/sound_chosen.png"))
		std::cerr << "Failed load Assets/background/sound_chosen.png\n";


	sf::Sprite affectChosen(affectChosenT), soundChosen(soundChosenT);
	soundChosen.setScale(scaleX, scaleY);
	affectChosen.setScale(scaleX, scaleY);
	soundChosen.setPosition(0.f, 0.f);
	affectChosen.setPosition(0.f, 0.f);

	// 1. Text cho Tab Phím chơi
	sf::Text keybindsText;
	keybindsText.setFont(font);
	keybindsText.setString(L"Di chuyển / Thay đổi\n\n\n\n\n\nChọn / Xác nhận");
	keybindsText.setCharacterSize(30);
	keybindsText.setFillColor(sf::Color(80, 48, 32));
	keybindsText.setPosition(580.f, 330.f);

	// 2. Text cho Tab Luật chơi
	sf::Text rulesText;
	rulesText.setFont(font);
	std::wstring rulesString =
		L"					LUẬT CHƠI:\n\n"
		L"1. Mỗi người đi một nước, X đi trước, O đi sau.\n\n"
		L"2. Bên nào có 5 quân liên tiếp trên một hàng, cột, hoặc\n"
		L"   đường chéo là THẮNG.\n\n"
		L"3. Khi có người thắng -> ván cờ kết thúc, hiển thị kết quả.\n\n"
		L"4. Nếu bàn cờ đầy mà không ai có 5 liên tiếp -> HOÀ\n";
	rulesText.setString(rulesString);
	rulesText.setCharacterSize(30);
	rulesText.setFillColor(sf::Color(80, 48, 32));
	rulesText.setPosition(235.f, 250.f);

	// 3. Text cho Tab Thông tin
	sf::Text infoText;
	infoText.setFont(font);
	std::wstring infoString =
		L"Trường Đại học Khoa học Tự nhiên - ĐHQGHCM\n"
		L"		ĐỒ ÁN GAME CARO - 25C10\n\n"
		L"		  Giảng viên hướng dẫn: \n"
		L"	   < ThS.Trương Toàn Thịnh >\n\n"
		L"	    Game được thực hiện bởi:\n"
		L"     24127132 - Nguyễn Thị Ngọc Trâm\n"
		L"     24127158 - Nguyễn Trần Lan Duy\n"
		L"     24127164 - Lê Kim Hằng\n"
		L"     24127262 - Đỗ Thành Vinh\n"
		L"     24127465 - Tạ Mai Như Ngọc\n\n";
	infoText.setString(infoString);
	infoText.setCharacterSize(30);
	infoText.setFillColor(sf::Color(80, 48, 32));
	infoText.setPosition(350.f, 235.f);

	// === Main loop ===
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) return;

			if (event.type == sf::Event::KeyPressed) {
				// Only A S W D and Enter are used
				auto key = event.key.code;

				// ESC (optional) keeps previous behavior: exit settings
				if (key == sf::Keyboard::Escape) return;

				// ENTER: if Exit is selected exit; otherwise toggle edit mode in audio tab
				if (key == sf::Keyboard::Enter) {
					if (tabChoice == 4) return; // Exit button selected
					if (tabChoice == 0) {
						editing = !editing; // toggle editing mode for focused control
					}
					// If not audio tab, Enter does nothing (tabs are navigated with A/D)
				}
				// W/S: inside audio tab, change focus between sound and effect (only when not editing)
				else if (key == sf::Keyboard::W) {
					if (tabChoice == 0 && !editing) {
						soundChoice = (soundChoice - 1 + 2) % 2;
					}
				}
				else if (key == sf::Keyboard::S) {
					if (tabChoice == 0 && !editing) {
						soundChoice = (soundChoice + 1) % 2;
					}
				}
				// A/D: behave as:
				// - if in audio tab and editing == true -> change value of focused control
				else if (key == sf::Keyboard::A) {
					if (tabChoice == 0 && editing) {
						// decrease focused value
						if (soundChoice == 0)
							soundLevel = std::max(static_cast<int>(MUTED), soundLevel - 1);
						else
							affectLevel = std::max(static_cast<int>(MUTED), affectLevel - 1);
					}
					else {
						// move to previous tab
						tabChoice = (tabChoice - 1 + totalChoices) % totalChoices;
						// leaving edit mode when switching tabs
						editing = false;
					}
				}
				else if (key == sf::Keyboard::D) {
					if (tabChoice == 0 && editing) {
						// increase focused value
						if (soundChoice == 0)
							soundLevel = std::min(static_cast<int>(MAX), soundLevel + 1);
						else
							affectLevel = std::min(static_cast<int>(MAX), affectLevel + 1);
					}
					else {
						// move to next tab
						tabChoice = (tabChoice + 1) % totalChoices;
						editing = false;
					}
				}

				// Update lastTabChoice to keep the right background shown
				if (tabChoice < 4) lastTabChoice = tabChoice;
			}
		}

		// Draw
		bg.setTexture(tabBGs[lastTabChoice]);
		window.clear();
		window.draw(bg);

		// Exit button (bright when selected)
		if (tabChoice == 4) window.draw(tabExit);
		else window.draw(tabExitDark);

		// Audio tab content drawing
		if (lastTabChoice == 0) {
			string currentSoundLvl = levels[soundLevel];
			string currentAffectLvl = levels[affectLevel];

			// Select textures for bright/dark states
			if (tabChoice == 0) {
				// audio tab is active
				if (soundChoice == 0) { // sound focus
					soundBar.setTexture(soundLevelT[currentSoundLvl]);
					affectBar.setTexture(affectLevelDarkT[currentAffectLvl]);
					window.draw(soundChosen);
				}
				else { // effect focus
					soundBar.setTexture(soundLevelDarkT[currentSoundLvl]);
					affectBar.setTexture(affectLevelT[currentAffectLvl]);
					window.draw(affectChosen);
				}
			}
			else {
				// audio tab not active -> both dark
				soundBar.setTexture(soundLevelDarkT[currentSoundLvl]);
				affectBar.setTexture(affectLevelDarkT[currentAffectLvl]);
			}

			// Visual cue for editing: slightly scale up focused control while editing
			if (tabChoice == 0 && editing && soundChoice == 0) {
				soundBar.setScale(baseScaleX + editZoom, baseScaleY + editZoom);
				affectBar.setScale(baseScaleX, baseScaleY);
				soundBar.setPosition(-8.f, -15.f);
			}
			else if (tabChoice == 0 && editing && soundChoice == 1) {
				soundBar.setScale(baseScaleX, baseScaleY);
				affectBar.setScale(baseScaleX + editZoom, baseScaleY + editZoom);
				affectBar.setPosition(-10.f, -10.f);
			}
			else {
				soundBar.setScale(baseScaleX, baseScaleY);
				soundBar.setPosition(3.f, 0.f);
				affectBar.setScale(baseScaleX, baseScaleY);
				affectBar.setPosition(0.f, 0.f);
			}
			window.draw(soundBar);
			window.draw(affectBar);
		}
		else if (lastTabChoice == 1) {
			// Tab Phím chơi
			window.draw(keybindsText);
		}
		else if (lastTabChoice == 2) {
			// Tab Luật chơi
			window.draw(rulesText);
		}
		else if (lastTabChoice == 3) {
			// Tab Thông tin
			window.draw(infoText);
		}

		window.display();
	}
}


int modeChoosing(sf::RenderWindow& window) {
	// Khởi tạo font
	sf::Font font;
	if (!font.loadFromFile("Assets/font/regular.ttf")) {
		std::cerr << "Không thể tải font!\n";
	}

	//Tải background
	sf::Texture backgroundT;
	if (!backgroundT.loadFromFile("Assets/background/background_menu.png")) {
	}

	sf::Sprite bg(backgroundT);
	bg.setScale(scaleX, scaleY);

	//Tải ảnh từ folder
	sf::Texture card1Front, card1Back, card1BG, card2Front, card2Back, card2BG, card3Front, card3Back, card3BG, okButton, okButtonDark;
	card1Front.loadFromFile("Assets/playing/card1.png");
	card1Back.loadFromFile("Assets/playing/card1_back.png");
	card1BG.loadFromFile("Assets/playing/card1_unchosen.png");
	card2Front.loadFromFile("Assets/playing/card2.png");
	card2Back.loadFromFile("Assets/playing/card2_back.png");
	card2BG.loadFromFile("Assets/playing/card2_unchosen.png");
	card3Front.loadFromFile("Assets/playing/card3.png");
	card3Back.loadFromFile("Assets/playing/card3_back.png");
	card3BG.loadFromFile("Assets/playing/card3_unchosen.png");
	okButton.loadFromFile("Assets/button/ok_button.png");
	okButtonDark.loadFromFile("Assets/button/ok_buttonDark.png");

	double baseScale = 3.1999f;
	double selectedScale = 3.1999f;

	sf::Sprite card1F(card1Front);
	sf::Sprite card1B(card1Back);
	sf::Sprite card1U(card1BG);
	sf::Sprite card2F(card2Front);
	sf::Sprite card2B(card2Back);
	sf::Sprite card2U(card2BG);
	sf::Sprite card3F(card3Front);
	sf::Sprite card3B(card3Back);
	sf::Sprite card3U(card3BG);
	sf::Sprite okButtonS(okButton);
	sf::Sprite okButton_Dark(okButtonDark);

	float card1CenterX = 270.0f;
	float card1CenterY = 350.0f;
	float card2CenterX = 660.0f;
	float card2CenterY = 350.0f;
	float card3CenterX = 1100.0f;
	float card3CenterY = 350.0f;

	//Set origin và position
	//Card 1
	card1F.setOrigin(card1Front.getSize().x / 2.0f, card1Front.getSize().y / 2.0f);
	card1B.setOrigin(card1Back.getSize().x / 2.0f, card1Back.getSize().y / 2.0f);
	card1U.setOrigin(card1BG.getSize().x / 2.0f, card1BG.getSize().y / 2.0f);
	card1F.setPosition(card1CenterX, card1CenterY);
	card1B.setPosition(card1CenterX, card1CenterY);
	card1U.setPosition(card1CenterX, card1CenterY);

	//Card 2
	card2F.setOrigin(card2Front.getSize().x / 2.0f, card2Front.getSize().y / 2.0f);
	card2B.setOrigin(card2Back.getSize().x / 2.0f, card2Back.getSize().y / 2.0f);
	card2U.setOrigin(card2BG.getSize().x / 2.0f, card2BG.getSize().y / 2.0f);
	card2F.setPosition(card2CenterX, card2CenterY);
	card2B.setPosition(card2CenterX, card2CenterY);
	card2U.setPosition(card2CenterX, card2CenterY);

	//Card 3
	card3F.setOrigin(card3Front.getSize().x / 2.0f, card3Front.getSize().y / 2.0f);
	card3B.setOrigin(card3Back.getSize().x / 2.0f, card3Back.getSize().y / 2.0f);
	card3U.setOrigin(card3BG.getSize().x / 2.0f, card3BG.getSize().y / 2.0f);
	card3F.setPosition(card3CenterX, card3CenterY);
	card3B.setPosition(card3CenterX, card3CenterY);
	card3U.setPosition(card3CenterX, card3CenterY);

	// OK Button
	float okButtonScale = 3.68f;
	okButtonS.setScale(okButtonScale, okButtonScale);
	okButton_Dark.setScale(okButtonScale, okButtonScale);

	// Tính toán vị trí giữa màn hình
	float okButtonX = 790.0f;
	float okButtonY = 580.0f;

	int cardChoice = 1;
	int row = 0; // 0 = cards, 1 = OK button
	bool isCard1Flipped = true;
	bool isCard2Flipped = true;
	bool isCard3Flipped = true;
	bool isFlipping = false;
	int flippingCard = 0;
	double flipProcess = 0.0f;
	const double flipSpeed = 4.0f;

	// Text cho Luật chơi
	// Card 1: Tự do
	sf::Text freestylesText;
	freestylesText.setFont(font);
	std::wstring freestyleString =
		L"	  LUẬT TỰ DO\n\n"
		L" Bên nào tạo được hàng\n"
		L" liên tiếp 5 quân trở \n"
		L" lên thì sẽ giành được\n"
		L" chiến thắng.\n";
	freestylesText.setString(freestyleString);
	freestylesText.setCharacterSize(27);
	freestylesText.setFillColor(sf::Color(80, 48, 32));
	freestylesText.setPosition(120.f, 330.f);

	// Card 2: Tiêu chuẩn
	sf::Text standardText;
	standardText.setFont(font);
	std::wstring standardString =
		L"   LUẬT TIÊU CHUẨN\n\n"
		L"Bên nào tạo được hàng\n"
		L"liên tiếp 5 quân sẽ \n"
		L"thắng. Nếu nhiều hơn 5\n"
		L"thì KHÔNG tính thắng,\n"
		L"ván cờ sẽ tiếp tục.\n";
	standardText.setString(standardString);
	standardText.setCharacterSize(27);
	standardText.setFillColor(sf::Color(80, 48, 32));
	standardText.setPosition(527.f, 330.f);

	// Card 3: Chặn 2 đầu
	sf::Text block2endsText;
	block2endsText.setFont(font);
	std::wstring blockString =
		L"	LUẬT CHẶN 2 ĐẦU\n\n"
		L"Bên nào tạo được hàng\n"
		L"liên tiếp nhiều hơn 5\n"
		L"hoặc không bị chặn 2\n"
		L"đầu thì sẽ thắng.\n"
		L"Tức là:  XOOOOOX\n"
		L"-> Không tính thắng.\n";
	block2endsText.setString(blockString);
	block2endsText.setCharacterSize(27);
	block2endsText.setFillColor(sf::Color(80, 48, 32));
	block2endsText.setPosition(963.f, 330.f);

	sf::Clock clock;

	while (window.isOpen()) {
		float time = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return -1;
			}

			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::A:
					if (row == 0) {
						cardChoice--;
						if (cardChoice < 1) cardChoice = 3;
					}
					break;

				case sf::Keyboard::D:
					if (row == 0) {
						cardChoice++;
						if (cardChoice > 3) cardChoice = 1;
					}
					break;

				case sf::Keyboard::W:
					if (row == 1) {
						row = 0;
					}
					break;

				case sf::Keyboard::S:
					if (row == 0) {
						row = 1;
					}
					break;

				case sf::Keyboard::Enter:
					if (row == 0) {
						if (!isFlipping) {
							isFlipping = true;
							flipProcess = 0.0f;
							flippingCard = cardChoice;
						}
					}
					else {
						return cardChoice + 1;
					}
					break;

				case sf::Keyboard::Escape:
					return -1;
				default:
					break;
				}
			}
		}
		if (isFlipping) {
			flipProcess += flipSpeed * time;

			if (flipProcess >= 1.0f) {
				flipProcess = 1.0f;
				isFlipping = false;
				if (flippingCard == 1) {
					isCard1Flipped = !isCard1Flipped;
				}
				else if (flippingCard == 2) {
					isCard2Flipped = !isCard2Flipped;
				}
				else if (flippingCard == 3) {
					isCard3Flipped = !isCard3Flipped;
				}
				flippingCard = 0;
			}
		}

		window.clear();

		if (backgroundT.getSize().x > 0) {
			window.draw(bg);
		}

		// Draw Card 1
		if (cardChoice == 1) {
			double card1ScaleX = baseScale;
			double card1ScaleY = baseScale;
			bool showFront1 = isCard1Flipped;

			if (isFlipping && flippingCard == 1) {
				double angle = flipProcess * 3.14159;
				card1ScaleX = baseScale * std::abs(std::cos(angle));
				double zoomFactor = 1.0 + 0.3 * std::sin(flipProcess * 3.14159);
				card1ScaleY = baseScale * zoomFactor;

				if (flipProcess < 0.5f) {
					showFront1 = isCard1Flipped;
				}
				else {
					showFront1 = !isCard1Flipped;
				}
			}

			if (showFront1) {
				card1F.setScale(card1ScaleX, card1ScaleY);
				window.draw(card1F);
			}
			else {
				card1B.setScale(card1ScaleX, card1ScaleY);
				window.draw(card1B);
				window.draw(freestylesText);
			}
		}
		else {
			card1U.setScale(baseScale, baseScale);
			window.draw(card1U);
		}

		// Draw Card 2
		if (cardChoice == 2) {
			double card2ScaleX = selectedScale;
			double card2ScaleY = selectedScale;
			bool showFront2 = isCard2Flipped;

			if (isFlipping && flippingCard == 2) {
				double angle = flipProcess * 3.14159;
				card2ScaleX = selectedScale * std::abs(std::cos(angle));
				double zoomFactor = 1.0 + 0.3 * std::sin(flipProcess * 3.14159);
				card2ScaleY = selectedScale * zoomFactor;

				if (flipProcess < 0.5f) {
					showFront2 = isCard2Flipped;
				}
				else {
					showFront2 = !isCard2Flipped;
				}
			}

			if (showFront2) {
				card2F.setScale(card2ScaleX, card2ScaleY);
				window.draw(card2F);
			}
			else {
				card2B.setScale(card2ScaleX, card2ScaleY);
				window.draw(card2B);
				window.draw(standardText);
			}
		}
		else {
			card2U.setScale(baseScale, baseScale);
			window.draw(card2U);
		}

		// Draw Card 3
		if (cardChoice == 3) {
			double card3ScaleX = selectedScale;
			double card3ScaleY = selectedScale;
			bool showFront3 = isCard3Flipped;

			if (isFlipping && flippingCard == 3) {
				double angle = flipProcess * 3.14159;
				card3ScaleX = selectedScale * std::abs(std::cos(angle));
				double zoomFactor = 1.0 + 0.3 * std::sin(flipProcess * 3.14159);
				card3ScaleY = selectedScale * zoomFactor;

				if (flipProcess < 0.5f) {
					showFront3 = isCard3Flipped;
				}
				else {
					showFront3 = !isCard3Flipped;
				}
			}

			if (showFront3) {
				card3F.setScale(card3ScaleX, card3ScaleY);
				window.draw(card3F);
			}
			else {
				card3B.setScale(card3ScaleX, card3ScaleY);
				window.draw(card3B);
				window.draw(block2endsText);
			}
		}
		else {
			card3U.setScale(baseScale, baseScale);
			window.draw(card3U);
		}

		// Draw OK button
		if (row == 1) {
			window.draw(okButtonS);
		}
		else {
			window.draw(okButton_Dark);
		}
		window.display();
	}

	return -1;
}

int loadGameScreen(sf::RenderWindow& window)
{
	// ============ LOAD TEXTURES ============
	sf::Texture bgT, tableT, titleT;
	bgT.loadFromFile("Assets/background/background_menu.png");
	tableT.loadFromFile("Assets/background/load_table.png");
	titleT.loadFromFile("Assets/background/load_title.png");

	sf::Sprite bg(bgT), table(tableT), title(titleT);
	bg.setScale(scaleX, scaleY);
	table.setScale(scaleX, scaleY);
	title.setScale(scaleX, scaleY);

	// ===== BLANKS =====
	const int slotCount = 5;
	sf::Texture blankT[slotCount];
	sf::Sprite blankS[slotCount];
	for (int i = 0; i < slotCount; ++i) {
		std::string path = "Assets/background/blank" + std::to_string(i + 1) + ".png";
		blankT[i].loadFromFile(path);
		blankS[i].setTexture(blankT[i]);
		blankS[i].setScale(scaleX, scaleY);
	}

	// ===== BUTTONS =====
	sf::Texture tOnLoad, tOffLoad, tOnDelete, tOffDelete, tOnRename, tOffRename;
	sf::Texture tOnExit, tOffExit;
	tOnLoad.loadFromFile("Assets/button/on_load_button.png");
	tOffLoad.loadFromFile("Assets/button/off_load_button.png");
	tOnDelete.loadFromFile("Assets/button/on_delete_button.png");
	tOffDelete.loadFromFile("Assets/button/off_delete_button.png");
	tOnRename.loadFromFile("Assets/button/on_rename_button.png");
	tOffRename.loadFromFile("Assets/button/off_rename_button.png");
	tOnExit.loadFromFile("Assets/button/on_exit_load_button.png");
	tOffExit.loadFromFile("Assets/button/off_exit_load_button.png");

	sf::Sprite btnLoad(tOffLoad), btnDelete(tOffDelete), btnRename(tOffRename), btnExit(tOffExit);
	btnLoad.setScale(scaleX, scaleY);
	btnDelete.setScale(scaleX, scaleY);
	btnRename.setScale(scaleX, scaleY);
	btnExit.setScale(scaleX, scaleY);

	// ===== STATE =====
	int selectedSlot = 0;   // 0..4 = blank1..5, 5=Load,6=Rename,7=Delete,8=Exit
	bool inButton = false;
	int lastSlot = 0;       // nhớ slot trước khi chuyển qua nút

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); return 0; }

			if (event.type == sf::Event::KeyPressed) {
				auto key = event.key.code;

				// ESC thoát
				if (key == sf::Keyboard::Escape) return 0;

				// ======== VÙNG SLOT ========
				if (!inButton) {
					if (key == sf::Keyboard::Down || key == sf::Keyboard::S) {
						if (selectedSlot < slotCount - 1)
							selectedSlot++;
					}
					else if (key == sf::Keyboard::Up || key == sf::Keyboard::W) {
						if (selectedSlot > 0)
							selectedSlot--;
						else
							selectedSlot = 8, inButton = true; // từ blank1 lên exit
					}
					else if (key == sf::Keyboard::Right || key == sf::Keyboard::D) {
						inButton = true;
						lastSlot = selectedSlot;
						selectedSlot = 5; // sang nút Load
					}
				}
				// ======== VÙNG BUTTON ========
				else {
					if (key == sf::Keyboard::Down || key == sf::Keyboard::S) {
						if (selectedSlot == 8) { // Exit xuống lại blank1
							inButton = false;
							selectedSlot = 0;
						}
						else if (selectedSlot < 8) selectedSlot++;
					}
					else if (key == sf::Keyboard::Up || key == sf::Keyboard::W) {
						if (selectedSlot == 5) { // Load lên Exit
							selectedSlot = 8;
						}
						else if (selectedSlot > 5) selectedSlot--;
					}
					else if (key == sf::Keyboard::Left || key == sf::Keyboard::A) {
						inButton = false;
						selectedSlot = lastSlot; // quay về slot cũ
					}
				}

				// ======== ENTER CHỌN ========
				if (key == sf::Keyboard::Enter) {
					if (!inButton) return selectedSlot + 1; // chọn slot
					else {
						switch (selectedSlot) {
						case 5: return selectedSlot + 1;      // Load
						case 6: std::cout << "Rename slot selected\n"; break;
						case 7: std::cout << "Delete slot selected\n"; break;
						case 8: return 0;                     // Exit
						}
					}
				}
			}
		}

		// ===== DRAW =====
		window.clear();
		window.draw(bg);
		window.draw(table);
		window.draw(title);

		// highlight slot
		for (int i = 0; i < slotCount; ++i) {
			blankS[i].setColor(!inButton && selectedSlot == i
				? sf::Color::White
				: sf::Color(180, 180, 180, 255));
			window.draw(blankS[i]);
		}

		// highlight buttons
		btnLoad.setTexture(selectedSlot == 5 ? tOnLoad : tOffLoad);
		btnRename.setTexture(selectedSlot == 6 ? tOnRename : tOffRename);
		btnDelete.setTexture(selectedSlot == 7 ? tOnDelete : tOffDelete);
		btnExit.setTexture(selectedSlot == 8 ? tOnExit : tOffExit);

		window.draw(btnLoad);
		window.draw(btnRename);
		window.draw(btnDelete);
		window.draw(btnExit);

		window.display();
	}

	return 0;
}


void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawBoard(sf::RenderWindow& window, int n, int result) {
	sf::Texture boardT, xTexture, oTexture, bgTexture, barT;
	sf::Sprite boardS, xSprite, oSprite, bgSprite, barS;

	boardT.loadFromFile("Assets/playing/board.png");
	xTexture.loadFromFile("Assets/playing/X_letter.png");
	oTexture.loadFromFile("Assets/playing/O_letter.png");
	barT.loadFromFile("Assets/background/text_board.png");

	string bgPath = "Assets/background/board_background" + to_string(_backgroundForBoard) + ".png";
	bgTexture.loadFromFile(bgPath);

	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(3.8f, 3.5f);

	boardS.setTexture(boardT);
	xSprite.setTexture(xTexture);
	oSprite.setTexture(oTexture);
	barS.setTexture(barT);

	//size bàn cờ
	float boardScale = 3.5f;
	boardS.setScale(boardScale, boardScale);


	float boardX = 15.0f;
	float boardY = 5.0f;
	boardS.setPosition(boardX, boardY);

	//Thanh thông báo
	float barScale = 3.5f;
	barS.setScale(barScale, barScale);
	float barX = 35.0f;
	float barY = 10.0f;
	barS.setPosition(barX, barY);

	float originalCellSize = 12.04f;
	float cellSize = originalCellSize * boardScale;

	//Vị trí bắt đầu
	float offsetX = 413.0f;
	float offsetY = 197.0f;

	float xoScale = 0.85f;
	float xScale = (cellSize * xoScale) / xTexture.getSize().x;
	float oScale = (cellSize * xoScale) / oTexture.getSize().x;

	xSprite.setScale(xScale, xScale);
	oSprite.setScale(oScale, oScale);

	window.draw(bgSprite);
	window.draw(boardS);

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c != 0) {

				float pieceX = boardX + offsetX + (j * cellSize) + (cellSize / 2.0f);
				float pieceY = boardY + offsetY + (i * cellSize) + (cellSize / 2.0f);

				if (_A[i][j].c == -1) {
					xSprite.setPosition(pieceX - (xTexture.getSize().x * xScale / 2.0f),
						pieceY - (xTexture.getSize().y * xScale / 2.0f));
					window.draw(xSprite);
				}
				else if (_A[i][j].c == 1) {
					oSprite.setPosition(pieceX - (oTexture.getSize().x * oScale / 2.0f),
						pieceY - (oTexture.getSize().y * oScale / 2.0f));
					window.draw(oSprite);
				}
			}
		}
	}

	// Set up cursor
	sf::RectangleShape cursor(sf::Vector2f(cellSize - 4, cellSize - 4));
	cursor.setFillColor(sf::Color::Transparent);
	cursor.setOutlineColor(sf::Color(138, 72, 54));
	cursor.setOutlineThickness(3.0f);

	float cursorX = boardX + offsetX + (_currentCol * cellSize) + 2;
	float cursorY = boardY + offsetY + (_currentRow * cellSize) + 2;
	cursor.setPosition(cursorX, cursorY);
	window.draw(cursor);

	// Thông tin game
	window.draw(barS);
	sf::Font font;
	if (font.loadFromFile("Assets/font/regular.ttf")) {
		sf::Text gameInfo;
		gameInfo.setFont(font);
		gameInfo.setCharacterSize(26);
		gameInfo.setStyle(sf::Text::Bold);

		std::string message;

		if (result == -1) {
			message = "NGUOI CHOI X THANG!";
			gameInfo.setFillColor(sf::Color(54, 39, 32));
			gameInfo.setPosition(550.0f, 34.0f);
		}
		else if (result == 1) {
			message = "NGUOI CHOI O THANG!";
			gameInfo.setFillColor(sf::Color(54, 39, 32));
			gameInfo.setPosition(550.0f, 34.0f);
		}
		else if (result == 0) {
			message = "HOA!";
			gameInfo.setFillColor(sf::Color(54, 39, 32));
			gameInfo.setPosition(650.0f, 34.0f);
		}
		else {
			std::string playerText = _TURN ? "X" : "O";
			message = "Luot choi: " + playerText;
			gameInfo.setFillColor(sf::Color(54, 39, 32));
			gameInfo.setPosition(590.0f, 34.0f);
		}

		gameInfo.setString(message);
		window.draw(gameInfo);
	}
}


int ProcessFinish(int pWhoWin) {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
	switch (pWhoWin) {
	case -1:
		printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", true, false);
		break;
	case 1:
		printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", false, true);
		break;
	case 0:
		printf("Nguoi choi %d da hoa nguoi choi %d\n", false, true);
		break;
	case 2:
		_TURN = !_TURN;
	}
	GotoXY(_X, _Y);
	return pWhoWin;

}

int AskContinue() {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
	printf("Nhan 'y/n' de tiep tuc/dung: ");
	return toupper(_getch());

}

// Hàm xử lý Menu Tạm dừng
int handlePauseMenu(sf::RenderWindow& window, sf::Font& font) {
	// 1. LƯU View hiện tại của game (để khôi phục sau)
	sf::View gameView = window.getView();

	// 2. ĐẶT View MẶC ĐỊNH (defaultView) cho UI
	sf::View defaultView = window.getDefaultView();
	window.setView(defaultView);

	// Lấy kích thước cửa sổ (kích thước View mặc định)
	sf::Vector2u winSize = window.getSize();

	// 3. TẠO LỚP LÀM MỜ ĐỒNG NHẤT (UNIVERSAL DIMMING LAYER)
	// Lớp này vừa khít với cửa sổ và làm mờ/tối cảnh game bên dưới
	sf::RectangleShape dimmingOverlay(sf::Vector2f(static_cast<float>(winSize.x), static_cast<float>(winSize.y)));

	// Đặt màu đen và độ trong suốt (Alpha = 150/255)
	dimmingOverlay.setFillColor(sf::Color(50, 50, 50, 40));


	// 4. Tải Background chính (dùng để tính toán scale và dự phòng)
	sf::Texture backgroundT;
	if (!backgroundT.loadFromFile("Assets/background/pause_menu.png")) {
		// Xử lý lỗi tải file
	}

	// Tính toán scale để Sprite phủ kín toàn bộ cửa sổ
	float scaleX_FullScreen = static_cast<float>(winSize.x) / backgroundT.getSize().x;
	float scaleY_FullScreen = static_cast<float>(winSize.y) / backgroundT.getSize().y;

	// 5. Tải các background phụ cho từng lựa chọn
	sf::Texture tCont, tReset, tSave, tMain;
	if (!tCont.loadFromFile("Assets/background/pause_continue.png")) tCont = backgroundT;
	if (!tReset.loadFromFile("Assets/background/pause_reset.png")) tReset = backgroundT;
	if (!tSave.loadFromFile("Assets/background/pause_save.png")) tSave = backgroundT;
	if (!tMain.loadFromFile("Assets/background/pause_exit.png")) tMain = backgroundT;

	std::vector<sf::Texture> chosenBGTs = { tCont, tReset, tSave, tMain };
	sf::Sprite fullScreenMenu(chosenBGTs[0]);

	// Áp dụng scale toàn màn hình
	fullScreenMenu.setScale(scaleX_FullScreen, scaleY_FullScreen);

	// Đặt vị trí bắt đầu từ góc trên bên trái
	fullScreenMenu.setOrigin(0.f, 0.f);
	fullScreenMenu.setPosition(0.f, 0.f);

	// ĐIỀU CHỈNH QUAN TRỌNG: BUỘC MENU CÓ ĐỘ TRONG SUỐT
	// Điều này đảm bảo menu Pixel Art của bạn mờ đi một chút, cho phép thấy cảnh game.
	fullScreenMenu.setColor(sf::Color(255, 255, 255, 255));


	// 6. Vòng lặp điều khiển
	int selectedItem = 0;
	const int optionCount = chosenBGTs.size();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
					selectedItem = (selectedItem + optionCount - 1) % optionCount;
				}
				else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
					selectedItem = (selectedItem + 1) % optionCount;
				}
				else if (event.key.code == sf::Keyboard::Enter) {
					// PHỤC HỒI View của game trước khi thoát
					window.setView(gameView);
					return selectedItem + 1;
				}
				else if (event.key.code == sf::Keyboard::Escape) {
					// PHỤC HỒI View của game trước khi thoát
					window.setView(gameView);
					return 1; // ESC để tiếp tục
				}
			}
		}

		// DRAW: 

		// 1. Vẽ Lớp Làm Mờ (Dimming Layer) lên trên cảnh game (làm tối)
		window.draw(dimmingOverlay);

		// 2. Vẽ Menu Toàn Màn hình (Pixel Art) lên trên lớp làm mờ (buộc thấy xuyên qua)
		fullScreenMenu.setTexture(chosenBGTs[selectedItem]);
		window.draw(fullScreenMenu);

		window.display();
	}

	// Thoát bất thường -> Phục hồi View
	window.setView(gameView);
	return 0;
}