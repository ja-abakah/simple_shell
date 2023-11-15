#include "main.h"

/**
* _which - Entry
* Description: locates a command
*
* @cmd: command name
* @_environ: environment variable
* Return: location of the command.
*/
char *_which(char *cmd, char **_environ)
{
char *path, *ptr_path, *token_path, *dir;
int len_dir, len_cmd, i;
struct stat st;

path = _getenv("PATH", _environ);
if (path)
{
ptr_path = _strdup(path);
len_cmd = _strlen(cmd);
token_path = _strtok(ptr_path, ":");
i = 0;
while (token_path != NULL)
{
if (isCdir(path, &i))
if (stat(cmd, &st) == 0)
return (cmd);
len_dir = _strlen(token_path);
dir = malloc(len_dir + len_cmd + 2);
_strcpy(dir, token_path);
_strcat(dir, "/");
_strcat(dir, cmd);
_strcat(dir, "\0");
if (stat(dir, &st) == 0)
{
free(ptr_path);
return (dir);
}
free(dir);
token_path = _strtok(NULL, ":");
}
free(ptr_path);
if (stat(cmd, &st) == 0)
return (cmd);
return (NULL);
}
if (cmd[0] == '/')
if (stat(cmd, &st) == 0)
return (cmd);
return (NULL);
}

/**
* A_atoi - Entry
* Description: converts a string to an integer.
* @s: input string.
* Return: integer.
*/
int A_atoi(char *s)
{
unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

while (*(s + count) != '\0')
{
if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
break;

if (*(s + count) == '-')
pn *= -1;

if ((*(s + count) >= '0') && (*(s + count) <= '9'))
{
if (size > 0)
m *= 10;
size++;
}
count++;
}

for (i = count - size; i < count; i++)
{
oi = oi + ((*(s + i) - 48) * m);
m /= 10;
}
return (oi * pn);
}

/**
* elpCd - Entry of program
* Description: this helps information in builtin alias.
* Return: no return
*/
void elpCd(void)
{
char *elp = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

write(STDOUT_FILENO, elp, _strlen(elp));
elp = "\tChange working directory of shell.\n ";
write(STDOUT_FILENO, elp, _strlen(elp));
}

/**
* elpUnsetenv - Entry of the program
* Description: this help information in builtin unsetenv
* Return: no return
*/
void elpUnsetenv(void)
{
char *elp = "unsetenv: unsetenv (const char *name)\n\t";

write(STDOUT_FILENO, elp, _strlen(elp));
elp = "Remove an entry completely in environment\n";
write(STDOUT_FILENO, elp, _strlen(elp));
}

/**
* errExitShell - Entry of program
* Description: the generic error message for exit
* @datash: data relevant (counter, arguments)
*
* Return: Error message
*/
char *errExitShell(data_shell *datash)
{
int length;
char *error;
char *ver_str;

ver_str = ItoaAux(datash->counter);
length = _strlen(datash->av[0]) + _strlen(ver_str);
length += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
error = malloc(sizeof(char) * (length + 1));
if (error == 0)
{
free(ver_str);
return (NULL);
}
_strcpy(error, datash->av[0]);
_strcat(error, ": ");
_strcat(error, ver_str);
_strcat(error, ": ");
_strcat(error, datash->args[0]);
_strcat(error, ": Illegal number: ");
_strcat(error, datash->args[1]);
_strcat(error, "\n\0");
free(ver_str);

return (error);
}
