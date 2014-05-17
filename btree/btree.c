/*************************************************************************
	> File Name: btree.c
	> Created Time: 2014年05月12日 星期一 14时05分29秒
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include "btree.h"
#include <stdlib.h>
#include "queue.h"



static void btree_del(struct btree *pbtree, struct bnode *pbnode)
{
	assert(pbtree != NULL);
	assert(pbnode != NULL);

	if (pbnode->parent->lchild == pbnode) {
		pbnode->parent->lchild = pbnode->rchild;

	}
	
}

static void btree_push(struct btree *pbtree, struct bnode *pbnode)
{
	assert(pbnode != NULL);
	assert(pbtree != NULL);
	bnode_init(pbnode);
	
	if (pbtree->root == NULL) {
		pbtree->root = pbnode;
		return ;
	}
	struct bnode *cur = NULL;
	struct bnode **pparent = &pbtree->root;
	for (; *pparent != NULL; ) {
		cur = *pparent;
		if (pbtree->cmp(pbnode, cur) >= 0) {
			pparent = &cur->rchild;
		} else {
			pparent = &cur->lchild;
		}
	}
	*pparent = pbnode;
	pbnode->parent = cur;
}


static void __pre_order(struct bnode *pbnode, void (*todo)(struct bnode *pbnode_todo))
{
	if (pbnode != NULL) {
		todo(pbnode);
		__pre_order(pbnode->lchild, todo);
		__pre_order(pbnode->rchild, todo);
	}
}
static void btree_pre_order(struct btree *pbtree, void (*todo)(struct bnode *pbnode_todo))
{
	__pre_order(pbtree->root, todo);
	assert(pbtree != NULL);
	assert(todo != NULL);
}


static void __in_order(struct bnode *pbnode, void (*todo)(struct bnode *pbnode_todo))
{
	if (pbnode != NULL) {
		__in_order(pbnode->lchild, todo);
		todo(pbnode);
		__in_order(pbnode->rchild, todo);
	}
}
static void btree_in_order(struct btree *pbtree, void (*todo)(struct bnode *pbnode_todo))
{
	__in_order(pbtree->root, todo);
	assert(pbtree != NULL);
	assert(todo != NULL);
}


static void __post_order(struct bnode *pbnode, void (*todo)(struct bnode *pbnode_todo))
{
	if (pbnode != NULL) {
		__post_order(pbnode->lchild, todo);
		__post_order(pbnode->rchild, todo);
		todo(pbnode);
	}
}
static void btree_post_order(struct btree *pbtree, void (*todo)(struct bnode *pbnode_todo))
{
	assert(pbtree != NULL);
	assert(todo != NULL);
	__post_order(pbtree->root, todo);
}

static void btree_level_order(struct btree *pbtree, void (*todo)(struct bnode *pbnode_todo))
{
	assert(pbtree != NULL);
	assert(todo != NULL);

	struct queue *pqueue = (struct queue *)malloc(sizeof(*pqueue));
	assert(pqueue != NULL);
	queue_init(pqueue);

	struct bnode *cur = pbtree->root;
	struct bnode *pbnode_todo = NULL;
	if (cur != NULL) {
		pqueue->push(pqueue, &cur, sizeof(cur));
	}
	while (!pqueue->is_empty(pqueue)) {
		pqueue->pop(pqueue, &cur, sizeof(pbnode_todo));
		todo(cur);
		if (cur->lchild != NULL) {
			pqueue->push(pqueue, &cur->lchild, sizeof(cur->lchild));
		} 
		if (cur->rchild != NULL) {
			pqueue->push(pqueue, &cur->rchild, sizeof(cur->rchild));
		}
	}
	queue_destroy(pqueue);
	free(pqueue);
}

int btree_init(struct btree *pbtree, int (*cmp)(const struct bnode *a, const struct bnode *b))
{
	assert(pbtree != NULL);
	assert(cmp != NULL);

	pbtree->root = NULL;

	pbtree->push = btree_push;
	pbtree->cmp = cmp;
	pbtree->pre_order = btree_pre_order;
	pbtree->in_order = btree_in_order;
	pbtree->post_order = btree_post_order;
	pbtree->level_order = btree_level_order;
	pbtree->del = btree_del;
	return 0;

}

int btree_destroy(struct btree *pbtree)
{
	return 0;
}
