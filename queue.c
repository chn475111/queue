#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "queue.h"

queue_t* queue_create()
{
    queue_t *h = (queue_t*)malloc(sizeof(queue_t));
    if(h == NULL)
    {
        fprintf(stderr, "%s %s:%u - %d: %s\n", __FUNCTION__, __FILE__, __LINE__, errno, strerror(errno));
        return NULL;
    }
    memset(h, 0, sizeof(queue_t));

    h->head = 0;
    h->tail = MAX_QUEUE_SIZE - 1;
    h->count = 0; 
    return h;
}

int queue_in(queue_t *h, membuf_t *inbuf)
{
    if(h->count >= MAX_QUEUE_SIZE)
    {
        fprintf(stderr, "%s %s:%u - queue is full\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
    }

    h->tail = (h->tail + 1) % MAX_QUEUE_SIZE;
    h->count = h->count + 1;

    h->membuf[h->tail].len = inbuf->len;
    h->membuf[h->tail].pos = inbuf->pos;
    h->membuf[h->tail].length = inbuf->length;
    memcpy(h->membuf[h->tail].buffer, inbuf->buffer, MAX_BUFFER_SIZE);
    return 0;
}

int queue_out(queue_t *h, membuf_t *outbuf)
{
    if(h->count <= 0)
    {
        fprintf(stderr, "%s %s:%u - queue is empty\n", __FUNCTION__, __FILE__, __LINE__);
        return -1;
    }

    if(outbuf)
    {
        outbuf->len = h->membuf[h->head].len;
        outbuf->pos = h->membuf[h->head].pos;
        outbuf->length = h->membuf[h->head].length;
        memcpy(outbuf->buffer, h->membuf[h->head].buffer, MAX_BUFFER_SIZE);
    }

    h->head = (h->head + 1) % MAX_QUEUE_SIZE;
    h->count = h->count - 1;
    return 0;
}

int queue_count(queue_t *h)
{
    return h->count;
}

void queue_dump(queue_t *h)
{
    int i = 1;
    int head = h->head;
    for(i = 1; i <= h->count; i++)
    {
        fprintf(stdout, "%d - %d: %s %d: %s\n", i, h->membuf[head].len, h->membuf[head].pos, h->membuf[head].length, h->membuf[head].buffer);
        head = (head + 1) % MAX_QUEUE_SIZE;
    }
}

void queue_destroy(queue_t *h)
{
    if(h) free(h);
}
