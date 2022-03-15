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

    void Print();

    void PrintBot();


};

#endif //UNTITLED12_CELL_H
