/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  io.h - console input/output definitions
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define CONSOLE_CLEAR_CMD "cls"
#elif __linux__
#define CONSOLE_CLEAR_CMD "clear"
#else
#define CONSOLE_CLEAR_CMD ""
#endif

void clearScreen();

void flushInputBuffer();

int inputInteger();

void inputString(char *s);

