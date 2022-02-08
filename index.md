In a [TED talk][ted] in 2016, Linus Torvalds is asked to explain his notion of "taste". As an
illustration he showcases code as is typically taught in universities:

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

In contrast, he provides an alternative that he considers superior:

```c
void remove_list_entry(node **head, node *entry)
{
	node **indirect;

	// The "indirect" pointer points to the
	// *address* of the thing we'll update

	indirect = head;

	// Walk the list, looking for the thing that
	// points to the entry we want to remove

	while ((*indirect) != entry)
		indirect = &(*indirect)->next;

	// ... and just remove it
	*indirect = entry->next;
}
```

He argues that the important part isn't the details of the code—although details are also important,
but that by looking at the code in a different way it can be greately improved.

Taste isn't something that can be taught: either you have it, or you don't. And it takes somebody
with good taste (like Linus Torvalds), to recognize another person with good taste. However, by
immersing yourself with examples of good taste, eventually you'll absorb that style.

Here we'll dive into this illustration, and why it is considered good taste.

## Linked list

Anyone who has studied computer science in university at some point was asked to create a linked
list, which is one of the most basic data structures.

The core of a linked linked list is a `node`, which is a structure consisting of two fileds: a
value, and a pointer to the next node.

<canvas id="node"></canvas>

```c
struct node {
	int value;
	struct node *next;
};
```

A linked list is nothing more than a sequence of nodes:

<canvas id="list"></canvas>

`head` points to the first node, and the last node's `next` pointer doesn't point to anything
(`NULL`).

So to get the second node's value (`1`), we could do this:

```c
head->next->value;
```

<script src="index.js"></script>

[ted]: https://youtu.be/o8NPllzkFhE?t=858
