This is an explanation of how to write code with good taste by using a single
linked list example inspired by Mark Kirchner's project
[linked-list-good-taste], which in turn was inspired by a comment Linus
Torvalds made in his [TED talk][ted] in 2016.

We start by turning this typical implementation:

```c
void remove_list_entry(node **head, node *entry)
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
```

into this:

```c
void remove_list_entry(node **head, node *entry)
{
	node **p = head;
	while (*p != entry)
		p = &(*p)->next;
	*p = entry->next;
}
```

in [part 1].

We then explore how a real library (GLib) does it and improve it to:

```c
GSList *g_slist_remove_link(GSList *list, GSList *link)
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
```

in [part 2].

And finally we explore how Linux does it, and arrive to:

```c
void llist_del(struct llist_head *list, struct llist_node *entry)
{
	struct llist_node *p;

	llist_for_each(p, (struct llist_node *)list) {
		if (p->next != entry) continue;
		p->next = entry->next;
		return;
	}
}
```

in [part 3] which is vastly superior, and in good taste.

[linked-list-good-taste]: https://github.com/mkirchner/linked-list-good-taste
[ted]: https://youtu.be/o8NPllzkFhE?t=858
[part 1]: https://felipec.github.io/good-taste/parts/1.html
[part 2]: https://felipec.github.io/good-taste/parts/2.html
[part 3]: https://felipec.github.io/good-taste/parts/3.html
