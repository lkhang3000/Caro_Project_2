#pragma execution_character_set("utf-8")
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "View.h"
#include "Model.h"
#include "Globals.h"

#define scaleX 4.26875f
#define scaleY 4.267f
static sf::Texture sharedBgTexture;
static sf::Sprite sharedBgSprite;


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
				case sf::Keyboard::Up:
					PlayMoveSFX();
					choice = (choice - 1 + totalOptions) % totalOptions;
					break;

				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					PlayMoveSFX();
					choice = (choice + 1) % totalOptions;
					break;

				case sf::Keyboard::A:
				case sf::Keyboard::Left:
					PlayMoveSFX();
					choice = (choice - 1 + totalOptions) % totalOptions;
					break;

				case sf::Keyboard::D:
				case sf::Keyboard::Right:
					PlayMoveSFX();
					choice = (choice + 1) % totalOptions;
					break;

				case sf::Keyboard::Enter:
					PlayClickSFX();
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

void handleSettings(sf::RenderWindow& window, sf::Font& font) {
	enum VolumeLevel { MUTED, LOW, MEDIUM, MAX };

	auto MapSoundLevel = [&](int level) -> SoundQuality
		{
			switch (level)
			{
			case MUTED:  return SOUND_MUTED;
			case LOW:    return SOUND_LOW;
			case MEDIUM: return SOUND_MEDIUM;
			case MAX:    return SOUND_HIGH;
			default:     return SOUND_HIGH;
			}
		};

	auto MapQualityToLevel = [&](SoundQuality q) -> int
		{
			switch (q)
			{
			case SOUND_MUTED:  return MUTED;
			case SOUND_LOW:    return LOW;
			case SOUND_MEDIUM: return MEDIUM;
			case SOUND_HIGH:   return MAX;
			default:           return MEDIUM;
			}
		};

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
	int soundLevel = MapQualityToLevel(_bgmQuality);
	int affectLevel = MapQualityToLevel(_sfxQuality);
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
		L"	    < TS.Trương Toàn Thịnh >\n\n"
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
			if (event.type == sf::Event::Closed) {
				PlayClickSFX();
				_bgm.setVolume(_bgmNormalVolume * GetBgmScale());
				return;
			}
			if (event.type == sf::Event::KeyPressed) {
				// Only A S W D and Enter are used
				auto key = event.key.code;

				// ESC (optional) keeps previous behavior: exit settings
				if (key == sf::Keyboard::Escape) {
					PlayClickSFX();
					_bgm.setVolume(_bgmNormalVolume * GetBgmScale());
					return;
				}

				// ENTER: if Exit is selected exit; otherwise toggle edit mode in audio tab
				if (key == sf::Keyboard::Enter) {
					PlayClickSFX();
					if (tabChoice == 4) {
						_bgm.setVolume(_bgmNormalVolume * GetBgmScale());
						return;// Exit button selected
					}
					if (tabChoice == 0) {
						editing = !editing; // toggle editing mode for focused control
					}
					// If not audio tab, Enter does nothing (tabs are navigated with A/D)
				}
				// W/S: inside audio tab, change focus between sound and effect (only when not editing)
				else if (key == sf::Keyboard::W) {
					PlayMoveSFX();
					if (tabChoice == 0 && !editing) {
						soundChoice = (soundChoice - 1 + 2) % 2;
					}
				}
				else if (key == sf::Keyboard::S) {
					PlayMoveSFX();
					if (tabChoice == 0 && !editing) {
						soundChoice = (soundChoice + 1) % 2;
					}
				}
				// A/D: behave as:
				// - if in audio tab and editing == true -> change value of focused control
				else if (key == sf::Keyboard::A) {
					PlayMoveSFX();
					if (tabChoice == 0 && editing) {
						// decrease focused value
						if (soundChoice == 0) {
							soundLevel = std::max(static_cast<int>(MUTED), soundLevel - 1);
							_bgmQuality = MapSoundLevel(soundLevel);
							_bgm.setVolume(_bgmNormalVolume * GetBgmScale());
							_bgm.setVolume(_bgmNormalVolume * GetBgmScale());
						}
						else {
							affectLevel = std::max(static_cast<int>(MUTED), affectLevel - 1);
							_sfxQuality = MapSoundLevel(affectLevel);
						}
					}
					else {
						// move to previous tab
						tabChoice = (tabChoice - 1 + totalChoices) % totalChoices;
						// leaving edit mode when switching tabs
						editing = false;
					}
				}
				else if (key == sf::Keyboard::D) {
					PlayMoveSFX();
					if (tabChoice == 0 && editing) {
						// increase focused value
						if (soundChoice == 0) {
							soundLevel = std::min(static_cast<int>(MAX), soundLevel + 1);
							_bgmQuality = MapSoundLevel(soundLevel);
							_bgm.setVolume(_bgmNormalVolume * GetBgmScale());
							_bgm.setVolume(_bgmNormalVolume * GetBgmScale());
						}
						else {
							affectLevel = std::min(static_cast<int>(MAX), affectLevel + 1);
							_sfxQuality = MapSoundLevel(affectLevel);
						}
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
	sf::Texture card1Front, card1Back, card1BG, card2Front, card2Back, card2BG, card3Front, card3Back, card3BG,
		okButton, okButtonDark, backButton, backButtonDark, settingButton, settingButtonDark;
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
	backButton.loadFromFile("Assets/button/back.png");
	backButtonDark.loadFromFile("Assets/button/back_off.png");
	settingButton.loadFromFile("Assets/button/setting2_button_on.png");
	settingButtonDark.loadFromFile("Assets/button/setting2_button_off.png");

	double baseScale = 3.0599f;
	double selectedScale = 3.0599f;

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
	sf::Sprite backButtonS(backButton);
	sf::Sprite backButton_Dark(backButtonDark);
	sf::Sprite settingS(settingButton);
	sf::Sprite setting_Dark(settingButtonDark);


	float card1CenterX = 290.0f;
	float card1CenterY = 385.0f;
	float card2CenterX = 675.0f;
	float card2CenterY = 385.0f;
	float card3CenterX = 1110.0f;
	float card3CenterY = 385.0f;

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
	float okButtonScale = 4.32222f;
	okButtonS.setScale(okButtonScale, okButtonScale);
	okButton_Dark.setScale(okButtonScale, okButtonScale);

	// Back button
	backButtonS.setScale(scaleX + 0.05f, scaleY + 0.05f);
	backButton_Dark.setScale(scaleX + 0.05f, scaleY + 0.05f);
	backButtonS.setPosition(40.0f, -40.0f);
	backButton_Dark.setPosition(40.0f, -40.0f);

	settingS.setScale(scaleX - 1.3f, scaleY - 1.3f);
	setting_Dark.setScale(scaleX - 1.3f, scaleY - 1.3f);
	settingS.setPosition(200.0f, 15.0f);
	setting_Dark.setPosition(200.0f, 15.0f);

	// Tính toán vị trí giữa màn hình
	float okButtonX = 790.0f;
	float okButtonY = 700.0f;

	// --- [QUAN TRỌNG] LOGIC ĐIỀU HƯỚNG ---
	int cardChoice = 1;
	int row = 1; // 0 = Back Button, 1 = cards, 2 = OK button
	int topChoice = 0; // 0 = Back, 1 = Setting 

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
	freestylesText.setPosition(140.f, 385.f);

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
	standardText.setPosition(542.f, 385.f);

	// Card 3: Chặn 2 đầu
	sf::Text block2endsText;
	block2endsText.setFont(font);
	std::wstring blockString =
		L"   LUẬT CHẶN 2 ĐẦU\n\n"
		L"Bên nào tạo được hàng\n"
		L"liên tiếp nhiều hơn 5\n"
		L"hoặc không bị chặn 2\n"
		L"đầu thì sẽ thắng.\n"
		L"Tức là:  XOOOOOX\n"
		L"-> Không tính thắng.\n";
	block2endsText.setString(blockString);
	block2endsText.setCharacterSize(27);
	block2endsText.setFillColor(sf::Color(80, 48, 32));
	block2endsText.setPosition(975.f, 382.f);
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
				case sf::Keyboard::Right:
					PlaySwitchSFX();
					if (row == 1) {
						cardChoice--;
						if (cardChoice < 1) cardChoice = 3;
					}
					else if (row == 0) {
						// Điều hướng hàng trên: A chuyển về nút Back (0)
						topChoice = 0;
					}
					   break;

				case sf::Keyboard::D:
				case sf::Keyboard::Left:
					PlaySwitchSFX();
					   if (row == 1) {
						   cardChoice++;
						   if (cardChoice > 3) cardChoice = 1;
					   }
					   else if (row == 0) {
						   // Điều hướng hàng trên: D chuyển sang nút Setting (1)
						   topChoice = 1;
					   }
					   break;

				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					PlayMoveSFX();
					if (row == 2) { // Từ OK lên Card
						row = 1;
					}
					else if (row == 1) { // Từ Card lên Back
						row = 0;
						topChoice = 0;
					}
					break;

				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					PlayMoveSFX();
					if (row == 0) { // Từ Back xuống Card
						row = 1;
					}
					else if (row == 1) { // Từ Card xuống OK
						row = 2;
					}
					break;

				case sf::Keyboard::Enter:
					PlayClickSFX();
					if (row == 0) {
						if (topChoice == 0) {
							// Chọn Back -> Về menu chính
							return 0;
						}
						else if (topChoice == 1) {
							// Chọn Setting -> Gọi hàm handleSettings
							handleSettings(window, font);
						}
					}
					else if (row == 1) {
						if (!isFlipping) {
							isFlipping = true;
							flipProcess = 0.0f;
							flippingCard = cardChoice;
						}
					}
					else if (row == 2) {
						return cardChoice + 1; // Vào game
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
		if (row == 2) {
			window.draw(okButtonS);
		}
		else {
			window.draw(okButton_Dark);
		}

		// Draw Back button
		if (row == 0 && topChoice == 0) {
			window.draw(backButtonS);
		}
		else {
			window.draw(backButton_Dark);
		}

		// Draw Setting button
		if (row == 0 && topChoice == 1) {
			window.draw(settingS);
		}
		else {
			window.draw(setting_Dark);
		}

		window.display();
	}

	return -1;
}

std::pair<std::string, std::string> enterPlayerNames(sf::RenderWindow& window, sf::Font& font)
{
	// Load textures
	sf::Texture backgroundT, nameOnT, nameOffT, okOnT, okOffT;
	nameOnT.loadFromFile("Assets/background/player_name.png");
	nameOffT.loadFromFile("Assets/background/player_name_off.png");
	okOnT.loadFromFile("Assets/button/save_ok_on.png");
	okOffT.loadFromFile("Assets/button/save_ok_off.png");
	if (!backgroundT.loadFromFile("Assets/background/background_menu.png")) {
		std::cerr << "Failed to load background\n";
	}

	sf::Sprite bg(backgroundT);
	bg.setScale(scaleX, scaleY);

	// Sprite for the name entry form
	sf::Sprite nameSprite(nameOnT);
	nameSprite.setScale(scaleX, scaleY);
	nameSprite.setPosition(0.f, 0.f);

	// OK button sprite
	sf::Sprite okButton(okOffT);
	okButton.setScale(4.32222f, 4.32222f);
	okButton.setPosition(-15.f, 10.f);

	sf::String nameX = "";
	sf::String nameO = "";
	sf::Clock cursorClock;

	// ============ Step 1: Enter Player 1's name ============
	{
		sf::Text labelX(L"Nhập tên người chơi 1", font, 40);
		labelX.setFillColor(sf::Color(255, 162, 50));
		labelX.setPosition(480.f, 150.f);

		sf::Text inputX("", font, 35);
		inputX.setFillColor(sf::Color(80, 48, 32));
		inputX.setPosition(560.f, 310.f);

		int selectedField = 0; // 0: Input, 1: OK
		bool finishedInput = false;
		bool ignoreNextTextInput = false;

		while (window.isOpen() && !finishedInput) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
					return { "", "" };
				}

				// Process KeyPressed FIRST to set ignore flag
				if (event.type == sf::Event::KeyPressed) {
					auto key = event.key.code;

					// Navigate down to OK button
					if ((key == sf::Keyboard::S || key == sf::Keyboard::Down) && selectedField == 0) {
						PlayMoveSFX();
						selectedField = 1;
						ignoreNextTextInput = true;
					}
					// Navigate up to input field
					else if ((key == sf::Keyboard::W || key == sf::Keyboard::Up) && selectedField == 1) {
						PlayMoveSFX();
						selectedField = 0;
						ignoreNextTextInput = true;
					}
					// Confirm
					else if (key == sf::Keyboard::Enter) {
						PlayClickSFX();
						ignoreNextTextInput = true;
						if (selectedField == 1) {
							// Trim whitespace and set default if empty
							std::string trimmed = nameX.toAnsiString();
							// Xóa khoảng trắng đầu cuối
							size_t start = trimmed.find_first_not_of(" \t\n\r");
							size_t end = trimmed.find_last_not_of(" \t\n\r");

							if (start == std::string::npos || trimmed.empty()) {
								nameX = L"Người chơi 1";
							}
							finishedInput = true;
						}
						else {
							selectedField = 1; // Move to OK
						}
					}
					// Cancel
					else if (key == sf::Keyboard::Escape) {
						PlayClickSFX();
						return { "", "" };
					}
				}

				// Process TextEntered AFTER KeyPressed
				if (event.type == sf::Event::TextEntered) {
					if (ignoreNextTextInput) {
						ignoreNextTextInput = false;
						continue;
					}
					if (selectedField == 0) {
						// Backspace
						if (event.text.unicode == 8 && !nameX.isEmpty()) {
							nameX.erase(nameX.getSize() - 1);
						}
						// Valid characters - cho phép tất cả ký tự Unicode
						else if (event.text.unicode > 31 && event.text.unicode != 127 && nameX.getSize() < 18) {
							nameX += event.text.unicode;
						}
					}
				}
			}

			// Update cursor blinking
			bool showCursor = (selectedField == 0) && (cursorClock.getElapsedTime().asSeconds() < 0.5f);
			if (cursorClock.getElapsedTime().asSeconds() > 1.f) {
				cursorClock.restart();
			}

			// Update display text
			sf::String displayText = nameX;
			if (showCursor) displayText += "|";
			inputX.setString(displayText);

			// Update textures: when input is selected, form is bright (On)
			// when OK is selected, OK button is bright (On)
			if (selectedField == 0) {
				nameSprite.setTexture(nameOnT);   // Input selected -> form bright
				okButton.setTexture(okOffT);       // OK not selected -> OK dim
			}
			else {
				nameSprite.setTexture(nameOffT);   // Input not selected -> form dim
				okButton.setTexture(okOnT);        // OK selected -> OK bright
			}

			// Render
			window.clear();
			window.draw(bg);
			window.draw(nameSprite);
			window.draw(labelX);
			window.draw(inputX);
			window.draw(okButton);
			window.display();
		}
	}

	// ============ Set Player 2's name based on mode ============


	if (_isPvE) {
		nameO = L"Máy";

	}
	else {
		// ============ Step 2: Enter Player 2's name (only if not PvE) ============
		{
			sf::Text labelO(L"Nhập tên người chơi 2", font, 40);
			labelO.setFillColor(sf::Color(255, 162, 50));
			labelO.setPosition(480.f, 150.f);

			sf::Text inputO("", font, 35);
			inputO.setFillColor(sf::Color(80, 48, 32));
			inputO.setPosition(560.f, 310.f);

			int selectedField = 0; // 0: Input, 1: OK
			bool finishedInput = false;
			bool ignoreNextTextInput = false;

			cursorClock.restart(); // Reset cursor clock for Player 2

			while (window.isOpen() && !finishedInput) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
						return { "", "" };
					}

					// Process KeyPressed FIRST to set ignore flag
					if (event.type == sf::Event::KeyPressed) {
						auto key = event.key.code;

						// Navigate down to OK button
						if ((key == sf::Keyboard::S || key == sf::Keyboard::Down) && selectedField == 0) {
							PlayMoveSFX();
							selectedField = 1;
							ignoreNextTextInput = true;
						}
						// Navigate up to input field
						else if ((key == sf::Keyboard::W || key == sf::Keyboard::Up) && selectedField == 1) {
							PlayMoveSFX();
							selectedField = 0;
							ignoreNextTextInput = true;
						}
						// Confirm
						else if (key == sf::Keyboard::Enter) {
							PlayClickSFX();
							ignoreNextTextInput = true;
							if (selectedField == 1) {
								// Trim whitespace and set default if empty
								std::string trimmed = nameO.toAnsiString();
								size_t start = trimmed.find_first_not_of(" \t\n\r");
								size_t end = trimmed.find_last_not_of(" \t\n\r");

								if (start == std::string::npos || trimmed.empty()) {
									nameO = L"Người chơi 2";
								}
								finishedInput = true;
							}
							else {
								selectedField = 1; // Move to OK
							}
						}
						// Cancel
						else if (key == sf::Keyboard::Escape) {
							PlayClickSFX();
							return { "", "" };
						}
					}

					// Process TextEntered AFTER KeyPressed
					if (event.type == sf::Event::TextEntered) {
						if (ignoreNextTextInput) {
							ignoreNextTextInput = false;
							continue;
						}
						if (selectedField == 0) {
							// Backspace
							if (event.text.unicode == 8 && !nameO.isEmpty()) {
								nameO.erase(nameO.getSize() - 1);
							}
							// Valid characters - cho phép tất cả ký tự Unicode
							else if (event.text.unicode > 31 && event.text.unicode != 127 && nameO.getSize() < 18) {
								nameO += event.text.unicode;
							}
						}
					}
				}

				// Update cursor blinking
				bool showCursor = (selectedField == 0) && (cursorClock.getElapsedTime().asSeconds() < 0.5f);
				if (cursorClock.getElapsedTime().asSeconds() > 1.f) {
					cursorClock.restart();
				}

				// Update display text
				sf::String displayText = nameO;
				if (showCursor) displayText += "|";
				inputO.setString(displayText);

				// Update textures: when input is selected, form is bright (On)
				// when OK is selected, OK button is bright (On)
				if (selectedField == 0) {
					nameSprite.setTexture(nameOnT);   // Input selected -> form bright
					okButton.setTexture(okOffT);       // OK not selected -> OK dim
				}
				else {
					nameSprite.setTexture(nameOffT);   // Input not selected -> form dim
					okButton.setTexture(okOnT);        // OK selected -> OK bright
				}

				// Render
				window.clear();
				window.draw(bg);
				window.draw(nameSprite);
				window.draw(labelO);
				window.draw(inputO);
				window.draw(okButton);
				window.display();
			}
		}
	}

	// Convert sf::String to std::string
	std::string nameXStr = nameX.toAnsiString();
	std::string nameOStr = nameO.toAnsiString();
	return { nameXStr, nameOStr };
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int DrawBoard(sf::RenderWindow& window, int n, int result) {
	sf::Texture board1T, xTexture, oTexture, bgTexture, barT, board2T, board3T, frameX_T, frameO_T, winBeforeT, XwinT, OwinT, XloseT, loseBeforeT, outGameT, outGameONT, continueGameT, continueGameONT;
	sf::Texture drawAfterT, frameXActive_T, frameOActive_T, modeX_T[4], modeO_T[3];

	sf::Sprite boardS, xSprite, oSprite, bgSprite, barS, frameX_S, frameO_S, winBeforeS, XwinS, OwinS, XloseS, loseBeforeS, outGameS, outGameONS, continueGameS, continueGameONS;
	sf::Sprite  modeX_S[4], modeO_S[3], drawAfterS;

	board1T.loadFromFile("Assets/playing/board.png");
	board3T.loadFromFile("Assets/playing/board_renju.png");
	board2T.loadFromFile("Assets/playing/board_standard.png");
	xTexture.loadFromFile("Assets/playing/X_letter.png");
	oTexture.loadFromFile("Assets/playing/O_letter.png");
	barT.loadFromFile("Assets/background/text_board.png");

	// win/lose overlays
	winBeforeT.loadFromFile("Assets/playing/winBefore.png");
	XwinT.loadFromFile("Assets/playing/winAfter_X.png");
	OwinT.loadFromFile("Assets/playing/winAfter_O.png");
	XloseT.loadFromFile("Assets/playing/loseAfter.png");
	loseBeforeT.loadFromFile("Assets/playing/loseBefore.png");
	drawAfterT.loadFromFile("Assets/playing/drawAfter.png");

	// button
	outGameT.loadFromFile("Assets/button/exit_game_on.png");
	outGameONT.loadFromFile("Assets/button/exit_game.png");
	continueGameT.loadFromFile("Assets/button/continue_game_on.png");
	continueGameONT.loadFromFile("Assets/button/continue_game.png");

	// frames X / O
	frameX_T.loadFromFile("Assets/playing/frameX.png");
	frameO_T.loadFromFile("Assets/playing/frameO.png");
	frameXActive_T.loadFromFile("Assets/playing/x_turn.png");
	frameOActive_T.loadFromFile("Assets/playing/o_turn.png");
	// Mode FREESTYLE
	modeX_T[0].loadFromFile("Assets/player/freestyle_X.png");
	modeO_T[0].loadFromFile("Assets/player/freestyle_O.png");
	// Mode STANDARD
	modeX_T[1].loadFromFile("Assets/player/standard_X.png");
	modeO_T[1].loadFromFile("Assets/player/standard_O.png");
	// Mode RENJU
	modeX_T[2].loadFromFile("Assets/player/renju_X.png");
	modeO_T[2].loadFromFile("Assets/player/renju_O.png");
	modeX_T[3].loadFromFile("Assets/player/momotaro.png");


	// assign textures to sprites for win/lose overlays
	if (winBeforeT.getSize().x > 0) winBeforeS.setTexture(winBeforeT);
	if (XwinT.getSize().x > 0) XwinS.setTexture(XwinT);
	if (OwinT.getSize().x > 0) OwinS.setTexture(OwinT);
	if (XloseT.getSize().x > 0) XloseS.setTexture(XloseT);
	if (loseBeforeT.getSize().x > 0) loseBeforeS.setTexture(loseBeforeT);
	if (drawAfterT.getSize().x > 0)  drawAfterS.setTexture(drawAfterT);
	for (int i = 0; i < 3; i++) {
		if (modeX_T[i].getSize().x > 0)
			modeX_S[i].setTexture(modeX_T[i]);

		if (modeO_T[i].getSize().x > 0)
			modeO_S[i].setTexture(modeO_T[i]);
	}
	if (modeX_T[3].getSize().x > 0) modeX_S[3].setTexture(modeX_T[3]);

	// Set background và giao diện theo mode
	string bgPath = "Assets/background/board_background" + to_string(_backgroundBoard) + ".png";
	bgTexture.loadFromFile(bgPath);

	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(3.8f, 3.5f);

	switch (_backgroundBoard) {
	case 1:
		boardS.setTexture(board1T);
		break;
	case 2:
		boardS.setTexture(board2T);
		break;
	case 3:
		boardS.setTexture(board3T);
		break;
	default:
		boardS.setTexture(board1T);
		break;
	}


	xSprite.setTexture(xTexture);
	oSprite.setTexture(oTexture);
	barS.setTexture(barT);
	frameX_S.setTexture(frameX_T);
	frameO_S.setTexture(frameO_T);
	outGameS.setTexture(outGameT);
	outGameONS.setTexture(outGameONT);
	continueGameS.setTexture(continueGameT);
	continueGameONS.setTexture(continueGameONT);

	// Size bàn cờ
	float boardScale = 3.5f;
	boardS.setScale(boardScale, boardScale);

	float boardX = 15.0f;
	float boardY = 5.0f;
	boardS.setPosition(boardX, boardY);


	// Thanh thông báo
	float barScale = 3.5f;
	barS.setScale(barScale, barScale);
	float barX = 35.0f;
	float barY = 10.0f;
	barS.setPosition(barX, barY);

	float originalCellSize = 12.04f;
	float cellSize = originalCellSize * boardScale;

	// Vị trí bắt đầu
	float offsetX = 413.0f;
	float offsetY = 197.0f;

	float xoScale = 0.85f;
	float xScale = (cellSize * xoScale) / xTexture.getSize().x;
	float oScale = (cellSize * xoScale) / oTexture.getSize().x;

	xSprite.setScale(xScale, xScale);
	oSprite.setScale(oScale, oScale);

	// Setup frames cho stats
	float frameScale = 3.8f;
	frameX_S.setScale(frameScale, frameScale);
	frameO_S.setScale(frameScale, frameScale);

	// Vị trí frames
	float frameLeftX = boardX + 10.0f;
	float frameRightX = 120.0f;
	float frameY = boardY + 80.0f;

	frameX_S.setPosition(frameLeftX, frameY);
	frameO_S.setPosition(frameRightX, frameY);
	if (result == 2) { // Game đang chơi
		if (_TURN) {
			// Lượt X
			frameX_S.setTexture(frameXActive_T);
			frameO_S.setTexture(frameO_T);
		}
		else {
			// Lượt O
			frameX_S.setTexture(frameX_T);
			frameO_S.setTexture(frameOActive_T);
		}
	}
	else {
		// Game kết thúc → trở về frame thường
		frameX_S.setTexture(frameX_T);
		frameO_S.setTexture(frameO_T);
	}

	window.draw(bgSprite);
	window.draw(boardS);

	// Giao diện trong FRAME theo MODE
	sf::Vector2f modeXScale[4] = {
		{0.9f, 0.9f},   // Mode 1
		{1.0f, 1.0f},   // Mode 2
		{1.03f, 1.03f},   // Mode 3
		{1.9f, 1.9f}  // Momotaro chung
	};

	sf::Vector2f modeOScale[3] = {
		{2.13f, 2.13f},
		{2.13f, 2.13f},
		{2.13f, 2.13f}
	};

	sf::Vector2f modeXOffset[4] = {
		{105.f, 497.f},
		{87.f, 493.f},
		{70.f, 496.f},
		{30.f, 303.f}
	};

	sf::Vector2f modeOOffset[3] = {
		{560.f, 310.f},
		{725.f, 320.f},
		{560.f, 310.f}
	};
	// 1 = Tự do, 2 = Tiêu chuẩn, 3 = Chặn 2 đầu
	int currentMode = _backgroundBoard - 1; // về index 0..2


	//Vẽ ván số mấy
	static std::vector<sf::Texture> numberTextures;
	if (numberTextures.empty()) {
		for (int i = 1; i <= 9; i++) {
			sf::Texture t;
			if (!t.loadFromFile("Assets/playing/" + std::to_string(i) + ".png")) {
				std::cerr << "Thieu anh so: " << i << "\n";
			}
			numberTextures.push_back(t);
		}
	}

	// 2. Chọn ảnh dựa trên _matchCount hiện tại

	int index = _matchCount - 1;

	if (index >= 0 && index < numberTextures.size()) {
		sf::Sprite matchNumberSprite;
		matchNumberSprite.setTexture(numberTextures[index]);

		// Scale ảnh nếu to quá (tuỳ chỉnh số này cho vừa ô)
		matchNumberSprite.setScale(boardScale, boardScale);
		matchNumberSprite.setPosition(boardX, boardY);

		window.draw(matchNumberSprite);
	}

	// ================= VẼ HIGHLIGHT NỀN Ô THẮNG =================
	if (!_winningLine.empty()) {
		// 1. Lấy thông tin
		int rStart = _winningLine[0].first;
		int cStart = _winningLine[0].second;
		int winner = _A[rStart][cStart].c;

		// 2. Tính toán kích thước (Khai báo biến rõ ràng tại đây)
		float hlSize = cellSize - 4.0f; // Trừ 4px để chừa viền
		sf::RectangleShape highlightShape(sf::Vector2f(hlSize, hlSize));

		// Set viền dày lên để dễ nhìn
		highlightShape.setOutlineThickness(3.0f);

		// 3. Chọn màu (Dùng màu ĐẬM, không trong suốt)
		if (winner == -1) {
			// X thắng: Nền Xanh Nhạt - Viền Xanh Đậm
			highlightShape.setFillColor(sf::Color(135, 206, 250, 255));
			highlightShape.setOutlineColor(sf::Color(0, 0, 139));
		}
		else if (winner == 1) {
			// O thắng: Nền Hồng - Viền Đỏ Đậm
			highlightShape.setFillColor(sf::Color(255, 182, 193, 255));
			highlightShape.setOutlineColor(sf::Color(139, 0, 0));
		}
		else {
			// Dự phòng (Nếu lỗi): Màu Tím Đậm (Magenta)
			highlightShape.setFillColor(sf::Color::Magenta);
			highlightShape.setOutlineColor(sf::Color::Yellow);
		}
		// std::cout << "--- DRAWING HIGHLIGHT ---" << std::endl;
		for (size_t k = 0; k < _winningLine.size(); k++) {
			int r = _winningLine[k].first;
			int c = _winningLine[k].second;

			// Tính tọa độ (Khớp với bàn cờ)
			float hlX = boardX + offsetX + (c * cellSize) + 2.0f;
			float hlY = boardY + offsetY + (r * cellSize) + 2.0f;

			// In thử tọa độ ô đầu tiên ra console để xem có bị lệch khỏi màn hình (0-1366) không
			if (k == 0) {
				// std::cout << "Highlight at: X=" << hlX << " Y=" << hlY << std::endl;
			}

			highlightShape.setPosition(hlX, hlY);
			window.draw(highlightShape);
		}
	}

	
	// Vẽ quân cờ
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

	// Cursor
	sf::RectangleShape cursor(sf::Vector2f(cellSize - 4, cellSize - 4));
	cursor.setFillColor(sf::Color::Transparent);
	cursor.setOutlineColor(sf::Color(138, 72, 54));
	cursor.setOutlineThickness(3.0f);

	float cursorX = boardX + offsetX + (_currentCol * cellSize) + 2;
	float cursorY = boardY + offsetY + (_currentRow * cellSize) + 2;
	cursor.setPosition(cursorX, cursorY);
	if (result == 2) {
		window.draw(cursor);
	}

	// Vẽ frames
	// ===== MODE ICON X =====
	modeX_S[currentMode].setScale(modeXScale[currentMode]);
	modeX_S[3].setScale(modeXScale[3]);
	modeX_S[currentMode].setPosition(
		frameX_S.getPosition().x + modeXOffset[currentMode].x,
		frameX_S.getPosition().y + modeXOffset[currentMode].y
	);
	modeX_S[3].setPosition(
		frameX_S.getPosition().x + modeXOffset[3].x,
		frameX_S.getPosition().y + modeXOffset[3].y
	);

	// ===== MODE ICON O =====
	modeO_S[currentMode].setScale(modeOScale[currentMode]);
	modeO_S[currentMode].setPosition(
		frameO_S.getPosition().x + modeOOffset[currentMode].x,
		frameO_S.getPosition().y + modeOOffset[currentMode].y
	);

	window.draw(frameX_S);
	window.draw(frameO_S);

	window.draw(modeX_S[3]);
	window.draw(modeX_S[currentMode]);
	window.draw(modeO_S[currentMode]);


	// Thông tin game
	window.draw(barS);
	sf::Font font;
	if (font.loadFromFile("Assets/font/regular.ttf")) {

		bool isTerminal = (result == -1 || result == 1 || result == 0);
		sf::Text gameInfo;
		gameInfo.setFont(font);
		gameInfo.setCharacterSize(26);
		gameInfo.setStyle(sf::Text::Bold);

		sf::String message;

		if (isTerminal) {
			// Nếu O thua
			if (result == -1 || result == 0) {
				sf::Sprite overlayO = frameO_S;
				overlayO.setColor(sf::Color(0, 0, 0, 180));
				window.draw(overlayO);
			}

			// Nếu X thua 
			if (result == 1 || result == 0) {
				sf::Sprite overlayX = frameX_S;
				overlayX.setColor(sf::Color(0, 0, 0, 180));
				window.draw(overlayX);
			}
		}
		else {
			if (_TURN)
				message = sf::String(L"Lượt chơi: X");
			else
				message = sf::String(L"Lượt chơi: O");
			gameInfo.setFillColor(sf::Color(54, 39, 32));
			gameInfo.setPosition(590.0f, 34.0f);
		}

		gameInfo.setString(message);
		window.draw(gameInfo);

		sf::Color textColor(54, 39, 32);

		float textAreaX = frameLeftX + 80.0f;
		float textAreaY = frameY + 180.0f;

		// Text "X" 
		sf::Text titleX;
		titleX.setFont(font);
		titleX.setCharacterSize(36);
		titleX.setStyle(sf::Text::Bold);
		titleX.setFillColor(textColor);
		titleX.setPosition(textAreaX + 65.0f, textAreaY - 10.0f);

		// Text thông số X
		sf::Text movesXText;
		movesXText.setFont(font);
		movesXText.setCharacterSize(24);
		movesXText.setFillColor(textColor);
		movesXText.setString(
			sf::String(L"Số lượt: ") + std::to_wstring(_movesX)
		);
		movesXText.setPosition(textAreaX + 25.0f, textAreaY + 67.0f);

		sf::Text winsXText;
		winsXText.setFont(font);
		winsXText.setCharacterSize(24);
		winsXText.setFillColor(textColor);
		winsXText.setString(
			sf::String(L"Số thắng: ") + std::to_wstring(_winsX)
		);
		winsXText.setPosition(textAreaX + 25.0f, textAreaY + 98.0f);

		window.draw(titleX);
		window.draw(movesXText);
		window.draw(winsXText);

		// Stats cho O
		float textAreaOX = frameRightX + 880.0f;
		float textAreaOY = frameY + 180.0f;

		// Text "O"
		sf::Text titleO;
		titleO.setFont(font);
		titleO.setCharacterSize(36);
		titleO.setStyle(sf::Text::Bold);
		titleO.setFillColor(textColor);
		titleO.setPosition(textAreaOX + 65.0f, textAreaOY - 10.0f);

		// Text thông số O
		sf::Text movesOText;
		movesOText.setFont(font);
		movesOText.setCharacterSize(24);
		movesOText.setFillColor(textColor);
		movesOText.setString(
			sf::String(L"Số lượt: ") + std::to_wstring(_movesO)
		);
		movesOText.setPosition(textAreaOX + 95.0f, textAreaOY + 74.0f);

		sf::Text winsOText;
		winsOText.setFont(font);
		winsOText.setCharacterSize(24);
		winsOText.setFillColor(textColor);
		winsOText.setString(
			sf::String(L"Số thắng: ") + std::to_wstring(_winsO)
		);
		winsOText.setPosition(textAreaOX + 95.0f, textAreaOY + 108.0f);

		window.draw(titleO);
		window.draw(movesOText);
		window.draw(winsOText);

		// ===== TÊN NGƯỜI CHƠI X (Player 1) =====
		sf::Text playerXName;
		playerXName.setFont(font);
		playerXName.setCharacterSize(28);
		playerXName.setStyle(sf::Text::Bold);
		playerXName.setFillColor(textColor);

		// Lấy tên từ biến toàn cục và chuyển sang sf::String
		sf::String nameX = sf::String::fromUtf8(_playerXName.begin(), _playerXName.end());
		if (nameX.getSize() > 12) {
			nameX = sf::String(nameX.substring(0, 12)) + "...";
		}
		playerXName.setString(nameX);

		sf::FloatRect boundsX = playerXName.getLocalBounds();
		playerXName.setPosition(
			textAreaX + 15.0f + (140.0f - boundsX.width) / 2.0f,
			textAreaY + 30.0f
		);

		// ===== TÊN NGƯỜI CHƠI O (Player 2) =====
		sf::Text playerOName;
		playerOName.setFont(font);
		playerOName.setCharacterSize(28);
		playerOName.setStyle(sf::Text::Bold);
		playerOName.setFillColor(textColor);

		sf::String nameO = sf::String::fromUtf8(_playerOName.begin(), _playerOName.end());
		if (nameO.getSize() > 12) {
			nameO = sf::String(nameO.substring(0, 12)) + "...";
		}
		playerOName.setString(nameO);

		sf::FloatRect boundsO = playerOName.getLocalBounds();
		playerOName.setPosition(
			textAreaOX + 95.0f + (140.0f - boundsO.width) / 2.0f,
			textAreaOY + 38.0f
		);

		// VẼ TÊN
		window.draw(playerXName);
		window.draw(playerOName);
	}


	//Hiệu ứng thắng thua
	static int animResult = 999;
	static sf::Clock animClock;
	static bool animShownForResult = false;
	static int buttonChoice = 0;

	const float scaleDuration = 0.4f;
	const float totalDuration = 4.5f;
	const float minScaleFactor = 0.05f;
	bool isTerminal = (result == -1 || result == 1 || result == 0);

	if (isTerminal) {
		continueGameS.setScale(barScale, barScale);
		continueGameS.setPosition(barX + 90.0f, barY - 46.0f);
		outGameS.setScale(barScale, barScale);
		outGameS.setPosition(barX + 70.0f, barY - 49.0f);

		// CHỈ cho phép chọn nút SAU KHI animation xong
		if (animShownForResult) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

				PlayMoveSFX();
				buttonChoice = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				PlayMoveSFX();
				buttonChoice = 0;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				PlayClickSFX();
				int returnValue = buttonChoice;
				animResult = 999;
				animShownForResult = false;
				buttonChoice = 0;
				return returnValue;
			}
		}

		if (buttonChoice == 0) {
			continueGameS.setTexture(continueGameONT);
			outGameS.setTexture(outGameT);
		}
		else {
			continueGameS.setTexture(continueGameT);
			outGameS.setTexture(outGameONT);
		}

		window.draw(continueGameS);
		window.draw(outGameS);
	}

	if (isTerminal) {
		if ((animResult != result) || (!animShownForResult && animResult == 999)) {
			animResult = result;
			animClock.restart();
			animShownForResult = false;
		}
	}
	else {
		animResult = 999;
		animShownForResult = false;
	}

	if (animResult != 999 && !animShownForResult) {
		float t = animClock.getElapsedTime().asSeconds();

		if (t >= totalDuration) {
			animShownForResult = true;
		}
		else {
			sf::FloatRect boardBounds = boardS.getGlobalBounds();
			float centerX = boardBounds.left + boardBounds.width / 2.f;
			float centerY = boardBounds.top + boardBounds.height / 2.f;

			// <<< ADDED: vertical offset for overlays (positive = move down) >>>
			const float overlayYOffset = 80.0f;

			sf::Sprite* chosen = nullptr;
			if (t < scaleDuration) {
				if (animResult == -1 || animResult == 1) {
					if (winBeforeT.getSize().x > 0) chosen = &winBeforeS;
				}
				else {
					if (loseBeforeT.getSize().x > 0) chosen = &loseBeforeS;
				}
			}
			else {
				if (animResult == -1) {
					if (XwinT.getSize().x > 0) chosen = &XwinS;
				}
				else if (animResult == 1) {
					if (_isPvE) {
						if (XloseT.getSize().x > 0) chosen = &XloseS;
					}
					else {
						if (OwinT.getSize().x > 0) chosen = &OwinS;
					}
				}
				else if (animResult == 0) {
					// HÒA
					if (drawAfterT.getSize().x > 0)
						chosen = &drawAfterS;
					chosen->setPosition(10.f, 0.0f);
				}
				else {
					if (XloseT.getSize().x > 0) chosen = &XloseS;
				}
			}

			if (chosen && chosen->getTexture()) {
				float baseTargetWidth = boardBounds.width * 0.90f;
				float baseScale = baseTargetWidth / static_cast<float>(chosen->getTexture()->getSize().x);

				float scaleFactor = 1.0f;
				if (t < scaleDuration) {
					float p = t / scaleDuration;
					float ease = 1.0f - (1.0f - p) * (1.0f - p);
					scaleFactor = minScaleFactor + (1.0f - minScaleFactor) * ease;
				}
				else {
					scaleFactor = 1.0f;
				}

				chosen->setOrigin(chosen->getTexture()->getSize().x / 2.f, chosen->getTexture()->getSize().y / 2.f);
				// moved down by overlayYOffset (was centerY - 20.0f)
				chosen->setPosition(centerX - 15.0f, centerY + overlayYOffset);
				chosen->setScale(baseScale * scaleFactor, baseScale * scaleFactor);
				chosen->setColor(sf::Color(255, 255, 255, 255));

				window.draw(*chosen);
			}
		}
	}

	return -1;
}

