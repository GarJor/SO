#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void erroryexit(char* c, int er){
	perror(c);
	exit(er);
}

void mutagrep(char* klk){
	execlp("grep","grep", "-i",klk,NULL);
	erroryexit("Error al mutar a grep\n", 1);
}
void mutagrepEXT(char* klk){
	execlp("grep","grep","-A","1", "-i",klk,NULL);
	erroryexit("Error al mutar a grep\n", 1);
}

void Usage(){
	erroryexit("Usage: queFa <options> [tag/file/key]\n\n./queFa file		explains what the file does\n\n./queFa tag		will search for tag in all documentation in the folder, if you don't know which tag you should use you can use '-t' option:\n	-t		show all tags\n	-t key		search for key in all tags\n	-h		show Usage\n",1);
}

int main(int argc, char *argv[]){
	char buf[256];
	if(argc < 2) Usage();
	else if(argc == 2) {
		if(strcmp(argv[1],"-t")==0) {
			int tags = open(".tags.txt",O_RDONLY);
			int ret;
			sprintf(buf,"TAGS:\n\n");
			write(1,buf,strlen(buf));
			while((ret=read(tags,buf,256))>0){
				write(1,buf,ret);
			}
		}
		else if(strcmp(argv[1],"-h")==0) Usage();
		else{
			int fd = open(".quehace.txt",O_RDONLY);
			close(0);
			dup(fd);
			mutagrepEXT(argv[1]);
		}
	}
	else if(argc == 3 && strcmp(argv[1],"-t")==0) {
		int tag = open(".tags.txt",O_RDONLY);
		close(0);
		dup(tag);
		mutagrep(argv[2]);
	}
	else Usage();



}
