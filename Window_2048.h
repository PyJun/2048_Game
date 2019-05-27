// 2048 Window 类，包含2048游戏的窗口事件，以及一些基本框架数据和函数

#ifndef WINDOW_2048_H
#define WINDOW_2048_H

#define GAMESIZE 4

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <windows.h>

using namespace std;

typedef int Table[GAMESIZE][GAMESIZE];
typedef int Color;
enum {
    SC = (15 << 4) + 1, 
    WC = (15 << 4) + 0, 
    VC1 =(15 << 4) + 2, 
    VC2 = (15 << 4) + 4
};

class Window_2048 {
    public:
        Window_2048(int x = 200, int y = 80, int w = 900, int h = 600, string t = "2048 游戏"):
            title(t), posx(x), posy(y), width(w), height(h) {
            setWindow();
            setBC();
        }
        Table table;
        bool gameover;
        int scores, best;
    protected:
        virtual void show2048() = 0;
    private:
        string title;
        int posx, posy, width, height;
        void setWindow();
        void printLine(int, bool);
        static void setBC() {
            system("color f0");
        }
        static void changeColor(Color);
        static void clsScreen();
        static void printColorStrs(int, const Color *, const string *);
        static string tostr(const void *);
        static Color numToColor(int);
        static void printCenter(int, string);
};

#endif 
