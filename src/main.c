/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  main.c - user and data interaction
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "song.h"
#include "genre.h"

#include <stdbool.h>

void generateTestData(Node **genres)
{
    Node *pop_songs = NULL;
    pushBackSong(&pop_songs, "Bohemian Rhapsody", "Queen");
    pushBackGenre(genres, "Pop", pop_songs);

    Node *rock_songs = NULL;
    pushBackSong(&rock_songs, "Strawberry Fields Forever", "The Beatles");
    pushBackSong(&rock_songs, "Stairway To Heaven", "Led Zeppelin");
    pushBackSong(&rock_songs, "Free Bird", "Lynyrd Skynyrd");
    pushBackGenre(genres, "Rock", rock_songs);

    Node *jazz_songs = NULL;
    pushBackGenre(genres, "Jazz", jazz_songs);

    Node *classical_songs = NULL;
    pushBackGenre(genres, "Classical", classical_songs);
}

void flushInputBuffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getUserAction()
{
    int action = 0;

    if (scanf("%d", &action) != 1)
    {
        flushInputBuffer();
    }

    return action;
}

int main()
{
    Node *genres = NULL;
    generateTestData(&genres);

    while (true)
    {
        switch (getUserAction())
        {
            case 1:
                exit(0);
                break;
            case 2:
                printList(&genres, genrePrinter);
                break;
            default:
                printf("Invalid action. Try again.\n");
                break;
        }
    }

    return 0;
}

