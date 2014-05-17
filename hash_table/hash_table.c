/*************************************************************************
	> File Name: hash_table.c
	> Created Time: 2014年05月08日 星期四 17时06分49秒
 ************************************************************************/

#include <stdio.h>
#include "hash_table.h"
#include <assert.h>
#include <stdlib.h>



static int hash_del(struct hash_table *phtable, struct list_head *node)
{
	assert(phtable != NULL);
	assert(node != NULL);
	size_t v = phtable->hash(node) % phtable->nmemb;
	struct list_head *cur = phtable->tab + v;
	list_for_each(cur, phtable->tab + v) {
		if (phtable->hash_cmp(cur, node)) {
			node_del_init(cur);
			return 0;
		}
	}
	return -1;
}

static int hash_push(struct hash_table *phtable, struct list_head *node)
{
	assert(phtable != NULL);
	assert(node != NULL);
	size_t v = phtable->hash(node) % phtable->nmemb;
	list_add_tail(node, phtable->tab + v);
	return 0;
}

static struct list_head *hash_search(const struct hash_table *phtable, const struct list_head *key)
{
	assert(phtable != NULL);
	assert(key != NULL);

	size_t v = phtable->hash(key) % phtable->nmemb;
	static struct list_head *cur = NULL;

	if (cur == NULL || !phtable->hash_cmp(key, cur)) {
		cur = phtable->tab + v;
	}

	list_for_each_continue(cur, phtable->tab + v) {
		if (phtable->hash_cmp(cur, key)) {
			return cur;
		}
	}
	return NULL;
}



int hash_table_init(struct hash_table *phtable, size_t nmemb,
		size_t (*hash)(const struct list_head *node),
		int (*hash_cmp)(const struct list_head *a, const struct list_head *b))
{
	assert(phtable != NULL);
	assert(hash != NULL);
	assert(hash_cmp != NULL);

	phtable->tab = (struct list_head *)malloc(sizeof(struct list_head) * nmemb);

	assert(phtable->tab != NULL);
	int i = 0;
	for (; i < nmemb; i++) {
		list_head_init(phtable->tab + i);
	}

	phtable->nmemb = nmemb;
	phtable->hash = hash;
	phtable->hash_cmp = hash_cmp;
	phtable->search = hash_search;
	phtable->push = hash_push;
	phtable->del = hash_del;

	return 0;
}

int hash_table_destroy(struct hash_table *phtable)
{
	int i;
	struct list_head *cur = NULL;
	struct list_head *Next = NULL;
	for (i = 0; i < phtable->nmemb; i++) {
		list_for_each_safe(cur, Next, phtable->tab + i) {
			node_del_init(cur);
		}
	}
	free(phtable->tab);
	return 0;
}
