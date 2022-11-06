#include <Windows.h>
#include <iostream>

#ifndef UNTITLED_SOURCE_H
#define UNTITLED_SOURCE_H

union int_convert {//buffer for reading
    int value = 0;
    BYTE bytes[sizeof(int)];//char
};

union double_convert {
    double value = 0.0;
    byte bytes[sizeof(double)];
};

DWORD WINAPI pow_(LPVOID lpParameter);
DWORD WINAPI sum_(LPVOID lpParameter);
DWORD WINAPI sqrt_(LPVOID lpParameter);


#endif //UNTITLED_SOURCE_H