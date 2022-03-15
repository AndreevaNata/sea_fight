#include "cell_method.h"
using namespace std;

void GameBoardCell::SetX(int x) { _x = x; }

void GameBoardCell::SetY(int y) { _y = y; }

void GameBoardCell::SetState(CellState state) { _state = state; }

CellState GameBoardCell::GetState() { return _state; }

int GameBoardCell::GetX() { return _x; }

int GameBoardCell::GetY() { return _y; }

void GameBoardCell::SetColor(int text) {
    if (text == 4)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    }
    else{
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)((text)));
    }

}

bool GameBoardCell::TryHit(int x, int y) {
    return (x == _x && y == _y && _state != HitDeck); }

void GameBoardCell::Print()
{
    if (_state == Empty)
        cout << ' ';
    else if (_state == HitDeck){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        std::cout<<'x';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
        //std::cout<< color('x',4) <<'x'<<std::color;
    }

    else if (_state == Deck){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
        cout << 'd';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
    }

    else
        cout << '*';
}

void GameBoardCell::PrintBot() {
    if (_state == Empty)
        cout << ' ';
    else if (_state == HitDeck){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
        std::cout<<'x';
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

    }

    else if (_state == Deck)
        cout << ' ';
    else
        cout << '*';
}
