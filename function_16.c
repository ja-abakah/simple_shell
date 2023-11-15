#include "main.h"

/**
* *_strcpy - Entry
* Description: Copies the string pointed.
* @dest: Type char pointer the dest of the copied str
* @src: Type char pointer the source of str
* Return: the dest.
*/
char *_strcpy(char *dest, char *src)
{

size_t a;

for (a = 0; src[a] != '\0'; a++)
{
dest[a] = src[a];
}
dest[a] = '\0';

return (dest);
}

/**
* _strlen - Returns the lenght of a string.
* @s: Type char pointer
* Return: Always 0.
*/
int _strlen(const char *s)
{
int len;

for (len = 0; s[len] != 0; len++)
{
}
return (len);
}

/**
* cmp_chars - compare chars of strings
* @str: input string.
* @delim: delimiter.
*
* Return: 1 if are equals, 0 if not.
*/
int cmp_chars(char str[], const char *delim)
{
unsigned int i, j, k;

for (i = 0, k = 0; str[i]; i++)
{
for (j = 0; delim[j]; j++)
{
if (str[i] == delim[j])
{
k++;
break;
}
}
}
if (i == k)
return (1);
return (0);
}

/**
* _getenv - Entry
* Description: get an environment variable
* @name: name of the environment variable
* @_environ: environment variable
*
* Return: value of the environment variable if is found.
* In other case, returns NULL.
*/
char *_getenv(const char *name, char **_environ)
{
char *ptr_env;
int i, mov;

/* Initialize ptr_env value */
ptr_env = NULL;
mov = 0;
for (i = 0; _environ[i]; i++)
{

mov = cmp_env_name(_environ[i], name);
if (mov)
{
ptr_env = _environ[i];
break;
}
}

return (ptr_env + mov);
}

/**
* _setenv - Entry
* Description: compares env variables names
* with the name passed.
* @datash: data relevant (env name and env value)
*
* Return: 1 on success.
*/
int _setenv(data_shell *datash)
{

if (datash->args[1] == NULL || datash->args[2] == NULL)
{
errGet(datash, -1);
return (1);
}

set_env(datash->args[1], datash->args[2], datash);

return (1);
}
