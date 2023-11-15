#include "main.h"

/**
* isExecutable - Entry
* Description: determines if is an executable
*
* @datash: data structure
* Return: 0 if is not an executable, other number if it does
*/
int isExecutable(data_shell *datash)
{
struct stat st;
int i;
char *input;

input = datash->args[0];
for (i = 0; input[i]; i++)
{
if (input[i] == '.')
{
if (input[i + 1] == '.')
return (0);
if (input[i + 1] == '/')
continue;
else
break;
}
else if (input[i] == '/' && i != 0)
{
if (input[i + 1] == '.')
continue;
i++;
break;
}
else
break;
}
if (i == 0)
return (0);

if (stat(input + i, &st) == 0)
{
return (i);
}
errGet(datash, 127);
return (-1);
}

/**
* execLine - Entry
* Description: finds builtins and commands
*
* @datash: data relevant (args)
* Return: 1 on success.
*/
int execLine(data_shell *datash)
{
int (*builtin)(data_shell *datash);

if (datash->args[0] == NULL)
return (1);

builtin = getBuiltin(datash->args[0]);

if (builtin != NULL)
return (builtin(datash));

return (cmdExec(datash));
}

/**
* printsyntaxerror - entry of program
* Description: prints when a syntax error is found
*
* @datash: data structure
* @input: input string
* @i: index of the error
* @bool: to control msg error
* Return: no return
*/
void printsyntaxerror(data_shell *datash, char *input, int i, int bool)
{
char *msg, *msg2, *msg3, *error, *counter;
int length;

if (input[i] == ';')
{
if (bool == 0)
msg = (input[i + 1] == ';' ? ";;" : ";");
else
msg = (input[i - 1] == ';' ? ";;" : ";");
}

if (input[i] == '|')
msg = (input[i + 1] == '|' ? "||" : "|");

if (input[i] == '&')
msg = (input[i + 1] == '&' ? "&&" : "&");

msg2 = ": Syntax error: \"";
msg3 = "\" unexpected\n";
counter = ItoaAux(datash->counter);
length = _strlen(datash->av[0]) + _strlen(counter);
length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(counter);
return;
}
_strcpy(error, datash->av[0]);
_strcat(error, ": ");
_strcat(error, counter);
_strcat(error, msg2);
_strcat(error, msg);
_strcat(error, msg3);
_strcat(error, "\0");

write(STDERR_FILENO, error, length);
free(error);
free(counter);
}

/**
* _reallocdp - entry
* Description: reallocates a memory block of a double pointer.
* @ptr: double pointer to the memory previously allocated.
* @old_size: size, in bytes, of the allocated space of ptr.
* @new_size: new size, in bytes, of the new memory block.
*
* Return: ptr.
* if new_size == old_size, returns ptr without changes.
* if malloc fails, returns NULL.
*/
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
char **newptr;
unsigned int i;

if (ptr == NULL)
return (malloc(sizeof(char *) * new_size));

if (new_size == old_size)
return (ptr);

newptr = malloc(sizeof(char *) * new_size);
if (newptr == NULL)
return (NULL);

for (i = 0; i < old_size; i++)
newptr[i] = ptr[i];

free(ptr);

return (newptr);
}
