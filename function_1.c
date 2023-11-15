#include "main.h"

/**
* GetLen - Entry
* Description: Get the lenght of a number.
* @n: type int number.
* Return: Lenght of a number.
*/
int GetLen(int n)
{
unsigned int n1;
int len = 1;

if (n < 0)
{
len++;
n1 = n * -1;
}
else
{
n1 = n;
}
while (n1 > 9)
{
len++;
n1 = n1 / 10;
}

return (len);
}

/**
* bringLine - Entry
* Description: assigns the line var for get_line
* @lineptr: Buffer that store the input str
* @buffer: str that is been called to line
* @n: size of line
* @j: size of buffer
*/
void bringLine(char **lineptr, size_t *n, char *buffer, size_t j)
{

if (*lineptr == NULL)
{
if  (j > BUFSIZE)
*n = j;

else
*n = BUFSIZE;
*lineptr = buffer;
}
else if (*n < j)
{
if (j > BUFSIZE)
*n = j;
else
*n = BUFSIZE;
*lineptr = buffer;
}
else
{
_strcpy(*lineptr, buffer);
free(buffer);
}
}

/**
* readLine - Entry
* Description: reads the input string.
*
* @i_eof: return value of getline function
* Return: input string
*/
char *readLine(int *i_eof)
{
char *input = NULL;
size_t bufsize = 0;

*i_eof = getLine(&input, &bufsize, stdin);

return (input);
}

/**
* checkEnv - Entry
* Description: checks if the typed variable is an env variable
*
* @h: head of linked list
* @in: input string
* @data: data structure
* Return: no return
*/
void checkEnv(r_var **h, char *in, data_shell *data)
{
int row, chr, j, lval;
char **_envr;

_envr = data->_environ;
for (row = 0; _envr[row]; row++)
{
for (j = 1, chr = 0; _envr[row][chr]; chr++)
{
if (_envr[row][chr] == '=')
{
lval = _strlen(_envr[row] + chr + 1);
addrvarnode(h, j, _envr[row] + chr + 1, lval);
return;
}

if (in[j] == _envr[row][chr])
j++;
else
break;
}
}

for (j = 0; in[j]; j++)
{
if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
break;
}

addrvarnode(h, j, NULL, 0);
}
