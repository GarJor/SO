#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
void Usage() {
	char buffer[256];
	sprintf(buffer, "Usage: set_holes f1 f2 \n");
	write(1, buffer, strlen(buffer));
}

void surtxerror(char* s, int e){
	perror(s);
	exit(e);
}

int main(int argc, char *argv[]) {
	char buffer[256];
	if(argc != 3) {
		Usage();
		surtxerror("Entrada incorrecte\n",2);
	}
	int fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1) surtxerror("Error en el primer open", 1);
	int fd2 = open(argv[2], O_WRONLY);
	if(fd2 == -1) surtxerror("Error en el segon open", 1);
	char c;
	int pos;
	int ret;

	while((ret = read(fd1, &pos, sizeof(int))) > 0) {
		if(lseek(fd2, pos, SEEK_SET) == -1) surtxerror("posicio incorrecte",1);
		write(fd2, "0", sizeof(char));

	}
	if(ret == -1) surtxerror("Error en el read", 1);


}
