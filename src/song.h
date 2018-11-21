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

#include "util.h"

#include <stdbool.h>
#include <string.h>

#define MAX_STRING 101

typedef struct Song Song;
struct Song
{
    char name[MAX_STRING];
    char artist[MAX_STRING];
    Song *prev, *next;
};

Song *createSong(char *name, char *artist);

Song *getSong(Song **head, int index);

bool pushBackSong(Song **head, char *name, char *artist);

bool pushFrontSong(Song **head, char *name, char *artist);

bool insertAfterSong(Song **head, char *name, char *artist, int index);

bool removeSong(Song **head, int index);

bool removeAllSongs(Song **head);

void printSongs(Song **head);

