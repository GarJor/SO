#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>

void Usage() {
	char buffer[256];
	sprintf(buffer, "Usage: tachaCaracteres file  \n");
  write(2, buffer, strlen(buffer));
	exit(1);
}

void surtxerror(char* s, int e){
	perror(s);
	exit(e);
}

int main(int argc, char *argv[]) {
  if(argc != 2)  Usage();

  int fd = open(argv[1],O_WRONLY);
  if(fd == -1) surtxerror("open() fallit",2);
  char buffer[256];
  int tam = lseek(fd,3,SEEK_END);
  int count=0;
  int p;

  while(read(0,&p,sizeof(p))>0){

    if(p>=0 && p<=tam){
      lseek(fd,p,SEEK_SET);
      sprintf(buffer,"X");
      write(fd,buffer,1);
      ++count;

    }
  }
  sprintf(buffer,"Se han tachado %d caracteres\n",count);
  write(1,buffer,strlen(buffer));
}