int ProcessFinish(int pWhoWin) {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
	switch (pWhoWin) {
	case -1:
		// X thắng
		++_winsX;
		printf("Nguoi choi X da thang\n");
		break;
	case 1:
		// O thắng
		++_winsO;
		printf("Nguoi choi O da thang\n");
		break;
	case 0:
		printf("Hoa!\n");
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
					PlayMoveSFX();
					selectedItem = (selectedItem + optionCount - 1) % optionCount;
				}
				else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
					PlayMoveSFX();
					selectedItem = (selectedItem + 1) % optionCount;
				}
				else if (event.key.code == sf::Keyboard::Enter) {
					PlayClickSFX();
					// PHỤC HỒI View của game trước khi thoát
					window.setView(gameView);
					return selectedItem + 1;
				}
				else if (event.key.code == sf::Keyboard::Escape) {
					PlayClickSFX();
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

int opponentChoosing(sf::RenderWindow& window) {
	// 1. Tải Background
	sf::Texture backgroundT;
	backgroundT.loadFromFile("Assets/background/background_menu.png");
	sf::Sprite bg(backgroundT);
	bg.setScale(scaleX, scaleY); // Sử dụng scale chuẩn của project

	// 2. Tải Texture cho 2 nút (Thay tên file đúng với thực tế của bạn)
	sf::Texture pvpT, pveT;
	if (!pvpT.loadFromFile("Assets/button/pvp.png")) std::cerr << "Loi pvp_button\n";
	if (!pveT.loadFromFile("Assets/button/pve.png")) std::cerr << "Loi pve_button\n";

	sf::Sprite pvpS(pvpT), pveS(pveT);

	// 3. Thiết lập Scale và Origin
	pvpS.setScale(scaleX, scaleY);
	pveS.setScale(scaleX, scaleY);

	// Đặt Origin vào tâm ảnh để căn chỉnh chính xác hơn
	pvpS.setOrigin(pvpT.getSize().x / 2.f, pvpT.getSize().y / 2.f);
	pveS.setOrigin(pveT.getSize().x / 2.f, pveT.getSize().y / 2.f);

	// 4. Căn chỉnh vị trí dựa trên ảnh mẫu (Dịch sang phải tâm màn hình một chút)
	float centerX = 1366.f / 2.f + 60.f; // Dịch sang phải 120px so với trục giữa
	float pvpY = 445.f; // Vị trí nút Chơi với người
	float pveY = 570.f; // Vị trí nút Chơi với máy

	pvpS.setPosition(centerX, pvpY);
	pveS.setPosition(centerX, pveY);

	int choice = 0; // 0: PvP, 1: PvE

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return -1;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
					PlayMoveSFX();
					choice = 0;
				}
				else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
					PlayMoveSFX();
					choice = 1;
				}
				else if (event.key.code == sf::Keyboard::Enter) {
					PlayClickSFX();
					return choice;
				}
				else if (event.key.code == sf::Keyboard::Escape) {
					PlayClickSFX();
					return -1;
				}
			}
		}

		// 5. Hiệu ứng mờ đen (Dimming) giống như code cũ
		// Nút được chọn để màu trắng (255, 255, 255), nút không chọn để màu xám tối
		if (choice == 0) {
			pvpS.setColor(sf::Color::White);
			pveS.setColor(sf::Color(100, 100, 100, 255)); // Mờ đen nút dưới
		}
		else {
			pvpS.setColor(sf::Color(100, 100, 100, 255)); // Mờ đen nút trên
			pveS.setColor(sf::Color::White);
		}

		window.clear();
		window.draw(bg);
		window.draw(pvpS);
		window.draw(pveS);
		window.display();
	}
	return -1;
}


