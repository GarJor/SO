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
	sprintf(buffer, "Usage: ./suma_enteros file \n");
	write(2, buffer, strlen(buffer));
	exit(1);
}

void surtxerror(char* s, int e){
	perror(s);
	exit(e);
}

int main(int argc, char *argv[]) {
  if(argc != 2) Usage();
  int fd = open("suma.txt", O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR);
  if(fd == -1) surtxerror("error en el open de suma.txt",1);
  int fd1 = open(argv[1], O_RDONLY);
  if(fd1 == -1) surtxerror("error en el open de argv[1]",1);
  int ret, suma, num;
  suma=0;
  while((ret=read(fd1,&num,sizeof(int)))>0){
    suma+=num;
  }
  if(ret == -1) surtxerror("error en el read de fd1",1);
  char buf[256];
  sprintf(buf,"%d\n",suma);
  write(1,buf,strlen(buf));
  write(fd,buf,strlen(buf));
  return 0;
}
