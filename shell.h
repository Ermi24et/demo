#ifndef SHELL_H
#define SHELL_H

/* standard headers for the files */
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/* declaring an external environment variables */
extern char **environ;

/* function prototypes for our shell */
void print_environment(void);
int cmd_ok(char **tok_str, int count, char **argv);
void c_execute(char **comm);
char **comm_tok(char *str, char *delimiters);
char *_getenv(const char *name);
char *find_path(char *command);
void handle_error(char *pro_name, char *com, int counter);
int count_str(char *str, char *delimiters);
void signal_handler(int signal);
char *_prompt(char *prompt);
char *non_interactive();

/* function prototypes for utility functions */
char *int_to_str(int val);
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
char *_strdup(char *str);

#endif
