#include "main.h"

/**
* addlinenodeend - entry
* Description: adds a command line at the end
* of a line_list.
* @head: head of the linked list.
* @line: command line.
* Return: address of the head.
*/
line_list *addlinenodeend(line_list **head, char *line)
{
line_list *new, *temp;

new = malloc(sizeof(line_list));
if (new == NULL)
return (NULL);

new->line = line;
new->next = NULL;
temp = *head;

if (temp == NULL)
{
*head = new;
}
else
{
while (temp->next != NULL)
temp = temp->next;
temp->next = new;
}

return (*head);
}

/**
* _realloc - Entry
* Description: reallocates a memory block.
* @ptr: pointer to the memory previously allocated.
* @old_size: size, in bytes, of the allocated space of ptr.
* @new_size: new size, in bytes, of the new memory block.
*
* Return: ptr.
* if new_size == old_size, returns ptr without changes.
* if malloc fails, returns NULL.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *newptr;

if (ptr == NULL)
return (malloc(new_size));

if (new_size == 0)
{
free(ptr);
return (NULL);
}

if (new_size == old_size)
return (ptr);

newptr = malloc(new_size);
if (newptr == NULL)
return (NULL);

if (new_size < old_size)
_memcpy(newptr, ptr, new_size);
else
_memcpy(newptr, ptr, old_size);

free(ptr);
return (newptr);
}

/**
* firstChar - Entry
* Description: finds index of the first char
*
* @input: input string
* @i: index
* Return: 1 if there is an error. 0 in other case.
*/
int firstChar(char *input, int *i)
{

for (*i = 0; input[*i]; *i += 1)
{
if (input[*i] == ' ' || input[*i] == '\t')
continue;

if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
return (-1);

break;
}

return (0);
}

/**
* repVar - Entry
* Description: calls functions to replace string into vars
*
* @input: input string
* @datash: data structure
* Return: replaced string
*/
char *repVar(char *input, data_shell *datash)
{
r_var *head, *indx;
char *status, *new_input;
int olen, nlen;

status = ItoaAux(datash->status);
head = NULL;

olen = checkVars(&head, input, status, datash);

if (head == NULL)
{
free(status);
return (input);
}

indx = head;
nlen = 0;

while (indx != NULL)
{
nlen += (indx->len_val - indx->len_var);
indx = indx->next;
}

nlen += olen;

new_input = malloc(sizeof(char) * (nlen + 1));
new_input[nlen] = '\0';

new_input = replacedInput(&head, input, new_input, nlen);

free(input);
free(status);
freervarlist(&head);

return (new_input);
}
