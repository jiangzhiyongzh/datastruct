/*************************************************************************
	> File Name: test.c
	> Created Time: 2014年05月13日 星期二 14时14分54秒
 ************************************************************************/
#include <stdio.h>
#include <mysort.h>

struct data_info {
	char *name;
	int age;
};

int int_cmp(const void *a, const void *b)
{
	struct data_info *pa = (struct data_info *)a;
	struct data_info *pb = (struct data_info *)b;
	
	return *pa->name - *pb->name;
}

int main(void)
{
	struct data_info s[] = {{"mary", 3}, {"jack", 5}, {"candy", 2}, {"john", 25}, {"yoyo",2}, {"niko",8}, {"richard", 9}};
	int i;
	printf("--------------before sort-------------\n");
	for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		printf("%s ", s[i].name);
	}
	printf("\n\n");
#if 0
	printf("--------------bubble sort-------------\n");
	array_bubble_sort(s, sizeof(s) / sizeof(s[0]), sizeof(s[0]), int_cmp);
	for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		printf("%s ", s[i].name);
	}
	printf("\n\n");
#endif
#if 0 
	printf("--------------select sort-------------\n");
	array_select_sort(s, sizeof(s) / sizeof(s[0]), sizeof(s[0]), int_cmp);
	for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		printf("%s ", s[i].name);
	}
	printf("\n\n");
#endif
#if 0 
	printf("--------------insert sort-------------\n");
	array_insert_sort(s, sizeof(s) / sizeof(s[0]), sizeof(s[0]), int_cmp);
	for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		printf("%s ", s[i].name);
	}
	printf("\n\n");
#endif
#if 0 
	printf("--------------shell sort-------------\n");
	array_shell_sort(s, sizeof(s) / sizeof(s[0]), sizeof(s[0]), int_cmp);
	for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		printf("%s ", s[i].name);
	}
	printf("\n\n");
#endif
#if 0  
	printf("--------------merge sort-------------\n");
	array_merge_sort(s, sizeof(s) / sizeof(s[0]), sizeof(s[0]), int_cmp);
	for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		printf("%s ", s[i].name);
	}
	printf("\n\n");
#endif
#if 1  
	printf("--------------quick sort-------------\n");
	array_quick_sort(s, sizeof(s) / sizeof(s[0]), sizeof(s[0]), int_cmp);
	for (i = 0; i < sizeof(s) / sizeof(s[0]); i++) {
		printf("%s ", s[i].name);
	}
	printf("\n\n");
#endif
	return 0;
}
