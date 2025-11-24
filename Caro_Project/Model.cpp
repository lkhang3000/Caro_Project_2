#include "Model.h"

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

void SaveGame(const string& filename, GameRule rule, int result)
{
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Không thể mở file để lưu!\n";
        return;
    }

    time_t now = time(nullptr);
    tm* ltm = localtime(&now);

    fout << "Thời gian lưu: " << put_time(ltm, "%H:%M:%S %d/%m/%Y") << "\n";
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
    cout << "Đã lưu game vào: " << filename << "\n";
}

// ====================== LOAD GAME ======================

bool LoadFromFile(int slot)
{
    string folder = "Saves";

#ifdef _WIN32
    _mkdir(folder.c_str());
#else
    mkdir(folder.c_str(), 0755);
#endif

    string filename = folder + "/save_slot_" + to_string(slot) + ".sav";
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cerr << "Không tìm thấy file lưu: " << filename << "\n";
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

    cout << "Đã load game từ slot " << slot << " (" << filename << ")\n";
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