// Save + Load
std::string GetInputString(sf::RenderWindow& window, sf::Font& font, const sf::View& restoreView, std::string initialText)
{
	
	sharedBgTexture.create(window.getSize().x, window.getSize().y);
	sharedBgTexture.update(window); // Chụp màn hình hiện tại
	sharedBgSprite.setTexture(sharedBgTexture);
	sharedBgSprite.setColor(sf::Color(150, 150, 150));

	sf::Texture boardOnT, boardOffT, okOnT, okOffT, exitOnT, exitOffT;

	// Load Assets (Giữ nguyên)
	boardOnT.loadFromFile("Assets/background/save_board_on.png");
	boardOffT.loadFromFile("Assets/background/save_board_off.png");
	okOnT.loadFromFile("Assets/button/save_ok_on.png");
	okOffT.loadFromFile("Assets/button/save_ok_off.png");
	exitOnT.loadFromFile("Assets/button/save_exit_on.png");
	exitOffT.loadFromFile("Assets/button/save_exit_off.png");

	sf::Sprite boardS(boardOnT);
	sf::Sprite btnOK(okOffT);
	sf::Sprite btnExit(exitOffT);

	// Cài đặt vị trí 
	boardS.setScale(scaleX, scaleY);
	btnOK.setScale(scaleX, scaleY);
	btnExit.setScale(scaleX, scaleY);

	sf::Vector2u winSize = window.getSize();
	float actualBoardWidth = boardOnT.getSize().x * scaleX;
	float actualBoardHeight = boardOnT.getSize().y * scaleY;

	float centerX = (winSize.x - actualBoardWidth) / 2.f;
	float centerY = (winSize.y - actualBoardHeight) / 2.f;

	boardS.setPosition(centerX, centerY);
	btnOK.setPosition(centerX, centerY);
	btnExit.setPosition(centerX, centerY);

	// Ô nhập liệu
	float textInputX = centerX + (actualBoardWidth * 0.43f);
	float textInputY = centerY + (actualBoardHeight * 0.42f);

	std::string userInput = initialText;
	sf::Text inputText(userInput, font, 35);
	inputText.setFillColor(sf::Color(80, 48, 32));
	inputText.setPosition(textInputX, textInputY);

	int selectedControl = 0; 
	sf::Clock cursorClock;

	
	window.setView(window.getDefaultView());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (selectedControl == 0)
				{
					if (event.text.unicode == 8) { 
						if (!userInput.empty()) userInput.pop_back();
					}
					else if (event.text.unicode > 31 && event.text.unicode < 127 && userInput.length() < 18) {
						if (std::isalnum(static_cast<char>(event.text.unicode)) || event.text.unicode == '_' || event.text.unicode == ' ') {
							userInput += static_cast<char>(event.text.unicode);
						}
					}
					inputText.setString(userInput);
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				auto key = event.key.code;
				if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
					PlayMoveSFX();
					if (selectedControl == 1) selectedControl = 0;
					else if (selectedControl == 0) selectedControl = 2;
				}
				else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
					PlayMoveSFX();
					if (selectedControl == 2) selectedControl = 0;
					else if (selectedControl == 0) selectedControl = 1;
				}
				else if (key == sf::Keyboard::Enter) {
					PlayClickSFX();
					if (selectedControl == 1) { // OK
						return userInput;
					}
					else if (selectedControl == 2) return ""; // Exit
					else if (selectedControl == 0) selectedControl = 1;
				}
				else if (key == sf::Keyboard::Escape) {
					PlayClickSFX();
					return "";
				}
			}
		}

		window.clear();

		window.draw(sharedBgSprite);

		if (selectedControl == 0) boardS.setTexture(boardOnT);
		else boardS.setTexture(boardOffT);

		btnOK.setTexture(selectedControl == 1 ? okOnT : okOffT);
		btnExit.setTexture(selectedControl == 2 ? exitOnT : exitOffT);

		bool showCursor = (selectedControl == 0) && (cursorClock.getElapsedTime().asSeconds() < 0.5f);
		if (cursorClock.getElapsedTime().asSeconds() > 1.f) cursorClock.restart();
		inputText.setString(userInput + (showCursor ? "|" : ""));

		window.draw(boardS);
		window.draw(inputText);
		window.draw(btnOK);
		window.draw(btnExit);
		window.display();
	}
	return "";
}


