#include "Globals.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>

#ifdef _WIN32
#include <direct.h> // để dùng _mkdir
#pragma warning(disable : 4996) // Tắt cảnh báo localtime
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#pragma execution_character_set("utf-8")
using namespace std;

// ====================== CẤU TRÚC CHUNG ======================

// Reset bàn cờ, gán lại tọa độ và giá trị mặc định
void ResetData();

// Kiểm tra bàn cờ đã đầy chưa (hòa)
bool IsFullBoard();

// Đánh dấu lượt đi tại vị trí (pX, pY)
int CheckBoard(int pX, int pY);

// ====================== LUẬT 1: TỰ DO (FREESTYLE) ======================
// ≥ 5 quân liên tiếp là thắng (không giới hạn 6)
bool CheckWin_Freestyle();
int TestBoard_Freestyle();

// ====================== LUẬT 2: TIÊU CHUẨN (STANDARD) ======================
// Thắng nếu đúng 5 quân, >5 thì phạm luật
bool CheckWin_Standard();
int TestBoard_Standard();

// ====================== LUẬT 3: CHẶN 2 ĐẦU (BLOCKED TWO ENDS) ======================
// ≥5 quân liên tiếp và không bị chặn cả 2 đầu
bool IsBlockedTwoEnds(int x, int y, int dx, int dy, int player);
bool CheckWin_BlockedTwoEnds();
int TestBoard_BlockedTwoEnds();

// ====================== ENUM CHỌN LUẬT (TÙY CHỌN) ======================
enum class GameRule
{
    FREESTYLE,       // Luật tự do
    STANDARD,        // Luật tiêu chuẩn
    BLOCKED_TWO_ENDS // Luật chặn 2 đầu
};

// Hàm tổng hợp kiểm tra kết quả theo luật (nếu muốn gọi chung)
int TestBoard(GameRule rule);

// ====================== LƯU & TẢI GAME ======================
bool LoadFromFile(int slot);
void SaveGame(const std::string& filename, GameRule rule, int result);
// =============================PvE========================================
_POINT GetBotMove();

extern GameRule _rule;

