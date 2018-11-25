/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  main.c - app entry point
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "ui.h"

int main(int argc, char **argv)
{
    clearScreen();
    Genre *playlist = NULL;
    parseArgs(&playlist, argc, argv);
    initMainLoop(&playlist);
    return 0;
}

