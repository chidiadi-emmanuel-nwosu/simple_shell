#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#define TRUE 1
#define MAX_NUM_ARGS 124
#define MAX_LINE 80
#define BUF_SIZE 1024


extern char **environ;
static __attribute__((unused)) int exit_v;


/**
 * struct op - Struct op
 *
 * @op: The operator
 * @f: The function associated
 */
typedef struct op
{
	char *op;
	int (*f)(char **, char *, int);
} op_t;




/************main********/
void prompt(void);
char *check_comments(char *s);
void signal_handler(__attribute__((unused)) int signal);
void free_args(char **args);


/***********builtins_helpers.c*********/
int (*get_cmd_func(char *s))(char **, char *, int);


/***********builtins.c*********/
int cd_cmd(char **args, char *, int);
int env_cmd(char **args, char *, int);
int exit_cmd(char **args, char *, int);
int pwd_cmd(char **args, char *, int);
int clear_cmd(char **, char *, int);




/***********builtins2.c*********/
int setenv_cmd(char **args, char *, int);
int unsetenv_cmd(char **args, char *, int);


/**********cmd_handlers**********/
void handle_cmd(char *cmd, char *, int *);
char **split(char *cmd, char *delim);



/***********cmd_helphers.c********/
char *get_cmd();
char *get_cmd_path(char *cmd);
int exec_cmds(char **args, char *, int);
int exec_cmd(char *arg, char **args);
int echo_cmd(char *arg, char **args);



/***********env.c********/
char *_getenv(char *name);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);




/***********errors.c********/
void cmd_error(char *cmd, char *, int);
void syntax_error(char *cmd, char *, int);
void cannot_open_error(char *cmd, char *prog, int hist);
void cd_error(char *cmd, char *prog, int hist);



/***********isatty.c********/
void _non_isatty(char *, int *);
void _isatty(char *, int *);
void file_input(char **av, char *, int *);



/************string_helphers********/
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
char *_strcat(char *dest, char *src);


/************string_helphers********/
char **parse_args(char *cmd, const char *delim);
char *_strtok(char *str, const char *delim);



/************string_helphers2********/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _atoi(char *s);
char *_strip(char *str);
char *_memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);




/************string_helphers3********/
char *_strchr(char *s, char c);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, char *accept);
char *_strstr(char *haystack, char *needle);
char *_strtok_r(char *str, char *delim, char **saveptr);




/************string_helphers3********/
char *_strdup(char *str);
char *_itoa(int num);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strncpy(char *dest, char *src, int n);


#endif
