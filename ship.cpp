#include "ship.h"
#include "bot.h"
#include <list>
const int N = 10;
class GameBoard;
void Ship::createRandom(GameBoard& gameBoard, int size_ship)
{
    _size = size_ship;
    // заполняем клетки в зависимости от начала координат корабля и его направления
    int x, y;
    int dir;
    int count_ship = 0;
    while (count_ship != 1) {
        x = rand() % N;
        y = rand() % N;

        dir = rand() % 4;

        if (createShip(x, y, dir, size_ship, gameBoard)) {
            count_ship++;
        }
    }
}

bool Ship::createShip(int x, int y, int dir, int size_ship, GameBoard& gameBoard) {
    bool setting_is_possible = true;
    _size = size_ship;
    _cells = new GameBoardCell[_size];
    int _x, _y;
    _x = x;
    _y = y;
    for (int i = 0; i < _size; i++) {
        if (gameBoard.getState(_x, _y) == Empty &&
                gameBoard.getState(_x, _y + 1) != Deck &&
                gameBoard.getState(_x, _y - 1) != Deck &&
                gameBoard.getState(_x + 1, _y) != Deck &&
                gameBoard.getState(_x + 1, _y + 1) != Deck &&
                gameBoard.getState(_x + 1, _y - 1) != Deck &&
                gameBoard.getState(_x - 1, _y) != Deck &&
                gameBoard.getState(_x - 1, _y + 1) != Deck &&
                gameBoard.getState(_x - 1, _y - 1) != Deck)
        { setting_is_possible = true;
        } else {
            setting_is_possible = false;
            break;
        }
        switch (dir) {
            case 0:
                _y++;
                break;
            case 1:
                _x++;
                break;
            case 2:
                _x--;
                break;
            case 3:
                _y--;
                break;
        }
    }
    if (setting_is_possible) {
        for (int i = 0; i < _size; i++) {
            _cells[i].setX(x);
            _cells[i].setY(y);
            gameBoard.setState(x, y, Deck);
            switch (dir) {
                case 0:
                    y++;
                    break;
                case 1:
                    x++;
                    break;
                case 2:
                    x--;
                    break;
                case 3:
                    y--;
                    break;
            }
        }
        return true;
    }
    else {
        return false;
    }
}
 bool Ship::tryHit(int x, int y)
{
    for (int i = 0; i < _size; i++)
        if (_cells[i].tryHit(x, y))
            return true;
    return false;
}


ShipState Ship::getState()
{
    // считаем число попаданий
    int hitCount = 0;
    for (int i = 0; i < _size; i++)
        if (_cells[i].getState() == HitDeck)
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

GameBoardCell *Ship::getCells() {
    return _cells;
}

bool Ship::shootShip(GameBoard& gameBoard, int x, int y)
{
    for (int i = 0; i < _size; i++)
        if (_cells[i].tryHit(x, y))
        {
            _cells[i].setState(HitDeck);
            gameBoard.setState(x, y, HitDeck);



        }
    if (getState() == Destroyed)
    {
        for (int i = 0; i < _size; i++)
        {
            int localX = _cells[i].getX();
            int localY = _cells[i].getY();
            if (localX - 1 >= 0 && localY - 1 >= 0 && !gameBoard.isDeck(localX - 1, localY - 1))
                gameBoard.setState(localX - 1, localY - 1, Miss);
            if (localX - 1 >= 0 && !gameBoard.isDeck(localX - 1, localY))
                gameBoard.setState(localX - 1, localY, Miss);
            if (localX - 1 >= 0 && localY + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX - 1, localY + 1))
                gameBoard.setState(localX - 1, localY + 1, Miss);

            if (localY - 1 >= 0 && !gameBoard.isDeck(localX, localY - 1))
                gameBoard.setState(localX, localY - 1, Miss);
            if (localY + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX, localY + 1))
                gameBoard.setState(localX, localY + 1, Miss);

            if (localX + 1 < gameBoard.getSize() && localY - 1 >= 0 && !gameBoard.isDeck(localX + 1, localY - 1))
                gameBoard.setState(localX + 1, localY - 1, Miss);
            if (localX + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX + 1, localY))
                gameBoard.setState(localX + 1, localY, Miss);
            if (localX + 1 < gameBoard.getSize() && localY + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX + 1,
                                                                                                          localY + 1))
                gameBoard.setState(localX + 1, _cells[i].getY() + 1, Miss);
        }
        return true;
    }
    return false;

}
int GameBoard::shootFunction(GameBoard& gameBoard, int x, int y) {
    // просмотрим все корабли
    int flag = 0;
    for (int i = 0; i < _shipsCount; i++) {
        // проверим попадание
        if (_ships[i].tryHit(x, y)) {
            // если попадаем - стреляем по кораблю
            if(!_ships[i].shootShip(*this, x, y))
                flag = 1;
            else flag = 2;
            break;
        }

}
    if (flag == 1) return 1;
    else if (flag == 2) return 3;
    else if (gameBoard.getState(x, y) == Empty) { _cells[y][x].setState(Miss); return 0;}
    else return 2;




}

