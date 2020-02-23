https://stackoverflow.com/questions/17160553/making-the-console-window-bigger-in-c
https://social.msdn.microsoft.com/Forums/en-US/7eb84377-10e8-4ac4-889a-33ce6bdaa185/changing-the-console-window-size
https://www.programming-techniques.com/2011/09/how-to-resize-console-window-using-c.html
https://www.c-sharpcorner.com/article/creating-custom-window-in-win32/
https://www.dreamincode.net/forums/topic/141561-using-createwindow-function/
http://zetcode.com/gui/winapi/main/
https://www.binarytides.com/winsock-socket-programming-tutorial/
https://www.clubedohardware.com.br/forums/topic/729087-ajuda-com-a-fun%C3%A7%C3%A3o-gotoxyxy/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.



// Set up the handles for reading/writing:
wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
rHnd = GetStdHandle(STD_INPUT_HANDLE);

// Change the window title:
SetConsoleTitle("The Box");

// Set up the required window size:
SMALL_RECT windowSize = {0, 0, 850, 810};
SetConsoleWindowInfo(wHnd, 1, &windowSize);

// Change the console window size:
// Create a COORD to hold the buffer size:

COORD bufferSize = {110, 110};
SetConsoleScreenBufferSize(wHnd, bufferSize);
// Exit

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);

COORD coord;

coord.X = X;

coord.Y = Y;

SetConsoleCursorPosition(H, coord);
