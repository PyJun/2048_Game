// Window_2048 类的成员函数和静态函数的实现

#include "Window_2048.h"

void Window_2048::show2048() {
    static const Color colors1[] = {SC, WC, SC};
    static const Color colors2[] = {SC};
    static const Color colors3[] = {SC, WC, SC, WC};
    static const Color colors4[] = {SC, WC, SC, WC};
    static const string strs1[] = {
    "\t\t" "┌┬─────────────────────────────────────────────────────┬┐\n"
    "\t\t" "││                     ", "2048  游戏                      ", "││\n"
    "\t\t" "├┼─────────────────────────────────────────────────────┼┤\n"
    "\t\t" "││      "
    };
    static const string strs2[] = {"      ││\n"
    "\t\t" "││                                                     ││\n"
    "\t\t" "││        ┌────────┬────────┬────────┬────────┐        ││\n"
    };
    static const string strs3[] = {
    "\t\t││                ", "Enjoy Yourself  \\(^o^)/", "              ││\n"
    "\t\t├┼─────────────────────────────────────────────────────┼┤\n"
    "\t\t└┴─────────────────────────────────────────────────────┴┘\n",
    "\t\t     [W]:Up  [S]:Down  [A]:Left  [D]:Right  [Q]:Exit     \n"
    };
    static const string strs4[] = {
    "\t\t││", "                 Game Over!  \\(╯-╰)/", "                 ││\n"
    "\t\t├┼─────────────────────────────────────────────────────┼┤\n"
    "\t\t└┴─────────────────────────────────────────────────────┴┘\n", 
    "\t\t            [R]:Restart             [Q]:Exit             \n"
    };
    static const string str1 = "\t\t││        ├────────┼────────┼────────┼────────┤        ││\n";
    static const string str2 = "\t\t││        └────────┴────────┴────────┴────────┘        ││\n";
    static const string str3 = "\t\t││                                                     ││\n";
    clsScreen();
    cout << endl << endl;
    printColorStrs(4, colors1, strs1);
    changeColor(VC1);
    printf("当前分数: %05d           ",scores);
    changeColor(VC2);
    printf("历史最高: %05d", best);
    printColorStrs(1, colors2, strs2);
    for (int row = 0; row < 3; row++) {
        printLine(row, false);
        printLine(row, true);
        printLine(row, false);
        cout << str1;  
    }
    printLine(3, false);
    printLine(3, true);
    printLine(3, false);
    cout << str2;
    cout << str3;
    if (!gameover){
        printColorStrs(4, colors3, strs3); 
    } else { 
        printColorStrs(4, colors4, strs4);
    }
}

void Window_2048::printColorStrs(int n, const Color * colors, const string * strs) {
    for (int i = 0; i < n; i++ ) {
        changeColor(colors[i]);
        cout << strs[i];
    }
}

void Window_2048::printLine(int row, bool numeric) {
    int num;
    Color color;
    cout << "\t\t││        │" ;
    for (int col = 0; col < 4; col++) {
        num = table[row][col];
        color = numToColor(num);
        changeColor(color);
        if (numeric) {
            printCenter(8, tostr(&num));
        } else {
            printCenter(8, "0");
        }
        changeColor(SC);
        cout << "│" ;
    }
    cout << "        ││" << endl;
}

void Window_2048::changeColor(Color color) {
    HANDLE outPutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(outPutHandle, color);
}

void Window_2048::setWindow() {
    SetConsoleTitle(title.c_str());
    HWND hwnd = GetForegroundWindow();
    SetWindowPos(hwnd, HWND_TOP, posx, posy, width, height, 0);
}

void Window_2048::clsScreen() {
    COORD pos = {0, 0};
    CONSOLE_CURSOR_INFO info = {1, 0};
    HANDLE outPutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(outPutHandle, pos);
    SetConsoleCursorInfo(outPutHandle, &info);
}

string Window_2048::tostr(const void * p) {
    string res;
    stringstream ss;
    ss << *((int *)p) ;
    ss >> res;
    return res;
}

Color Window_2048::numToColor(int num) {
    Color color;
    if (num == 0) {
        color = (15 <<4);
    } else {
        color = ((15- (int)log2(num)) << 4);
    }
    return color;
}

void Window_2048::printCenter(int n, string numstr) {
    int size = numstr.size(), i;
    for (i = 0; i < (n-size)/2; i++) 
        cout << " ";
    if (numstr.compare("0") == 0)
        for (int j = 0; j < size; j++)
            cout << " ";
    else 
        cout << numstr;
    for (i = (n-size)/2+size; i < n; i++) 
        cout << " ";
}