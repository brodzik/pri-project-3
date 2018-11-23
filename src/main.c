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

void generateTestData(Genre **playlist)
{
    Song *pop_songs = NULL;
    pushBackSong(&pop_songs, "Song 2", "Author");
    pushBackSong(&pop_songs, "Song 3", "Author");
    pushBackSong(&pop_songs, "Song 4", "Author");
    pushBackSong(&pop_songs, "Song 5", "Author");
    pushFrontSong(&pop_songs, "Song 1", "Author");
    pushBackGenre(playlist, "Pop", pop_songs);

    Song *rock_songs = NULL;
    pushFrontSong(&rock_songs, "Song 6", "Author");
    pushFrontSong(&rock_songs, "Song 7", "Author");
    pushFrontSong(&rock_songs, "Song 8", "Author");
    insertAfterSong(&rock_songs, "Song 6.5", "Author", 2);
    pushFrontGenre(playlist, "Rock", rock_songs);

    Song *jazz_songs = NULL;
    pushBackGenre(playlist, "Jazz", jazz_songs);

    Song *blues_songs = NULL;
    pushBackGenre(playlist, "Blues", blues_songs);

    Song *classical_songs = NULL;
    pushBackSong(&classical_songs, "Song 9", "Author");
    pushBackSong(&classical_songs, "Song 10", "Author");
    pushBackGenre(playlist, "Classical", classical_songs);
}

int main()
{
    Genre *playlist = NULL;
    generateTestData(&playlist);
    clearScreen();
    initMainLoop(&playlist);
    return 0;
}

