//Создать иерархию классов и запрограммировать компьютерную игру “Морской бой”. Игровое поле разбивается на клетки. Палуба корабля занимает одну клетку. Кораблем считается совокупность смежных клеток. Допускаются четыре категории кораблей: одно-, двух-, трех- и четырехпалубные. Двух-, трех- и четырехпалубные корабли могут иметь всевозможные конфигурации и ориентации на игровом поле. Не допускается размещение кораблей в смежных клетках.
#include<iostream>
#include "emun.h"
#include "cell_method.h"
#include "ship.h"
#include <ctime>
#include "bot.h"
using namespace std;
// заранее объявим, чтобы можно было указывать в качестве аргумент функций класса Ship
class GameBoard;

const int N = 10;
int main(int argc, char** argv)
{   int natasha = 10;
    srand(time(0));
    GameBoard Player;
    GameBoard Bot;
    Player.Generate();
    Player.Print();
    Bot.GenerateBot();
    Bot.PrintBot();
    int Direction = -1;
    bool step = true;
    bool BotHit = false;
    bool BotHitForSecondBotHit = false;
    bool SecondBotHit = false;
    bool BotMiss[4] = {false, false, false, false};
    int x = 0,y = 0;
    int Botx = 0, Boty = 0, botx = 0,boty = 0;
    do {
        if (step == true) {
            cout << "\nYour step..." << endl;
            cout << "Enter x and y coord: X_Y: " << endl;
            char fx;

            bool run = true;
            while (run) {
                run = false;
                cin >> fx >> y;
                switch (fx) {
                    case ('a'): {
                        x = 0;
                        break;
                    }
                    case ('b'): {
                        x = 1;
                        break;
                    }
                    case ('c'): {
                        x = 2;
                        break;
                    }
                    case ('d'): {
                        x = 3;
                        break;
                    }
                    case ('e'): {
                        x = 4;
                        break;
                    }
                    case ('f'): {
                        x = 5;
                        break;
                    }
                    case ('g'): {
                        x = 6;
                        break;
                    }
                    case ('h'): {
                        x = 7;
                        break;
                    }
                    case ('i'): {
                        x = 8;
                        break;
                    }
                    case ('j'): {
                        x = 9;
                        break;
                    }
                    default: {
                        cout
                                << "This letter is not permitted. Choose X from: |a b c d e f g h i j| and Y from: |1 2 3 4 5 6 7 8 9 10| - ";
                        run = true;
                    }
                }
                if ((y < 1 || y > 10) && !run) {
                    cout
                            << "This letter is not permitted. Choose X from: |a b c d e f g h i j| and Y from: |1 2 3 4 5 6 7 8 9 10| - ";
                    run = true;
                }
            }
            --y;

            if (!Bot.Shoot_function(x, y)){//стреляем в поле бота
                step = false;
                Player.Print();
                Bot.PrintBot();
                cout << "\nYou missed!" << endl;}
            else  {
                Player.Print();
                Bot.PrintBot();
                cout << "\nYou hit bot's ship\a" << endl;
            }

        } else {

            cout << "\nStep Bot...\n"<< endl;
            if (BotHit == true){

                if (SecondBotHit == false){
                    while (true){
                        Botx = botx;
                        Boty = boty;
                        Direction = 1+rand() % 4;
                        if (Direction == 1 && BotMiss[0] == false && Boty-1 >= 0){
                            Boty--; //Стреляет левее
                            BotMiss[0] == true;
                            break;
                        }
                        else if (Direction == 2 && BotMiss[1] == false && Botx-1 >= 0){
                            Botx--; //Стреляет выше
                            BotMiss[1] == true;
                            break;
                        }
                        else if (Direction == 3 && BotMiss[2] == false && Boty+1 <= 9){
                            Boty++; //Стреляет правее
                            BotMiss[2] == true;
                            break;
                        }
                        else if (Direction == 4 && BotMiss[3] == false && Botx+1 <= 9){
                            Botx++; //Стреляет ниже
                            BotMiss[3] == true;
                            break;
                        }



                    }
                }
                else{ //При втором попадании стреляет в направлении, в котором раньше стрелял
                    if (Direction == 1 && Boty - 1 >= 0){
                        Boty--;
                    }
                    else if (Direction == 2 && Botx -1 >= 0){
                        Botx--;
                    }
                    else if (Direction == 3 && Boty +1 <= 9){
                        Boty++;
                    }
                    else if (Direction == 4 && Botx+1 <= 9){
                        Botx++;
                    }
                    else{
                        SecondBotHit = false;
                    }
                }
            }
            else {
                Botx = rand() % N;
                Boty =  rand() % N;
                botx = Botx;
                boty = Boty;

            }


               // cout << "Bot entered the coordinates: x[" << x+1<< "] and y[" << y+1 << "]\n";
                if (!(Player.Shoot_function(Botx, Boty))) {
                    step = true;
                    Player.Print();
                    Bot.PrintBot();
                    cout << "Bot entered the coordinates: x[" << Botx+1<< "] and y[" << Boty+1 << "]\n";
                    cout << "\nBot missed!" << endl;
                    SecondBotHit = false;
                } else {
                    if (BotHit){

                        SecondBotHit = true;
                    }
                    BotHit = true;
                    Player.Print();
                    Bot.PrintBot();
                    cout << "Bot entered the coordinates: x[" << Botx+1<< "] and y[" << Boty+1 << "]\n";
                    cout << "\n\t\t\t\tBot hit your ship!\a" << endl;
                }


    }
    } while (!Player.AllShipsDestroyed() || !Bot.AllShipsDestroyed());
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
void GameBoard::GenerateBot()
{
    // заполняем игровое поле пустыми клетками

    int idx = 0;
    for (int i = 0; i < _size; i++)
        for (int j = 0; j < _size; j++)
            _cells[i][j].SetState(Empty);
    // расставляем 4-х палубные
    _ships[idx++].Create_random(*this, 4, 1);
    // расставляем 3-х палубные
    _ships[idx++].Create_random(*this, 3, 2);

    // расставляем 2-х палубные
    _ships[idx++].Create_random(*this, 2, 3);

    // расставляем 1-х палубные
    _ships[idx++].Create_random(*this, 1, 4);
}


void GameBoard::Print()
{
    cout<< "Player's bord"<<endl;
    cout << ' ' << ' ' << ' ';
    cout << 'a' << ' ';
    cout << 'b' << ' ';
    cout << 'c' << ' ';
    cout << 'd' << ' ';
    cout << 'e' << ' ';
    cout << 'f' << ' ';
    cout << 'g' << ' ';
    cout << 'h' << ' ';
    cout << 'i' << ' ';
    cout << 'j' << ' ';
    cout << endl;
    for (int i = 0; i < _size; i++)
    {
        if (i == _size-1) {
            cout << i + 1; }
        else {
            cout << ' ' << i + 1; }
        cout << "|";
        for (int j = 0; j < _size; j++)
        {
            _cells[i][j].Print();
            cout << "|";
        }
        cout << endl;
    }

}
void GameBoard::PrintBot() {
    cout << "Bot's bord" << endl;
    cout << ' ' << ' ' << ' ';
    cout << 'a' << ' ';
    cout << 'b' << ' ';
    cout << 'c' << ' ';
    cout << 'd' << ' ';
    cout << 'e' << ' ';
    cout << 'f' << ' ';
    cout << 'g' << ' ';
    cout << 'h' << ' ';
    cout << 'i' << ' ';
    cout << 'j' << ' ';
    cout << endl;
    for (int i = 0; i < _size; i++) {
        if (i == _size-1) {
            cout << i + 1; }
        else {
            cout << ' ' << i + 1; }
        cout << "|";
        for (int j = 0; j < _size; j++) {

            _cells[i][j].PrintBot();
            cout << "|";
        }
        cout << endl;
    }
}


