//Создать иерархию классов и запрограммировать компьютерную игру “Морской бой”. Игровое поле разбивается на клетки. Палуба корабля занимает одну клетку. Кораблем считается совокупность смежных клеток. Допускаются четыре категории кораблей: одно-, двух-, трех- и четырехпалубные. Двух-, трех- и четырехпалубные корабли могут иметь всевозможные конфигурации и ориентации на игровом поле. Не допускается размещение кораблей в смежных клетках.
#include<iostream>
#include "emun.h"
#include "cell_method.h"
#include "ship.h"
#include <ctime>
#include "bot.h"
#include <iomanip>
#include <stdio.h>
using namespace std;
// заранее объявим, чтобы можно было указывать в качестве аргумент функций класса Ship
class GameBoard;

int main(int argc, char** argv) {
    srand(time(0));
    const int N = 10;
    GameBoard Player;
    GameBoard Bot;
    GameBoard Ar;
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
    int x, y, pos;
    int Botx = 0, Boty = 0;
    Ship ship;
    do {
        if (step) {
            cout << "\nYour step..." << endl;
            string letter = "Enter x and y coord: X_Y: ";

            ship.Ship::Entry(x, y, letter, pos, 2, 3, Ar);
            if (!Bot.Shoot_function(x, y)){//стреляем в поле бота
                step = false;
                system ("cls");
                Player.Print();
                Bot.PrintBot();
                cout << "\nYou missed!\a" << endl;}
            else  {
                system ("cls");
                Player.Print();
                Bot.PrintBot();
                cout << "\nYou hit bot's ship\a" << endl;
            }

        } else {

            cout << "\nStep Bot...\n"<< endl;
            if (BotHit == true){
                if (SecondBotHit == false){
                    while (true){
                        Direction = 1+rand() % 4;
                        if (Direction == 1 && BotMiss[0] == false && Boty > 0){
                            Boty--; //Стреляет левее
                            break;
                        }
                        else if (Direction == 2 && BotMiss[1] == false && Botx> 0){
                            Botx--; //Стреляет выше
                            break;
                        }
                        else if (Direction == 3 && BotMiss[2] == false && Boty < 9){
                            Boty++; //Стреляет правее
                            break;
                        }
                        else if (Direction == 4 && BotMiss[3] == false && Botx < 9){
                            Botx++; //Стреляет ниже
                            break;
                        }
                        else{
                            BotMiss[Direction - 1] = true; //Если никуда не получилось выстрелить
                        }
                        if (BotMiss[0] == true && BotMiss[1] == true && BotMiss[2] == true && BotMiss[3] == true){
                            break; //Если уже были попытки выстрелить по всем сторонам
                        }
                    }
                }
                else{ //При втором попадании стреляет в направлении, в котором раньше стрелял
                    if (Direction == 1 && Boty > 0){
                        Boty--;
                    }
                    else if (Direction == 2 && Botx > 0){
                        Botx--;
                    }
                    else if (Direction == 3 && Boty < 9){
                        Boty++;
                    }
                    else if (Direction == 4 && Botx < 9){
                        Botx++;
                    }
                    else{
                        SecondBotHit = false;
                    }
                }
            }
            else {
                Botx = rand() % N;
                Boty = rand() % N;

            }


               // cout << "Bot entered the coordinates: x[" << x+1<< "] and y[" << y+1 << "]\n";
                if (!(Player.Shoot_function(Botx, Boty))) {
                    step = true;
                    system ("cls");
                    Player.Print();
                    Bot.PrintBot();
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
                    cout << "Bot entered the coordinates: " << Botx_char<< " " << Boty+1 << ""
                                                                                            ""
                                                                                            "\n";
                    cout << "\nBot missed!\a" << endl;
                } else {
                    if (BotHit){
                        BotHitForSecondBotHit = true;
                    }
                    if (BotHitForSecondBotHit){
                        SecondBotHit = true;
                    }
                    system ("cls");
                    BotHit = true;
                    system ("cls");

                    Player.Print();
                    Bot.PrintBot();
                    cout << "Bot entered the coordinates: x[" << x+1<< "] and y[" << y+1 << "]\n";
                    cout << "\n\t\t\t\tBot hit your ship!\a" << endl;
                }


    }
    } while (!Player.AllShipsDestroyed() || !Bot.AllShipsDestroyed());
    return 0;
}


void GameBoard::Generate() {
    GameBoard gameBoard;
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
            _ships[idx++].Entry(x, y, letter, pos, 3, 4, gameBoard);
            Print();
            cout << endl;
            i++;
        }
        for (int i = 0; i < _3DeckShipCount; i++) {
            cout << "3 deck ship (quantity " << _3DeckShipCount-i << "): ";
            _ships[idx++].Entry(x, y, letter, pos, 3, 3, gameBoard);
            Print();
            cout << endl;
        }
        for (int i = 0; i < _2DeckShipCount; i++) {
            cout << "2 deck ship (quantity " << _2DeckShipCount-i << "): ";
            _ships[idx++].Entry(x, y, letter, pos, 3, 2, gameBoard);
            Print();
            cout << endl;
        }
        for (int i = 0; i < _1DeckShipCount; i++) {
            cout << "1 deck ship (quantity " << _1DeckShipCount-i << "): ";
            _ships[idx++].Entry(x, y, letter, pos, 3, 1, gameBoard);
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


