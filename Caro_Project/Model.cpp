#define _CRT_SECURE_NO_WARNINGS
#pragma execution_character_set("utf-8")
#include "Model.h"
#include <filesystem> // Thư viện quét file

using namespace std; // Thêm dòng này để dùng cout, string, vector thoải mái trong file cpp
namespace fs = std::filesystem;

// ====================== RESET BÀN CỜ ======================

void ResetData()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            _A[i][j].x = 4 * j + BOARD_LEFT + 2;
            _A[i][j].y = 2 * i + BOARD_TOP + 1;
            _A[i][j].c = 0;
        }
    }
    _TURN = true;   // true: lượt X đi, false: lượt O đi
    _COMMAND = -1;
    _X = _A[0][0].x;
    _Y = _A[0][0].y;
}

// ====================== CHUNG ======================

bool IsFullBoard()
{
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (_A[i][j].c == 0)
                return false;
    return true;
}

int CheckBoard(int pX, int pY)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0)
            {
                _A[i][j].c = _TURN ? -1 : 1;
                return _A[i][j].c;
            }
        }
    }
    return 0;
}

// ====================== LUẬT 1: TỰ DO (FREESTYLE) ======================
// >= 5 quân liên tiếp là thắng, không giới hạn 6

bool CheckWin_Freestyle()
{
    const int dx[4] = { 1, 0, 1, 1 };
    const int dy[4] = { 0, 1, 1, -1 };

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            int player = _A[i][j].c;
            if (player == 0) continue;

            for (int dir = 0; dir < 4; dir++)
            {
                int count = 1;
                int x = i + dx[dir];
                int y = j + dy[dir];

                // Đếm xuôi
                while (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && _A[x][y].c == player)
                {
                    count++;
                    x += dx[dir];
                    y += dy[dir];
                }

                // Đếm ngược
                x = i - dx[dir];
                y = j - dy[dir];
                while (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && _A[x][y].c == player)
                {
                    count++;
                    x -= dx[dir];
                    y -= dy[dir];
                }

                if (count >= 5)
                    return true;
            }
        }
    }
    return false;
}

int TestBoard_Freestyle()
{
    if (IsFullBoard())
        return 0;
    if (CheckWin_Freestyle())
        return _TURN ? -1 : 1;
    return 2;
}

// ====================== LUẬT 2: TIÊU CHUẨN (STANDARD) ======================
// Chỉ thắng nếu đúng 5 quân, >5 thì phạm luật

bool CheckWin_Standard()
{
    const int dx[4] = { 1, 0, 1, 1 };
    const int dy[4] = { 0, 1, 1, -1 };

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            int player = _A[i][j].c;
            if (player == 0) continue;

            for (int dir = 0; dir < 4; dir++)
            {
                int count = 1;
                int x = i + dx[dir];
                int y = j + dy[dir];

                // Đếm xuôi
                while (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && _A[x][y].c == player)
                {
                    count++;
                    x += dx[dir];
                    y += dy[dir];
                }

                // Đếm ngược
                x = i - dx[dir];
                y = j - dy[dir];
                while (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && _A[x][y].c == player)
                {
                    count++;
                    x -= dx[dir];
                    y -= dy[dir];
                }

                if (count == 5)
                    return true;
                if (count > 5)
                    continue;
            }
        }
    }
    return false;
}

int TestBoard_Standard()
{
    if (IsFullBoard())
        return 0;
    if (CheckWin_Standard())
        return _TURN ? -1 : 1;
    return 2;
}

// ====================== LUẬT 3: CHẶN 2 ĐẦU ======================

bool IsBlockedTwoEnds(int x, int y, int dx, int dy, int player)
{
    int count = 1;
    int i = x + dx, j = y + dy;

    // Đếm xuôi
    while (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && _A[i][j].c == player)
    {
        count++;
        i += dx;
        j += dy;
    }
    bool blocked1 = (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && _A[i][j].c == -player);

    // Đếm ngược
    i = x - dx;
    j = y - dy;
    while (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && _A[i][j].c == player)
    {
        count++;
        i -= dx;
        j -= dy;
    }
    bool blocked2 = (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && _A[i][j].c == -player);

    return (count >= 5 && !(blocked1 && blocked2)); // chỉ thắng nếu không bị chặn cả 2 đầu
}

