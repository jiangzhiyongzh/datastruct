/*************************************************************************
	> File Name: list.h
	> Created Time: 2014年05月08日 星期四 10时07分47秒
 ************************************************************************/
#pragma once

struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(head) \
	struct list_head (head) = {&head, &head}

static inline void list_head_init(struct list_head *head)
{
	head->next = head;
	head->prev = head;
}

static inline void __list_add(struct list_head *new, struct list_head *Prev, struct list_head *Next)
{
	new->next = Next;
	new->prev = Prev;

	Prev->next = new;
	Next->prev = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

static inline void node_del(struct list_head *node)
{
	node->next->prev = node->prev;
	node->prev->next = node->next;
}

static inline void node_del_init(struct list_head *node)
{
	node_del(node);
	list_head_init(node);
}


#define list_for_each(cur, head) \
	for ((cur) = (head)->next; (cur) != (head); (cur) = (cur)->next)

#define offset_of(type, member) \
	((size_t)(&(((type *)0)->member)))

#define container_of(ptr, type, member) \
	(type *)((size_t)(ptr) - offset_of(type, member))

#define  list_for_each_reverse(cur, head)	\
	for (cur = (head)->prev; cur != (head); cur = (cur)->prev)


#define  list_for_each_continue(cur, head)	\
	for (cur = (cur)->next; cur != (head); cur = (cur)->next)

#define  list_for_each_from(cur, head)	\
	for ( ; cur != (head); cur = (cur)->next)

/*直接遍历大结构体(宿主结构)*/
#define  list_for_each_entry(pos, head, member)	\
	for (pos = container_of((head)->next, typeof(*pos), member); &(pos)->member != head; \
	pos = container_of((pos)->member.next, typeof(*pos), member))
