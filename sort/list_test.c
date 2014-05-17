/*************************************************************************
	> File Name: test.c
	> Created Time: 2014年05月14日 星期三 10时29分43秒
 ************************************************************************/
#include <stdio.h>
#include <mysort.h> 
#include <assert.h>
#include <stdlib.h>

struct data_info {
	int data;
	struct list_head list;
};

int list_cmp(const struct list_head *a, const struct list_head *b)
{
	struct data_info *pa = container_of(a, struct data_info, list);
	struct data_info *pb = container_of(b, struct data_info, list);
	return pa->data - pb->data;
}

int main(void)
{
	struct data_info s[] = {{1}, {4}, {6}, {7}};
	struct list_head *phead = (struct list_head *)malloc(sizeof(*phead));
	assert(phead != NULL);
	list_head_init(phead);

	int i;
	for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		list_add(&s[i].list, phead);
	}
#if 0
	printf("---------------before sort----------------\n");
	struct data_info *pa = NULL;
	list_for_each_entry(pa, phead, list) {
		printf("%d ", pa->data);
	}
	printf("\n");
#endif
#if 0	
	printf("---------------bubble sort----------------\n");
	list_bubble_sort(phead, list_cmp);
	list_for_each_entry(pa, phead, list) {
		printf("%d ", pa->data);
	}
	printf("\n");
#endif
#if 0
	printf("---------------select sort----------------\n");
	list_select_sort(phead, list_cmp);
	list_for_each_entry(pa, phead, list) {
		printf("%d ", pa->data);
	}
	printf("\n");
#endif
#if 0
	printf("---------------bubble sort----------------\n");
	list_select_sort(phead, list_cmp);
	list_for_each_entry(pa, phead, list) {
		printf("%d ", pa->data);
	}
	printf("\n");
#endif
#if 1 
	printf("---------------shell sort----------------\n");
	list_select_sort(phead, list_cmp);
	list_for_each_entry(pa, phead, list) {
		printf("%d ", pa->data);
	}
	printf("\n");
#endif
#if 1 
	printf("---------------merge sort----------------\n");
	list_select_sort(phead, list_cmp);
	list_for_each_entry(pa, phead, list) {
		printf("%d ", pa->data);
	}
	printf("\n");
#endif
#if 1 
	printf("---------------quick sort----------------\n");
	list_select_sort(phead, list_cmp);
	list_for_each_entry(pa, phead, list) {
		printf("%d ", pa->data);
	}
	printf("\n");
#endif
	return 0;
}