bool CheckWin_BlockedTwoEnds()
{
    int player = _TURN ? -1 : 1;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (_A[i][j].c == player)
            {
                if (IsBlockedTwoEnds(i, j, 1, 0, player)) return true;
                if (IsBlockedTwoEnds(i, j, 0, 1, player)) return true;
                if (IsBlockedTwoEnds(i, j, 1, 1, player)) return true;
                if (IsBlockedTwoEnds(i, j, 1, -1, player)) return true;
            }
        }
    }
    return false;
}

int TestBoard_BlockedTwoEnds()
{
    if (IsFullBoard())
        return 0;
    if (CheckWin_BlockedTwoEnds())
        return _TURN ? -1 : 1;
    return 2;
}

int TestBoard(GameRule rule) {
    switch (rule) {
    case GameRule::FREESTYLE:
        return TestBoard_Freestyle();
    case GameRule::STANDARD:
        return TestBoard_Standard();
    case GameRule::BLOCKED_TWO_ENDS:
        return TestBoard_BlockedTwoEnds();
    default:
        return 2;  // Continue game
    }
}

// ====================== SAVE GAME ======================

// ====================== FILE SYSTEM (NEW) ======================

SaveInfo ParseSaveFile(const string& filePath) {
    SaveInfo info;
    info.isValid = false;
    info.fullPath = filePath;

    ifstream fin(filePath);
    if (!fin.is_open()) return info;

    info.isValid = true;

    // Lấy tên file
    fs::path p(filePath);
    info.filename = p.stem().string();

    string line;
    // Dòng 1: Thời gian
    if (getline(fin, line)) {
        if (line.size() > 15) {
            size_t timeStart = line.find(": ") + 2;
            info.time = line.substr(timeStart, 5);
            size_t dateStart = line.rfind(" ") + 1;
            info.date = line.substr(dateStart);
        }
    }

    // Dòng 2: Rule
    int ruleInt = 0;
    if (fin >> ruleInt) {
        GameRule r = static_cast<GameRule>(ruleInt);
        switch (r) {
        case GameRule::FREESTYLE: info.ruleName = L"Freestyle"; break;
        case GameRule::STANDARD:  info.ruleName = L"Standard"; break;
        case GameRule::BLOCKED_TWO_ENDS: info.ruleName = L"Block 2 Ends"; break;
        default: info.ruleName = L"Unknown"; break;
        }
    }
    fin.close();
    return info;
}
void ReadSaveInfo(SaveInfo& info) {
    ifstream fin(info.fullPath);
    if (!fin.is_open()) {
        info.ruleName = L"Error";
        return;
    }

    string line;
    // Đọc dòng 1: Thời gian lưu
    if (getline(fin, line)) {
        size_t pos = line.find(": ");
        if (pos != string::npos) {
            stringstream ss(line.substr(pos + 2));
            ss >> info.time >> info.date;
        }
    }

    // Đọc dòng 2: Luật chơi (số nguyên)
    int ruleInt = 0;
    if (fin >> ruleInt) {
        switch (ruleInt) {
        case 0:
            // Luật Tự Do
            info.ruleName = L"Lu\u1EADt T\u1EF1 Do";
            break;
        case 1:
            // Luật Tiêu Chuẩn
            info.ruleName = L"Lu\u1EADt Ti\u00EAu Chu\u1EA9n";
            break;
        case 2:
            // Luật Chặn 2 Đầu
            info.ruleName = L"Lu\u1EADt Ch\u1EB7n 2 \u0110\u1EA7u";
            break;
        default:
            info.ruleName = L"Unknown";
            break;
        }
    }
    fin.close();
}
std::vector<SaveInfo> GetListSaveFiles() {
    std::vector<SaveInfo> listSaves;
    std::string path = "Saves";

    // Tạo thư mục nếu chưa có (dùng filesystem C++17)
    if (!fs::exists(path)) {
        fs::create_directory(path);
        return listSaves;
    }

    // Duyệt qua các file trong thư mục Saves
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".sav") {
            SaveInfo info;
            info.fullPath = entry.path().string();
            info.filename = entry.path().filename().string();

            // Lấy tên file làm ngày giờ tạm (để tránh lỗi logic phức tạp)
            info.date = "Unknown";
            info.time = "Unknown";
            info.ruleName = L"Unknown";
            info.isValid = true;
            ReadSaveInfo(info);
            listSaves.push_back(info);
        }
    }
    return listSaves;
}

