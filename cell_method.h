// класс - клетка игрового поля
#include <iostream>
#include "emun.h"
#include <windows.h>
#ifndef UNTITLED12_CELL_H
#define UNTITLED12_CELL_H
using namespace std;
class GameBoardCell {
private:
    int _x, _y;         // координаты клетки
    CellState _state;   // состояние клетки
public:
    GameBoardCell(int x = 0, int y = 0, CellState state = Empty) {
        _x = x;
        _y = y;
        _state = state;
    }

    void SetX(int x);

// функция устанавливает y-координату клети
    void SetY(int y);

// функция устанавливает состояние клети
    void SetState(CellState state);

// функция возвращает состояние текущей клетки
    CellState GetState();

// функция возвращает x текущей клетки
    int GetX();

// функция возвращает y текущей клетки
    int GetY();

// функция - проверка попадания в клетку
    bool TryHit(int x, int y);

    void Print()
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

    void PrintBot()
    {
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


};

#endif //UNTITLED12_CELL_H
