// класс - клетка игрового поля
#include <iostream>
#include "emun.h"
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
    void SetX(int x)
    { _x = x; }

// функция устанавливает y-координату клети
    void SetY(int y)
    { _y = y; }

// функция устанавливает состояние клети
    void SetState(CellState state)
    { _state = state; }

// функция возвращает состояние текущей клетки
    CellState GetState()
    { return _state; }

// функция возвращает x текущей клетки
    int GetX()
    { return _x; }

// функция возвращает y текущей клетки
    int GetY()
    { return _y; }
    bool Cell(int x, int y)
    { return x == _x && y == _y && _state != Deck; }

// функция - проверка попадания в клетку
    bool TryHit(int x, int y)
    { return x == _x && y == _y && _state != HitDeck; }
    void Print()
    {
        if (_state == Empty)
            cout << ' ';
        else if (_state == HitDeck)
            cout << 'x';
        else if (_state == Deck)
            cout << 'd';
        else
            cout << '*';
    }

    void PrintBot()
    {
        if (_state == Empty)
            cout << ' ';
        else if (_state == HitDeck)
            cout << 'x';
        else if (_state == Deck)
            cout << ' ';
        else
            cout << '*';
    }


};

#endif //UNTITLED12_CELL_H
