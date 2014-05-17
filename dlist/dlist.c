#include "dlist.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*  头插  */
static void add(struct list *list, void *data, size_t size)
{
	assert(list != NULL);
	assert(data != NULL);

	struct node *pa = (struct node *)malloc(sizeof(*pa)+size);
	assert(pa != NULL);

	memcpy(pa->data, data, size); /* 将数据拷贝到节点中 */

	pa->next = list->head->next;
	pa->prev = list->head;

	list->head->next = pa;
	pa->next->prev = pa;
}


/* 尾插  */
static void add_tail(struct list *list, void *data, size_t size)
{

}

/*  顺向遍历  */
static void for_each(struct list *list, void (*todo)(struct node *node))
{
	assert(list != NULL);
	struct node *cur = list->head->next;
	for(; cur != list->head; cur = cur->next)
		todo(cur);
}


/* 反向遍历  */
static void for_each_rev(struct list *list, void (*todo)(struct node *node))
{
	assert(list != NULL);
	struct node *cur = list->head->prev;
	for(; cur != list->head; cur = cur->prev)
		todo(cur);
}

/* 查找 */
static struct node *find(struct list *list, const void *key, int (*cmp)(const struct node *node, const void *key))
{
	static struct node *cur = NULL;
	if (cur == NULL) {
		cur = list->head;
	}
	for (cur = cur->next; cur != list->head; cur = cur->next) {
		if (cmp(cur, key)) {
			return cur;
		}
	}
	
	return NULL;
}

/* 删除 */
static void del(struct node *node)
{
	assert(node != NULL);
	
	node->prev->next = node->next;
	node->next->prev = node->prev;

	node->next = node;
	node->prev = node;
	free(node);

}


/*初始化函数 */
void init(struct list *list)
{
	assert(list != NULL);
	list->head = (struct node *)malloc(sizeof(*list->head));  /* 申请头节点空间 */
	assert(list->head != NULL);

	list->head->next = list->head;   /* 初始化头节点 */
	list->head->prev = list->head;
	list->head->data[0] = 0;

	list->add = add;      /* 挂载函数 */
	list->add_tail = add_tail;
	list->for_each = for_each;
	list->for_each_rev = for_each_rev;
	list->find = find;
	list->del = del;
}

void destroy(struct list *list)
{
	while(list->head->next != list->head)
		del(list->head->next);
	free(list->head);
	free(list);
}
