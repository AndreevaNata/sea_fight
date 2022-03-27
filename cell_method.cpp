#include "cell_method.h"
using namespace std;

void GameBoardCell::setX(int x) { _x = x; }

void GameBoardCell::setY(int y) { _y = y; }

void GameBoardCell::setState(CellState state) { _state = state; }

CellState GameBoardCell::getState() { return _state; }

int GameBoardCell::getX() { return _x; }

int GameBoardCell::getY() { return _y; }

bool GameBoardCell::tryHit(int x, int y) {
    return (x == _x && y == _y && _state != HitDeck); }

