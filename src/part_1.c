#include <stdio.h>
#include <stdbool.h>

typedef struct node {
	int value;
	struct node *next;
} node;

void remove_list_entry_0(node **head, node *entry)
{
	node *prev, *walk;

	prev = NULL;
	walk = *head;

	// Walk the list

	while (walk != entry) {
		prev = walk;
		walk = walk->next;
	}

	// Remove the entry by updating the
	// head or the previous entry

	if (!prev)
		*head = entry->next;
	else
		prev->next = entry->next;
}

void remove_list_entry_1(node **head, node *entry)
{
	node *prev, *walk;

	prev = NULL;
	walk = *head;

	while (walk != entry) {
		prev = walk;
		walk = walk->next;
	}

	node **tmp;
	if (!prev)
		tmp = head;
	else
		tmp = &prev->next;
	*tmp = entry->next;
}

void remove_list_entry_2(node **head, node *entry)
{
	node *walk, **tmp;

	tmp = head;
	walk = *head;

	while (walk != entry) {
		tmp = &walk->next;
		walk = walk->next;
	}

	*tmp = entry->next;
}

void remove_list_entry_3(node **head, node *entry)
{
	node **p = head;
	while (*p != entry)
		p = &(*p)->next;
	*p = entry->next;
}

void remove_list_entry_4(node **head, node *entry)
{
	node **p;
	for (p = head; *p != entry; p = &(*p)->next);
	*p = entry->next;
}

typedef void (*remove_list_entry)(node **head, node *entry);

int do_test(remove_list_entry fn)
{
	node *head;
	node a = { .value = 0 };
	node b = { .value = 1 };
	node c = { .value = 2 };

	head = &a;
	a.next = &b;
	b.next = &c;

	fn(&head, &b);
	if (a.next != &c) return false;

	fn(&head, &a);
	if (head != &c) return false;

	return true;
}

remove_list_entry list[] = {
	remove_list_entry_0,
	remove_list_entry_1,
	remove_list_entry_2,
	remove_list_entry_3,
	remove_list_entry_4,
	NULL,
};

int main(void)
{
	for (int i = 0; list[i]; i++) {
		int r = do_test(list[i]);
		printf("%i: %s\n", i, r ? "OK" : "FAIL");
	}
	return 0;
}