void SaveGame(const string& filename, GameRule rule, int result)
{
    string folder = "Saves";
    if (!fs::exists(folder)) {
        fs::create_directory(folder);
    }

    // Đảm bảo file nằm trong folder Saves nếu chưa có đường dẫn
    string path = filename;
    if (path.find("/") == string::npos && path.find("\\") == string::npos) {
        path = folder + "/" + filename;
    }

    // Tự động thêm đuôi .sav nếu chưa có
    if (path.find(".sav") == string::npos) {
        path += ".sav";
    }

    ofstream fout(path);
    if (!fout.is_open()) {
        return;
    }

    time_t now = time(nullptr);
    tm* ltm = localtime(&now);

    fout << "Thoi gian luu: " << put_time(ltm, "%H:%M:%S %d/%m/%Y") << "\n";
    fout << (int)rule << "\n";
    fout << _TURN << "\n";
    fout << result << "\n";

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (_A[i][j].c == -1) fout << 'X';
            else if (_A[i][j].c == 1) fout << 'O';
            else fout << '.';
        }
        fout << "\n";
    }

    fout.close();
}


// ====================== LOAD GAME ======================

bool LoadFromFile(int slot)
{
    string folder = "Saves";

    
    if (!fs::exists(folder)) {
        fs::create_directory(folder);
    }
    // -----------------------

    string filename = folder + "/save_slot_" + to_string(slot) + ".sav";
    ifstream fin(filename);
    if (!fin.is_open())
    {
       
        return false;
    }

    string header;
    getline(fin, header);

    int ruleInt = 0;
    int result = 2;
    fin >> ruleInt >> _TURN >> result;
    fin.ignore();

    GameRule rule = static_cast<GameRule>(ruleInt);

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        string line;
        getline(fin, line);
        for (int j = 0; j < BOARD_SIZE && j < (int)line.size(); j++)
        {
            if (line[j] == 'X') _A[i][j].c = -1;
            else if (line[j] == 'O') _A[i][j].c = 1;
            else _A[i][j].c = 0;
        }
    }

    fin.close();

    _rule = rule;
    _COMMAND = -1;

    cout << "Da load game tu slot " << slot << " (" << filename << ")\n";
    return true;
}
bool LoadFromFile(const std::string& filePath)
{
    std::ifstream fin(filePath);
    if (!fin.is_open()) return false;

    std::string header;
    std::getline(fin, header); // Bỏ qua dòng thời gian

    int ruleInt = 0;
    int result = 2;
    fin >> ruleInt >> _TURN >> result;
    fin.ignore(); // Bỏ qua ký tự xuống dòng

    GameRule rule = static_cast<GameRule>(ruleInt);

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        std::string line;
        std::getline(fin, line);
        for (int j = 0; j < BOARD_SIZE && j < (int)line.size(); j++)
        {
            if (line[j] == 'X') _A[i][j].c = -1;
            else if (line[j] == 'O') _A[i][j].c = 1;
            else _A[i][j].c = 0;
        }
    }

    fin.close();

    _rule = rule; // Biến _rule cần có trong Globals hoặc Model
    _COMMAND = -1;

    return true;
}
// ====================== (BOT) ======================

