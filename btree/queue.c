/*************************************************************************
	> File Name: queue.c
	> Created Time: 2014年05月06日 星期二 12时42分59秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "queue.h"
#include "dlist.h"


static void push(struct queue *queue, const void *data, size_t size)
{
	assert(queue != NULL);
	assert(data != NULL);
	queue->dlist->add_tail(queue->dlist, data, size);
}

static int is_empty(struct queue *queue)
{
	return queue->dlist->is_empty(queue->dlist);
}
static int top(struct queue *queue, void *dest, size_t size)
{
	if (is_empty(queue)) {
		return -1;
	}
	memcpy(dest, queue->dlist->head->next->data, size);
	return 0;

}


static int pop(struct queue *queue, void *dest, size_t size)
{
	if (top(queue, dest, size) < 0) {
		return -1;
	}
	queue->dlist->del(queue->dlist->head->next);
	return 0;
}

int queue_init(struct queue *queue)
{
	assert(queue != NULL);

	queue->dlist = (struct dlist *)malloc(sizeof(struct dlist));
	assert(queue->dlist != NULL);

	dlist_init(queue->dlist);

	queue->push = push;
	queue->pop = pop;
	queue->top = top;
	queue->is_empty = is_empty;

	return 0;
}

int queue_destroy(struct queue *queue)
{
	assert(queue != NULL);
	dlist_destroy(queue->dlist);
	free(queue->dlist);
	return 0;
}
