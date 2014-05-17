/*************************************************************************
	> File Name: joseph_loop_test.c
	> Created Time: 2014年05月08日 星期四 11时33分36秒
 ************************************************************************/

#include <stdio.h>
#include "lis.h"

struct data_info {
	char *name;
	struct list_head *list;
};


int main(void)
{
	struct data_info s[] = {
		{"aaa"},
		{"bbb"},
		{"ccc"},
		{"ddd"},
		{"eee"},
		{"fff"},
		{"ggg"},
		{"hhh"},
		{"iii"},
		{"jjj"},
		{"kkk"},
		{"lll"},
		{"mmm"},
	};

	int i = 0;
	for (; i < sizeof(s) / sizeof(s[0]); i++) {
		list_add()









	return 0;
}
