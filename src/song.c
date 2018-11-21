/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  song.c - song list implementation
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "song.h"

Song *createSong(char *name, char *artist)
{
    Song *new_song = (Song*)safeMalloc(sizeof(Song));

    strncpy(new_song->name, name, MAX_STRING);
    strncpy(new_song->artist, artist, MAX_STRING);

    return new_song;
}

Song *getSong(Song **head, int index)
{
    if (*head != NULL)
    {
        Song *curr = *head;
        int i = 1;

        while (i != index && curr->next != *head)
        {
            ++i;
            curr = curr->next;
        }

        if (i == index)
        {
            return curr;
        }
    }

    return NULL;
}

bool pushBackSong(Song **head, char *name, char *artist)
{
    Song *new_song = createSong(name, artist);

    if (*head == NULL)
    {
        new_song->prev = new_song;
        new_song->next = new_song;

        *head = new_song;
    }
    else
    {
        new_song->prev = (*head)->prev;
        new_song->next = *head;

        (*head)->prev->next = new_song;
        (*head)->prev = new_song;
    }

    return true;
}

bool pushFrontSong(Song **head, char *name, char *artist)
{
    Song *new_song = createSong(name, artist);

    if (*head == NULL)
    {
        new_song->prev = new_song;
        new_song->next = new_song;

        *head = new_song;
    }
    else
    {
        new_song->prev = (*head)->prev;
        new_song->next = *head;

        (*head)->prev->next = new_song;
        (*head)->prev = new_song;

        *head = new_song;
    }

    return true;
}

bool insertAfterSong(Song **head, char *name, char *artist, int index)
{
    Song *curr = getSong(head, index);

    if (curr == NULL)
    {
        return false;
    }
    else
    {
        Song *new_song = createSong(name, artist);

        new_song->prev = curr;
        new_song->next = curr->next;

        curr->next->prev = new_song;
        curr->next = new_song;

        return true;
    }
}

bool removeSong(Song **head, int index)
{
    Song *curr = getSong(head, index);

    if (curr == NULL)
    {
        return false;
    }
    else
    {
        if (curr == *head && curr->next == *head && curr->prev == *head)
        {
            *head = NULL;
        }
        else
        {
            if (curr == *head)
            {
                *head = curr->next;
            }

            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

        free(curr);

        return true;
    }
}

bool removeAllSongs(Song **head)
{
    if (*head != NULL)
    {
        if ((*head)->prev == *head)
        {
            free(*head);
        }
        else
        {
            (*head)->prev->next = NULL;

            while (*head != NULL)
            {
                Song *temp = *head;
                *head = (*head)->next;
                free(temp);
            }
        }

        *head = NULL;
    }

    return true;
}

void printSongs(Song **head)
{
    if (*head != NULL)
    {
        int i = 1;
        Song *curr = *head;

        do
        {
            printf("    %d) %s - %s\n", i, curr->artist, curr->name);
            ++i;
            curr = curr->next;
        }
        while (curr != *head);
    }
    else
    {
        printf("    (Empty)\n");
    }
}

