#include "main.h"

/**
* shellCd - Entry of program
* Description: changes current directory
*
* @datash: data relevant
* Return: 1 on success
*/
int shellCd(data_shell *datash)
{
char *dir;
int ishome, ishome2, isddash;

dir = datash->args[1];

if (dir != NULL)
{
ishome = _strcmp("$HOME", dir);
ishome2 = _strcmp("~", dir);
isddash = _strcmp("--", dir);
}

if (dir == NULL || !ishome || !ishome2 || !isddash)
{
homeCd(datash);
return (1);
}

if (_strcmp("-", dir) == 0)
{
cd_previous(datash);
return (1);
}

if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
{
dotCd(datash);
return (1);
}

CdTo(datash);

return (1);
}

/**
* previousCd - Entry of program
* Description: changes to the previous directory
*
* @datash: data relevant (environ)
* Return: no return
*/
void previousCd(data_shell *datash)
{
char pwd[PATH_MAX];
char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

getcwd(pwd, sizeof(pwd));
cp_pwd = _strdup(pwd);

p_oldpwd = _getenv("OLDPWD", datash->_environ);

if (p_oldpwd == NULL)
cp_oldpwd = cp_pwd;
else
cp_oldpwd = _strdup(p_oldpwd);

set_env("OLDPWD", cp_pwd, datash);

if (chdir(cp_oldpwd) == -1)
set_env("PWD", cp_pwd, datash);
else
set_env("PWD", cp_oldpwd, datash);

p_pwd = _getenv("PWD", datash->_environ);

write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
write(STDOUT_FILENO, "\n", 1);

free(cp_pwd);
if (p_oldpwd)
free(cp_oldpwd);

datash->status = 0;

chdir(p_pwd);
}

/**
* addrvarnode - entry
* Description: adds a variable at the end
* of a r_var list.
* @head: head of the linked list.
* @lvar: length of the variable.
* @val: value of the variable.
* @lval: length of the value.
* Return: address of the head.
*/
r_var *addrvarnode(r_var **head, int lvar, char *val, int lval)
{
r_var *new, *temp;

new = malloc(sizeof(r_var));
if (new == NULL)
return (NULL);

new->len_var = lvar;
new->val = val;
new->len_val = lval;

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

/**
* homeCd - entry of program
* Description: changes to home directory
*
* @datash: data relevant (environ)
* Return: no return
*/
void homeCd(data_shell *datash)
{
char *p_pwd, *home;
char pwd[PATH_MAX];

getcwd(pwd, sizeof(pwd));
p_pwd = _strdup(pwd);

home = _getenv("HOME", datash->_environ);

if (home == NULL)
{
set_env("OLDPWD", p_pwd, datash);
free(p_pwd);
return;
}

if (chdir(home) == -1)
{
errGet(datash, 2);
free(p_pwd);
return;
}

set_env("OLDPWD", p_pwd, datash);
set_env("PWD", home, datash);
free(p_pwd);
datash->status = 0;
}
