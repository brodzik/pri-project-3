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

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING 101

typedef struct Node Node;
struct Node
{
    void *data;
    Node *prev, *next;
};

void pushBack(Node **head, void *data, size_t size);

void pushFront(Node **head, void *data, size_t size);

bool insertAfter(Node **head, void *data, size_t size, int index);

