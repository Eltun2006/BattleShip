#pragma once

#include <windows.h>
#include <time.h>

enum Color
{
    Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
    DarkGray, LightBlue = 9, LightGreen, LightCyan, LightRed,
    LightMagenta, Yellow, White
};

enum Direction
{
    Up = 72, Left = 75, Right = 77, Down = 80,
    Enter = 13, EscKey = 27, BackSpace = 8, R = 114
};

extern HANDLE hStdOut;

void setColor(Color text, Color background);
void SetCursor(int x, int y);
void delay(clock_t ms);
void theme();
void CreatField(int X, int numColor);
void PaintPos(int arr[12][24], int x, int numColor);
