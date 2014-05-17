/*************************************************************************
	> File Name: stack.c
	> Created Time: 2014年05月06日 星期二 12时42分59秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "dlist.h"


static void push(struct stack *stack, const void *data, size_t size)
{
	assert(stack != NULL);
	assert(data != NULL);
	stack->dlist->add(stack->dlist, data, size);
}

static int is_empty(struct stack *stack)
{
	return stack->dlist->is_empty(stack->dlist);
}
static int top(struct stack *stack, void *dest, size_t size)
{
	if (is_empty(stack)) {
		return -1;
	}
	memcpy(dest, stack->dlist->head->next->data, size);
	return 0;

}


static int pop(struct stack *stack, void *dest, size_t size)
{
	if (top(stack, dest, size) < 0) {
		return -1;
	}
	stack->dlist->del(stack->dlist->head->next);
	return 0;
}

int stack_init(struct stack *stack)
{
	assert(stack != NULL);

	stack->dlist = (struct dlist *)malloc(sizeof(struct dlist));
	assert(stack->dlist != NULL);

	dlist_init(stack->dlist);

	stack->push = push;
	stack->pop = pop;
	stack->top = top;
	stack->is_empty = is_empty;

	return 0;
}

int stack_destroy(struct stack *stack)
{
	assert(stack != NULL);
	dlist_destroy(stack->dlist);
	free(stack->dlist);
	return 0;
}
