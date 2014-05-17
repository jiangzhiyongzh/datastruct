/*************************************************************************
	> File Name: address_list_test.c
	> Created Time: 2014年05月09日 星期五 10时54分17秒
 ************************************************************************/

#include <stdio.h>
#include "address_list.h"
#include <assert.h>
#include <stdlib.h>

int main(void)
{
	struct address_list *palist = (struct address_list *)malloc(sizeof(*palist));
	assert(palist != NULL);
	address_list_init(palist);
	char c;
	while(1) {
		printf("		a) for add;\n		d) for del;\n		f) for find;\n		l) for list;\n		s) for save;\n		q) for quit;\n");
		printf("# ");
		scanf("%c", &c);
		getchar();
		switch (c) {
			case 'a' : palist->add(palist);break;
			case 's' : palist->save(palist);break;
			case 'd' : palist->del(palist);break;
			case 'q' : address_list_destroy(palist);break;
			case 'l' : palist->for_each(palist);break;
			case 'f' : palist->search(palist);break;
			default : printf("invalid character\n");
		}
	}
	
	return 0;
}
