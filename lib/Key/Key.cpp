#include <iostream>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

#include "Key.h"
#include "KeyPlus.h"

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

int Key::GetAsyncKey() {
    if (_keyInterrupt()) {
        return GetKey();
    }
    return 0;
}

int Key::GetKey() {
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

std::string Key::GetAsyncChar() {
    if (_keyInterrupt()) {
        return GetChar();
    }
    return "";
}

std::string Key::GetChar() {
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

std::string Key::GetAsyncString() {
    std::string line { "" };
    if (_keyInterrupt()) {
        line = GetString();
    }
    return line;
}

std::string Key::GetString() {
    std::string line = "";
    while (1) {
        std::string newChar = GetAsyncChar();
        if (newChar == "\n")  {
            break; 
        } else {
            std::string bs { (char)BACKSPACE };
            if (newChar == bs)  {
                line.pop_back();
            } else {
                line += newChar;
            }
        }
    }
    return line;
}
