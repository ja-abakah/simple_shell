#include "main.h"

/**
* _strchr - Entry
* Description: locates a character in a string,
* @s: string.
* @c: character.
* Return: the pointer to the first occurrence of the character c.
*/
char *_strchr(char *s, char c)
{
unsigned int i = 0;

for (; *(s + i) != '\0'; i++)
if (*(s + i) == c)
return (s + i);
if (*(s + i) == c)
return (s + i);
return ('\0');
}

/**
* _env - Entry
* Descriptiom: prints the evironment variables
*
* @datash: data relevant.
* Return: 1 on success.
*/
int _env(data_shell *datash)
{
int i, j;

for (i = 0; datash->_environ[i]; i++)
{

for (j = 0; datash->_environ[i][j]; j++)
;

write(STDOUT_FILENO, datash->_environ[i], j);
write(STDOUT_FILENO, "\n", 1);
}
datash->status = 0;

return (1);
}

/**
* set_env - Entry
* Description: sets an environment variable
*
* @name: name of the environment variable
* @value: value of the environment variable
* @datash: data structure (environ)
* Return: no return
*/
void set_env(char *name, char *value, data_shell *datash)
{
int i;
char *var_env, *name_env;

for (i = 0; datash->_environ[i]; i++)
{
var_env = _strdup(datash->_environ[i]);
name_env = _strtok(var_env, "=");
if (_strcmp(name_env, name) == 0)
{
free(datash->_environ[i]);
datash->_environ[i] = copy_info(name_env, value);
free(var_env);
return;
}
free(var_env);
}

datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
datash->_environ[i] = copy_info(name, value);
datash->_environ[i + 1] = NULL;
}

/**
* add_nodes - Entry
* Description: add separators and command lines in the lists
*
* @head_s: head of separator list
* @head_l: head of command lines list
* @input: input string
* Return: no return
*/
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
int i;
char *line;

input = swap_char(input, 0);

for (i = 0; input[i]; i++)
{
if (input[i] == ';')
addsepnodeend(head_s, input[i]);

if (input[i] == '|' || input[i] == '&')
{
addsepnodeend(head_s, input[i]);
i++;
}
}

line = _strtok(input, ";|&");
do {
line = swap_char(line, 1);
addlinenodeend(head_l, line);
line = _strtok(NULL, ";|&");
} while (line != NULL);

}

/**
* _strspn - Entry
* Description: gets the length of a prefix substring.
* @s: initial segment.
* @accept: accepted bytes.
* Return: the number of accepted bytes.
*/
int _strspn(char *s, char *accept)
{
int i, j, bool;

for (i = 0; *(s + i) != '\0'; i++)
{
bool = 1;
for (j = 0; *(accept + j) != '\0'; j++)
{
if (*(s + i) == *(accept + j))
{
bool = 0;
break;
}
}
if (bool == 1)
break;
}
return (i);
}

