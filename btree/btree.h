/*************************************************************************
	> File Name: btree.h
	> Created Time: 2014年05月12日 星期一 13时58分30秒
 ************************************************************************/
#pragma once

struct bnode {
	struct bnode *parent;
	struct bnode *lchild;
	struct bnode *rchild;
};

struct btree {
	struct bnode *root;
	void (*push)(struct btree *pbtree, struct bnode *pbnode);
	void (*del)(struct btree *pbtree, struct bnode *pbnode);
	int (*cmp)(const struct bnode *a, const struct bnode *b);
	void (*pre_order)(struct btree *pbtree, void (*todo)(struct bnode *pbnode_todo));
	void (*in_order)(struct btree *pbtree, void (*todo)(struct bnode *pbnode_todo));
	void (*post_order)(struct btree *pbtree, void (*todo)(struct bnode *pbnode_todo));
	void (*level_order)(struct btree *pbtree, void (*todo)(struct bnode *pbnode_todo));
};

int btree_init(struct btree *pbtree, int (*cmp)(const struct bnode *a, const struct bnode *b));
int btree_destroy(struct btree *pbtree);


static inline void bnode_init(struct bnode *pbnode)
{
	pbnode->parent = NULL;
	pbnode->lchild = NULL;
	pbnode->rchild = NULL;
}
