/*************************************************************************
	> File Name: hash_test.c
	> Created Time: 2014年05月08日 星期四 18时48分34秒
 ************************************************************************/

#include <stdio.h>
#include "hash_table.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct data_info {
	char *name;
	char *tel;
	struct list_head list;
};


size_t hash(const struct list_head *node)
{
	struct data_info *pa = container_of(node, struct data_info, list);
	return pa->name[0];
}


int hash_cmp(const struct list_head *a, const struct list_head *b)
{
	struct data_info *pa = container_of(a, struct data_info, list);
	struct data_info *pb = container_of(b, struct data_info, list);
	return strcmp(pa->name, pb->name) == 0;
}


int main(void)
{
	struct data_info s[] = {
		{"tom", "137"},
		{"mary", "135"},
		{"candy", "155"},
		{"jack", "189"},
		{"richard", "131"},
	};
	
	struct hash_table *phtable = (struct hash_table *)malloc(sizeof(*phtable));
	assert(phtable != NULL);
	hash_table_init(phtable, 3, hash, hash_cmp);

	int i = 0;
	for(; i < sizeof(s) / sizeof(s[0]); i++) {
		phtable->push(phtable, &s[i].list);
	}

	
	struct data_info person = {"jack", "122"};
	phtable->del(phtable, &(person.list));
	struct list_head *pa = phtable->search(phtable, &(person.list));
	if (pa == NULL) {
		printf("not fount\n");
	} else {
		struct data_info *p = container_of(pa, struct data_info, list);
		printf("%s %s\n", p->name, p->tel);
	}
	hash_table_destroy(phtable);
	free(phtable);
	return 0;
}
