#include "slist.h"

int main(void)
{
	struct slist *head = init();
	
	int i;
	for (i = 0; i < 10; i++) {
		insert(head, i);
	}
	for_each(head);
	del(head, 5);
	for_each(head);

	printf("data[%d] = %d\n", 2, get_elem(head, 2)->data);
	

	destroy(head);
	return 0;
}
