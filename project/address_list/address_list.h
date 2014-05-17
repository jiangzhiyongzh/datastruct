/*************************************************************************
	> File Name: tongxunlu.h
	> Created Time: 2014年05月09日 星期五 10时27分38秒
 ************************************************************************/
#pragma once

#define MAX_NAME_LEN 20
#define MAX_PYNAME_LEN 10
#define MAX_TEL_LEN 15
#define MAX_EMAIL_LEN 20

#include "hash_table.h"

struct data_info {
	char name[MAX_NAME_LEN];
	char pyname[MAX_PYNAME_LEN];
	char tel[MAX_TEL_LEN];
	char email[MAX_EMAIL_LEN];
	struct list_head list;
};

struct address_list {
	struct hash_table *phtable;
	void (*wait)(struct address_list *palist);
	int (*add)(struct address_list *palist);
	struct list_head *(*search)(const struct address_list *palist);
	int (*del)(struct address_list *palist);
	void (*save)(struct address_list *palist);
	void (*for_each)(struct address_list *palist);
};

void address_list_init(struct address_list *palist);
void address_list_destroy(struct address_list *palist);

