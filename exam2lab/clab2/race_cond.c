#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
char parent[] = "123456789";
char child[] = "ABCDEFGHIJ";
int pfd1[2];  //padre->hijo
int pfd2[2]; //hijo->padre

void Usage() {
	char buffer[256];
	sprintf(buffer, "Usage: race_cond num\n");
	write(1, buffer, strlen(buffer));
	exit(1);
}

void surtxerror(char* s, int e){
	perror(s);
	exit(e);
}

void TELL_WAIT() {
  pipe(pfd1);
  pipe(pfd2);
}
void TELL_PARENT() {
  write(pfd2[1],"c",1);
}
void TELL_CHILD() {
  write(pfd1[1],"p",1);
}
void WAIT_PARENT() {
  char c;
  read(pfd1[0],&c,1);
}
void WAIT_CHILD() {
  char c;
  read(pfd2[0],&c,1);
}
int main(int argc, char *argv[]) {
  if(argc != 2) {
		Usage();
	}
  int ordre = atoi(argv[1]);
  pid_t pid; int j;
  TELL_WAIT();
  if ((pid = fork())<0) {
    perror ("error->fork"); exit(1);
  }
  else if (pid==0) {
    close(pfd1[1]); close(pfd2[0]);
    WAIT_PARENT();
    for (j=0;j<strlen(child)-1;j++) {
      write(1,(child+j),1);
      if((j+1)%ordre==0) {
        TELL_PARENT();
        WAIT_PARENT();
      }
    }
  }
  else if (pid>0) {
    close(pfd1[0]); close(pfd2[1]);
    for (int j=0;j<strlen(parent);j++) {

      write(1,(parent+j),1);
      if((j+1)%ordre==0) {
        TELL_CHILD();
        WAIT_CHILD();
      }
    }
  }
}
