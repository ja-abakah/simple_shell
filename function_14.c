#include "main.h"

/**
* repeatedChar - entry
* Description: counts the repetitions of a char
*
* @input: input string
* @i: index
* Return: repetitions
*/
int repeatedChar(char *input, int i)
{
if (*(input - 1) == *input)
return (repeatedChar(input - 1, i + 1));

return (i);
}

/**
* checkerrorcmd - Entry
* Description: verifies if user has permissions to access
*
* @dir: destination directory
* @datash: data structure
* Return: 1 if there is an error, 0 if not
*/
int checkerrorcmd(char *dir, data_shell *datash)
{
if (dir == NULL)
{
errGet(datash, 127);
return (1);
}

if (_strcmp(datash->args[0], dir) != 0)
{
if (access(dir, X_OK) == -1)
{
errGet(datash, 126);
free(dir);
return (1);
}
free(dir);
}
else
{
if (access(datash->args[0], X_OK) == -1)
{
errGet(datash, 126);
return (1);
}
}

return (0);
}

/**
* cmdExec - Entry
* Description: executes command lines
*
* @datash: data relevant (args and input)
* Return: 1 on success.
*/
int cmdExec(data_shell *datash)
{
pid_t pd;
pid_t wpd;
int state;
int exec;
char *dir;
(void) wpd;

exec = isExecutable(datash);
if (exec == -1)
return (1);
if (exec == 0)
{
dir = _which(datash->args[0], datash->_environ);
if (checkerrorcmd(dir, datash) == 1)
return (1);
}

pd = fork();
if (pd == 0)
{
if (exec == 0)
dir = _which(datash->args[0], datash->_environ);
else
dir = datash->args[0];
execve(dir + exec, datash->args, datash->_environ);
}
else if (pd < 0)
{
perror(datash->av[0]);
return (1);
}
else
{
do {
wpd = waitpid(pd, &state, WUNTRACED);
} while (!WIFEXITED(state) && !WIFSIGNALED(state));
}

datash->status = state / 256;
return (1);
}
