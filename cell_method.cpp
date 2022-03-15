#include "cell_method.h"
using namespace std;

void GameBoardCell::SetX(int x) { _x = x; }

void GameBoardCell::SetY(int y) { _y = y; }

void GameBoardCell::SetState(CellState state) { _state = state; }

CellState GameBoardCell::GetState() { return _state; }

int GameBoardCell::GetX() { return _x; }

int GameBoardCell::GetY() { return _y; }

bool GameBoardCell::TryHit(int x, int y) {
    return (x == _x && y == _y && _state != HitDeck); }

