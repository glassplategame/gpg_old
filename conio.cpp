#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <string.h>
#include <_mingw.h>
void clrscr();
typedef enum {BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,
              LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE
             } COLORS;
static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;
void
gotoxy(int x, int y)
{
  COORD c;

  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void
clrscr ()
{
    DWORD written;

    FillConsoleOutputAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
      __FOREGROUND + (__BACKGROUND << 4), 2000, (COORD) {0, 0},
      &written);
      FillConsoleOutputCharacter (GetStdHandle
      (STD_OUTPUT_HANDLE), ' ',
      2000, (COORD) {0, 0}, &written);
    gotoxy (1, 1);
}

int
gettext (int left, int top, int right, int bottom,
  char *str)
{
    int i, j, n;
    SMALL_RECT r;
    CHAR_INFO buffer[25][80];

    r = (SMALL_RECT) {left - 1, top - 1, right - 1, bottom - 1};
    ReadConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),
      (PCHAR_INFO) buffer, (COORD) {80, 25}, (COORD) {0, 0}, &r);

    lstrcpy (str, "");
    for (i = n = 0; i <= bottom - top; i++)
    for (j = 0; j <= right - left; j++)
    {
        str[n] = buffer[i][j].Char.AsciiChar;
        n++;
    }
    str[n] = 0;
    return 1;
}

void
puttext (int left, int top, int right, int bottom, char *str)
{ 
    int i, j, n;
    SMALL_RECT r;
    CHAR_INFO buffer[25][80];

    memset (buffer, 0, sizeof (buffer));
    r = (SMALL_RECT) {left - 1, top - 1, right - 1, bottom - 1};

    for (i = n = 0; i <= bottom - top; i++)
    for (j = 0; j <= right - left && str[n] != 0; j++)
    {
        buffer[i][j].Char.AsciiChar = str[n];
        buffer[i][j].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        n++;
    }

    WriteConsoleOutput (GetStdHandle (STD_OUTPUT_HANDLE),
      (CHAR_INFO *) buffer, (COORD) {80, 25},
      (COORD) {0, 0}, &r);
}