int handleSaveSuccessScreen(sf::RenderWindow& window, sf::Font& font, bool askContinue)
{
	sf::Texture blankT, yesOnT, yesOffT, noOnT, noOffT, okOnT, okOffT;

	// Load Assets
	if (!blankT.loadFromFile("Assets/background/save_board_blank.png")) return 0;
	if (!yesOnT.loadFromFile("Assets/button/save_blank_yes_on.png")) return 0;
	if (!yesOffT.loadFromFile("Assets/button/save_blank_yes_off.png")) return 0;
	if (!noOnT.loadFromFile("Assets/button/save_blank_no_on.png")) return 0;
	if (!noOffT.loadFromFile("Assets/button/save_blank_no_off.png")) return 0;

	// Load thêm nút OK cho trường hợp Load/Rename
	if (!okOnT.loadFromFile("Assets/button/save_ok_on.png")) return 0;
	if (!okOffT.loadFromFile("Assets/button/save_ok_off.png")) return 0;

	sf::Sprite blankS(blankT);
	sf::Sprite btnYes(yesOffT), btnNo(noOffT);
	sf::Sprite btnOK(okOffT); // Sprite cho nút OK

	blankS.setScale(scaleX, scaleY);
	btnYes.setScale(scaleX, scaleY);
	btnNo.setScale(scaleX, scaleY);
	btnOK.setScale(scaleX, scaleY);

	sf::Vector2u winSize = window.getSize();

	// Tính toán vị trí trung tâm
	float actualWidth = blankT.getSize().x * scaleX;
	float actualHeight = blankT.getSize().y * scaleY;
	float centerX = (winSize.x - actualWidth) / 2.f;
	float centerY = (winSize.y - actualHeight) / 2.f;

	// Đặt vị trí (Tất cả đều nằm trùng khớp lên nhau tại centerX, centerY)
	blankS.setPosition(centerX, centerY);
	btnYes.setPosition(centerX, centerY);
	btnNo.setPosition(centerX, centerY);
	btnOK.setPosition(centerX, centerY);

	
	sf::Text msg1, msg2, msg3;
	msg1.setFont(font);
	msg2.setFont(font);
	msg3.setFont(font);

	msg1.setCharacterSize(40);
	msg2.setCharacterSize(30);
	msg3.setCharacterSize(30);

	msg1.setFillColor(sf::Color(80, 48, 32));
	msg2.setFillColor(sf::Color(80, 48, 32));

	if (askContinue) {
		msg1.setString(L"Lưu thành công!");
		msg2.setString(L"Bạn có muốn chơi tiếp không?");
	}
	else {
		msg1.setString(L"Lưu thành công!");
		msg2.setString(L"     Nhấn Ok để tiếp tục ");
	}

	msg1.setPosition(centerX + actualWidth * 0.40f, centerY + actualHeight * 0.35f);
	msg2.setPosition(centerX + actualWidth * 0.35f, centerY + actualHeight * 0.44f);
	int selectedButton = 0; 

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (askContinue) {
					if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
						PlayMoveSFX();
						selectedButton = 0;
					}
					else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
						PlayMoveSFX();
						selectedButton = 1;
						} 
				}

				if (event.key.code == sf::Keyboard::Enter) {
					PlayClickSFX();
					return selectedButton; // 0: Yes/OK, 1: No
				}
			}
		}

		// Vẽ nền cũ
		window.draw(sharedBgSprite);
		window.draw(blankS);
		window.draw(msg1);
		window.draw(msg2);

		if (askContinue) {
			// Logic vẽ nút Yes/No
			if (selectedButton == 0) {
				btnYes.setTexture(yesOnT);
				btnNo.setTexture(noOffT);
			}
			else {
				btnYes.setTexture(yesOffT);
				btnNo.setTexture(noOnT);
			}
			window.draw(btnYes);
			window.draw(btnNo);
		}
		else {
			// Logic vẽ nút OK
			btnOK.setTexture(okOnT); // Luôn sáng
			window.draw(btnOK);
		}

		window.display();
	}
	return 0;
}

