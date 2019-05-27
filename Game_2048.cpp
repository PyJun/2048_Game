// 实现 2048 游戏类中头文件定义的成员函数

#include "Game_2048.h"

Game_2048::Game_2048(): Window_2048() {
    scores = 0;
    best = 0;
    srand(time(NULL));
    start();
}

Game_2048::~Game_2048() {
    writeBest();
}

void Game_2048::mainLoop() {
    int ch;
    show2048();
    while (true) {
        if (_kbhit()) {
            ch = _getch();
            switch (ch) {
                case 'W':
                case 'w':
                case 72: if(!gameover) up(); break;
                case 'S':
                case 's':
                case 80: if(!gameover) down(); break;
                case 'D':
                case 'd': 
                case 77: if(!gameover) right(); break;
                case 'A':
                case 'a':
                case 75: if(!gameover) left(); break;
                case 'R':
                case 'r': if (gameover) {writeBest(); start();} break;
                case 'Q':
                case 'q':
                case 27: return;
            }
        }
        Sleep(10);
    }
}

void Game_2048::start() {
    readBest();
    scores = 0;
    gameover = false;
    ischanged = true;
    for (int i = 0; i < GAMESIZE; i++) {
        for (int j = 0; j < GAMESIZE; j++) {
            table[i][j] = 0;
        }
    }
    randomAppear();
    randomAppear();
    show2048();
}

void Game_2048::readBest() {
    int data;
    ifstream infile(DATAFILE);
    if (infile.is_open()) {
        infile >> data;
        if (data > best) {
            best = data;
        }
        infile.close();
    }
}

void Game_2048::writeBest() {
    if (scores <= best) {
        return;
    }
    if (access(DATADIR, 0) == -1) {
        mkdir(DATADIR);
    }
    ofstream outfile(DATAFILE);
    if (outfile.is_open()) {
        outfile << scores;
        outfile.close();
    }
}

void Game_2048::up() {
    move(1, 0); 
    flush2048();
}

void Game_2048::down() {
    move(-1, 0); 
    flush2048();
}

void Game_2048::right() {
    move(0, 1); 
    flush2048();
}

void Game_2048::left() {
    move(0 ,-1); 
    flush2048();
}

void Game_2048::flush2048() {
    if (!gameover && ischanged) {
        randomAppear();
        show2048();
        ischanged = false;
    } else if (ischanged) {
        show2048();
        ischanged = false;
    }
}

void Game_2048::show2048() {
    Window_2048::show2048();
}

void Game_2048::randomAppear() {
    int size = 20;
    int randnum = rand() % size, start = 0;
    int number;
    if (scores < 1000)
        number = (randnum > size/5) ? 2 : 4;
    else
        number = (randnum > size/4) ? 2 : ((randnum > size/20)?4:8);
    while (true) {
        for (int i = 0; i < GAMESIZE; i++) {
            for (int j = 0; j < GAMESIZE; j++) {
                if (table[i][j] != 0) 
                    continue;
                if (start == randnum) {
                    table[i][j] = number;
                    return;
                }
                start = (start + 1) % size;
            }
        }
    }
}

void Game_2048::move(int ud, int lr) { // up = 1 上， -1 下， 0 不动； lr = 1 右， -1 左， 0 不动
    int i, j, x, y, pre_x, pre_y;
    bool flag_ok, flag_add, flag_voice = false;
    for (j = 0; j < GAMESIZE; j++) {
        flag_add = false;
        while (true) {
            flag_ok = true; 
            for (i = 1; i < GAMESIZE; i++) {
                if (ud != 0 && lr == 0) {
                    x = (ud == -1)?(GAMESIZE-1-i):i ;
                    pre_x = (ud == -1)?(x+1):(x-1);
                    pre_y = y = j;
                }
                if (ud == 0 && lr != 0) {
                    y = (lr == -1)?i:(GAMESIZE-1-i);
                    pre_y = (lr == -1)?(y-1):(y+1);
                    pre_x = x = j;
                }
                if (table[pre_x][pre_y] ==0 && table[x][y] != 0) {
                    table[pre_x][pre_y] = table[x][y];
                    table[x][y] = 0;
                    flag_ok = false;
                } 
                if (table[pre_x][pre_y] != 0 && table[pre_x][pre_y] == table[x][y]) {
                    if (flag_add)
                        continue;
                    scores += table[x][y] *2;
                    table[pre_x][pre_y] *= 2;
                    table[x][y] = 0;
                    flag_ok = false;
                    flag_add = true;
                    flag_voice = true;
                } 
            }
            if (flag_ok)
                break;
            else 
                ischanged = true;
        }
    }
    if (flag_voice) {
        cout << "\a";
    }
    Sleep(100);
    for (i = 0; i < GAMESIZE; i++) {
        for (j = 0; j <GAMESIZE; j++) {
            if (table[i][j] == 0) {
                gameover = false;
                return;
            }
        }
    }
    gameover = true;
    show2048();
}
