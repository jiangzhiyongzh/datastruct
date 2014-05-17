#pragma once
#include <stdlib.h>
struct node {
	struct node *prev;
	struct node *next;
	char data[1];
};
struct dlist {
	struct node *head;
	void (*add)(struct dlist *, const void *, size_t);
	void (*add_tail)(struct dlist *, const void *, size_t);
	void (*for_each)(struct dlist *, void (*)(struct node *));
	void (*for_each_rev)(struct dlist *, void (*)(struct node *));
	struct node *(*find)(struct dlist *, const void *, int (*cmp)(const struct node *, const void *));
	void (*del)(struct node *);
	int (*is_empty)(struct dlist *);
};
void dlist_init(struct dlist *);
void dlist_destroy(struct dlist *);
