
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
	sprintf(buffer, "Usage: ./ej1 numero \n");
	write(2, buffer, strlen(buffer));
	exit(1);
}

void surtxerror(char* s, int e){
	perror(s);
	exit(e);
}

int main(int argc, char *argv[]) {
  if(argc!=2) Usage();
  int need = atoi(argv[1]);
  int *nums;

  char buffer[256];
  long int pr = (long int)sbrk(0); //llegim posicio del top del heap abans de reservar
  nums = malloc(need*sizeof(int));
  long int final = (long int)sbrk(0); //llegim posicio del top del heap despres de reservar
  for(int i = 0; i < need;++i){
    nums[i]=i;
  }
  free(nums);
  sprintf(buffer,"Malloc ha reservado %d Bytes\n", final-pr);
  write(1,buffer,strlen(buffer));
  while(1); //espera activa per poder mirar la carpeta /proc/[pid]/maps

}
