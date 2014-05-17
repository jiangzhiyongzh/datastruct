/*************************************************************************
	> File Name: test.c
	> Created Time: 2014年05月12日 星期一 14时28分34秒
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "btree.h"
#include "list.h"

struct data_info {
	int data;
	struct bnode pbnode;
};

static int btree_cmp(const struct bnode *a, const struct bnode *b)
{
	struct data_info *pa = container_of(a, struct data_info, pbnode);
	struct data_info *pb = container_of(b, struct data_info, pbnode);
	return pa->data - pb->data;
}

static void print_bnode(struct bnode *pbnode)
{
	struct data_info *pa = container_of(pbnode, struct data_info, pbnode);
	printf("%d ", pa->data);
}

int main(void)
{
	struct data_info s[] = {{6}, {4}, {9}, {2}, {5}, {7}};
	struct btree *pbtree = (struct btree *)malloc(sizeof(*pbtree));
	assert(pbtree != NULL);

	btree_init(pbtree, btree_cmp);
	int i;
	for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		pbtree->push(pbtree, &s[i].pbnode);
	}

	printf("---------pre_order------------\n");
	pbtree->pre_order(pbtree, print_bnode);
	printf("\n");
	printf("---------in_order-------------\n");
	pbtree->in_order(pbtree, print_bnode);
	printf("\n");
	printf("---------post_order-----------\n");
	pbtree->post_order(pbtree, print_bnode);
	printf("\n");
	printf("---------level_order----------\n");
	pbtree->level_order(pbtree, print_bnode);
	printf("\n");
	btree_destroy(pbtree);
	free(pbtree);
	return 0;
}
