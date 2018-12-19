#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>

void erroryexit(char* c, int er){
	perror(c);
	exit(er);
}

void mutacat(char* klk){
	execlp("cat","cat",klk, NULL);
	erroryexit("Error al mutar a cat\n",1);
}
void mutagrep(char* klk){
	execlp("grep","grep",klk,NULL);
	erroryexit("Error al mutar a grep\n", 1);
}

void mutawc(){
	execlp("wc","wc","-l",NULL);
	erroryexit("Error al mutar a wc\n", 1);
}
void Usage(){
	erroryexit("Uso: ./cuenta_lineas file pattern\n",1);
}

int main(int argc, char *argv[]){
	if(argc != 3) Usage();
	char buf[256];

  //creem una primera pipe per que el grep es comuniqui amb el wc (fent que aquest ultim hagi desperar lescriptura del grep)
  int fd_grep[2]; //0 -> read; 1 -> write;
  if(pipe(fd_grep) == -1) erroryexit("Error en la creacion de PIPE del grep\n",2);
	int pidcat= fork();
	if(pidcat== 0){ //hijo

    close(fd_grep[0]); //no lutilitza cap dels fills, nomes el pare quan muti a wc

    //una altre pipe per que el cat es comuniqui amb el grep (fent que aquest ultim hagi desperar lescriptura del cat)
    int fd_cat[2];
    if(pipe(fd_cat) == -1) erroryexit("Error en la creacion de PIPE del cat\n",2);

    int pidgrep = fork();
    if(pidgrep == 0){
      //GREP
      close(fd_cat[1]);
      dup2(fd_cat[0],0);//sobrescric el default del read del grep, que es el 0
      dup2(fd_grep[1],1);//sobrescric el default del write del grep, que es el 1
      close(fd_grep[1]); close(fd_cat[0]);
		  mutagrep(argv[2]);
    }
    else {
      if(pidgrep==-1) surtxerror("Error de fork",1)
      //CAT
      close(fd_cat[0]); close(fd_grep[1]);
  		dup2(fd_cat[1],1);//sobrescric el default del write del cat, que es el 1
  		close(fd_cat[1]);
  		mutacat(argv[1]);
    }

	}
	else { //padre
    if(pidcat==-1) surtxerror("Error de fork",1)
    //WC
    dup2(fd_grep[0],0); // sobrescric el default del read del wc k es el 0
    close(fd_grep[0]); close(fd_grep[1]); //tanquem les entrades del file descriptor que no farem servir, per tal devitar bloquejos no desitjats en el write/read
    mutawc();
	}

}
