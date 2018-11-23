/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  io.c - console input/output implementations
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "io.h"

void clearScreen()
{
    system(CONSOLE_CLEAR_CMD);
}

void flushInputBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int inputInteger()
{
    int i = 0;
    scanf("%d", &i);
    flushInputBuffer();
    clearScreen();
    return i;
}

void inputString(char *s)
{
    scanf("%100s", s);
    flushInputBuffer();
    clearScreen();
}

