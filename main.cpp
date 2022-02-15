//Создать иерархию классов и запрограммировать компьютерную игру “Морской бой”. Игровое поле разбивается на клетки. Палуба корабля занимает одну клетку. Кораблем считается совокупность смежных клеток. Допускаются четыре категории кораблей: одно-, двух-, трех- и четырехпалубные. Двух-, трех- и четырехпалубные корабли могут иметь всевозможные конфигурации и ориентации на игровом поле. Не допускается размещение кораблей в смежных клетках.
#include<iostream>
#include "emun.h"
#include "cell_method.h"
#include "ship.h"
#include <ctime>
using namespace std;
// заранее объявим, чтобы можно было указывать в качестве аргумент функций класса Ship
class GameBoard;

// ВАУ НАТАША

int main(int argc, char** argv)
{
    srand(time(0));
    GameBoard gameBoard;
    gameBoard.Print();
    do {
        cout << "Enter x and y coord: X_Y: " << endl;
        int x;
        int y;
        cin >> x >> y;
        --x;
        --y;
        gameBoard.Shoot(x, y);
        gameBoard.Print();
    } while (!gameBoard.AllShipsDestroyed());
    return 0;
}

void GameBoard::Generate()
{
    // заполняем игровое поле пустыми клетками
    for (int i = 0; i < _size; i++)
        for (int j = 0; j < _size; j++)
            _cells[i][j].SetState(Empty);
    int idx = 0;
    cout << "How do you want to set up the ships?" << endl;
    cout << "Enter 0 (on your own) or 1 (random): ";
    short nm;
    cin >> nm;
    cout << endl;
    if (nm == 0) {
        cout << "Enter x, y and position (if horizontal - 1, else - 0): X_Y_Position" << endl;
        int x, y;
        bool pos;
        for (int i = 0; i < _4DeckShipCount; i++) {
            cout << "4 deck ship (quantity " << _4DeckShipCount-i << "): ";
            cin >> x >> y >> pos;
            _ships[idx++].Create_hand(*this, 4, --x, --y, pos);
            Print();
            cout << endl;
        }
        for (int i = 0; i < _3DeckShipCount; i++) {
            cout << "3 deck ship (quantity " << _3DeckShipCount-i << "): ";
            cin >> x >> y >> pos;
            _ships[idx++].Create_hand(*this, 3, --x, --y, pos);
            Print();
            cout << endl;
        }
        for (int i = 0; i < _2DeckShipCount; i++) {
            cout << "2 deck ship (quantity " << _2DeckShipCount-i << "): ";
            cin >> x >> y >> pos;
            _ships[idx++].Create_hand(*this, 2, --x, --y, pos);
            Print();
            cout << endl;
        }
        for (int i = 0; i < _1DeckShipCount; i++) {
            cout << "1 deck ship (quantity " << _1DeckShipCount-i << "): ";
            cin >> x >> y >> pos;
            _ships[idx++].Create_hand(*this, 1, --x, --y, pos);
            Print();
            cout << endl;
        }
        cout << "Game starts!" << endl;
    }
    else{
        // заполняем игровое поле пустыми клетками
        for (int i = 0; i < _size; i++)
            for (int j = 0; j < _size; j++)
                _cells[i][j].SetState(Empty);
        // расставяем 4-х палубные
        _ships[idx++].Create_random(*this, 4, 1);
        // расставяем 3-х палубные
        _ships[idx++].Create_random(*this, 3, 2);

        // расставяем 2-х палубные
        _ships[idx++].Create_random(*this, 2, 3);

        // расставяем 1-х палубные
        _ships[idx++].Create_random(*this, 1, 4);
    }

}

void GameBoard::Print()
{
    cout<< "Player's bord"<<endl;
    for (int i = 0; i < _size; i++)
    {
        cout << "|";
        for (int j = 0; j < _size; j++)
        {
            _cells[i][j].Print();
            cout << "|";
        }
        cout << endl;
    }
    cout<< "Opponent's bord"<<endl;
    for (int i = 0; i < _size; i++)
    {
        cout << "|";
        for (int j = 0; j < _size; j++)
        {
            _cells[i][j].Opponent();
            cout << "|";
        }
        cout << endl;
    }
}


