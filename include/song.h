/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  song.h - song list definition
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#pragma once

#include "list.h"

typedef struct Song Song;
struct Song
{
    char name[MAX_STRING], artist[MAX_STRING];
};

Song *createSong(char *name, char *artist);

void pushBackSong(Node **head, char *name, char *artist);

void pushFrontSong(Node **head, char *name, char *artist);

void insertAfterSong(Node **head, char *name, char *artist, int index);

void songPrinter(void *data);