// Trả về 1 nếu chọn Yes (Muốn xóa), 0 nếu chọn No (Hủy)
int ShowFullMemoryAlert(sf::RenderWindow& window, sf::Font& font)
{
	// 1. Tải tài nguyên
	sf::Texture blankT, yesOnT, yesOffT, noOnT, noOffT;

	// Background bảng
	if (!blankT.loadFromFile("Assets/background/save_board_blank.png")) return 0;

	// Nút Yes/No (Tận dụng lại asset của màn hình Save Success)
	if (!yesOnT.loadFromFile("Assets/button/save_blank_yes_on.png")) return 0;
	if (!yesOffT.loadFromFile("Assets/button/save_blank_yes_off.png")) return 0;
	if (!noOnT.loadFromFile("Assets/button/save_blank_no_on.png")) return 0;
	if (!noOffT.loadFromFile("Assets/button/save_blank_no_off.png")) return 0;

	sf::Sprite blankS(blankT);
	sf::Sprite btnYes(yesOffT);
	sf::Sprite btnNo(noOffT);

	// 2. Scale
	blankS.setScale(scaleX, scaleY);
	btnYes.setScale(scaleX, scaleY);
	btnNo.setScale(scaleX, scaleY);

	// 3. Vị trí
	sf::Vector2u winSize = window.getSize();
	float actualWidth = blankT.getSize().x * scaleX;
	float actualHeight = blankT.getSize().y * scaleY;
	float centerX = (winSize.x - actualWidth) / 2.f;
	float centerY = (winSize.y - actualHeight) / 2.f;

	blankS.setPosition(centerX, centerY);
	// Nút Yes/No đặt trùng vị trí bg (vì asset đã căn sẵn), hoặc chỉnh nhẹ nếu cần
	btnYes.setPosition(centerX, centerY);
	btnNo.setPosition(centerX, centerY);

	// 4. Text thông báo
	sf::Text msg1, msg2, msg3;
	msg1.setFont(font);
	msg2.setFont(font);
	msg3.setFont(font);

	msg1.setCharacterSize(35);
	msg2.setCharacterSize(28);
	msg3.setCharacterSize(28);

	msg1.setFillColor(sf::Color(139, 0, 0)); // Đỏ
	msg2.setFillColor(sf::Color(80, 48, 32)); // Nâu
	msg3.setFillColor(sf::Color(80, 48, 32)); // Nâu

	msg1.setString(L"Bộ nhớ đã đầy (5/5)!");
	msg2.setString(L"Bạn có muốn xóa file cũ");
	msg3.setString(L"để tiếp tục lưu không?");

	
	msg1.setPosition(centerX + actualWidth * 0.38f, centerY + actualHeight * 0.33f);
	msg2.setPosition(centerX + actualWidth * 0.38f, centerY + actualHeight * 0.40f);
	msg3.setPosition(centerX + actualWidth * 0.39f, centerY + actualHeight * 0.44f);

	int choice = 0; 

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				
				if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
					PlayMoveSFX();
					choice = 0;
				}
				else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
					PlayMoveSFX();
					choice = 1;
				}
				if (event.key.code == sf::Keyboard::Enter) {
					PlayClickSFX();
					return (choice == 0) ? 1 : 0;
				}				
				if (event.key.code == sf::Keyboard::Escape) {
					PlayClickSFX();
					return 0;
				}
			}
		}

		window.clear();
		window.draw(sharedBgSprite);
		window.draw(blankS);

		
		if (choice == 0) { 
			btnYes.setTexture(yesOnT);
			btnNo.setTexture(noOffT);
		}
		else { 
			btnYes.setTexture(yesOffT);
			btnNo.setTexture(noOnT);
		}

		window.draw(btnYes);
		window.draw(btnNo);

		window.draw(msg1);
		window.draw(msg2);
		window.draw(msg3);

		window.display();
	}
	return 0;
}

