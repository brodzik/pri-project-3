/*
 *  [PRI] Project 3
 *  Playlist manager.
 *
 *  util.c - utility function implementations
 *
 *  Adrian Brodzik
 *  Warsaw University of Technology
 *  Faculty of Electronics and Information Technology
 */

#include "utility.h"

void *safeMalloc(size_t size)
{
    void *mem = malloc(size);

    if (mem == NULL)
    {
        printf("Fatal: failed to allocate '%lu' bytes of memory at '%p'\n", size, mem);
        exit(-1);
    }

    return mem;
}

