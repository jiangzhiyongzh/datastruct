/*************************************************************************
	> File Name: address_list.c
	> Created Time: 2014年05月09日 星期五 10时39分47秒
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include "address_list.h"
#include <string.h>
#include <stdlib.h>


static size_t hash(const struct list_head *node)
{
    struct data_info *pa = container_of(node, struct data_info, list);
	return pa->name[0] - 'a';
}

static int hash_cmp(const struct list_head *a, const struct list_head *b) 
{
    struct data_info *pa = container_of(a, struct data_info, list);
    struct data_info *pb = container_of(b, struct data_info, list);
    return strcmp(pa->name, pb->name) == 0;
}
#if 0
static void get_from_txt(struct address_list *pdlist)
{
	FILE *fp = NULL;
	struct data_info *pa = NULL;
	if (fopen("address_list.txt", "r+") < 0) {
		perror("open file for read error ");
		exit(-1);
	}

//	while( fscanf(fp, "%s"))

}
#endif

static struct list_head *get_add_node()
{
	struct data_info *pa = (struct data_info *)malloc(sizeof(*pa));
	printf("Please input \n");
	printf("name> ");
	scanf("%s", pa->name);
	printf("py> ");
	scanf("%s", pa->pyname);
	printf("tel> ");
	scanf("%s", pa->tel);
	printf("email> ");
	scanf("%s", pa->email);
	getchar();
	return &pa->list;
}


static void address_list_save(struct address_list *palist)
{
	assert(palist != NULL);
	FILE *fp = NULL;
	if ((fp = fopen("address_list.txt", "a+")) < 0) {
		perror("open file for write error");
		exit(-1);
	}
	int i = 0;
	struct data_info *pa;
	for (i = 0; i < palist->phtable->nmemb; i++) {
		list_for_each_entry(pa, palist->phtable->tab + i, list) {
			fprintf(fp, "%s:%s:%s:%s\n", pa->name, pa->pyname, pa->tel, pa->email);
		}
	}
	fclose(fp);
}

static void address_list_for_each(struct address_list *palist)
{	
	assert(palist != NULL);
	int i = 0;
	struct data_info *pa = NULL;

	for (i = 0; i < palist->phtable->nmemb; i++) {
		list_for_each_entry(pa, palist->phtable->tab + i, list) {
			printf("%s:%s:%s:%s\n", pa->name, pa->pyname, pa->tel, pa->email);
		}
	}
}
static int address_list_del(struct address_list *palist)
{
	assert(palist != NULL);
	printf("Please input the name you want to del\n");
	struct data_info *pdata_to_del = (struct data_info *)malloc(sizeof(*pdata_to_del));
	scanf("%s", pdata_to_del->name);
	getchar();
	palist->phtable->del(palist->phtable, &pdata_to_del->list);
	return 0;
}
static int address_list_add(struct address_list *palist)
{
	assert(palist != NULL);
	struct list_head *node = get_add_node(palist);
	palist->phtable->push(palist->phtable, node);
	return 0;
}

static struct list_head *address_list_search(const struct address_list *palist)
{
	assert(palist != NULL);
	printf("Please input the name you want to search\n");
	struct data_info *pdata_to_find = (struct data_info *)malloc(sizeof(*pdata_to_find));
	scanf("%s", pdata_to_find->name);
	getchar();
	struct list_head *node = palist->phtable->search(palist->phtable, &pdata_to_find->list);
	struct data_info *pa = container_of(node, struct data_info, list);

	printf("Got it :\n %s:%s:%s:%s\n", pa->name, pa->pyname, pa->tel, pa->email);
	
	return NULL;
}


void address_list_init(struct address_list *palist)
{
	assert(palist != NULL);

	palist->phtable = (struct hash_table *)malloc(sizeof(struct hash_table));
	assert(palist->phtable != NULL);
	hash_table_init(palist->phtable, 26, hash, hash_cmp);
	

	palist->add = address_list_add;
	palist->search = address_list_search;
	palist->del = address_list_del;
	palist->save = address_list_save;
	palist->for_each = address_list_for_each;
}

void address_list_destroy(struct address_list *palist)
{
	assert(palist != NULL);
	hash_table_destroy(palist->phtable);
	free(palist->phtable);
	exit(0);
}
