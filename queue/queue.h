/*************************************************************************
	> File Name: queue.h
	> Created Time: 2014年05月06日 星期二 12时38分44秒
 ************************************************************************/
#pragma once

#include "dlist.h"

struct queue {
	struct dlist *dlist;
	void (*push)(struct queue *queue, const void *data, size_t size);
	int (*pop)(struct queue *queue, void *dest, size_t size);
	int (*top)(struct queue *queue, void *dest, size_t size);
	int (*is_empty)(struct queue *queue);
};

int queue_init(struct queue *queue);
int queue_destroy(struct queue *queue);
