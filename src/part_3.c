#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

struct llist_head {
	struct llist_node *first;
};

struct llist_node {
	struct llist_node *next;
};

struct node {
	struct llist_node node;
	int value;
};

#define container_of(ptr, type, member) ((type *)((void *)(ptr) - offsetof(type, member)))
#define llist_entry(ptr, type, member) container_of(ptr, type, member)
#define llist_for_each(pos, node) for ((pos) = (node); pos; (pos) = (pos)->next)

#define node_entry(ptr) container_of(ptr, struct node, node)

void llist_del_0(struct llist_head *list, struct llist_node *entry)
{
	struct llist_node *p;

	if (entry == list->first) {
		list->first = entry->next;
		return;
	}

	for (p = list->first; p; p = p->next) {
		if (p->next != entry) continue;
		p->next = entry->next;
		return;
	}
}

void llist_del_1(struct llist_head *list, struct llist_node *entry)
{
	struct llist_node *p;

	p = (struct llist_node *)list;
	if (entry == p->next) {
		p->next = entry->next;
		return;
	}

	for (p = list->first; p; p = p->next) {
		if (p->next != entry) continue;
		p->next = entry->next;
		return;
	}
}

void llist_del_2(struct llist_head *list, struct llist_node *entry)
{
	struct llist_node *p;

	for (p = (struct llist_node *)list; p; p = p->next) {
		if (p->next != entry) continue;
		p->next = entry->next;
		return;
	}
}

void llist_del_3(struct llist_head *list, struct llist_node *entry)
{
	struct llist_node *p;

	if (entry == list->first) {
		list->first = entry->next;
		return;
	}

	llist_for_each(p, list->first) {
		if (p->next != entry) continue;
		p->next = entry->next;
		return;
	}
}

void llist_del_4(struct llist_head *list, struct llist_node *entry)
{
	struct llist_node *p;

	llist_for_each(p, (struct llist_node *)list) {
		if (p->next != entry) continue;
		p->next = entry->next;
		return;
	}
}

typedef void (*llist_del)(struct llist_head *list, struct llist_node *entry);

int do_test(llist_del fn) {
	struct node a = { .value = 0 };
	struct node b = { .value = 1 };
	struct node c = { .value = 2 };

	struct llist_head list = { .first = &a.node };
	a.node.next = &b.node;
	b.node.next = &c.node;

	fn(&list, &b.node);
	if (a.node.next != &c.node) return false;

	fn(&list, &a.node);
	if (list.first != &c.node) return false;

	fn(&list, &a.node);
	if (list.first != &c.node) return false;

	return true;
}

llist_del list[] = {
	llist_del_0,
	llist_del_1,
	llist_del_2,
	llist_del_3,
	llist_del_4,
	NULL,
};

int main(void)
{
	int ret = 0;
	for (int i = 0; list[i]; i++) {
		int r = do_test(list[i]);
		printf("%i: %s\n", i, r ? "OK" : "FAIL");
		ret |= !r;
	}
	return 0;
}
