#pragma once


struct  list_head {
	struct list_head *next;
	struct list_head *prev;
};

#define   INIT_LIST_HEAD(head) \
	struct list_head (head) = { &(head), &(head)}

/*inline 内联函数
内联函数，减少了函数寻址，传参返回等过程，效率比较高，适合在一些频繁调用的场合使用。
1. inline 仅仅是个建议,具体能不能被采纳还需要符合条件
2. 条件
	a) 函数体比较简单， 10行以下代码
	   只有if之类的判断语句，没有循环和递归
	b) 不能使用递归函数
	c) 不能使用函数指针，指向改函数
	d) 使用内联函数，可能引起程序体积增大
	e) 内联定义放在头文件中，通常配合static，使得作用域限定在当前代码文件。
*/

static inline  void list_head_init(struct list_head *head)
{
	head->next = head;
	head->prev = head;
}

static inline void __list_add(struct list_head *node,
	struct list_head *Prev, struct list_head *Next)
{
	node->next = Next;
	node->prev = Prev;
	
	Next->prev = node;
	Prev->next = node;
}
static inline void list_add(struct list_head *node,
			struct list_head *phead)
{
	__list_add(node, phead, phead->next);
}

static inline void list_add_tail(struct list_head *node,
			struct list_head *phead)
{
	__list_add(node, phead->prev, phead);

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

#define  list_for_each(cur, head)	\
	for (cur = (head)->next; cur != (head); cur = (cur)->next)

#define   offset_of(type, member) \
		(size_t)(&((type *)0)->member)

#define   container_of(ptr, type, member) \
	(type *)((char *)ptr - offset_of(type, member))

#define  list_for_each_reverse(cur, head)	\
	for (cur = (head)->prev; cur != (head); cur = (cur)->prev)


#define  list_for_each_continue(cur, head)	\
	for (cur = (cur)->next; cur != (head); cur = (cur)->next)

#define  list_for_each_from(cur, head)	\
	for ( ; cur != (head); cur = (cur)->next)

#define  list_for_each_safe(cur, Next, head)	\
	for ( cur = (head)->next; ((Next) = cur->next) && (cur != (head)); cur = Next)

/*直接遍历大结构体(宿主结构)*/
#define  list_for_each_entry(pos, head, member)	\
	for (pos = container_of((head)->next, typeof(*pos), member); &(pos)->member != head; \
	pos = container_of((pos)->member.next, typeof(*pos), member))
