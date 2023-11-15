#include "main.h"

/**
* withoutComment - Entry
* Description: deletes comments from the input
*
* @in: input string
* Return: input without comments
*/
char *withoutComment(char *in)
{
int i, up_to;

up_to = 0;
for (i = 0; in[i]; i++)
{
if (in[i] == '#')
{
if (i == 0)
{
free(in);
return (NULL);
}

if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
up_to = i;
}
}

if (up_to != 0)
{
in = _realloc(in, i, up_to + 1);
in[up_to] = '\0';
}

return (in);
}

/**
* errEnv - Entry of program
* Description: the error message for env.
* @datash: data relevant (counter, arguments)
* Return: error message.
*/
char *errEnv(data_shell *datash)
{
int len;
char *error;
char *ver_str;
char *msg;

ver_str = ItoaAux(datash->counter);
msg = ": Unable to add/remove from environment\n";
len = _strlen(datash->av[0]) + _strlen(ver_str);
len += _strlen(datash->args[0]) + _strlen(msg) + 4;
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
_strcat(error, msg);
_strcat(error, "\0");
free(ver_str);

return (error);
}

/**
* strcatCd - Entry of program
* Description: this function concatenates the message of cd error
*
* @datash: data relevant (directory)
* @msg: message to print
* @error: output message
* @ver_str: counter lines
* Return: error message
*/
char *strcatCd(data_shell *datash, char *msg, char *error, char *ver_str)
{
char *illegal_flag;

_strcpy(error, datash->av[0]);
_strcat(error, ": ");
_strcat(error, ver_str);
_strcat(error, ": ");
_strcat(error, datash->args[0]);
_strcat(error, msg);
if (datash->args[1][0] == '-')
{
illegal_flag = malloc(3);
illegal_flag[0] = '-';
illegal_flag[1] = datash->args[1][1];
illegal_flag[2] = '\0';
_strcat(error, illegal_flag);
free(illegal_flag);
}
else
{
_strcat(error, datash->args[1]);
}

_strcat(error, "\n");
_strcat(error, "\0");
return (error);
}

/**
 * getSigint - Entry of program 
 * Description: this handles the crtl + c call in prompt
 * @sig: Signal handler
 */
void getSigint(int sig)
{
(void)sig;
write(STDOUT_FILENO, "\n^-^ ", 5);
}
