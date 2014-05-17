/*************************************************************************
	> File Name: test.c
	> Created Time: 2014年05月08日 星期四 10时35分10秒
 ************************************************************************/

#include <stdio.h>
#include "list.h"

struct data_info {
	char *name;
	int age;
	struct list_head list;
};

int main(void)
{
	LIST_HEAD_INIT(head);
	struct data_info s[] = {
		{"mary", 25},
		{"candy", 18},
		{"jack", 24},
	};

	int i = 0;
	for (; i < sizeof(s) / sizeof(s[0]); i++) {
		list_add(&s[i].list, &head);
	}

	struct list_head *cur = NULL;
	struct data_info *pa = NULL;
	list_for_each(cur, &head) {
		pa = container_of(cur, struct data_info, list);
		printf("%s %d\n", pa->name, pa->age);
	}
	

	
	return 0;
}
