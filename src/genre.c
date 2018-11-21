/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  genre.c - genre list implementation
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "genre.h"

Genre *createGenre(char *name, Song *songs)
{
    Genre *new_genre = (Genre*)safeMalloc(sizeof(Genre));

    strncpy(new_genre->name, name, MAX_STRING);
    new_genre->songs = songs;

    return new_genre;
}

Genre *getGenre(Genre **head, int index)
{
    if (*head != NULL)
    {
        Genre *curr = *head;
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

bool pushBackGenre(Genre **head, char *name, Song *songs)
{
    Genre *new_genre = createGenre(name, songs);

    if (*head == NULL)
    {
        new_genre->prev = new_genre;
        new_genre->next = new_genre;

        *head = new_genre;
    }
    else
    {
        new_genre->prev = (*head)->prev;
        new_genre->next = *head;

        (*head)->prev->next = new_genre;
        (*head)->prev = new_genre;
    }

    return true;
}

bool pushFrontGenre(Genre **head, char *name, Song *songs)
{
    Genre *new_genre = createGenre(name, songs);

    if (*head == NULL)
    {
        new_genre->prev = new_genre;
        new_genre->next = new_genre;

        *head = new_genre;
    }
    else
    {
        new_genre->prev = (*head)->prev;
        new_genre->next = *head;

        (*head)->prev->next = new_genre;
        (*head)->prev = new_genre;

        *head = new_genre;
    }

    return true;
}

bool insertAfterGenre(Genre **head, char *name, Song *songs, int index)
{
    Genre *curr = getGenre(head, index);

    if (curr == NULL)
    {
        return false;
    }
    else
    {
        Genre *new_genre = createGenre(name, songs);

        new_genre->prev = curr;
        new_genre->next = curr->next;

        curr->next->prev = new_genre;
        curr->next = new_genre;

        return true;
    }
}

bool removeGenre(Genre **head, int index)
{
    Genre *curr = getGenre(head, index);

    if (curr == NULL)
    {
        return false;
    }
    else
    {
        removeAllSongs(&curr->songs);

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

bool removeAllGenres(Genre **head)
{
    if (*head != NULL)
    {
        if ((*head)->prev == *head)
        {
            removeAllSongs(&(*head)->songs);
            free(*head);
        }
        else
        {
            (*head)->prev->next = NULL;

            while (*head != NULL)
            {
                Genre *temp = *head;
                *head = (*head)->next;

                removeAllSongs(&temp->songs);
                free(temp);
            }
        }

        *head = NULL;
    }

    return true;
}

void printGenres(Genre **head, void (*callback)(Song**))
{
    if (*head != NULL)
    {
        int i = 1;
        Genre *curr = *head;

        do
        {
            printf("%d) %s\n", i, curr->name);

            if (callback != NULL)
            {
                callback(&curr->songs);
            }

            ++i;
            curr = curr->next;
        }
        while (curr != *head);

        printf("\n");
    }
    else
    {
        printf("(Empty)\n");
    }

}

void printAll(Genre **head)
{
    printGenres(head, printSongs);
}

