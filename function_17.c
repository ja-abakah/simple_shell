#include "main.h"

/**
* copy_info - Entry
* Description: copies info to create
* a new env or alias
* @name: name (env or alias)
* @value: value (env or alias)
*
* Return: new env or alias.
*/
char *copy_info(char *name, char *value)
{
char *new;
int len_name, len_value, len;

len_name = _strlen(name);
len_value = _strlen(value);
len = len_name + len_value + 2;
new = malloc(sizeof(char) * (len));
_strcpy(new, name);
_strcat(new, "=");
_strcat(new, value);
_strcat(new, "\0");

return (new);
}

/**
* swap_char - Entry
* Description: swaps | and & for non-printed chars
*
* @input: input string
* @bool: type of swap
* Return: swapped string
*/
char *swap_char(char *input, int bool)
{
int i;

if (bool == 0)
{
for (i = 0; input[i]; i++)
{
if (input[i] == '|')
{
if (input[i + 1] != '|')
input[i] = 16;
else
i++;
}

if (input[i] == '&')
{
if (input[i + 1] != '&')
input[i] = 12;
else
i++;
}
}
}
else
{
for (i = 0; input[i]; i++)
{
input[i] = (input[i] == 16 ? '|' : input[i]);
input[i] = (input[i] == 12 ? '&' : input[i]);
}
}
return (input);
}

/**
* _strtok - splits a string by some delimiter.
* @str: input string.
* @delim: delimiter.
*
* Return: string splited.
*/
char *_strtok(char str[], const char *delim)
{
static char *splitted, *str_end;
char *str_start;
unsigned int i, bool;

if (str != NULL)
{
if (cmp_chars(str, delim))
return (NULL);
splitted = str;
i = _strlen(str);
str_end = &str[i];
}
str_start = splitted;
if (str_start == str_end)
return (NULL);

for (bool = 0; *splitted; splitted++)
{
if (splitted != str_start)
if (*splitted && *(splitted - 1) == '\0')
break;

for (i = 0; delim[i]; i++)
{
if (*splitted == delim[i])
{
*splitted = '\0';
if (splitted == str_start)
str_start++;
break;
}
}
if (bool == 0 && *splitted)
bool = 1;
}
if (bool == 0)
return (NULL);
return (str_start);
}

/**
* _strcmp - Entry
* Description: Function that compares two strings.
* @s1: type str compared
* @s2: type str compared
* Return: Always 0.
*/
int _strcmp(char *s1, char *s2)
{
int i;

for (i = 0; s1[i] == s2[i] && s1[i]; i++)
;

if (s1[i] > s2[i])
return (1);
if (s1[i] < s2[i])
return (-1);
return (0);
}

/**
* _isdigit - Entry
*Description: defines if string passed is a number
*
* @s: input string
* Return: 1 if string is a number. 0 in other case.
*/
int _isdigit(const char *s)
{
unsigned int i;

for (i = 0; s[i]; i++)
{
if (s[i] < 48 || s[i] > 57)
return (0);
}
return (1);
}
