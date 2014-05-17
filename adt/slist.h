#pragma once 
#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;
struct node_info {
	elem_t data;
	struct node_info *next;

};

struct slist_info {

	struct node_info phead;
	/*insert*/
	void add(struct slist_info *, elem_t);
	
	/*del*/
	void del(struct slist *, elem_t);
	
	/*for_each*/
	void for_each(struct slist *);

	/*search*/
	struct slist *get_elem(struct slist *, int);
	struct slist *locate_elem(struct slist *, int);

	/*is_empty*/
	int is_empty(struct slist *);
};

/*init*/

struct node_info init();
/*destroy*/
void destroy(struct slist *);
