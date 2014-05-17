/*************************************************************************
	> File Name: calc.c
	> Created Time: 2014年05月06日 星期二 16时58分06秒
 ************************************************************************/

#include <stdio.h>
#include "calc.h"
#include <assert.h>
#include <stdlib.h>



int flag = 1;
int flag1 = 1;
/* 运算时  数据栈出栈两次   操作符栈出栈一次 
 * 运算完之后的结果压栈
 * */
static int do_operate(struct calc *calc)
{
	num_t a, b;
	char c;

	if (NUM_POP(b) < 0) {
		fprintf(stderr,"Error: num pop failed.\n");
		return -1;
	}
	if (NUM_POP(a) < 0) {
		fprintf(stderr,"Error: num pop failed.\n");
		return -1;
	}
	if (OPR_POP(c) < 0) {
		fprintf(stderr,"Error: opr pop failed.\n");
		return -2;
	}

	num_t res = 0;
	switch(c) {
		case '+': res = a + b; break;
		case '-': res = a - b; break;
		case '*': res = a * b; break;
		case '/': res = a / b; break;
		case '%': res = a % b; break;
		default : break;
	}

#ifdef _DEBUG
	printf("DEBUG %d %c %d = %d\n",a, c, b, res);
#endif
	NUM_PUSH(res);

	return 0;
}

/* 将操作符转化为优先级 */
static int  opr2level(char opr)
{
	int level = 0;
	switch(opr) {
		case '+':case '-': level += 1;break;
		case '*':case '/':case '%': level += 2;break;
		default:break;
	}
	return level;
}
static int num_handler(struct calc *calc)
{
	static num_t n = 0;
	if (*calc->next >= '0' && *calc->next <= '9') {
		n = ((*calc->cur - '0') + n ) * 10;
		return 0;
	}
	n += (*calc->cur -'0');
	n = n * flag;
	NUM_PUSH(n);
	flag = 1;
	n = 0;
	return 0;
}

static int opr_handler(struct calc *calc)
{
	flag1++;
	assert(calc != NULL);
	char c = *calc->cur;
	if (*calc->next == '-')
		flag = -1;
	if ((*calc->next > '9' || *calc->next < '0') && *calc->next != '-') {
		fprintf(stderr, "Error: error expr.\n");
		exit(-1);
	}
	/* 如果操作符栈是空栈的话就压栈 */
	if (STACK_IS_EMPTY(calc->opr)) {
		OPR_PUSH(c);
		return 0;
	}

	/* 如果操作符栈非空， 且该操作符优先级高于栈顶运算符就压栈 */
	char top_c = 0;
	if (OPR_TOP(top_c) < 0) {
		fprintf(stderr, "Error: opr top failed.\n");
		return -1;
	}
	
	while(1) {
		if (opr2level(c) > opr2level(top_c) || STACK_IS_EMPTY(calc->opr)) {
			OPR_PUSH(c);
			return 0;
		}
		if (do_operate(calc) < 0) {
		fprintf(stderr, "Error: do operate failed.\n");
		return -1;
		}
		if ( !STACK_IS_EMPTY(calc->opr) && OPR_TOP(top_c) < 0) {
			fprintf(stderr, "Error: while opr top failed.\n");
			return -1;
		}
	}
	return 0;
}

static num_t parser(struct calc *calc, const char *expr)
{
	assert(calc != NULL);
	assert(expr != NULL && expr != '\0');
	
	calc->cur = expr;
	calc->next = expr;
	calc->next++;
	for (; *calc->cur != '\0'; calc->cur++, calc->next++) {
		switch(*calc->cur) {
			case '0' ... '9': num_handler(calc);break;
			case '-':if(flag1 == 1) flag = -1; if(flag == -1) break;
			case '+':
			case '*':
			case '/':
			case '%': opr_handler(calc);break;
			case ' ':
			case '\t':
			case '\n': break;
			default: fprintf(stderr, "Error: Unknow character ");return -1;
		}
	}
	while(!STACK_IS_EMPTY(calc->opr))
		do_operate(calc);
	num_t res = 0;
	NUM_POP(res);
	return res;
}
int calc_init(struct calc *calc)
{
	assert(calc != NULL);

	calc->num = (struct stack *)malloc(sizeof(struct stack));
	assert(calc->num != NULL);
	stack_init(calc->num);
	calc->opr = (struct stack *)malloc(sizeof(struct stack));
	assert(calc->opr != NULL);
	stack_init(calc->opr);
	calc->cur = NULL;
	calc->next = NULL;

	calc->parser = parser;

	return 0;
}

int calc_destroy(struct calc *calc)
{
	assert(calc != NULL);

	stack_destroy(calc->num);
	stack_destroy(calc->opr);
	free(calc->num);
	free(calc->opr);
	return 0;
}
