#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <sys/wait.h>

void Usage() {
	char buffer[256];
	sprintf(buffer, "Usage: tachaVocales file \n");
	write(2, buffer, strlen(buffer));
	exit(1);
}

void surtxerror(char* s, int e){
	perror(s);
	exit(e);
}

int main(int argc, char *argv[]) {
  if(argc != 2) Usage();
  int pid;
  char *voc[5] = {"a","e","i","o","u"};
  int fd[2];
  if(pipe(fd)==-1) surtxerror("Error al crear la pipe",1);;
  for(int i = 0; i < 5; ++i) {
  	pid = fork();
  	if (pid == 0) {
      dup2(fd[1],1);
      close(fd[0]); close(fd[1]);

      execlp("./buscaLetra","buscaLetra", voc[i] , argv[1], NULL);
  		surtxerror("Error al mutar 1",1);
  	}
  	else if (pid < 0) {
  		surtxerror("Error al fork",1);
  	}
  	else {
  		//PADRE
  		waitpid(-1,NULL,0);
  	}
  }
  dup2(fd[0],0);
  close(fd[0]); close(fd[1]);
  execlp("./tachaCaracteres","tachaCaracteres", argv[1], NULL);
  surtxerror("Error al mutar 2",1);

}
