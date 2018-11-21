/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  genre.h - genre list definition
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#pragma once

#include "song.h"

typedef struct Genre Genre;
struct Genre
{
    char name[MAX_STRING];
    Song *songs;
    Genre *prev, *next;
};

Genre *createGenre(char *name, Song *songs);

Genre *getGenre(Genre **head, int index);

bool pushBackGenre(Genre **head, char *name, Song *songs);

bool pushFrontGenre(Genre **head, char *name, Song *songs);

bool insertAfterGenre(Genre **head, char *name, Song *songs, int index);

bool removeGenre(Genre **head, int index);

bool removeAllGenres(Genre **head);

void printGenres(Genre **head, void (*callback)(Song**));

void printAll(Genre **head);

