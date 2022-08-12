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

Part 2 and 3 are pending.

[linked-list-good-taste]: https://github.com/mkirchner/linked-list-good-taste
[ted]: https://youtu.be/o8NPllzkFhE?t=858
[part 1]: https://felipec.github.io/good-taste/