// Trong View.cpp

int handleSaveScreen(sf::RenderWindow& window, sf::Font& font, const sf::View& gameView)
{
	// Vòng lặp để cho phép quay lại nhập tên nếu cần (tùy chọn), hoặc đơn giản là xử lý flow
	while (true) {
		std::string filename = GetInputString(window, font, gameView);
		if (filename == "") return 2; // Người dùng nhấn ESC hoặc chọn Exit tại bảng nhập tên

		if (filename.empty()) filename = "Untitled";

		// 1. Kiểm tra logic ghi đè và đầy bộ nhớ
		std::vector<SaveInfo> currentFiles = GetListSaveFiles();
		bool isOverwriting = false;
		for (const auto& file : currentFiles) {
			if (file.filename == filename) {
				isOverwriting = true;
				break;
			}
		}

		if (!isOverwriting && currentFiles.size() >= 5) {

			
			int userChoice = ShowFullMemoryAlert(window, font);

			if (userChoice == 1) {
				int action = loadGameScreen(window);

				if (action == 1) {
					return 1;
				}

				std::vector<SaveInfo> newFileList = GetListSaveFiles();

				if (newFileList.size() < 5) {
					extern GameRule rule;
					SaveGame(filename, rule, 2);

					int choice = handleSaveSuccessScreen(window, font, true);
					return (choice == 0) ? 1 : 0;
				}
				else {
					return 2;
				}
			}
			else {
				return 2;
			}
		}

		extern GameRule rule;
		SaveGame(filename, rule, 2);

		int choice = handleSaveSuccessScreen(window, font, true);
		if (choice == 0) return 1;
		return 0;
	}
}

