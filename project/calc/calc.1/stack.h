/*************************************************************************
	> File Name: stack.h
	> Created Time: 2014年05月06日 星期二 12时38分44秒
 ************************************************************************/
#pragma once

#include "dlist.h"

struct stack {
	struct dlist *dlist;
	void (*push)(struct stack *stack, const void *data, size_t size);
	int (*pop)(struct stack *stack, void *dest, size_t size);
	int (*top)(struct stack *stack, void *dest, size_t size);
	int (*is_empty)(struct stack *stack);
};

int stack_init(struct stack *stack);
int stack_destroy(struct stack *stack);
