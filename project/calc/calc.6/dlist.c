#include "dlist.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*  头插  */
static void add(struct dlist *dlist, const void *data, size_t size)
{
	assert(dlist != NULL);
	assert(data != NULL);

	struct node *pa = (struct node *)malloc(sizeof(*pa)+size);
	assert(pa != NULL);

	memcpy(pa->data, data, size); /* 将数据拷贝到节点中 */

	pa->next = dlist->head->next;
	pa->prev = dlist->head;

	dlist->head->next = pa;
	pa->next->prev = pa;
}

static int is_empty(struct dlist *dlist)
{
	return (dlist->head->next == dlist->head) && (dlist->head->prev == dlist->head);
}


/* 尾插  */
static void add_tail(struct dlist *dlist, const void *data, size_t size)
{

}

/*  顺向遍历  */
static void for_each(struct dlist *dlist, void (*todo)(struct node *node))
{
	assert(dlist != NULL);
	struct node *cur = dlist->head->next;
	for(; cur != dlist->head; cur = cur->next)
		todo(cur);
}


/* 反向遍历  */
static void for_each_rev(struct dlist *dlist, void (*todo)(struct node *node))
{
	assert(dlist != NULL);
	struct node *cur = dlist->head->prev;
	for(; cur != dlist->head; cur = cur->prev)
		todo(cur);
}

/* 查找 */
static struct node *find(struct dlist *dlist, const void *key, int (*cmp)(const struct node *node, const void *key))
{
	static struct node *cur = NULL;
	if (cur == NULL) {
		cur = dlist->head;
	}
	for (cur = cur->next; cur != dlist->head; cur = cur->next) {
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
void dlist_init(struct dlist *dlist)
{
	assert(dlist != NULL);
	dlist->head = (struct node *)malloc(sizeof(*dlist->head));  /* 申请头节点空间 */
	assert(dlist->head != NULL);

	dlist->head->next = dlist->head;   /* 初始化头节点 */
	dlist->head->prev = dlist->head;
	dlist->head->data[0] = 0;

	dlist->add = add;      /* 挂载函数 */
	dlist->add_tail = add_tail;
	dlist->for_each = for_each;
	dlist->for_each_rev = for_each_rev;
	dlist->find = find;
	dlist->is_empty = is_empty;
	dlist->del = del;
}

void dlist_destroy(struct dlist *dlist)
{
	while(dlist->head->next != dlist->head)
		del(dlist->head->next);
	free(dlist->head);
}
