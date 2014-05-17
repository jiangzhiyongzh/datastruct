/*************************************************************************
	> File Name: huffman.c
	> Created Time: 2014年05月15日 星期四 12时21分29秒
 ************************************************************************/

#include <stdio.h>
#include "huffman.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
	
static int weight_cmp(const struct list_head *a, const struct list_head *b)
{
	struct huff_table_node *pa = container_of(a, struct huff_table_node, list);
	struct huff_table_node *pb = container_of(b, struct huff_table_node, list);
	return pa->weight - pb->weight;
}
static int huff_get_weight(struct huffman *phf)
{
	assert(phf != NULL);
	unsigned char buf = 0;
	while (fread(&buf, 1, 1, phf->fp_src) != 0) {
		WEIGHT(buf) += 1;
	}
#ifdef _DEBUG
{
	int i;
	for (i = 0; i < LEAF_NUM; i++) {
		if (WEIGHT(i) > 0) {
			printf("[DEBUG] tab[%d] %c weigh: %d\n", i, i, WEIGHT(i));
		}
	}
	printf("\n");
}
#endif

	return 0;
}
static int huff_build_list_with_sort(struct huffman *phf)
{
	assert(phf != NULL);
	int i;
	for (i = 0; i < LEAF_NUM; i++) {
		if (WEIGHT(i) > 0) {
			list_add(&LIST(i), phf->phead);
		}
	}
	list_insert_sort(phf->phead, weight_cmp);
#ifdef _DEBUG
{
	struct huff_table_node *pa;
	list_for_each_entry(pa, phf->phead, list) {
		printf("[DEBUG] tab[%d] weight %d --> ", pa - phf->tab, pa->weight);	
	}
	printf("\n");
}
#endif
	return 0;
}
static int huff_build_huff_tree(struct huffman *phf)
{
	assert(phf != NULL);
	struct list_head *a, *b;
	ui16_t index = LEAF_NUM, ia, ib;
	while (phf->phead->next->next != phf->phead) {
		a = phf->phead->next;
		b = a->next;
		ia = container_of(a, struct huff_table_node, list) - phf->tab; /*下标*/
		ib = container_of(b, struct huff_table_node, list) - phf->tab;
	
		WEIGHT(index) = WEIGHT(ia) + WEIGHT(ib);
		PARENT(ia) = index;
		PARENT(ib) = index;
		LCHILD(index) = ia;
		RCHILD(index) = ib;

		node_del_init(a);  /*删除a, b*/
		node_del_init(b);
		
		list_add(&LIST(index), phf->phead); /*把中间节点加到链表中*/
		list_insert_sort(phf->phead, weight_cmp);/*排序*/
#ifdef _DEBUG
{
	printf("[DEBUG] M: tab[%d] weight %d  L: tab[%d] weight %d  R: tab[%d] weight %d\n", index, WEIGHT(index), ia, WEIGHT(ia), ib, WEIGHT(ib));
}
#endif

		index++;
	}
	phf->root = index - 1;
	return 0;
}

static int huff_fill_code(struct huffman *phf)
{
	assert(phf != NULL);
	ui16_t i, cur;
	for (i = 0; i < LEAF_NUM; i++) {   
		if (WEIGHT(i) > 0) {
			cur = i;
			while(cur != phf->root) {/*从叶子节点往root遍历,获得反转了的编码*/
				CODE(i) <<= 1;
				CODE_LEN(i)++;
				if (RCHILD(PARENT(cur)) == cur) {
					CODE(i) |= 1;
				}
				cur = PARENT(cur);
			}
#ifdef _DEBUG
{
	printf("[DEBUG] code %x  code_len %d\n", CODE(i), CODE_LEN(i));
}
#endif
		}
	}
	return 0;
}

