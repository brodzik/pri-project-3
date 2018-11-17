/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  list.c - generic circular doubly linked list implementation
 *  
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "list.h"

void pushBack(Node **head, void *data, size_t size)
{
    Node *new_node = (Node*)malloc(sizeof(Node));

    new_node->data = malloc(size);
    memcpy(new_node->data, data, size);

    if (*head == NULL)
    {
        new_node->prev = new_node;
        new_node->next = new_node;
        *head = new_node;
    }
    else
    {
        // Link new node to first and last element
        new_node->next = *head;
          new_node->prev = (*head)->prev;

        // Link last element to new node
        (*head)->prev->next = new_node;

        // Link first element to new node
        (*head)->prev = new_node;
    }
}

void printList(Node **head, void (*printer)(void*))
{
    if (*head != NULL)
    {
        Node *last = *head;

        do
        {
            printer(last->data);
            last = last->next;
        }
        while (last != *head);
    }
}

