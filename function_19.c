#include "main.h"

/**
* go_next - Entry
* Description: go to the next command line stored
*
* @list_s: separator list
* @list_l: command line list
* @datash: data structure
* Return: no return
*/
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
int loop_sep;
sep_list *ls_s;
line_list *ls_l;

loop_sep = 1;
ls_s = *list_s;
ls_l = *list_l;

while (ls_s != NULL && loop_sep)
{
if (datash->status == 0)
{
if (ls_s->separator == '&' || ls_s->separator == ';')
loop_sep = 0;
if (ls_s->separator == '|')
ls_l = ls_l->next, ls_s = ls_s->next;
}
else
{
if (ls_s->separator == '|' || ls_s->separator == ';')
loop_sep = 0;
if (ls_s->separator == '&')
ls_l = ls_l->next, ls_s = ls_s->next;
}
if (ls_s != NULL && !loop_sep)
ls_s = ls_s->next;
}

*list_s = ls_s;
*list_l = ls_l;
}

/**
* _unsetenv - Entry
* Descriptin: deletes a environment variable
*
* @datash: data relevant (env name)
*
* Return: 1 on success.
*/
int _unsetenv(data_shell *datash)
{
char **realloc_environ;
char *var_env, *name_env;
int i, j, k;

if (datash->args[1] == NULL)
{
get_error(datash, -1);
return (1);
}
k = -1;
for (i = 0; datash->_environ[i]; i++)
{
var_env = _strdup(datash->_environ[i]);
name_env = _strtok(var_env, "=");
if (_strcmp(name_env, datash->args[1]) == 0)
{
k = i;
}
free(var_env);
}
if (k == -1)
{
errGet(datash, -1);
return (1);
}
realloc_environ = malloc(sizeof(char *) * (i));
for (i = j = 0; datash->_environ[i]; i++)
{
if (i != k)
{
realloc_environ[j] = datash->_environ[i];
j++;
}
}
realloc_environ[j] = NULL;
free(datash->_environ[k]);
free(datash->_environ);
datash->_environ = realloc_environ;
return (1);
}

/**
* split_line - Entry
* Description: tokenizes the input string
*
* @input: input string.
* Return: string splitted.
*/
char **split_line(char *input)
{
size_t bsize;
size_t i;
char **tokens;
char *token;

bsize = TOK_BUFSIZE;
tokens = malloc(sizeof(char *) * (bsize));
if (tokens == NULL)
{
write(STDERR_FILENO, ": allocation error\n", 18);
exit(EXIT_FAILURE);
}

token = _strtok(input, TOK_DELIM);
tokens[0] = token;

for (i = 1; token != NULL; i++)
{
if (i == bsize)
{
bsize += TOK_BUFSIZE;
tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
if (tokens == NULL)
{
write(STDERR_FILENO, ": allocation error\n", 18);
exit(EXIT_FAILURE);
}
}
token = _strtok(NULL, TOK_DELIM);
tokens[i] = token;
}

return (tokens);
}

/**
* split_commands - Entry
* Description: splits command lines according to
* the separators ;, | and &, and executes them
*
* @datash: data structure
* @input: input string
* Return: 0 to exit, 1 to continue
*/
int split_commands(data_shell *datash, char *input)
{

sep_list *head_s, *list_s;
line_list *head_l, *list_l;
int loop;

head_s = NULL;
head_l = NULL;

add_nodes(&head_s, &head_l, input);

list_s = head_s;
list_l = head_l;

while (list_l != NULL)
{
datash->input = list_l->line;
datash->args = split_line(datash->input);
loop = exec_line(datash);
free(datash->args);

if (loop == 0)
break;

go_next(&list_s, &list_l, datash);

if (list_l != NULL)
list_l = list_l->next;
}

freeseplist(&head_s);
freelinelist(&head_l);

if (loop == 0)
return (0);
return (1);
}
