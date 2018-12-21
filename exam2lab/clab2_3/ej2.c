
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <signal.h>

void Usage() {
	char buffer[256];
	sprintf(buffer, "Usage: ./ej1 numero f1 \n");
	write(2, buffer, strlen(buffer));
	exit(1);
}

void surtxerror(char* s, int e){
	perror(s);
	exit(e);
}
void trat(int s) {

}

int main(int argc, char *argv[]) {
  if(argc!=3) Usage();
  int need = atoi(argv[1]);
  int *nums;
  char buffer[256];
  long int pr = (long int)sbrk(0); //llegim posicio del top del heap abans de reservar
  nums = malloc(need*sizeof(int));
  long int final = (long int)sbrk(0); //llegim posicio del top del heap despres de reservar
  for(int i = 0; i < need;++i){
    nums[i]=i;
  }
	int n;
	int fd = open(argv[2],O_CREAT|O_TRUNC|O_RDWR, 0644); //pueden compartir el open puesto que el padre siempre dejara el puntero al inicio del fitxero
	int pid = fork();
	if(pid==0){
		sigset_t mask;
		struct sigaction sa;
		//bloqueig de signals
		sigemptyset(&mask);
		sigaddset(&mask, SIGUSR1);
		sigprocmask(SIG_BLOCK, &mask, NULL);
		//reprogamacio del signal
		sa.sa_handler=trat;
		sa.sa_flags=SA_RESTART; //evitem interrupcions per si revem la senyal mentre estem executant una syscall
		sigaction(SIGUSR1,&sa,NULL);
		sprintf(buffer,"HIJO: el pare esta escribint...\n");
		write(1,buffer,strlen(buffer));
		sprintf(buffer,"HIJO: Ja ha acabat\n");
		write(1,buffer,strlen(buffer));
		//preparem la mascara per a la espera bloquejant sigsuspent, on nomes acceptara els dos signals que ens interessi
		sigfillset(&mask);
		sigdelset(&mask, SIGUSR1);
		sigsuspend(&mask);
		for(int i = 0; i < need; ++i){
				read(fd,&n,sizeof(int));
				sprintf(buffer,"%d\n",n);
				write(1,buffer,strlen(buffer));
		}

	}
	else if(pid > 0) {
		for(int i = 0; i < need; ++i){
			int ret;
			if(i==0) write(fd,&nums[0],sizeof(int));
			for(int j = i; j>=0 && i!=0;--j){
				write(fd,&nums[j],sizeof(int));
			}

				lseek(fd,0,SEEK_SET);

		}
		free(nums);
		sprintf(buffer,"Malloc ha reservado %d Bytes\n", final-pr);
		write(1,buffer,strlen(buffer));
		kill(pid,SIGUSR1);
	}
while(1); //espera activa per poder mirar la carpeta /proc/[pid]/maps



}
