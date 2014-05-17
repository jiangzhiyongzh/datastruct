/*************************************************************************
	> File Name: hash_table.h
	> Created Time: 2014年05月08日 星期四 16时17分47秒
 ************************************************************************/
#pragma once
#include "list.h"

struct hash_table {
	struct list_head *tab;  /* 哈希表首元素的地址 */
	size_t nmemb;           /* 哈希表元素个数 */
	size_t (*hash)(const struct list_head *node); /* 哈希函数  */
	int (*hash_cmp)(const struct list_head *a, const struct list_head *b); /*哈希比较 */
	int (*push)(struct hash_table *phtable, struct list_head *node);
	struct list_head *(*search)(const struct hash_table *phtable, const struct list_head *key);
	int (*del)(struct hash_table *phtable, struct list_head *node);
};

int hash_table_init(struct hash_table *phtable, size_t nmemb,
		size_t (*hash)(const struct list_head *node),
		int (*hash_cmp)(const struct list_head *a, const struct list_head *b));

int hash_table_destroy(struct hash_table *phtable);
