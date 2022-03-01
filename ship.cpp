#include "ship.h"
#include "bot.h"
#include <windows.h>
const int N = 10;
class GameBoard;
void Ship::Create_random(GameBoard& gameBoard, int size_ship, int num_ships)
{
    _size = size_ship;
    _cells = new GameBoardCell[size_ship];
    // заполняем клетки в зависимости от начала координат корабля и его направления
    int x, y;
    int dir;
    int count_ship = 0;
    while (count_ship < num_ships) {
        x = rand() % N;
        y = rand() % N;

        int temp_x = x;
        int temp_y = y;

        bool setting_is_possible = true;
        dir = rand() % 4;
        for (int i = 0; i < size_ship; i++) {


            if (gameBoard.GetState(x, y) == Empty &&
                gameBoard.GetState(x, y + 1) != Deck &&
                gameBoard.GetState(x, y - 1) != Deck &&
                gameBoard.GetState(x + 1, y) != Deck &&
                gameBoard.GetState(x + 1, y + 1) != Deck &&
                gameBoard.GetState(x + 1, y - 1) != Deck &&
                gameBoard.GetState(x - 1, y) != Deck &&
                gameBoard.GetState(x - 1, y + 1) != Deck &&
                gameBoard.GetState(x - 1, y - 1) != Deck) {
                setting_is_possible = true;
            } else {
                setting_is_possible = false;
                break;
            }


            switch (dir) {
                case 0:
                    x++;
                    break;
                case 1:
                    y++;
                    break;
                case 2:
                    x--;
                    break;
                case 3:
                    y--;
                    break;
            }
        }

        if (setting_is_possible) {
            x = temp_x;
            y = temp_y;

            for (int i = 0; i < size_ship; i++) {
                _cells[i].SetX(x);
                _cells[i].SetY(y);
                gameBoard.SetState(x , y, Deck);
                switch (dir) {
                    case 0:
                        x++;
                        break;
                    case 1:
                        y++;
                        break;
                    case 2:
                        x--;
                        break;
                    case 3:
                        y--;
                        break;
                }
            }
            count_ship++;
        }

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

void Ship::Shoot_ship(GameBoard& gameBoard, int x, int y)
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
bool GameBoard::Shoot_function(int x, int y) {
    // просмотрим все корабли

    for (int i = 0; i < _shipsCount; i++){
        // проверим попадание
        if (_ships[i].TryHit(x, y)) {
            // если попадаем - стреляем по кораблю
            _ships[i].Shoot_ship(*this, x, y);
            return true;
            break;
        } else {
            // иначе засчитываем промах
            _cells[y][x].SetState(Miss);
            //после промаха игрока, должен появиться бот
           return false;
        }
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


Ship::~Ship()
{
    // очистим память, если она была выделена.
    if (_size)
        delete _cells;
}
void GameBoard::cls(HANDLE hConsole)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Scroll the rectangle of the entire buffer.
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    // Fill with empty spaces with the buffer's default text attribute.
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    // Move the cursor to the top left corner too.
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}