#pragma once 
#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;
struct slist {
	elem_t data;
	struct slist *next;
};


/*init*/
struct slist *init(void);

/*insert*/
void insert(struct slist *, elem_t);

/*del*/
void del(struct slist *, elem_t);

/*for_each*/
void for_each(struct slist *);

/*search*/
struct slist *get_elem(struct slist *, int);
struct slist *locate_elem(struct slist *, int);

/*is_empty*/
int is_empty(struct slist *);

/*destroy*/
void destroy(struct slist *);
