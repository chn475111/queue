#ifndef __QUEUE_H__
#define __QUEUE_H__

#define MAX_QUEUE_SIZE 16
#define MAX_BUFFER_SIZE 4096

typedef struct membuf_s
{
    int len;                                //动态长度
    unsigned char *pos;                     //动态指针

    int length;                             //缓存长度
    unsigned char buffer[MAX_BUFFER_SIZE];  //缓存地址
}membuf_t;

typedef struct queue_s
{
    int head;
    int tail;
    int count;
    membuf_t membuf[MAX_QUEUE_SIZE];        //缓存队列
}queue_t;

queue_t* queue_create();

int queue_in(queue_t *h, membuf_t *inbuf);

int queue_out(queue_t *h, membuf_t *outbuf);

int queue_count(queue_t *h);

void queue_dump(queue_t *h);

void queue_destroy(queue_t *h);

#endif
