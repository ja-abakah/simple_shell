#include "main.h"

/**
* cmp_env_name - Entry
* Description: compares environment variables names
* with the name passed.
* @nenv: name of the environment variable
* @name: name passed
*
* Return: 0 if are not equal. Another value if they are.
*/
int cmp_env_name(const char *nenv, const char *name)
{
int i;

for (i = 0; nenv[i] != '='; i++)
{
if (nenv[i] != name[i])
{
return (0);
}
}

return (i + 1);
}

/**
* rev_string - Entry
* Description: reverses string.
* @s: input string.
* Return: no return.
*/
void rev_string(char *s)
{
int count = 0, i, j;
char *str, temp;

while (count >= 0)
{
if (s[count] == '\0')
break;
count++;
}
str = s;

for (i = 0; i < (count - 1); i++)
{
for (j = i + 1; j > 0; j--)
{
temp = *(str + j);
*(str + j) = *(str + (j - 1));
*(str + (j - 1)) = temp;
}
}
}

/**
* _strdup - Entry
* Description: duplicates in the heap memory.
* @s: Type char pointer str
* Return: duplicated str
*/
char *_strdup(const char *s)
{
char *new;
size_t len;

len = _strlen(s);
new = malloc(sizeof(char) * (len + 1));
if (new == NULL)
return (NULL);
_memcpy(new, s, len + 1);
return (new);
}

/**
* _strcat - Entry
* Description: concatenate two strings
* @dest: char pointer the dest of the copied str
* @src: const char pointer the source of str
* Return: the dest
*/
char *_strcat(char *dest, const char *src)
{
int i;
int j;

for (i = 0; dest[i] != '\0'; i++)
;

for (j = 0; src[j] != '\0'; j++)
{
dest[i] = src[j];
i++;
}

dest[i] = '\0';
return (dest);
}
