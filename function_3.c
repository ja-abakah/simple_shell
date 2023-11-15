#include "main.h"

/**
* elpGet - Entry of program
* Description: this function retrieves help messages according builtin
* @datash: data structure (args and input)
* Return: Return 0
*/
int elpGet(data_shell *datash)
{

if (datash->args[1] == 0)
elpGeneral();
else if (_strcmp(datash->args[1], "setenv") == 0)
elpSetenv();
else if (_strcmp(datash->args[1], "env") == 0)
elpEnv();
else if (_strcmp(datash->args[1], "unsetenv") == 0)
elpUnsetenv();
else if (_strcmp(datash->args[1], "help") == 0)
elpAux();
else if (_strcmp(datash->args[1], "exit") == 0)
elpExit();
else if (_strcmp(datash->args[1], "cd") == 0)
elpCd();
else if (_strcmp(datash->args[1], "alias") == 0)
elpAlias();
else
write(STDERR_FILENO, datash->args[0],
_strlen(datash->args[0]));

datash->status = 0;
return (1);
}

/**
* elpEnv - Entry of program
* Description: this help information in builtin env
* Return: no return
*/
void elpEnv(void)
{
char *elp = "env: env [option] [name=value] [command [args]]\n\t";

write(STDOUT_FILENO, elp, _strlen(elp));
elp = "shows the enviroment of the shell.\n";
write(STDOUT_FILENO, elp, _strlen(elp));

}

/**
* elpAux - Entry of program
* Description: elps information in builtin elp.
* Return: no return
*/
void elpAux(void)
{
char *elp = "elp: elp [-dms] [pattern ...]\n";

write(STDOUT_FILENO, elp, _strlen(elp));
elp = "\tDisplays information about builtin commands.\n ";
write(STDOUT_FILENO, elp, _strlen(elp));
elp = "Display summaries of builtin commands.\n";
write(STDOUT_FILENO, elp, _strlen(elp));
}

/**
* exitShell - Entry
* Description: exits the shell
*
* @datash: data relevant (status and args)
* Return: 0 on success.
*/
int(*getBuiltin(char * cmd) )(data_shell *datash)
{
return nullptr;
}
int exitShell(data_shell *datash)
{
unsigned int ustatus;
int is_digit;
int str_len;
int big_number;

if (datash->args[1] != NULL)
{
ustatus = A_atoi(datash->args[1]);
is_digit = _isdigit(datash->args[1]);
str_len = _strlen(datash->args[1]);
big_number = ustatus > (unsigned int)INT_MAX;
if (!is_digit || str_len > 10 || big_number)
{
errGet(datash, 2);
datash->status = 2;
return (1);
}
datash->status = (ustatus % 256);
}
return (0);
}
