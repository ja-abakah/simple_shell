#include "main.h"

/**
* freeseplist - entry
* Description: frees a sep_list
* @head: head of the linked list.
* Return: no return.
*/
void freeseplist(sep_list **head)
{
sep_list *temp;
sep_list *curr;

if (head != NULL)
{
curr = *head;
while ((temp = curr) != NULL)
{
curr = curr->next;
free(temp);
}
*head = NULL;
}
}

/**
* _memcpy - Entry
* Desription: copies information between void pointers.
* @newptr: destination pointer.
* @ptr: source pointer.
* @size: size of the new pointer.
*
* Return: no return.
*/
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
char *char_ptr = (char *)ptr;
char *char_newptr = (char *)newptr;
unsigned int i;

for (i = 0; i < size; i++)
char_newptr[i] = char_ptr[i];
}

/**
* errsepop - Entry
* Description: finds syntax errors
*
* @input: input string
* @i: index
* @last: last char read
* Return: index of error. 0 when there are no
* errors
*/
int errsepop(char *input, int i, char last)
{
int count;

count = 0;
if (*input == '\0')
return (0);

if (*input == ' ' || *input == '\t')
return (errorsepop(input + 1, i + 1, last));

if (*input == ';')
if (last == '|' || last == '&' || last == ';')
return (i);

if (*input == '|')
{
if (last == ';' || last == '&')
return (i);

if (last == '|')
{
count = repeatedChar(input, 0);
if (count == 0 || count > 1)
return (i);
}
}

if (*input == '&')
{
if (last == ';' || last == '|')
return (i);

if (last == '&')
{
count = repeatedChar(input, 0);
if (count == 0 || count > 1)
return (i);
}
}
return (errorsepop(input + 1, i + 1, *input));
}

/**
* checkVars - Entry
* Description: check if the typed variable is $$ or $?
*
* @h: head of the linked list
* @in: input string
* @st: last status of the Shell
* @data: data structure
* Return: no return
*/
int checkVars(r_var **h, char *in, char *st, data_shell *data)
{
int i, lst, lpd;

lst = _strlen(st);
lpd = _strlen(data->pid);

for (i = 0; in[i]; i++)
{
if (in[i] == '$')
{
if (in[i + 1] == '?')
addrvarnode(h, 2, st, lst), i++;
else if (in[i + 1] == '$')
addrvarnode(h, 2, data->pid, lpd), i++;
else if (in[i + 1] == '\n')
addrvarnode(h, 0, NULL, 0);
else if (in[i + 1] == '\0')
addrvarnode(h, 0, NULL, 0);
else if (in[i + 1] == ' ')
addrvarnode(h, 0, NULL, 0);
else if (in[i + 1] == '\t')
addrvarnode(h, 0, NULL, 0);
else if (in[i + 1] == ';')
addrvarnode(h, 0, NULL, 0);
else
checkEnv(h, in + i, data);
}
}

return (i);
}
