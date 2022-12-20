#include "monty.h"

/**
 * push - pushes an element to the stack
 * @stack: the stack
 * @line_number: instruction line number
 * Return: nothing
 */

void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new, *temp = *stack;
	int number, bol = 0, i = 0;

	for (; argument[0][i]; i++)
		bol = _isalpha((int)argument[0][i]);

	if (bol != 0)
	{
		dprintf(STDERR_FILENO, "L%d: usage: push integer\n", line_number);
		argument[0] = "FAIL";
		return; }
	number = atoi(argument[0]);
	new = malloc(sizeof(stack_t));
	if (!new)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		argument[0] = "FAIL";
		return; }
	new->n = number;
	if (strcmp(argument[1], "queue") == 0)
	{
		if (temp)
			temp->next = new;
		else
			*stack = new;
	}
	else
	{
		new->next = *stack;
		new->prev = NULL;
		if (*stack)
			(*stack)->prev = new;
		*stack = new;
	}
}