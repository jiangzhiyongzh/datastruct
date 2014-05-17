/*************************************************************************
	> File Name: stack_test.c
	> Created Time: 2014年05月06日 星期二 13时21分12秒
 ************************************************************************/

#include <stdio.h>
#include "stack.h"
#include <assert.h>

int main(void)
{
	int s[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9
	};
	struct stack *stack = (struct stack *)malloc(sizeof(*stack));
	assert(stack != NULL);
	stack_init(stack);
	int i = 0;
	for(; i < sizeof(s) / sizeof(s[0]); i++) {
		stack->push(stack, s+i, sizeof(s[0]));
	}

	int ret = 0;
	while(1) {
		if (stack->pop(stack, &ret, sizeof(ret)) < 0) {
			printf("end.\n");
			break;
		}
		printf("%d ", ret);
	}
	stack_destroy(stack);
	free(stack);

	return 0;
}
