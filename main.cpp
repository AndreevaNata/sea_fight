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
int main() {
    srand(time(0));
    const int N = 10;
    GameBoard Player;
    GameBoard Bot;

    Player.Generate();
    Player.Print();
    Bot.GenerateBot();

    Bot.PrintBot();
    int Direction = -1;
    bool step = true;
    bool BotHit = false;

    bool SecondBotHit = false;
    bool BotMiss[4] = {false, false, false, false};
    int x = 0,y = 0;
    int Botx = 0, Boty = 0, botx = 0,boty = 0;
    string letter = "This letter is not permitted. Choose X from: |a b c d e f g h i j| and Y from: |1 2 3 4 5 6 7 8 9 10| - ";
    do {
        if (step) {
            cout << "\nYour step..." << endl;
            cout << "Enter x and y coord: X_Y: " << endl;
            char fx;
            Ship::Entry(x, y, letter, -1, 2, -1, Bot);

            int check = Bot.Shoot_function( Bot, x, y);
            if (check == 0){//стреляем в поле бота
                step = false;
                Player.Print();
                Bot.PrintBot();
                cout << "\nYou missed!" << endl;}
            else if (check == 1)  {
                Player.Print();
                Bot.PrintBot();
                cout << "\nYou hit bot's ship\a" << endl;
            }
            else if (check == 2)  {
                cout<<"ERROR";
                cout<<" You already was in this cell"<<endl;
            }
            else if (check == 3){
                cout<<"You kill Bot's ship";
                list<int> list;
                list = Bot.ShipsDestroyed();
                Bot.Remain(list);

            }

        } else {

            cout << "\nStep Bot...\n"<< endl;
            if (BotHit){

                if (!SecondBotHit){
                    while (true){
                        Botx = botx;
                        Boty = boty;
                        Direction = 1+rand() % 4;
                        if (Direction == 1 && !BotMiss[0] && Boty - 1 >= 0){
                            Boty--; //Стреляет левее
                            BotMiss[0] = true;
                            break;
                        }
                        else if (Direction == 2 && !BotMiss[1] && Botx - 1 >= 0){
                            Botx--; //Стреляет выше
                            BotMiss[1] = true;
                            break;
                        }
                        else if (Direction == 3 && !BotMiss[2] && Boty + 1 <= 9){
                            Boty++; //Стреляет правее
                            BotMiss[2] = true;
                            break;
                        }
                        else if (Direction == 4 && !BotMiss[3] && Botx + 1 <= 9){
                            Botx++; //Стреляет ниже
                            BotMiss[3] = true;
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

            char Botx_char;
            switch (Botx) {
                case (0): { Botx_char = 'a'; break; }
                case (1): { Botx_char = 'b'; break; }
                case (2): { Botx_char = 'c'; break; }
                case (3): { Botx_char = 'd'; break; }
                case (4): { Botx_char = 'e'; break; }
                case (5): { Botx_char = 'f'; break; }
                case (6): { Botx_char = 'g'; break; }
                case (7): { Botx_char = 'h'; break; }
                case (8): { Botx_char = 'i'; break; }
                case (9): { Botx_char = 'j'; break; }
            }
                // cout << "Bot entered the coordinates: x[" << x+1<< "] and y[" << y+1 << "]\n";
                int check = Player.Shoot_function( Player,Botx, Boty);
                if (check ==0) {
                    step = true;
                    Player.Print();

                   // cout << "Bot entered the coordinates: x[" << Botx+1<< "] and y[" << Boty+1 << "]\n";
                    SecondBotHit = false;

                    cout << "Bot entered the coordinates: " << Botx_char<< " " << Boty+1;
                    cout << "\nBot missed!\a" << endl;
                } else if (check ==1) {
                    if (BotHit){

                        SecondBotHit = true;
                    }
                    //system ("cls");
                    BotHit = true;
                    //system ("cls");

                    Player.Print();
                    Sleep(5000);
                    Bot.PrintBot();

                    cout << "Bot entered the coordinates: " << Botx_char<< " " << Boty+1;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
                    cout << "\nBot hit your ship!\a" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
                }
                else if (check == 3){
                    cout<<"Bot kill your ship"<<endl;
                     BotHit= false;
                        list<int> list;
                        list = Player.ShipsDestroyed();
                        Player.Remain(list);

                    }

                }



    }while (!Player.AllShipsDestroyed() || !Bot.AllShipsDestroyed());
  if(Player.AllShipsDestroyed()) cout<<"Bot win!";
  else cout<<"You win!";
    return 0;
}


void GameBoard::Generate() {

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
        int pos;
        string letter = "This letter is not permitted. Choose X from: |a b c d e f g h i j| and Y from: |1 2 3 4 5 6 7 8 9 10| and Position from |0(vertical) 1(horizontal)| - ";
        int i = 0;
        while (i < _4DeckShipCount) {
            cout << "4 deck ship (quantity " << _4DeckShipCount-i << "): ";
            _ships[idx++].Entry(x, y, letter, pos, 3, 4, *this);
            Print();
            cout << endl;
            i++;
        }
        for ( i = 0; i < _3DeckShipCount; i++) {
            cout << "3 deck ship (quantity " << _3DeckShipCount-i << "): ";
            _ships[idx++].Entry(x, y, letter, pos, 3, 3, *this);
            Print();
            cout << endl;
        }
        for (i = 0; i < _2DeckShipCount; i++) {
            cout << "2 deck ship (quantity " << _2DeckShipCount-i << "): ";
            _ships[idx++].Entry(x, y, letter, pos, 3, 2, *this);
            Print();
            cout << endl;
        }
        for ( i = 0; i < _1DeckShipCount; i++) {
            cout << "1 deck ship (quantity " << _1DeckShipCount-i << "): ";
            _ships[idx++].Entry(x, y, letter, pos, 3, 1, *this);
            Print();
            cout << endl;
        }
        cout << "Game starts!" << endl;
    }
    else{
        // заполняем игровое поле пустыми клетками

        _ships[idx++].Create_random(*this, 4);
        // расставляем 3-х палубные
        _ships[idx++].Create_random(*this, 3);
        _ships[idx++].Create_random(*this, 3);
        // расставляем 2-х палубные
        _ships[idx++].Create_random(*this, 2);
        _ships[idx++].Create_random(*this, 2);
        _ships[idx++].Create_random(*this, 2);

        // расставляем 1-х палубные
        _ships[idx++].Create_random(*this, 1);
        _ships[idx++].Create_random(*this, 1);
        _ships[idx++].Create_random(*this, 1);
        _ships[idx++].Create_random(*this, 1);
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
    _ships[idx++].Create_random(*this, 4);
    // расставляем 3-х палубные
    _ships[idx++].Create_random(*this, 3);
    _ships[idx++].Create_random(*this, 3);
    // расставляем 2-х палубные
    _ships[idx++].Create_random(*this, 2);
    _ships[idx++].Create_random(*this, 2);
    _ships[idx++].Create_random(*this, 2);

    // расставляем 1-х палубные
    _ships[idx++].Create_random(*this, 1);
    _ships[idx++].Create_random(*this, 1);
    _ships[idx++].Create_random(*this, 1);
    _ships[idx++].Create_random(*this, 1);
}

        switch (list.front()) {
            case (0): { foursheep++; break; }
            case (1): { threesheep++; break;}
            case (2): { threesheep++; break;}
            case (3): { twosheep++; break; }
            case (4): { twosheep++; break; }
            case (5): { twosheep++; break; }
            case (6): { onesheep++; break; }
            case (7): { onesheep++; break; }
            case (8): { onesheep++; break; }
            case (9): { onesheep++; break; }
        }
        list.pop_front();
    }
    cout<<endl;
    cout<<"The remaining sheeps"<<endl;
    cout<<endl;
    cout<<"Four deck:1/"<<foursheep<<endl;
    cout<<"Three deck:2/"<<threesheep<<endl;
    cout<<"Two deck:3/"<<twosheep<<endl;
    cout<<"One deck:4/"<<onesheep<<endl;

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


