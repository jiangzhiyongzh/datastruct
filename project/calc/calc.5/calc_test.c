/*************************************************************************
	> File Name: calc_test.c
	> Created Time: 2014年05月06日 星期二 18时11分22秒
 ************************************************************************/

#include <stdio.h>
#include "calc.h"
#include <assert.h>

int main(int argc, char *argv[])
{
	assert(argc >= 2);

	struct calc *calc = (struct calc *)malloc(sizeof(*calc));
	assert(calc != NULL);
	calc_init(calc);
	printf("%s = %d\n", argv[1], calc->parser(calc, argv[1]));

	calc_destroy(calc);
	free(calc);
	return 0;
}