// Điểm ưu tiên: [0, 1 con, 2 con, 3 con, 4 con, 5 con]
// Tấn công mạnh hơn phòng thủ một chút để máy aggressive hơn
long AttackScore[7] = { 0, 9, 54, 162, 1458, 13122, 65000 };
long DefenseScore[7] = { 0, 3, 27, 99, 729, 6561, 59000 };

long EvaluatePosition(int row, int col) {
    long totalScore = 0;
    // 4 hướng: Ngang, Dọc, Chéo chính, Chéo phụ
    int dr[4] = { 0, 1, 1, 1 };
    int dc[4] = { 1, 0, 1, -1 };

    // Máy là O (1), Người là X (-1)
    for (int dir = 0; dir < 4; dir++) {
        // --- TÍNH ĐIỂM TẤN CÔNG (Cho quân O) ---
        int countAlly = 0;
        int countEnemy = 0;

        // Duyệt dương
        for (int k = 1; k <= 4; k++) {
            int r = row + dr[dir] * k;
            int c = col + dc[dir] * k;
            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE) {
                if (_A[r][c].c == 1) countAlly++;
                else if (_A[r][c].c == -1) { countEnemy++; break; }
                else break;
            }
            else break;
        }
        // Duyệt âm
        for (int k = 1; k <= 4; k++) {
            int r = row - dr[dir] * k;
            int c = col - dc[dir] * k;
            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE) {
                if (_A[r][c].c == 1) countAlly++;
                else if (_A[r][c].c == -1) { countEnemy++; break; }
                else break;
            }
            else break;
        }

        // Nếu bị chặn 2 đầu thì điểm tấn công = 0 (luật chặn 2 đầu hoặc để an toàn)
        if (countEnemy == 2) totalScore += 0;
        else totalScore += AttackScore[countAlly];

        // --- TÍNH ĐIỂM PHÒNG THỦ (Chặn quân X) ---
        countEnemy = 0;
        int blocked = 0;

        for (int k = 1; k <= 4; k++) {
            int r = row + dr[dir] * k;
            int c = col + dc[dir] * k;
            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE) {
                if (_A[r][c].c == -1) countEnemy++;
                else if (_A[r][c].c == 1) { blocked++; break; }
                else break;
            }
            else { blocked++; break; }
        }
        for (int k = 1; k <= 4; k++) {
            int r = row - dr[dir] * k;
            int c = col - dc[dir] * k;
            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE) {
                if (_A[r][c].c == -1) countEnemy++;
                else if (_A[r][c].c == 1) { blocked++; break; }
                else break;
            }
            else { blocked++; break; }
        }

        // Nếu địch chưa bị chặn hết thì cộng điểm phòng thủ
        if (blocked < 2) totalScore += DefenseScore[countEnemy];
    }
    return totalScore;
}

_POINT GetBotMove() {
    _POINT bestMove = { 0, 0, 0 };
    long maxScore = -1;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Chỉ tính điểm ô trống
            if (_A[i][j].c == 0) {
                long score = EvaluatePosition(i, j);
                if (score > maxScore) {
                    maxScore = score;
                    bestMove.x = i;
                    bestMove.y = j;
                }
            }
        }
    }
    return bestMove;
}

bool RenameSaveFile(const std::string& oldFilename, const std::string& newFilename) {
    std::string folder = "Saves/";
    // Đảm bảo đuôi .sav
    std::string oldPath = folder + oldFilename;
    if (oldPath.find(".sav") == std::string::npos) oldPath += ".sav";

    std::string newPath = folder + newFilename;
    if (newPath.find(".sav") == std::string::npos) newPath += ".sav";

    try {
        if (fs::exists(oldPath)) {
            fs::rename(oldPath, newPath);
            return true;
        }
    }
    catch (...) { return false; }
    return false;
}

bool DeleteSaveFile(const std::string& filename) {
    std::string folder = "Saves/";
    std::string path = folder + filename;
    if (path.find(".sav") == std::string::npos) path += ".sav";

    try {
        if (fs::exists(path)) {
            fs::remove(path);
            return true;
        }
    }
    catch (...) { return false; }
    return false;
}