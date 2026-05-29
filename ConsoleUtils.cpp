#include "ConsoleUtils.h"
#include <iostream>

using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void setColor(Color text, Color background)
{
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void SetCursor(int x, int y)
{
    COORD myCoords = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hStdOut, myCoords);
}

void delay(clock_t ms)
{
    clock_t start = clock();
    while (clock() - start < ms) {}
}

void theme()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << '\a';

    const char* symbolLogo[7] = {
        " _______       __  ___________  ___________  ___      _______   ________  __    __   __        _______              ",
        "|   _  \"\\     /\"\"\\(\"     _   \")(\"    _    \")|\"  |    /\"     \"| /\"       )/\" |  | \"\\ |\" \\      |   __ \"\\           ",
        "(. |_)  :)   /    \\)__/  \\\\__/  )__/  \\\\__/ ||  |   (: ______)(:   \\___/(:  (__)  :)|   |     (. |__) :)         ",
        "|:     \\/   /  /\\  \\  \\\\_ /        \\\\_ /    |:  |    \\/    |   \\___  \\   \\/      \\/ |    |    |:  ____/          ",
        "(|  _  \\\\  /   __   \\ |.  |        |.  |     \\  |___ // ___)_   __/  \\\\  //  __  \\\\ |   |     (|  /             ",
        "|: |_)  :)/   /  \\   \\\\:  |        \\:  |   (  \\_|: \\(:      \"| /\"     :)(:  (  )  :)/\\  |\\   /|__/\\            ",
        "(_______/(___/    \\___)\\__|         \\__|    \\_______)\\_______)(_______/  \\__|  |__/(__\\_|_)(_______)"
    };

    for (int i = 0; i < 7; i++)
    {
        cout << symbolLogo[i] << endl;
        delay(120);
    }
}

void CreatField(int X, int numColor)
{
    SetCursor(X, 1);
    char mas[10] = { 'A','B','C','D','E','F','G','H','I','J' };
    setColor(White, Color(numColor));
    int A = 0, B = 0;
    cout << "  " << mas[0];

    for (size_t i = 0; i < 12; i++)
    {
        if (B == 0)
        {
            SetCursor(X + 3, 1 + i);
            B++;
        }
        else
        {
            SetCursor(X, 1 + i);
        }

        for (size_t j = 0; j < 23; j++)
        {
            if (i == 0 && j == 22)
            {
                setColor(Color(numColor), Color(numColor));
                cout << ' ';
            }
            if (i == 0 && j > 0 && j < 10)
            {
                setColor(White, Color(numColor));
                cout << " " << mas[j];
            }
            else if (i > 0 && i < 11 && j == 0)
            {
                setColor(White, Color(numColor));
                if (i < 10)
                    cout << i << ' ';
                else
                    cout << i;
            }
            else if (i == 11 || (j > 20 && j < 23))
            {
                if (A == 0 && i == 11)
                {
                    cout << " ";
                    A++;
                }
                setColor(Color(numColor), Color(numColor));
                cout << ' ';
            }
            else if (i > 0)
            {
                setColor(White, White);
                cout << ' ';
            }
        }
    }
    setColor(Black, Black);
}

void PaintPos(int arr[12][24], int x, int numColor)
{
    for (size_t i = 1; i < 11; i++)
    {
        int y = 1 + i;
        SetCursor(x, y);

        for (size_t j = 2; j < 22; j++)
        {
            if (arr[i][j] == 2)
                setColor(LightGray, LightGray);
            else if (arr[i][j] == 3)
                setColor(LightMagenta, LightMagenta);
            else if (arr[i][j] >= 4)
                setColor(Color(numColor), Color(numColor));
            else
                setColor(White, White);

            cout << " ";
        }
        cout << endl;
    }
}
