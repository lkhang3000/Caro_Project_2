#include "Control.h"
#include "Model.h"
#include "View.h"
#include "Globals.h"

void StartGame() {
    system("cls");
    ResetData();
    _currentRow = 0;  
    _currentCol = 0;
    _movesX = 0;
    _movesO = 0;
    _winsX = 0;   
    _winsO = 0; 
    _matchCount = 1;
    _playedResultSfx = false;
}

void ExitGame() {
    system("cls");
    //GabageCollect();
}

void MoveRight() {
    if (_currentCol < BOARD_SIZE - 1) {
        _currentCol++;
        // Cập nhật _X, _Y cho console compatibility
        _X = _A[_currentRow][_currentCol].x;
        _Y = _A[_currentRow][_currentCol].y;
    }
}

void MoveLeft() {
    if (_currentCol > 0) {
        _currentCol--;
        // Cập nhật _X, _Y cho console compatibility
        _X = _A[_currentRow][_currentCol].x;
        _Y = _A[_currentRow][_currentCol].y;
    }
}

void MoveDown() {
    if (_currentRow < BOARD_SIZE - 1) {
        _currentRow++;
        // Cập nhật _X, _Y cho console compatibility
        _X = _A[_currentRow][_currentCol].x;
        _Y = _A[_currentRow][_currentCol].y;
    }
}

void MoveUp() {
    if (_currentRow > 0) {
        _currentRow--;
        // Cập nhật _X, _Y cho console compatibility
        _X = _A[_currentRow][_currentCol].x;
        _Y = _A[_currentRow][_currentCol].y;
    }
}

// Thêm hàm để đặt quân cờ ở vị trí hiện tại
bool PlacePiece() {
    if (_A[_currentRow][_currentCol].c == 0) {  // Ô trống
        _A[_currentRow][_currentCol].c = _TURN ? -1 : 1;
        // increment move count for the player who moved
        if (_TURN) {
            ++_movesX;
        } else {
            ++_movesO;
        }
        return true;  // Đặt thành công
    }
    return false;  // Ô đã có quân
}
