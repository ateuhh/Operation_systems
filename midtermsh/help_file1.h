#ifndef HELP_FILE1_H

#define HELP_FILE1_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

struct buf_t {
	char* buf;
	size_t capacity;
	size_t size;
};
struct buf_t *buf_new(size_t capacity);
void buf_free(struct buf_t* buffer);
size_t buf_capacity(struct buf_t* buffer);
size_t buf_size(struct buf_t* buffer);
ssize_t buf_fill(int fd, struct buf_t* buffer, size_t required);
ssize_t buf_flush(int fd, struct buf_t* buffer, size_t required);
ssize_t buf_getline(int fd, struct buf_t* buffer, char* dest);
ssize_t buf_write(int fd, struct buf_t* buffer, char* src, size_t len);

#endif