bool GameBoard::allShipsDestroyed()
{
    // обход всех кораблей
    for (int i = 0; i < _shipsCount; i++)
        // если хотя бы один не уничтожен, вернем false
        if (_ships[i].getState() != Destroyed) {

            return false;
        }
    return true;    // иначе true
}

list<int> GameBoard::shipsDestroyed()
{
    list<int> list;
    // обход всех кораблей
    for (int i = 0; i < _shipsCount; i++)
        // если хотя бы один не уничтожен, вернем false
        if (_ships[i].getState() != Destroyed) {
            list.push_back(i);

        }
    return list;    // иначе true
}

GameBoardCell GameBoard::getSafeCell(GameBoard& gameBoard) {
    GameBoardCell cell;
    bool check = false;
    for (Ship ship : _ships) {
        if (ship.getState() == Safe) {
            check = true;
            cell = ship.getCells()[0];
        }
    }
    if (!check) {
        cell.setX(-1);
        cell.setY(-1);
    }
    return cell;
}

LevelOfComplexity GameBoard::getLevelOfComplexity() const {
    return levelOfComplexity;
}

void GameBoard::setLevelOfComplexity(LevelOfComplexity levelOfComplexity) {
    GameBoard::levelOfComplexity = levelOfComplexity;
}


void Ship::entry(GameBoard& gameBoard, int &x, int &y, const string& letter, int pos, int n, int size_ship) {
    _size = size_ship;
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
            default: { cout << letter; run = true;
                cin.clear();
                cin.ignore(32767, '\n');
                continue; }
        }
        if (((y < 1 || y > 10) && !run) or cin.fail()) {
            cout << letter; run = true;
            cin.clear();
            cin.ignore(32767, '\n');
            continue; }

        --y;
        if (n==3) {
            if(!(createShip(x, y, pos, size_ship, gameBoard))) {
                cout << letter; run = true;
            }
        }
        cin.clear();
        cin.ignore(32767, '\n');
    }
}


Ship::~Ship()
{
    // очистим память, если она была выделена.
    if (_size)
        delete _cells;
}

//void GameBoard::cls(HANDLE hConsole)
//{
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    SMALL_RECT scrollRect;
//    COORD scrollTarget;
//    CHAR_INFO fill;
//
//    // Get the number of character cells in the current buffer.
//    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
//    {
//        return;
//    }
//
//    // Scroll the rectangle of the entire buffer.
//    scrollRect.Left = 0;
//    scrollRect.Top = 0;
//    scrollRect.Right = csbi.dwSize.X;
//    scrollRect.Bottom = csbi.dwSize.Y;
//
//    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
//    scrollTarget.X = 0;
//    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);
//
//    // Fill with empty spaces with the buffer's default text attribute.
//    fill.Char.UnicodeChar = TEXT(' ');
//    fill.Attributes = csbi.wAttributes;
//
//    // Do the scroll
//    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);
//
//    // Move the cursor to the top left corner too.
//    csbi.dwCursorPosition.X = 0;
//    csbi.dwCursorPosition.Y = 0;
//
//    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
//}