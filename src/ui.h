/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  ui.h - user interaction definitions
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#pragma once

#include "io.h"
#include "genre.h"
#include "song.h"

enum LoadFlag { NONE, ONLY, NOT, FULL };
typedef enum LoadFlag LoadFlag;

void handlePlay(Genre **playlist);

void handleAddSong(Genre **playlist);

void handleAddGenre(Genre **playlist);

void handleAdd(Genre **playlist);

void handleRemoveSong(Genre **playlist);

void handleRemoveGenre(Genre **playlist);

void handleRemove(Genre **playlist);

bool loadPlaylist(Genre **playlist, char *file_name, LoadFlag flag, char *genre_name);

void handleLoad(Genre **playlist);

void handleSave(Genre **playlist);

void generateTestData(Genre **playlist);

void parseArgs(Genre **playlist, int argc, char **argv);

void initMainLoop(Genre **playlist);

