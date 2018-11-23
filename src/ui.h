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

void handlePlay(Genre **playlist);

void handleAddSong(Genre **playlist);

void handleAddGenre(Genre **playlist);

void handleAdd(Genre **playlist);

void handleRemoveSong(Genre **playlist);

void handleRemoveGenre(Genre **playlist);

void handleRemove(Genre **playlist);

void handleLoad(Genre **playlist);

void handleSave(Genre **playlist);

void initMainLoop(Genre **playlist);

