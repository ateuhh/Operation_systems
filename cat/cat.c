#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

const int buffer_size = 4096;

void copy (char* buffer, int a) 
{
	ssize_t buf_r;
	while ((buf_r=read(a, buffer, buffer_size))>0)
	{
		write(1, buffer, buf_r);
	}
}
int main(int argc, char** argv) {
	char* buffer = (char*) malloc(buffer_size);
	if (argc == 1) {
		copy(0, buffer);
	} else {
		size_t i;
		for (i = 1; i < argc; i++) {
			int a = open(argv[i], O_RDONLY);
			if (a == -1)
				continue;
			copy(a, buffer);
			close(a);
		}
	}
	free(buffer);
	return 0;
}