#include "Model.h"
#include "Globals.h"

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
