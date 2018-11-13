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

void pushBackSong(Node **head, char *name, char *artist);

void songPrinter(void *data);

