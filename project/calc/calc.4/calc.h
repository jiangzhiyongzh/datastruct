/*************************************************************************
	> File Name: calc.h
	> Created Time: 2014年05月06日 星期二 16时42分19秒
	> Function: 能处理括号的
 ************************************************************************/
#pragma once

#include "stack.h"   
enum flag_t {
	F_ERR = -1,
	F_OPR ,
	F_NUM
};

typedef int num_t;

struct calc {
	struct stack *num;
	struct stack *opr;
	const char *cur;
	enum flag_t pre_flag;
	num_t (*parser)(struct calc *calc, const char *expr);
};

int calc_init(struct calc *calc);
int calc_destroy(struct calc *calc);


#define NUM_PUSH(n) \
	calc->num->push(calc->num, &(n), sizeof(n))
#define NUM_TOP(n) \
	calc->num->top(calc->num, &(n), sizeof(n))
#define NUM_POP(n) \
	calc->num->pop(calc->num, &(n), sizeof(n))

#define OPR_PUSH(c) \
	calc->opr->push(calc->opr, &(c), sizeof(c))
#define OPR_TOP(c) \
	calc->opr->top(calc->opr, &(c), sizeof(c))
#define OPR_POP(c) \
	calc->opr->pop(calc->opr, &(c), sizeof(c))

#define STACK_IS_EMPTY(stack) \
	(stack)->is_empty(stack)
