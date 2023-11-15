#include "main.h"

/**
* CdTo - Entry of program
* Description: changes to a directory given
* by the user
*
* @datash: data relevant (directories)
* Return: no return
*/
void CdTo(data_shell *datash)
{
char pwd[PATH_MAX];
char *dir, *cp_pwd, *cp_dir;

getcwd(pwd, sizeof(pwd));

dir = datash->args[1];
if (chdir(dir) == -1)
{
errGet(datash, 2);
return;
}

cp_pwd = _strdup(pwd);
set_env("OLDPWD", cp_pwd, datash);

cp_dir = _strdup(dir);
set_env("PWD", cp_dir, datash);

free(cp_pwd);
free(cp_dir);

datash->status = 0;

chdir(dir);
}

/**
* shellLoop - Entry
* Description: Loop of shell
* @datash: data relevant (av, input, args)
*
* Return: no return.
*/
void shellLoop(data_shell *datash)
{
int loop, i_eof;
char *input;

loop = 1;
while (loop == 1)
{
write(STDIN_FILENO, "^-^ ", 4);
input = readLine(&i_eof);
if (i_eof != -1)
{
input = withoutComment(input);
if (input == NULL)
continue;

if (checksyntaxerror(datash, input) == 1)
{
datash->status = 2;
free(input);
continue;
}
input = repVar(input, datash);
loop = split_commands(datash, input);
datash->counter += 1;
free(input);
}
else
{
loop = 0;
free(input);
}
}
}

/**
* freervarlist - entry
* description: frees a r_var list
* @head: head of the linked list.
* Return: no return.
*/
void freervarlist(r_var **head)
{
r_var *temp;
r_var *curr;

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
* addsepnodeend - aentry
* Description: dds a separator found at the end
* of a sep_list.
* @head: head of the linked list.
* @sep: separator found (; | &).
* Return: address of the head.
*/
sep_list *addsepnodeend(sep_list **head, char sep)
{
sep_list *new, *temp;

new = malloc(sizeof(sep_list));
if (new == NULL)
return (NULL);

new->separator = sep;
new->next = NULL;
temp = *head;

if (temp == NULL)
{
*head = new;
}
else
{
while (temp->next != NULL)
temp = temp->next;
temp->next = new;
}

return (*head);
}
