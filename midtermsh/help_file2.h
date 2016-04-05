#ifndef HELP_FILE2_H
#define HELP_FILE2_H

#ifndef _POSIX_C_SOURCE 
#define _POSIX_C_SOURCE 199309L
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h> 
#include <sys/wait.h>
#include <sys/types.h>

ssize_t read_(int fd, void* buf, size_t count);
ssize_t write_(int fd, void* buf, size_t count);
ssize_t read_until(int fd, void* buf, size_t count, char delimiter);

struct execargs_t {
	size_t kol;
	char** args;
};

struct execargs_t* execargs_new(char* str, size_t kol);
void execargs_free(struct execargs_t* ea, int kol);
int exec(struct execargs_t* args);
int runpiped(struct execargs_t** programs, size_t n);

#endif