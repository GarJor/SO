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
	sprintf(buffer, "Usage: ./ordenar fitxero_a_ordenar  \n");
	write(2, buffer, strlen(buffer));
	exit(1);
}

void surtxerror(char* s, int e){
	perror(s);
	exit(e);
}

int main(int argc, char *argv[]) {
  if (argc!=2) Usage();
  int fd = open(argv[1],O_RDWR);
  if (fd==-1) surtxerror("Error al open",1);
  int max = lseek(fd,0,SEEK_END);
  if(max == -1) surtxerror("Error al lseek",1);

  int next = 1;
  char c[256];

 while(next){ //while per repetir si hi ha hagut algun canvi en la sequencia anterior
    next = 0;
    int go = lseek(fd,0,SEEK_SET);
    while(go<(max-1)) { // mentre no siguis a lultim byte del fitxer --> llegeix els dos seguents bytes i fes el k has de fer
      int val;
      for(int i = 0; i<2; ++i){
        if(i==0){
          read(fd,c,1); //read a;
          val = atoi(c);
        }
        else{
          read(fd,c,1); //read b;
          if(val>atoi(c)){
            next=1; //hi ha canvi
            go=lseek(fd,-2,SEEK_CUR);
            write(fd,c,1); //print b
            sprintf(c,"%d",val);
            write(fd,c,1); //print a
          }
          go = lseek(fd,-1,SEEK_CUR);
        }


      }
   }
 }

}