int loadGameScreen(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("Assets/font/regular.ttf"))
	{
		std::cerr << "Loi font!\n";
	}

	// --- SETUP TEXTURES ---
	sf::Texture bgT, tableT, titleT;
	bgT.loadFromFile("Assets/background/background_menu.png");
	tableT.loadFromFile("Assets/background/load_table.png");
	titleT.loadFromFile("Assets/background/load_title.png");

	sf::Sprite bg(bgT), table(tableT), title(titleT);
	bg.setScale(scaleX, scaleY);
	table.setScale(scaleX, scaleY);
	title.setScale(scaleX, scaleY);

	// --- BUTTONS ---
	sf::Texture tOnLoad, tOffLoad, tOnDelete, tOffDelete, tOnRename, tOffRename, tOnExit, tOffExit;
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

	// --- SETUP SLOTS ---
	const int slotsPerPage = 5;
	sf::Texture blankT[slotsPerPage];
	sf::Sprite blankS[slotsPerPage];

	// Tọa độ tính toán (Của bạn)
	float startY = 220.0f;
	float stepY = 80.0f;
	float startX = 350.0f;

	for (int i = 0; i < slotsPerPage; ++i)
	{
		std::string path = "Assets/background/blank" + std::to_string(i + 1) + ".png";
		blankT[i].loadFromFile(path);
		blankS[i].setTexture(blankT[i]);
		blankS[i].setScale(scaleX, scaleY);
		blankS[i].setPosition(0.0f, 0.0f);
	}

	// --- SETUP TEXT ---
	sf::Text txtName, txtRule, txtTime, txtDate, txtEmpty, txtMatch;
	txtName.setFont(font);
	txtRule.setFont(font);
	txtTime.setFont(font);
	txtDate.setFont(font);
	txtEmpty.setFont(font);
	txtMatch.setFont(font);

	sf::Color brownColor(80, 48, 32);
	txtName.setFillColor(brownColor);
	txtRule.setFillColor(brownColor);
	txtTime.setFillColor(brownColor);
	txtDate.setFillColor(brownColor);
	txtMatch.setFillColor(brownColor);
	txtEmpty.setFillColor(sf::Color(150, 150, 150));

	txtName.setCharacterSize(30);
	txtRule.setCharacterSize(24);
	txtTime.setCharacterSize(20);
	txtDate.setCharacterSize(20);
	txtMatch.setCharacterSize(24);
	txtEmpty.setCharacterSize(28);

	int selectedSlot = 0;
	bool inButton = false;
	int lastSlot = 0;

	while (window.isOpen())
	{
		
		std::vector<SaveInfo> allSaves = GetListSaveFiles();
		int totalFiles = static_cast<int>(allSaves.size());

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				auto key = event.key.code;
				if (key == sf::Keyboard::Escape) {
					PlayClickSFX();
					return 0;
				}

				// --- ĐIỀU HƯỚNG (GIỮ NGUYÊN) ---
				if (!inButton)
				{
					if (key == sf::Keyboard::Down || key == sf::Keyboard::S)
					{
						PlayMoveSFX();
						if (selectedSlot < slotsPerPage - 1)
							selectedSlot++;
					}
					else if (key == sf::Keyboard::Up || key == sf::Keyboard::W)
					{
						PlayMoveSFX();
						if (selectedSlot > 0)
							selectedSlot--;
						else
						{
							selectedSlot = 8;
							inButton = true;
						}
					}
					else if (key == sf::Keyboard::Right || key == sf::Keyboard::D)
					{

						inButton = true;
						lastSlot = selectedSlot;
						selectedSlot = 5;
					}
				}
				else
				{
					if (key == sf::Keyboard::Down || key == sf::Keyboard::S)
					{
						PlayMoveSFX();
						if (selectedSlot == 8)
						{
							inButton = false;
							selectedSlot = 0;
						}
						else if (selectedSlot < 8)
							selectedSlot++;
					}
					else if (key == sf::Keyboard::Up || key == sf::Keyboard::W)
					{
						PlayMoveSFX();
						if (selectedSlot == 5)
							selectedSlot = 8;
						else if (selectedSlot > 5)
							selectedSlot--;
					}
					else if (key == sf::Keyboard::Left || key == sf::Keyboard::A)
					{
						PlayMoveSFX();
						inButton = false;
						selectedSlot = lastSlot;
					}
				}

				// --- XỬ LÝ CHỌN (ENTER) - ĐÃ THÊM LOGIC ---
				if (key == sf::Keyboard::Enter)
				{
					PlayClickSFX();
					if (!inButton)
					{
						// Chọn trực tiếp vào slot -> LOAD
						if (selectedSlot < totalFiles)
						{
							if (LoadFromFile(allSaves[selectedSlot].fullPath))
							{
								return 1; // Load thành công
							}
						}
					}
					else
					{
						// Chọn các nút chức năng
						if (selectedSlot == 5) // NÚT LOAD
						{
							if (lastSlot < totalFiles)
							{
								if (LoadFromFile(allSaves[lastSlot].fullPath))
								{
									return 1;
								}
							}
						}
						else if (selectedSlot == 6) // NÚT RENAME
						{
							if (lastSlot < totalFiles)
							{
								std::string oldName = allSaves[lastSlot].filename;
								// Gọi bảng nhập tên
								std::string newName = GetInputString(window, font, window.getDefaultView(), oldName);

								if (!newName.empty() && newName != oldName)
								{
									if (RenameSaveFile(oldName, newName))
									{
										// Thông báo thành công (false = không hỏi chơi tiếp)
										handleSaveSuccessScreen(window, font, false);
									}
								}
							}
						}
						else if (selectedSlot == 7) // NÚT DELETE
						{
							if (lastSlot < totalFiles)
							{
								if (DeleteSaveFile(allSaves[lastSlot].filename))
								{
							
								}
							}
						}
						else if (selectedSlot == 8) // NÚT EXIT
							return 0;
					}
				}
			}
		}

		window.clear();
		window.draw(bg);
		window.draw(table);
		window.draw(title);


		for (int i = 0; i < slotsPerPage; ++i)
		{
			
			if (!inButton && selectedSlot == i)
				blankS[i].setColor(sf::Color::White);
			else if (inButton && lastSlot == i)
				blankS[i].setColor(sf::Color(220, 220, 220));
			else
				blankS[i].setColor(sf::Color(120, 120, 120));

			window.draw(blankS[i]);

			float currentY = startY + (static_cast<float>(i) * stepY);

			if (i < totalFiles)
			{
				SaveInfo& info = allSaves[i];

				txtName.setString(info.filename);
				txtName.setPosition(startX - 150.0f, currentY + 40.0f);

				txtRule.setString(info.ruleName);
				txtRule.setPosition(startX + 100.0f, currentY + 33.0f);

				txtMatch.setString(info.matchCountStr);
				txtMatch.setPosition(startX + 350.0f, currentY + 33.0f);

				txtTime.setString(info.time);
				txtDate.setString(info.date);
				txtTime.setPosition(startX + 100.0f, currentY + 62.0f);
				txtDate.setPosition(startX + 350.0f, currentY + 62.0f);

				window.draw(txtName);
				window.draw(txtRule);
				window.draw(txtTime);
				window.draw(txtDate);
				window.draw(txtMatch);
			}
		}

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