static int huff_prepare(struct huffman *phf)
{
	/* 1.遍历文件，获得字符出现的频率 */
	if (huff_get_weight(phf) < 0) {
		fprintf(stderr, "huff_get_weight failed.\n");
		return -1;
	}

	/* 2.构建有序序列 */
	if (huff_build_list_with_sort(phf) < 0) {
		fprintf(stderr, "huff_build_list_with_sort failed.\n");
		return -2;
	}

	/* 3.构建最优二叉树 */
	if (huff_build_huff_tree(phf) < 0) {
		fprintf(stderr, "huff_build_huff_tree failed.\n");
		return -3;
	}
	/* 4.填充字符编码 */
	if (huff_fill_code(phf) < 0) {
		fprintf(stderr, "huff_fill_code failed.\n");
		return -4;
	}
	return 0;
}
static int huff_make_head_info(struct huffman *phf)
{
	size_t huff_table_size = sizeof(struct huff_table_node) * (phf->root + 1);
	struct huff_head_info *pheadinfo = (struct huff_head_info *)malloc(huff_table_size + sizeof(*pheadinfo));
	assert(pheadinfo != NULL);

	pheadinfo->magic = MAGIC_NUM;
	pheadinfo->type = HF_ZIP_TYPE;
	pheadinfo->file_size = ftell(phf->fp_src);
	pheadinfo->root = phf->root;
	pheadinfo->offset = huff_table_size;
	memcpy(pheadinfo->tab, phf->tab, huff_table_size);

	fwrite(pheadinfo, huff_table_size + sizeof(*pheadinfo), 1, phf->fp_dest);

	free(pheadinfo);
	return 0;
}
static int huffman_compress(struct huffman *phf, const char *origin, const char *zip)
{
	assert(phf != NULL);
	if ((phf->fp_src = fopen(origin, "r")) == NULL) {
		fprintf(stderr, "fopen failed.\n");
		return -1;
	}
	if ((phf->fp_dest = fopen(zip, "w")) == NULL) {
		fprintf(stderr, "fopen failed.\n");
		return -2;
	}

	if (huff_prepare(phf) < 0) {
		fprintf(stderr, "huff_prepare faild\n");
		return -3;
	}

	/*写入头部信息*/
	if (huff_make_head_info(phf) < 0) {
		fprintf(stderr, "huff_make_head_info failed\n");
		return -4;
	}

	/*获得正向编码*/
	rewind(phf->fp_src);
	code_t rbuf = 0;
	code_t wbuf = 0;
	code_len_t i = 0;
	unsigned char count = 0;
	while ((fread(&rbuf, 1, 1, phf->fp_src) != 0)) {
		for (i = 0; i < CODE_LEN(rbuf); i++) {
			wbuf <<= 1;
			count++;
			if ((CODE(rbuf) >> i) & 1){
				wbuf |= 1;
			}
			if (count == 8) {  /*如果凑满一个字节，就写入文件*/
				fwrite(&wbuf, 1, 1, phf->fp_dest);
#ifdef _DEBUG
{
	printf(" %x ", wbuf);
}
#endif
				count = 0;
				wbuf = 0;
			}
		}
	}
	/*将剩余不足一个字节的写入文件*/
	if (count != 0) {
		wbuf <<= (8 - count);/*不够的补零，解压的时候删掉*/
		fwrite(&wbuf, 1, 1, phf->fp_dest);
#ifdef _DEBUG
{
	printf(" %x \n", wbuf);
}
#endif
	}
	return 0;
}

static int huff_get_head_info(struct huffman *phf)
{
	struct huff_head_info *pheadinfo = (struct huff_head_info *)malloc(sizeof(*pheadinfo));
	assert(pheadinfo != NULL);
	fread(pheadinfo, sizeof(*pheadinfo) - 1, 1, phf->fp_src);
#ifdef _DEBUG
{
	printf("after pheadinfo... offset %d\n", ftell(phf->fp_src));
}
#endif
	size_t huff_table_size = sizeof(struct huff_table_node) * (pheadinfo->root + 1);
	fread(&phf->tab, sizeof(struct huff_table_node), pheadinfo->root + 1, phf->fp_src);
	phf->root = pheadinfo->root;
	phf->file_size = pheadinfo->file_size;	
#ifdef _DEBUG
{
	printf("after huff_table... offset %d\n", ftell(phf->fp_src));
}
#endif

#ifdef _DEBUG
{
	printf("[DEBUG] pheadinfo->magic = %x\n", pheadinfo->magic);
	printf("[DEBUG] pheadinfo->type = %x\n", pheadinfo->type);
	printf("[DEBUG] pheadinfo->file_size = %d\n", pheadinfo->file_size);
	printf("[DEBUG] pheadinfo->root = %d\n", pheadinfo->root);
	printf("[DEBUG] pheadinfo->offset = %d\n", pheadinfo->offset);
	printf("[DEBUG] huff_table_size = %d\n", huff_table_size);
}
#endif
	return 0;
}
static int huffman_decompress(struct huffman *phf, const char *zip, const char *origin)
{
	assert(phf != NULL);

	if ((phf->fp_src = fopen(zip, "r")) == NULL) {
		fprintf(stderr, "fopen failed.\n");
		return -1;
	}
	if ((phf->fp_dest = fopen(origin, "w")) == NULL) {
		fprintf(stderr, "fopen failed.\n");
		return -2;
	}
	
	/*获取文件头部信息*/
	if (huff_get_head_info(phf) < 0) {
		fprintf(stderr, "huff_prepare faild\n");
		return -3;
	}

#if 1 
	unsigned short i = phf->root;
	char buf = 0;
/*多了一个   不知道什么原因， 所以读取掉*/
	fread(&buf, 1, 1, phf->fp_src);
	char count = 0;
	while ((fread(&buf, 1, 1, phf->fp_src))) {
		for (count = 0; count < 8; count++) {
			if (i < LEAF_NUM) {  
				fwrite(&i, 1, 1, phf->fp_dest);
				i = phf->root;
				if (--phf->file_size == 0) {
					goto end;
				}
			}
			if ((buf >> (7 - count)) & 1)	{
				i = RCHILD(i);
			} else {
				i = LCHILD(i);
			}	
		}
//		printf("enter while %d\n",  ftell(phf->fp_src));
	}
	
#endif
end:
	return 0;
}


int huffman_init(struct huffman *phf)
{
	assert(phf != NULL);
	int i;
	for (i = 0; i < LEAF_NUM + UNLEAF_NUM; i++) {
		huff_table_node_init(phf->tab + i);
	}
	phf->phead = (struct list_head *)malloc(sizeof(struct list_head));
	assert(phf->phead != NULL);
	list_head_init(phf->phead);
	phf->root = UNUSED_INDEX;
	phf->fp_src = NULL;
	phf->fp_dest = NULL;
	phf->compress = huffman_compress;
	phf->decompress = huffman_decompress;
	return 0;
}

int huffman_destroy(struct huffman *phf)
{
	assert(phf != NULL);
	fclose(phf->fp_src);
	fclose(phf->fp_dest);
	return 0;

}
