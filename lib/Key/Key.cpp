#include <iostream>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

#include "Key.h"
int Key::_keyInterrupt() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

int Key::GetKey() {
    if (_keyInterrupt()) {
        struct termios oldt,
        newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        if (ch == 27) {
            int ch1 = getchar();
            if (ch1 == 91) {
                int ch2 = getchar();
                if (ch2 == 51) {
                    ch = ((ch * 100 + ch1) * 100 + ch2) * 1000 + getchar();
                } else {
                    ch = (ch * 100 + ch1) * 100 + ch2;
                }
            } else {
                ch = ch * 100 + ch1;
            }
        } else if(ch >= 48 && ch < 58) {
            ch -= 48;
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
    return 0;
}

std::string Key::GetChar() {
    if (_keyInterrupt()) {
        struct termios oldt,
        newt;
        std::string ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
    return "";
}

std::string Key::GetString() {
    std::string line = "";
    if (_keyInterrupt()) {
        while (1) {
            std::string newChar = GetChar();
            if (newChar == "\n") break; else line += newChar;
        }
    }
    return line;
}
