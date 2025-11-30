#pragma once
#ifndef Model_h
#define Model_h

#include "Globals.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>


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

// Thêm std:: trước string
bool LoadFromFile(const std::string& filePath);

// Thêm std:: trước string
void SaveGame(const std::string& filename, GameRule rule, int result);
bool RenameSaveFile(const std::string& oldFilename, const std::string& newFilename);
bool DeleteSaveFile(const std::string& filename);

// =============================PvE========================================
struct SaveInfo {
    std::string filename; // Tên file hiển thị (ví dụ: duyio)
    std::string fullPath; // Đường dẫn đầy đủ (Saves/duyio.sav)
    std::string date;
    std::string time;
    std::wstring ruleName;
    bool isValid = false; // <--- Đã khởi tạo để tránh lỗi
};

// Thêm std:: trước vector
std::vector<SaveInfo> GetListSaveFiles();

_POINT GetBotMove();

extern GameRule _rule;

#endif