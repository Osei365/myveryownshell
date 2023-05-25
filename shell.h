#ifndef _MAIN_H_
#define _MAIN_H_


#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RD_BUF 1024
#define WR_BUF 1024
#define BUF_FL -1


#define COMMAND_N	0
#define COMMAND_O	1
#define COMMAND_A	2
#define COMMAND_C	3


#define LC_CONVERT	1
#define UN_CONVERT	2

#define GETLINE_UT 0
#define STRTOK_UT  0

#define HFILE	".simple_shell_history"
#define HMAX	4096

extern char **environ;


/**
 * struct list_of_str - singly linked list
 * @n: number
 * @str: the string
 * @next: pointer for linked list
 */
typedef struct list_of_str
{
	int n;
	char *str;
	struct list_of_str *next;
} liststr_t;

/**
 *struct passarg - all arguments to pas into function 
 *@a: getline string
 *@av: vector of string
 *@path: path to string
 *@ac: the argument count
 *@l_count: count of error
 *@err_no: code for error exit
 *@lc_flag: line count flag
 *@fn: filename
 *@envp: environ local copy
 *@environ: environ
 *@hist: history
 *@alias: alias
 *@env_ch: environ changed
 *@status: status of exec
 *@cmd_buffer: address that points to command buffer
 *@cmd_buffer_type: command buffer type
 *@readfd: filedescriptor to read
 *@histlen: length of history
 */
typedef struct passinfo
{
	char *a;
	char **av;
	char *path;
	int ac;
	unsigned int l_count;
	int err_no;
	int lc_flag;
	char *fn;
	list_t *envp;
	list_t *hist;
	list_t *alias;
	char **environ;
	int env_ch;
	int status;

	char **cmd_buffer;
	int cmd_buffer_type;
	int readfd;
	int histlen;
} arg_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - builtin
 *@type: command
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} blt_t;


int hshell(arg_t *, char **);
int disc_builtin(arg_t *);
void disc_cmd(arg_t *);
void fork_cmd(arg_t *);


int check_cmd(arg_t *, char *);
char *double_chars(char *, int, int);
char *disc_path(arg_t *, char *, char *);

int loophshell(char **);

int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);


int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);


char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
/
char **strtow(char *, char *);
char **strtow2(char *, char);


char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);

int _isalpha(int);
int _atoi(char *);
int shellinteractive(arg_t *);
int is_delim(char, char *);



int _erratoi(char *);
void print_error(arg_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int _myexit(arg_t *);
int _mycd(arg_t *);
int _myhelp(arg_t *);

int _myhistory(arg_t *);
int _myalias(arg_t *);

ssize_t get_input(arg_t *);
int _getline(arg_t *, char **, size_t *);
void sigintHandler(int);

void clear_arg(arg_t *);
void set_arg(arg_t *, char **);
void free_arg(arg_t *, int);

char *_getenv(arg_t *, const char *);
int _myenv(arg_t *);
int _mysetenv(arg_t *);
int _myunsetenv(arg_t *);
int populate_env_list(arg_t *);

char **get_environ(arg_t *);
int _unsetenv(arg_t *, char *);
int _setenv(arg_t *, char *, char *);

char *get_history_file(arg_t *arg);
int write_history(arg_t *arg);
int read_history(arg_t *arg);
int build_history_list(arg_t *arg, char *buf, int linecount);
int renumber_history(arg_t *arg);


list_t *add_node(liststr_t **, const char *, int);
list_t *add_node_end(liststr_t **, const char *, int);
size_t print_list_str(const liststr_t *);
int delete_node_at_index(liststr_t **, unsigned int);
void free_list(liststr_t **);


size_t list_len(const liststr_t *);
char **list_to_strings(liststr_t *);
size_t print_list(const liststr_t *);
list_t *node_starts_with(liststr_t *, char *, char);
ssize_t get_node_index(liststr_t *, liststr_t *);

int is_chain(arg_t *, char *, size_t *);
void check_chain(arg_t *, char *, size_t *, size_t, size_t);
int replace_alias(arg_t *);
int replace_vars(arg_t *);
int replace_string(char **, char *);

#endif
