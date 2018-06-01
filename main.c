#include <stdio.h>
#include "queue.h"

membuf_t inbuf[] =
{
    {
        .length = 3,
        .buffer = "lyy"
    },
    {0, NULL, 3, "ljk"},
    {0, NULL, 3, "gpy"},
    [MAX_QUEUE_SIZE] =
    {
        .length = 3,
        .buffer = "njr"
    }
};

int main(int argc, char *argv[])
{
    int i = 0, ret = 0;
    membuf_t outbuf = {0};

    queue_t *h = queue_create();

    for(i = 0; i < sizeof(inbuf)/sizeof(membuf_t); i++)
        queue_in(h, &inbuf[i]);

    fprintf(stdout, "%s %s:%u - head: %d\n", __FUNCTION__, __FILE__, __LINE__, h->head);
    fprintf(stdout, "%s %s:%u - tail: %d\n", __FUNCTION__, __FILE__, __LINE__, h->tail);
    fprintf(stdout, "%s %s:%u - count: %d\n", __FUNCTION__, __FILE__, __LINE__, h->count);
    queue_dump(h);

    for(i = 0; i < sizeof(inbuf)/sizeof(membuf_t); i++)
        queue_out(h, &outbuf);

    fprintf(stdout, "%s %s:%u - head: %d\n", __FUNCTION__, __FILE__, __LINE__, h->head);
    fprintf(stdout, "%s %s:%u - tail: %d\n", __FUNCTION__, __FILE__, __LINE__, h->tail);
    fprintf(stdout, "%s %s:%u - count: %d\n", __FUNCTION__, __FILE__, __LINE__, h->count);
    queue_dump(h);

    queue_destroy(h);
    return ret;
}
