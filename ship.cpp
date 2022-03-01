#include "ship.h"
const int N = 10;
class GameBoard;
void Ship::Create_random(GameBoard& gameBoard, int size_ship, int num_ships)
{
    _size = size_ship;
    // заполняем клетки в зависимости от начала координат корабля и его направления
    int x, y;
    int dir;
    int count_ship = 0;
    while (count_ship < num_ships) {
        x = rand() % N;
        y = rand() % N;

        dir = rand() % 4;

        if (Create_ship(x, y, dir, "", size_ship, gameBoard)) {
            count_ship++;
        }
    }
}

bool Ship::Create_ship(int x, int y, int dir, string letter, int size_ship, GameBoard& gameBoard) {
    bool setting_is_possible = true;
    _cells = new GameBoardCell[size_ship];
    int _x, _y;
    _x = x;
    _y = y;
    for (int i = 0; i < size_ship; i++) {
        if (gameBoard.GetState(_x, _y) == Empty &&
            gameBoard.GetState(_x, _y + 1) != Deck &&
            gameBoard.GetState(_x, _y - 1) != Deck &&
            gameBoard.GetState(_x + 1, _y) != Deck &&
            gameBoard.GetState(_x + 1, _y + 1) != Deck &&
            gameBoard.GetState(_x + 1, _y - 1) != Deck &&
            gameBoard.GetState(_x - 1, _y) != Deck &&
            gameBoard.GetState(_x - 1, _y + 1) != Deck &&
            gameBoard.GetState(_x - 1, _y - 1) != Deck) {
            setting_is_possible = true;
        } else {
            setting_is_possible = false;
            cout << letter;
            break;
        }
        switch (dir) {
            case 0:
                _y--;
                break;
            case 1:
                _x++;
                break;
            case 2:
                _x--;
                break;
            case 3:
                _y++;
                break;
        }
    }
    if (setting_is_possible) {
        for (int i = 0; i < size_ship; i++) {
            _cells[i].SetX(x);
            _cells[i].SetY(y);
            gameBoard.SetState(x , y, Deck);
            switch (dir) {
                case 0:
                    y--;
                    break;
                case 1:
                    x++;
                    break;
                case 2:
                    x--;
                    break;
                case 3:
                    y++;
                    break;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

void Ship::Create_hand(GameBoard& gameBoard, int size, int x, int y, bool horizontal)
{
    _size = size;
    _cells = new GameBoardCell[size];
    // заполняем клетки в зависимости от начала координат корябля и его направления
    for (int i = 0; i < size; i++)
    {
        if (horizontal) {
            _cells[i].SetX(x + i);
            _cells[i].SetY(y);
            gameBoard.SetState(x + i, y, Deck);
        } else {
            _cells[i].SetX(x);
            _cells[i].SetY(y + i);
            gameBoard.SetState(x, y + i, Deck);
        }
    }
}
bool Ship::TryHit(int x, int y)
{
    for (int i = 0; i < _size; i++)
        if (_cells[i].TryHit(x, y))
            return true;
    return false;
}


ShipState Ship::GetState()
{
    // считаем число попаданий
    int hitCount = 0;
    for (int i = 0; i < _size; i++)
        if (_cells[i].GetState() == HitDeck)
            hitCount++;

    // сверяем число попаданий с числом палуб
    if (hitCount == 0)  // если не попали - корабль цел
        _state = Safe;
    else if (hitCount < _size)  // если попали но меньше раз, чем число палуб, то ранен
        _state = ShipHit;
    else
        _state = Destroyed; // иначе уничтожен

    return _state;
}

void Ship::Shoot(GameBoard& gameBoard, int x, int y)
{
    for (int i = 0; i < _size; i++)
        if (_cells[i].TryHit(x, y))
        {
            _cells[i].SetState(HitDeck);
            gameBoard.SetState(x, y, HitDeck);
            break;
        }
    if (GetState() == Destroyed)
    {
        for (int i = 0; i < _size; i++)
        {
            int localX = _cells[i].GetX();
            int localY = _cells[i].GetY();
            if (localX - 1 >= 0 && localY - 1 >= 0 && !gameBoard.IsDeck(localX - 1, localY - 1))
                gameBoard.SetState(localX - 1, localY - 1, Miss);
            if (localX - 1 >= 0 && !gameBoard.IsDeck(localX - 1, localY))
                gameBoard.SetState(localX - 1, localY, Miss);
            if (localX - 1 >= 0 && localY + 1 < gameBoard.GetSize() && !gameBoard.IsDeck(localX - 1, localY + 1))
                gameBoard.SetState(localX - 1, localY + 1, Miss);

            if (localY - 1 >= 0 && !gameBoard.IsDeck(localX, localY - 1))
                gameBoard.SetState(localX, localY - 1, Miss);
            if (localY + 1 < gameBoard.GetSize() && !gameBoard.IsDeck(localX, localY + 1))
                gameBoard.SetState(localX, localY + 1, Miss);

            if (localX + 1 < gameBoard.GetSize() && localY - 1 >= 0 && !gameBoard.IsDeck(localX + 1, localY - 1))
                gameBoard.SetState(localX + 1, localY - 1, Miss);
            if (localX + 1 < gameBoard.GetSize() && !gameBoard.IsDeck(localX + 1, localY))
                gameBoard.SetState(localX + 1, localY, Miss);
            if (localX + 1 < gameBoard.GetSize() && localY + 1 < gameBoard.GetSize() && !gameBoard.IsDeck(localX + 1, localY + 1))
                gameBoard.SetState(localX + 1, _cells[i].GetY() + 1, Miss);
        }
    }
}
void GameBoard::Shoot(int x, int y)
{
    // просмотрим все корабли
    for (int i = 0; i < _shipsCount; i++)
        // проверим попадание
        if (_ships[i].TryHit(x, y))
        {
            // если попадаем - стреляем по кораблю
            _ships[i].Shoot(*this, x, y);
            break;
        }
        else
        {
            // иначе засчитываем промах
            _cells[y][x].SetState(Miss);
        }
}

bool GameBoard::AllShipsDestroyed()
{
    // обход всех кораблей
    for (int i = 0; i < _shipsCount; i++)
        // если хотя бы один не уничтожен, вернем false
        if (_ships[i].GetState() != Destroyed)
            return false;
    return true;    // иначе true
}

void Ship::Entry(int &x, int &y, const string& letter, int &pos, int n, int size_ship, GameBoard& gameBoard) {
    Ship ship;
    char fx;
    bool run = true;
    while (run) {
        run = false;
        //если нужно ввести 3 элемента (x, y, position)
        if (n == 3) {
            cin >> fx >> y >> pos;
            while (cin.fail() or (pos!=0 and pos!=1)) {
                cin.clear();
                cin.ignore(32767, '\n');
                cout << letter;
                cin >> fx >> y >> pos;
            }
        }
        else { cin >> fx >> y; }
        switch (fx) {
            case ('a'): { x = 0; break; }
            case ('b'): { x = 1; break; }
            case ('c'): { x = 2; break; }
            case ('d'): { x = 3; break; }
            case ('e'): { x = 4; break; }
            case ('f'): { x = 5; break; }
            case ('g'): { x = 6; break; }
            case ('h'): { x = 7; break; }
            case ('i'): { x = 8; break; }
            case ('j'): { x = 9; break; }
            default: { cout << letter; run = true; }
        }
        if (((y < 1 || y > 10) && !run) or cin.fail()) {
            cout << letter; run = true; }

        --y;
        if (n==3) {
            if(!(ship.Ship::Create_ship(x,y,pos,letter,size_ship,gameBoard))) {
                cout << letter; run = true;
            }
        }
    }
        cin.clear();
        cin.ignore(32767, '\n');
}


Ship::~Ship()
{
    // очистим память, если она была выделена.
    if (_size)
        delete _cells;
}