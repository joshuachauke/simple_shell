#include "shell.h"

/**
 * list_len - Length of linked list is determined
 * @h: First node pointer
 *
 * Return: List size
 */
size_t list_len(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		h = h->next;
		t++;
	}
	return (t);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t t = list_len(head), v;
	char **strs;
	char *str;

	if (!head || !t)
		return (NULL);
	strs = malloc(sizeof(char *) * (t + 1));
	if (!strs)
		return (NULL);
	for (t = 0; node; node = node->next, t++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (v = 0; v < t; v++)
				free(strs[v]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[t] = str;
	}
	strs[t] = NULL;
	return (strs);
}

/**
 * print_list - All elements of a list_t linked list should be printed
 * @h: First node pointer
 *
 * Return: List size
 */
size_t print_list(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(' ');
		_putchar(':');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		t++;
	}
	return (t);
}

/**
 * node_starts_with - Node whose string starts with prefix should be returned
 * @node: List head pointer
 * @prefix: Match string
 * @c: Next charac after prefix to be matched
 *
 * Return: Return node of a match  or NULL
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index – Should get an index of a node
 * @head: List head pointer
 * @node:  Node Pointer
 *
 * Return: Index of node should be returned or return -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t t = 0;

	while (head)
	{
		if (head == node)
			return (t);
		head = head->next;
		t++;
	}
	return (-1);
}
