#include "main.h"

/**
* replacedInput - Entry
* Description: replaces string into variables
*
* @head: head of the linked list
* @input: input string
* @new_input: new input string (replaced)
* @nlen: new length
* Return: replaced string
*/
char *replacedInput(r_var **head, char *input, char *new_input, int nlen)
{
r_var *indx;
int i, j, k;

indx = *head;
for (j = i = 0; i < nlen; i++)
{
if (input[j] == '$')
{
if (!(indx->len_var) && !(indx->len_val))
{
new_input[i] = input[j];
j++;
}
else if (indx->len_var && !(indx->len_val))
{
for (k = 0; k < indx->len_var; k++)
j++;
i--;
}
else
{
for (k = 0; k < indx->len_val; k++)
{
new_input[i] = indx->val[k];
i++;
}
j += (indx->len_var);
i--;
}
indx = indx->next;
}
else
{
new_input[i] = input[j];
j++;
}
}

return (new_input);
}

/**
* getLine - Entry
* Description: Read inpt from stream
* @lineptr: buffer that stores the input
* @n: size of lineptr
* @stream: stream to read from
* Return: The number of bytes
*/
ssize_t getLine(char **lineptr, size_t *n, FILE *stream)
{
int i;
static ssize_t input;
ssize_t retval;
char *buffer;
char t = 'z';

if (input == 0)
fflush(stream);
else
return (-1);
input = 0;

buffer = malloc(sizeof(char) * BUFSIZE);
if (buffer == 0)
return (-1);
while (t != '\n')
{
i = read(STDIN_FILENO, &t, 1);
if (i == -1 || (i == 0 && input == 0))
{
free(buffer);
return (-1);
}
if (i == 0 && input != 0)
{
input++;
break;
}
if (input >= BUFSIZE)
buffer = _realloc(buffer, input, input + 1);
buffer[input] = t;
input++;
}
buffer[input] = '\0';
bringLine(lineptr, n, buffer, input);
retval = input;
if (i != 0)
input = 0;
return (retval);
}

/**
* isCdir - Entry
* Description: checks ":" if is in the current directory.
* @path: type char pointer char.
* @i: type int pointer of index.
* Return: 1 if the path is searchable in the cd, 0 otherwise.
*/
int isCdir(char *path, int *i)
{
if (path[*i] == ':')
return (1);

while (path[*i] != ':' && path[*i])
{
*i += 1;
}

if (path[*i])
*i += 1;

return (0);
}

/**
* ItoaAux - Entry
* Description: function converts int to string.
* @n: type int number
* Return: String.
*/
char *ItoaAux(int n)
{
unsigned int n1;
int len = GetLen(n);
char *buffer;

buffer = malloc(sizeof(char) * (len + 1));
if (buffer == 0)
return (NULL);

*(buffer + len) = '\0';

if (n < 0)
{
n1 = n * -1;
buffer[0] = '-';
}
else
{
n1 = n;
}

len--;
do {
*(buffer + len) = (n1 % 10) + '0';
n1 = n1 / 10;
len--;
}
while (n1 > 0)
;
return (buffer);
}
