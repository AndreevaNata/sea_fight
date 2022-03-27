#include <iostream>
#include "emun.h"
#include "cell_method.h"
#include <list>
// класс - корабль
#ifndef UNTITLED12_SHIP_H
#define UNTITLED12_SHIP_H
class GameBoard;
class Ship
{
private:
    GameBoardCell* _cells;

private:
    // клетки корабля
    ShipState _state;   // состояние корабля
    int _size;
public:
    Ship()
    {
        _cells = NULL;
        _size = 0;
    }
    void createRandom(GameBoard& gameBoard, int size_ship);

    bool createShip(int x, int y, int dir, int size_ship, GameBoard& gameBoard);
    void entry(GameBoard& gameBoard, int &x, int &y, const string& letter, int pos, int n, int size_ship);

    // функция возвращает состояние корабля, выполнив проверку целостности всех палуб
    ShipState getState();
    GameBoardCell *getCells();

    // функция выстрела по кораблю, возвращает состояние корабля, после выстрела
    bool shootShip(GameBoard& gameBoard, int x, int y);

    bool tryHit(int x, int y);
    ~Ship();
};

// класс - игровое поле
class GameBoard {
private:
    static const int _size = 10;            // размер игрового поля
    static const int _4DeckShipCount = 1;   // число 4-х палубных
    static const int _3DeckShipCount = 2;   // число 3-х палубных
    static const int _2DeckShipCount = 3;   // число 2-х палубных
    static const int _1DeckShipCount = 4;   // число 1-х палубных
    static const int _shipsCount = _4DeckShipCount + _3DeckShipCount + _2DeckShipCount + _1DeckShipCount;   // число кораблей
    GameBoardCell _cells[_size][_size]; // клетки игрового поля
    Ship _ships[_shipsCount];   // корабли
    LevelOfComplexity _levelOfComplexity = Easy;

public:

    LevelOfComplexity getLevelOfComplexity() const;

    void setLevelOfComplexity(LevelOfComplexity levelOfComplexity);

    // функция создание игрового поля

    void Generate();
    void GenerateBot();

    ~GameBoard() { }


    // функция установки статуса клетки игрового поля
    void setState(int x, int y, CellState state)
    { _cells[y][x].setState(state); }



    CellState getState(int x, int y)
    { if (x >= 0 && y >= 0 && x < _size && y < _size)
            return _cells[y][x].getState();
        else
            return OutOfBoard;
    }

    // функция возвращает, является ли клетка палубой
    bool isDeck(int x, int y)
    { return _cells[y][x].getState() == Deck || _cells[y][x].getState() == HitDeck; }

    // функция печати игрового поля
    void print();
    void printBot();
//    void cls(HANDLE hConsole);
    // функция возвращает число клеток игровой области

    // функция возвращает размер игровой области
    int getSize()
    { return _size; }

    // функция возвращает координаты клетки safe корабля
    GameBoardCell getSafeCell(GameBoard& gameBoard, GameBoardCell& cell);

    // функция - выстрел в игровое поле
    int shootFunction(GameBoard& gameBoard, int x, int y);

    // функция проверки - уничтожены ли все корабли на поле
    bool allShipsDestroyed();
    list<int> shipsDestroyed();

    static void remain(list<int>list);

};



#endif //UNTITLED12_SHIP_H
