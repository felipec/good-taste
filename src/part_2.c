#include <stdio.h>
#include <stdbool.h>

typedef struct node_data {
	int value;
} node_data;

typedef struct GSList {
	void *data;
	struct GSList *next;
} GSList;

GSList *g_slist_remove_link_0(GSList *list, GSList *link)
{
	GSList *tmp = NULL;
	GSList **previous_ptr = &list;

	while (*previous_ptr) {
		tmp = *previous_ptr;
		if (tmp == link) {
			*previous_ptr = tmp->next;
			tmp->next = NULL;
			break;
		}

		previous_ptr = &tmp->next;
	}

	return list;
}

GSList *g_slist_remove_link_1(GSList *list, GSList *link)
{
	GSList **p = &list;

	while (*p && *p != link)
		p = &(*p)->next;

	*p = (*p)->next;

	return list;
}

GSList *g_slist_remove_link_2(GSList *list, GSList *link)
{
	GSList **p = &list;

	while (*p) {
		if (*p == link) {
			*p = (*p)->next;
			break;
		}

		p = &(*p)->next;
	}

	return list;
}

GSList *g_slist_remove_link_3(GSList *list, GSList *link)
{
	GSList **p = &list;

	while (*p && *p != link)
		p = &(*p)->next;

	if (*p) *p = (*p)->next;

	return list;
}

typedef GSList *(*g_slist_remove_link)(GSList *list, GSList *link);

int do_test(g_slist_remove_link fn) {
	node_data a = { .value = 0 };
	node_data b = { .value = 1 };
	node_data c = { .value = 2 };

	GSList link_a = { .data = &a };
	GSList link_b = { .data = &b };
	GSList link_c = { .data = &c };

	GSList *head = &link_a;
	link_a.next = &link_b;
	link_b.next = &link_c;

	head = fn(head, &link_b);
	if (link_a.next != &link_c) return false;

	head = fn(head, &link_a);
	if (head != &link_c) return false;

	head = fn(head, &link_a);
	if (head != &link_c) return false;

	head = fn(head, NULL);
	if (head != &link_c) return false;

	head = fn(head, &link_c);
	if (head != NULL) return false;

	head = fn(NULL, NULL);
	head = fn(NULL, &link_c);

	return true;
}

g_slist_remove_link list[] = {
	g_slist_remove_link_0,
	// g_slist_remove_link_1,
	g_slist_remove_link_2,
	g_slist_remove_link_3,
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
