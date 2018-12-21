#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

void erroryexit(char* c, int er){
	perror(c);
	exit(er);
}



int main(){
	char buf[256];
	int fd;
	do {
		printf("Waiting for reader\n");
	}while((fd = open("PIPE1", O_WRONLY | O_NONBLOCK)) == -1 && errno == ENXIO);
	printf("Reader found\n");
	int ret;
	close(1);
	while((ret = read(0,&buf,256))>0){
		write(fd, buf, ret);
	}
	close(fd);


}
