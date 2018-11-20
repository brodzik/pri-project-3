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

Node *createNode(void *data, size_t size)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = malloc(size);
    memcpy(new_node->data, data, size);

    return new_node;
}

void pushBack(Node **head, void *data, size_t size)
{
    Node *new_node = createNode(data, size);

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

void pushFront(Node **head, void *data, size_t size)
{
    Node *new_node = createNode(data, size);

    if (*head == NULL)
    {
        new_node->prev = new_node;
        new_node->next = new_node;

        *head = new_node;
    }
    else
    {
        Node *last = (*head)->prev;

        new_node->next = *head;
        new_node->prev = last;

        last->next = new_node;
        (*head)->prev = new_node;

        *head = new_node;
    }
}

bool insertAfter(Node **head, void *data, size_t size, int index)
{
    if (*head != NULL)
    {
        Node *last = *head;
        int i = 1;

        while (i != index && last->next != *head)
        {
            ++i;
            last = last->next;
        }

        if (i == index)
        {
            Node *new_node = createNode(data, size);

            new_node->next = last->next;
            new_node->prev = last;

            last->next->prev = new_node;
            last->next = new_node;

            return true;
        }
    }

    return false;
}

Node *getNode(Node **head, int index)
{
    if (*head == NULL)
    {
        return NULL;
    }

    Node *last = *head;
    int i = 1;

    while (i != index && last->next != *head)
    {
        ++i;
        last = last->next;
    }

    if (i == index)
    {
        return last;
    }
    else
    {
        return NULL;
    }
}

bool removeNodeAt(Node **head, int index)
{
    if (*head != NULL)
    {
        Node *curr = *head;
        int i = 1;

        while (i != index && curr->next != *head)
        {
            ++i;
            curr = curr->next;
        }

        if (i == index)
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

            free(curr->data);
            free(curr);

            return true;
        }
    }

    return false;
}

