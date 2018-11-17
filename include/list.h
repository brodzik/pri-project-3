/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  list.h - generic circular doubly linked list definition
 *  
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING 100

typedef struct Node Node;
struct Node
{
    void *data;
    Node *prev, *next;
};

void pushBack(Node **head, void *data, size_t size);

void printList(Node **head, void (*printer)(void*));

