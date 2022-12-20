#include "monty.h"

global_t global = {NULL, NULL, NULL, NULL, 1, -1, 1};

/**
 * choose_option - Find if the flag match with an existence and
 * give the correct function.
 *
 * @tokens: Double pointer to the tokens of the command.
 *
 * Return: A print_operation struct with a flag (0 or 1
 * and a function pointer or NULL.
 */
void (*choose_option(char **tokens))(stack_t **, unsigned int)
{
	instruction_t options[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"nop", nop},
		{"swap", swap},
		{"add", add},
		{"sub", sub},
		{"div", _div},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{"rotr", rotr},
		{"stack", stack},
		{"queue", queue},
		{NULL, NULL}
	};
	int i = 0;

	while (options[i].opcode)
	{
		if (strcmp(options[i].opcode, tokens[0]) == 0)
			return (options[i].f);
		i++;
	}
	return (NULL);
}

/**
 * main - Function that calls opcodes
 *
 * @ac: Arguments Count
 * @av: Arguments Vector
 * Return: int
 */

int main(int ac, char **av)
{
	size_t len = 0;
	void (*op_func)(stack_t **, unsigned int);

	if (ac != 2)
		dprintf(STDERR_FILENO, "USAGE: monty file\n"), exit(EXIT_FAILURE);

	if (access(av[1], R_OK) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	global.fd_monty = fopen(av[1], "r");
	while (getline(&global.command, &len, global.fd_monty) != EOF)
	{
		if (global.command[0] == '\n' || is_comment(global.command) ||
			all_spaces(global.command, strlen(global.command)))
		{
			global.line_num++, len = 0, free(global.command);
			continue;
		}
		global.tokens = tokenizer(global.command);
		if (!global.tokens)
		{
			dprintf(STDERR_FILENO, "Error: malloc failed\n");
			free_cases(1);
			exit(EXIT_FAILURE);
		}
		op_func = choose_option(global.tokens);
		if (op_func == NULL)
		{
			dprintf(STDERR_FILENO, "L%u: unknown instruction %s\n",
					global.line_num, global.tokens[0]);
			free_cases(0), exit(EXIT_FAILURE);
		}
		op_func(&global.stack, global.line_num);
		free_cases(2), global.line_num++, len = 0;
	}
	free_cases(1);
	return (EXIT_SUCCESS);
}