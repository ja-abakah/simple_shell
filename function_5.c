#include "main.h"

/**
* errNotFound - Entry of program
* Description: the generic error message for command not found
* @datash: data relevant (counter, arguments)
* Return: Error message
*/
char *errNotFound(data_shell *datash)
{
int len;
char *error;
char *ver_str;

ver_str = ItoaAux(datash->counter);
len = _strlen(datash->av[0]) + _strlen(ver_str);
len += _strlen(datash->args[0]) + 16;
error = malloc(sizeof(char) * (len + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}
_strcpy(error, datash->av[0]);
_strcat(error, ": ");
_strcat(error, ver_str);
_strcat(error, ": ");
_strcat(error, datash->args[0]);
_strcat(error, ": not found\n");
_strcat(error, "\0");
free(ver_str);
return (error);
}

/**
* errPath_26 - Entry of program
* Description: the message for path and failure denied permission.
* @datash: data relevant (counter, arguments).
*
* Return: The error string.
*/
char *errPath_26(data_shell *datash)
{
int len;
char *ver_str;
char *error;

ver_str = ItoaAux(datash->counter);
len = _strlen(datash->av[0]) + _strlen(ver_str);
len += _strlen(datash->args[0]) + 24;
error = malloc(sizeof(char) * (len + 1));
if (error == 0)
{
free(error);
free(ver_str);
return (NULL);
}
_strcpy(error, datash->av[0]);
_strcat(error, ": ");
_strcat(error, ver_str);
_strcat(error, ": ");
_strcat(error, datash->args[0]);
_strcat(error, ": Permission denied\n");
_strcat(error, "\0");
free(ver_str);
return (error);
}

/**
* errGet - calls the error according the builtin, syntax or permission
* @datash: data structure that contains arguments
* @eval: error value
* Return: error
*/
int errGet(data_shell *datash, int eval)
{
char *error;

switch (eval)
{
case -1:
error = errEnv(datash);
break;
case 126:
error = errPath_26(datash);
break;
case 127:
error = errNotFound(datash);
break;
case 2:
if (_strcmp("exit", datash->args[0]) == 0)
error = errExitShell(datash);
else if (_strcmp("cd", datash->args[0]) == 0)
error = errGetCd(datash);
break;
}

if (error)
{
write(STDERR_FILENO, error, _strlen(error));
free(error);
}

datash->status = eval;
return (eval);
}

/**
* dotCd - entry of program
* Description: changes to the parent directory
*
* @datash: data relevant (environ)
*
* Return: no return
*/
void dotCd(data_shell *datash)
{
char pwd[PATH_MAX];
char *dir, *cp_pwd, *cp_strtok_pwd;

getcwd(pwd, sizeof(pwd));
cp_pwd = _strdup(pwd);
set_env("OLDPWD", cp_pwd, datash);
dir = datash->args[1];
if (_strcmp(".", dir) == 0)
{
set_env("PWD", cp_pwd, datash);
free(cp_pwd);
return;
}
if (_strcmp("/", cp_pwd) == 0)
{
free(cp_pwd);
return;
}
cp_strtok_pwd = cp_pwd;
rev_string(cp_strtok_pwd);
cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
if (cp_strtok_pwd != NULL)
{
cp_strtok_pwd = _strtok(NULL, "\0");

if (cp_strtok_pwd != NULL)
rev_string(cp_strtok_pwd);
}
if (cp_strtok_pwd != NULL)
{
chdir(cp_strtok_pwd);
set_env("PWD", cp_strtok_pwd, datash);
}
else
{
chdir("/");
set_env("PWD", "/", datash);
}
datash->status = 0;
free(cp_pwd);
}
