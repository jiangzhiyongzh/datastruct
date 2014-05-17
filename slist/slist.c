#include "slist.h" 


/*init*/
struct slist *init(void)
{
	struct slist *head = NULL;
	if ( (head = (struct slist *)malloc(sizeof(*head))) == NULL) {
		perror("malloc failed");
		return head;
	}

	head->data = 0;
	head->next = head;

	return head;
}

/* insert */
void insert(struct slist *head, elem_t data)
{
	struct slist *new = (struct slist *)malloc(sizeof(*new));
	new->data = data;
	new->next = head->next;
	head->next = new;
}

/*for_each*/
void for_each(struct slist *head)
{
	struct slist *cur = head->next;
	for(; cur != head; cur = cur->next)
		printf("%d ",cur->data);
	putchar('\n');
}

/*del*/
void del(struct slist *head, elem_t data)
{
	struct slist *cur = head->next;
	struct slist *pre = head;
	for(; cur != head; cur = cur->next) {
		if (cur->data == data) {
			pre->next = cur->next;
			free(cur);
		} else {
			pre = cur;
		}
	}
}

/*is_empty*/
int is_empty(struct slist *head)
{
	return head->next == head ? 1 : 0;
}

/*destroy*/
void destroy(struct slist *head)
{

	while(!(is_empty(head)))
		del(head, head->next->data);
	free(head);
}

/*search*/
struct slist *get_elem(struct slist *head, int i)
{
	int n=0;
	struct slist *cur = head->next;
	for(; cur != head; cur = cur->next) {
		if (n == i) {
			return cur;
		}
		n++;
	}
	return NULL;
}

//struct slist *locate_elem(
