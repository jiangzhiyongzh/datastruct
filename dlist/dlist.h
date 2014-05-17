#pragma once
#include <stdlib.h>
struct node {
	struct node *prev;
	struct node *next;
	char data[1];
};
struct list {
	struct node *head;
	void (*add)(struct list *, void *, size_t);
	void (*add_tail)(struct list *, void *, size_t);
	void (*for_each)(struct list *, void (*)(struct node *));
	void (*for_each_rev)(struct list *, void (*)(struct node *));
	struct node *(*find)(struct list *, const void *, int (*cmp)(const struct node *, const void *));
	void (*del)(struct node *); 
};
void init(struct list *);
void destroy(struct list *);
