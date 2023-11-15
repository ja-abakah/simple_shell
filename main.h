#ifndef _MAIN_H_
#define _MAIN_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>


#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
* struct data - struct that holds data on runtime
* @av: argument vector
* @input: command line by the user
* @args: tokens of command line
* @status: last status of shell
* @counter: lines counter
* @_environ: environment variable
* @pid: process ID of the shell
*/
typedef struct data
{
char **av;
char *input;
char **args;
int status;
int counter;
char **_environ;
char *pid;
}
data_shell;

/**
* struct sep_list_s - single linked list
* @separator: ; | &
* @next: next node
* Description: single linked list to store separators
*/
typedef struct sep_list_s
{
char separator;
struct sep_list_s *next;
} sep_list;

/**
* struct line_list_s - single list
* @line: command line
* @next: next node
* Description: single linked list to store command lines
*/
typedef struct line_list_s
{
char *line;
struct line_list_s *next;
}
line_list;
/**
* struct r_var_list - single linked list
* @len_var: length of the variable
* @val: value of the variable
* @len_val: length of the value
* @next: next node
* Description: single linked list to store variables
*/
typedef struct r_var_list
{
int len_var;
char *val;
int len_val;
struct r_var_list *next;
}
r_var;

/**
* struct builtin_s - for command args.
* @name: The name of the command builtin i.e cd, exit, env
* @f: data type pointer function.
*/
typedef struct builtin_s
{
char *name;
int (*f)(data_shell *datash);
}
builtin_t;

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
char *_strdup(const char *s);
int _strlen(const char *s);
void printsyntaxerror(data_shell *datash, char *input, int i, int bool);
int checksyntaxerror(data_shell *datash, char *input);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);
char *replacedInput(r_var **head, char *input, char *new_input, int nlen);
char *repVar(char *input, data_shell *datash);
int checkerrorcmd(char *dir, data_shell *datash);
int cmdExec(data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);
void previousCd(data_shell *datash);
void homeCd(data_shell *datash);
char *error_get_alias(char **args);
char *errEnv(data_shell *datash);
void elpEnv(void);
void elpSetenv(void);
void elpAlias(void);
void elpCd(void);
int elpGet(data_shell *datash);
void bringLine(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t getLine(char **lineptr, size_t *n, FILE *stream);
int isCdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
void dotCd(data_shell *datash);
void CdTo(data_shell *datash);
line_list *addlinenodeend(line_list **head, char *line);
void freelinelist(line_list **head);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
char *ItoaAux(int n);
int A_atoi(char *s);
char *strcatCd(data_shell *, char *, char *, char *);
char *errGetCd(data_shell *datash);
char *error_permission(char **args);
char *errPath_26(data_shell *datash);
void elpGeneral(void);
void elpExit(void);
sep_list *addsepnodeend(sep_list **head, char sep);
void freeseplist(sep_list **head);
r_var *addrvarnode(r_var **head, int lvar, char *var, int lval);
void freervarlist(r_var **head);
void elpUnsetenv(void);
void elpAux(void);
void getSigint(int sig);
int errGet(data_shell *datash, int eval);
int GetLen(int n);
char *errNotFound(data_shell *datash);
char *error_syntax(char **args);
char *errExitShell(data_shell *datash);
int exitShell(data_shell *datash);
int (*getBuiltin(char *cmd))(data_shell *datash);
int cd_shell(data_shell *datash);
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);
int isExecutable(data_shell *datash);
char *readLine(int *i_eof);
char *swap_char(char *input, int bool);
void checkEnv(r_var **h, char *in, data_shell *data);
int checkVars(r_var **h, char *in, char *st, data_shell *data);
int exec_line(data_shell *datash);
char *withoutComment(char *in);
void shellLoop(data_shell *datash);
int errsepop(char *input, int i, char last);
int firstChar(char *input, int *i);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
void rev_string(char *s);
int repeatedChar(char *input, int i);
int cmp_chars(char str[], const char *delim);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
char *_strcat(char *dest, const char *src);
int cmp_env_name(const char *name);

#endif
