/*************************************************************************
	> File Name: queue_test.c
	> Created Time: 2014年05月06日 星期二 13时21分12秒
 ************************************************************************/

#include <stdio.h>
#include "queue.h"
#include <assert.h>

int main(void)
{
	int s[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9
	};
	struct queue *queue = (struct queue *)malloc(sizeof(*queue));
	assert(queue != NULL);
	queue_init(queue);
	int i = 0;
	for(; i < sizeof(s) / sizeof(s[0]); i++) {
		queue->push(queue, s+i, sizeof(s[0]));
	}

	int ret = 0;
	while(1) {
		if (queue->pop(queue, &ret, sizeof(ret)) < 0) {
			printf("end.\n");
			break;
		}
		printf("%d ", ret);
	}
	queue_destroy(queue);
	free(queue);

	return 0;
}
