#include <iostream>
#include "emun.h"
#include "cell_method.h"

// класс - корабль
#ifndef UNTITLED12_SHIP_H
#define UNTITLED12_SHIP_H
class GameBoard;
class Ship
{
private:
    GameBoardCell* _cells;  // клетки корабля
    ShipState _state;   // состояние корабля
    int _size;
public:
    Ship()
    {
        _cells = NULL;
        _size = 0;
    }
    void Create_random(GameBoard& gameBoard, int size_ship, int num_ships);
    void Create_hand(GameBoard& gameBoard, int size, int x, int y, bool horizontal);
    ~Ship();

    // функция возвращает состояние корабля, выполнив проверку целостности всех палуб
    ShipState GetState();

    // функция выстрела по кораблю, возвращает состояние корабля, после выстрела
    void Shoot(GameBoard& gameBoard, int x, int y);

    bool TryHit(int x, int y);
};

// класс - игровое поле
class GameBoard {
private:
    static const int _size = 10;            // размер игорового поля
    static const int _4DeckShipCount = 1;   // число 4-х палубных
    static const int _3DeckShipCount = 2;   // число 3-х палубных
    static const int _2DeckShipCount = 3;   // число 2-х палубных
    static const int _1DeckShipCount = 4;   // число 1-х палубных
    static const int _shipsCount = _4DeckShipCount + _3DeckShipCount + _2DeckShipCount + _1DeckShipCount;   // число кораблей
    GameBoardCell _cells[_size][_size]; // клетки игрового поля
    Ship _ships[_shipsCount];   // корабли

    // функция создание игрового поля
    void Generate();
public:
    GameBoard()
    { Generate(); }

    ~GameBoard() { }

    // функция установки статуса клетки игрового поля
    void SetState(int x, int y, CellState state)
    { _cells[y][x].SetState(state); }

    // функция возвращает, является ли клетка палубой
    bool IsDeck(int x, int y)
    { return _cells[y][x].GetState() == Deck || _cells[y][x].GetState() == HitDeck; }

    // функция печати игрового поля
    void Print();

    // функция возвращает число клеток игровой области
    int GetCount()
    { return _size * _size; }

    // функция возвращает размер игровой области
    int GetSize()
    { return _size; }

    // функция - выстрел в игровое поле
    void Shoot(int x, int y);

    // функция проверки - уничтожены ли все корабли на поле
    bool AllShipsDestroyed();
};


#endif //UNTITLED12_SHIP_H
