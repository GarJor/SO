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
	sprintf(buffer, "Usage: buscaLetra char file\n");
  write(2, buffer, strlen(buffer));
	exit(1);
}

void surtxerror(char* s, int e){
	perror(s);
	exit(e);
}

int main(int argc, char *argv[]) {
  if(argc != 3) Usage();

  int fd = open(argv[2], O_RDONLY);
  if(fd == -1) surtxerror("open() fallit.\n",2);
  char *c;
  int ret;
  char buffer[256];
  int pos = 0;
  while((ret=read(fd,c,1))>0){ //si declaro c com un punter no he de posar el &c en el read, sino directament c
    if(strcmp(c,argv[1])==0){
      write(1,&pos,sizeof(pos)); //representacion interna de entero
    }
    ++pos;
  }
  if(ret == -1) surtxerror("read() fallit.\n",2);
}
