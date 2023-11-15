#include "main.h"

/**
* freelinelist - entry
* Description: frees a line_list
* @head: head of the linked list.
* Return: no return.
*/
void freelinelist(line_list **head)
{
line_list *temp;
line_list *curr;

if (head != NULL)
{
curr = *head;
while ((temp = curr) != NULL)
{
curr = curr->next;
free(temp);
}
*head = NULL;
}
}

/**
* elpGeneral - Entry point of program
* Description this help information for the help builtin
* Return: no return
*/
void elpGeneral(void)
{
char *elp = "^-^ bash, version 1.0(1)-release\n";

write(STDOUT_FILENO, elp, _strlen(elp));
elp = "These commands are defined internally.Type 'help' to see the list";
write(STDOUT_FILENO, elp, _strlen(elp));
elp = "Type 'help name' to find out more about the function 'name'.\n\n ";
write(STDOUT_FILENO, elp, _strlen(elp));
elp = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
write(STDOUT_FILENO, elp, _strlen(elp));
elp = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
write(STDOUT_FILENO, elp, _strlen(elp));
elp = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
write(STDOUT_FILENO, elp, _strlen(elp));
elp = "unsetenv [variable]\n";
write(STDOUT_FILENO, elp, _strlen(elp));
}
/**
* elpExit - Entry of program
* Description: this help information in builint exit
* Return: no return
*/
void elpExit(void)
{
char *elp = "exit: exit [n]\n Exit shell.\n";

write(STDOUT_FILENO, elp, _strlen(elp));
elp = "Exits shell with a status of N. If N is ommited, the exit";
write(STDOUT_FILENO, elp, _strlen(elp));
elp = "statusis that of the last command executed\n";
write(STDOUT_FILENO, elp, _strlen(elp));
}

/**
* checksyntaxerror - Entry
* Description: intermediate function to
* find and print a syntax error
*
* @datash: data structure
* @input: input string
* Return: 1 if there is an error. 0 in other case
*/
int checksyntaxerror(data_shell *datash, char *input)
{
int begin = 0;
int f_char = 0;
int i = 0;

f_char = firstChar(input, &begin);
if (f_char == -1)
{
printsyntaxerror(datash, input, begin, 0);
return (1);
}

i = errorsepop(input + begin, 0, *(input + begin));
if (i != 0)
{
printsyntaxerror(datash, input, begin + i, 1);
return (1);
}

return (0);
}
