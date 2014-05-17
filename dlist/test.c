#include "dlist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_node(struct node *);
int cmp_name(const struct node *, const void *);
int cmp_age(const struct node *, const void *);

struct data_info {
	char name[10];
	int age;
};

int main(void)
{
	struct list *list = (struct list *)malloc(sizeof(*list));
	assert(list != NULL);

	init(list);	
	struct data_info s[]= {
		{"jack", 13},
		{"mary", 18},
		{"candy", 20},
	};
	int i = 0;
	for (; i < sizeof(s) / sizeof(s[0]); i++) {
		list->add(list, s + i, sizeof(s[0]));
	}

	printf("顺向遍历:\n");	
	list->for_each(list, print_node);
	
	printf("逆向遍历:\n");	
	list->for_each_rev(list, print_node);
	
	struct node *node = NULL;
#if 1	
	printf("按姓名查找\n");
	node = list->find(list, "jack", cmp_name);
	if (node == NULL) {
		printf("没有找到\n");
	} else {
		struct data_info *info = (struct data_info *)node->data;
		printf("%s: %d\n", info->name, info->age);
		printf("删除该节点\n");
		list->del(node);
	}
#endif

#if 0 
	printf("按年龄查找\n");
	while(1) {
		node = list->find(list, (int *)19, cmp_age);
		if (node == NULL) {
			break;
		} else {
			struct data_info *info = (struct data_info *)node->data;
			printf("%s: %d\n", info->name, info->age);
		}
	}
#endif

	printf("顺向遍历:\n");	
	list->for_each(list, print_node);
	destroy(list);

	return 0;
}



void print_node(struct node *node)
{
	struct data_info *getdata = (struct data_info *)node->data;
	printf("%s: %d\n", getdata->name, getdata->age);
}


int cmp_name(const struct node *node, const void *key)
{
	struct data_info *getdata = (struct data_info *)node->data;
	return strcmp(getdata->name, (const char *)key) == 0;
}

int cmp_age(const struct node *node, const void *key)
{
	int age = (int)key;
	struct data_info *getdata = (struct data_info *)node->data;
	return (getdata->age >= age);
}
