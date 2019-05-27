// 定义一个 2048 的游戏类，包含其中的游戏逻辑业务部分

#ifndef GAME_2048_H
#define GAME_2048_H

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <io.h>
#include <conio.h>
#include "Window_2048.h"

#define DATADIR "C://2048"
#define DATAFILE "C://2048//2048_data.txt"
#define GAMESIZE 4

typedef int Table[GAMESIZE][GAMESIZE];

class Game_2048: private Window_2048 {
    public:
        Game_2048();
        ~Game_2048();
        void mainLoop();
    private:
        bool ischanged;
        void start();
        void readBest();
        void writeBest();
        void up();
        void down();
        void left();
        void right();
        void show2048();
        void flush2048();
        // void printLine(int, bool);
        void randomAppear();
        void move(int , int);
};

#endif