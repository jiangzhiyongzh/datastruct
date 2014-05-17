/*************************************************************************
	> File Name: huffman.h
	> Created Time: 2014年05月15日 星期四 12时15分04秒
 ************************************************************************/
#pragma once
#include "list.h"

typedef unsigned short ui16_t;
typedef unsigned short code_t;
typedef unsigned char code_len_t;

#define LEAF_NUM 256
#define UNLEAF_NUM (LEAF_NUM - 1)
#define UNUSED_INDEX (LEAF_NUM + UNLEAF_NUM)
#define MAGIC_NUM 0xFF;
#define HF_ZIP_TYPE 0x01
#pragma pack(1)
struct huff_tree_node {
	ui16_t parent;
	ui16_t lchild;
	ui16_t rchild;
};

struct huff_table_node {
	size_t weight;
	code_t code;
	code_len_t code_len;
	struct list_head list;
	struct huff_tree_node tree;
};

struct huff_head_info {
	unsigned char magic;
	unsigned char type;
	size_t file_size;
	ui16_t root;
	size_t offset;
	char tab[1];
};
#pragma pack(0)
struct huffman {
	struct huff_table_node tab[LEAF_NUM + UNLEAF_NUM];
	struct list_head *phead;
	size_t file_size;/*解压的时候用到*/
	ui16_t root;
	FILE *fp_src;
	FILE *fp_dest;
	int (*compress)(struct huffman *phf, const char *origin, const char *zip);
	int (*decompress)(struct huffman *phf, const char *zip, const char *origin);

};

int huffman_init(struct huffman *phf);
int huffman_destroy(struct huffman *phf);

static inline void huff_table_node_init(struct huff_table_node *phftn)
{
	phftn->weight = 0;
	phftn->code = 0;
	phftn->code_len = 0;
	list_head_init(&phftn->list);
	phftn->tree.parent = UNUSED_INDEX;
	phftn->tree.lchild = UNUSED_INDEX;
	phftn->tree.rchild = UNUSED_INDEX;
}

#define WEIGHT(n)	 (phf->tab[n].weight)
#define LIST(n)  	 (phf->tab[n].list)
#define PARENT(n)	 (phf->tab[n].tree.parent)
#define LCHILD(n)	 (phf->tab[n].tree.lchild)
#define RCHILD(n)	 (phf->tab[n].tree.rchild)
#define CODE(n)  	 (phf->tab[n].code)
#define CODE_LEN(n)	 (phf->tab[n].code_len)




#define DELCHILD(n)	 (pheadinfo->tab[n].tree.lchild)
#define DERCHILD(n)	 (pheadinfo->tab[n].tree.rchild)
