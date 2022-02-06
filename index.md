In a [TED talk][ted] in 2016, Linus Torvalds is asked to explain his notion of "taste". As an
illustration he showcases code as is typically taught in universities:

```c
remove_list_entry(entry)
{
	prev = NULL;
	walk = head;

	// Walk the list

	while (walk != entry) {
		prev = walk;
		walk = walk->next;
	}

	// Remove the entry by updating the
	// head or the previous entry

	if (!prev)
		head = entry->next;
	else
		prev->next = entry->next;
}
```

In contrast, he provides an alternative that he considers superior:

```c
remove_list_entry(entry)
{
	// The "indirect" pointer points to the
	// *address* of the thing we'll update

	indirect = &head;

	// Walk the list, looking for the thing that
	// points to the entry we want to remove

	while ((*indirect) != entry)
		indirect = &(*indirect)->next;

	// .. and just remove it
	*indirect = entry->next;
}
```

[ted]: https://youtu.be/o8NPllzkFhE?t=858
