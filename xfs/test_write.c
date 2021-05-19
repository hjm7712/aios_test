#define _GNU_SOURCE

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <sched.h>

#define MARK(__msg) write(marker_fd, __msg, strlen(__msg));
#define O_CLUSTER 040000000

void main(void)
{
	int marker_fd;
	int trace_fd;

	int fd;

	cpu_set_t mask;
	CPU_ZERO(&mask);

	marker_fd = open("/sys/kernel/debug/tracing/trace_marker", O_RDWR);

	MARK("##### before open\n");
	fd = open("./test.txt", O_RDWR | O_CREAT);
	MARK("##### after open\n");

	if (fd <= 0) {
		printf("error\n");
		return;
	} else {
		int i;
		char *buf = (char *)malloc(sizeof(char)*4096);
		for(int i=0;i<4096;i++)	
			buf[i]='a';
		MARK("##### before write\n");
		i = write(fd, buf, 4096);
		MARK("##### after write\n");
		MARK("##### before fsync\n");
		fsync(fd);
		MARK("##### after fsync\n");
	}
	close(fd);
	close(marker_fd);
}

