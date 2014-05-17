/*************************************************************************
	> File Name: test.c
	> Created Time: 2014年05月13日 星期二 14时14分54秒
 ************************************************************************/
#include <string.h>
#include <stdlib.h>
#include "mysort.h"

/* 连续存放(数组)排序
 */
void array_swap(void *a, void *b, size_t width)
{
	void *pc = malloc(width);
	memcpy(pc, a, width);
	memcpy(a, b, width);
	memcpy(b, pc, width);
	free(pc);
}
void array_bubble_sort(void *base, size_t nelm, size_t width, int (*cmp)(const void *a, const void *b))
{
	size_t i_start, i_end;
	for (i_end = nelm - 1; i_end > 0; i_end--) {
		for (i_start = 0; i_start < i_end; i_start++) {
			if (cmp(N2PTR(i_start), N2PTR(i_start + 1)) > 0) {
				array_swap(N2PTR(i_start), N2PTR(i_start + 1), width);
			}
		}
	}
}
void array_select_sort(void *base, size_t nelm, size_t width, int (*cmp)(const void *a, const void *b))
{
	size_t i, j, index;
	for (i = 0; i < nelm - 1; i++) {
		index = i;
		for (j = i + 1; j < nelm; j++) {
			if (cmp(N2PTR(index), N2PTR(j)) > 0) {
				index = j;
			}
		}
		if (index != i) {
			array_swap(N2PTR(index), N2PTR(i), width);
		}
	}
}
void array_insert_sort(void *base, size_t nelm, size_t width, int (*cmp)(const void *a, const void *b))
{
	void *buf = malloc(width);

	ssize_t i, j;

	for (i = 1; i < nelm; i++) {
		j = i - 1;
		if (cmp(N2PTR(i), N2PTR(j)) >= 0 ) {
			continue;
		}
		memcpy(buf, N2PTR(i), width);
		for (; j >= 0; j--) {
			if (cmp(N2PTR(j), buf) < 0) {
				break;
			} else {
				memcpy(N2PTR(j + 1), N2PTR(j), width);
			}
		}
		memcpy(N2PTR(j + 1), buf, width);
	}
	free(buf);
}

void array_shell_sort(void *base, size_t nelm, size_t width, int (*cmp)(const void *a, const void *b))
{
	size_t i, j, step[] = {3, 2, 1}, offset;
	int k;
	void *buf = malloc(width);
	for (i = 0; i < sizeof(step) / sizeof(step[0]); i++) {
		for (offset = 0; offset < step[i]; offset++) {
			for (j = offset + step[i]; j < nelm; j += step[i]) {
				k = j - step[i];
				if (cmp(N2PTR(j), N2PTR(k)) >= 0) {
					continue;
				}
				memcpy(buf, N2PTR(j), width);
				for (; k >= 0; k -= step[i]) {
					if (cmp(N2PTR(k), buf) < 0) {
						break;
					}
					memcpy(N2PTR(k + step[i]), N2PTR(k), width);
				}
				memcpy(N2PTR(k + step[i]), buf, width);
			}
		}
	}
}



static void __array_merge_sort(void *base, size_t nelm, size_t width, void *buf, int (*cmp)(const void *a, const void *b))
{
	//分
	if (nelm <= 1) {
		return;
	} else {
		__array_merge_sort(base, nelm / 2, width, buf, cmp);
		__array_merge_sort(N2PTR(nelm / 2), nelm - nelm / 2, width, buf, cmp);
	}
	
	//治
	size_t l = 0, r = nelm / 2, index = 0;
	while ((l < nelm / 2) && (r < nelm)) {
		if (cmp(N2PTR(l), N2PTR(r)) <= 0) {
			memcpy(_N2PTR(buf, index, width), N2PTR(l), width);
			l++;
		} else {
			memcpy(_N2PTR(buf, index, width), N2PTR(r), width);
			r++;
		}
		index++;
	}
	//拷贝剩余数据到缓冲区buf
	if (l < nelm / 2) {
		memcpy(_N2PTR(buf, index, width), N2PTR(l), width * ((nelm / 2) - l));
	} else {
		memcpy(_N2PTR(buf, index, width), N2PTR(l), width * (nelm - r));
	}
	//并
	memcpy(base, buf, nelm * width);

}
void array_merge_sort(void *base, size_t nelm, size_t width, int (*cmp)(const void *a, const void *b))
{
	void *buf = malloc(width * nelm);
	__array_merge_sort(base, nelm, width, buf, cmp);
	free(buf);
}

static __array_quick_sort(void *base, size_t nelm, size_t width, void *buf, int (*cmp)(const void *a, const void *b))
{
	if (nelm < 2) {
		return;
	}
	size_t l = 0, r = nelm - 1, pivot = l;  //pivot轴值

	memcpy(buf, N2PTR(pivot), width);
	while (l < r) {
		while(l < r) {
			if (cmp(N2PTR(r), buf) < 0 ) {
				memcpy(N2PTR(l), N2PTR(r), width);
				l++;
				break;
			} else {
				r--;
			}
		}
		while(l < r) {
			if (cmp(N2PTR(l), buf) > 0) {
				memcpy(N2PTR(r), N2PTR(l), width);
				r--;
				break;
			} else {
				l++;
			}
		}
	}
	memcpy(N2PTR(l), buf, width);
	__array_quick_sort(base, l, width, buf, cmp);
	__array_quick_sort(N2PTR(l + 1), nelm - l - 1, width, buf, cmp);
}

void array_quick_sort(void *base, size_t nelm, size_t width, int (*cmp)(const void *a, const void *b))
{
	void *buf = malloc(width);
	__array_quick_sort(base, nelm, width, buf, cmp);
	free(buf);
}



/*链表排序(内核链表)
 */

void list_swap(struct list_head *pa, struct list_head *pb)
{
	struct list_head tmp;
	__list_add(&tmp, pa, pa->next);
	node_del(pa);
	__list_add(pa, pb, pb->next);
	node_del(pb);
	__list_add(pb, &tmp, tmp.next);
	node_del(&tmp);
}

void list_bubble_sort(struct list_head *phead, int (*cmp)(const struct list_head *a, const struct list_head *b))
{
	struct list_head *index = phead->prev;
	struct list_head *cur = NULL;
	for (; index != phead; index = index->prev) {
		for (cur = phead->next; cur != index; cur = cur->next) {
			if (cmp(cur, cur->next) > 0) {
				list_swap(cur, cur->next);
				cur = cur->prev;
			}
			if (cur == index) {
				index = index->next;
			}
		}
			
	}

}

void list_select_sort(struct list_head *phead, int (*cmp)(const struct list_head *a, const struct list_head *b))
{
	struct list_head *pi, *pj, *pmin, *Next;
	for (pi = phead->next; pi != phead; pi = Next) {
		Next = pi->next;
		pmin = pi;
		for (pj = pi->next; pj != phead; pj = pj->next) {
			if (cmp(pj,pmin) < 0) {
				pmin = pj;
			}
		}
		if (pmin != pi) {
			list_swap(pmin, pi);
		}
	}
	
}

void list_insert_sort(struct list_head *phead, int (*cmp)(const struct list_head *a, const struct list_head *b))
{
	struct list_head *pi, *pj, *Next;
	for (pi = phead->next->next; pi != phead; pi = Next) {
		Next = pi->next;
		pj = pi->prev;
		if (cmp(pj, pi) <= 0) {
			continue;
		}
		node_del(pi);
		for (; pj != phead; pj = pj->prev) {
			if (cmp(pj, pi) < 0) {
				break;
			}
		}
		__list_add(pi, pj, pj->next);
	}
}

