#include "main.h"

/**
* GetBuiltin - Entry of program
* Description: the builtin that pais the command in the arg
* @cmd: command
* Return: function pointer of the builtin command
*/
int (*GetBuiltin(char *cmd))(data_shell *)
{
builtin_t builtin[] = {
{ "env", _env },
{ "exit", exitShell },
{ "setenv", _setenv },
{ "unsetenv", _unsetenv },
{ "cd", cd_shell },
{ "help", elpGet},
{ NULL, NULL }
};
int i;

for (i = 0; builtin[i].name; i++)
{
if (_strcmp(builtin[i].name, cmd) == 0)
break;
}

return (builtin[i].f);
}

/**
* elpAlias - Entry of program
* Description: This helps information in builtin alias.
* Return: no return
*/
void elpAlias(void)
{
char *elp = "alias: alias [-p] [name[=value]...]\n";

write(STDOUT_FILENO, elp, _strlen(elp));
elp = "\tDisplay aliases.\n ";
write(STDOUT_FILENO, elp, _strlen(elp));
}

/**
* elpSetenv - Entry of program
* Description: this help information in builtin setenv
* Return: no return
*/
void elpSetenv(void)
{

char *elp = "setenv: setenv (const char *name, const char *value,";

write(STDOUT_FILENO, elp, _strlen(elp));
elp = "int replace)\n\t";
write(STDOUT_FILENO, elp, _strlen(elp));
elp = "A new definition to the environment\n";
write(STDOUT_FILENO, elp, _strlen(elp));
}

/**
* errGetCd - Entry of program
* Description: the error message for cd command
* @datash: data relevant (directory)
* Return: Error message
*/
char *errGetCd(data_shell *datash)
{
int len, len_id;
char *error, *ver_str, *msg;

ver_str = ItoaAux(datash->counter);
if (datash->args[1][0] == '-')
{
msg = ": Illegal option ";
len_id = 2;
}
else
{
msg = ": can't cd to ";
len_id = _strlen(datash->args[1]);
}

len = _strlen(datash->av[0]) + _strlen(datash->args[0]);
len += _strlen(ver_str) + _strlen(msg) + len_id + 5;
error = malloc(sizeof(char) * (len + 1));

if (error == 0)
{
free(ver_str);
return (NULL);
}

error = strcatCd(datash, msg, error, ver_str);

free(ver_str);

return (error);
}
