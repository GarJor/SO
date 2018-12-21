#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void trat(int s) {
	if(s == SIGINT){
		char buf[256];
		sprintf(buf, "\nSIGINT RECIBIDO\n");
		write(1, &buf, strlen(buf));
	}
}

int main(){
	char c;
	int ret;
	sigset_t mask;
	struct sigaction sa;
	sa.sa_handler=trat;
	sa.sa_flags=SA_RESTART; //si actibamos este flag SA_RESTART el programa no terminara despues del SIGINT ya que se volvera a llamar al read
	sigaction(SIGINT, &sa, NULL);
	ret = read(0, &c, sizeof(char));
	char buffer[256];
	if(ret > 0) {
		sprintf(buffer, "\nleido correctamente\n");

		write(1, &c, sizeof(char));
	}
	else{
		if(errno == EINTR){
			sprintf(buffer, "Interrumpido por signal\n");
		}
		else{
			sprintf(buffer, "\nerror random\n");
		}
	}
	write(1, &buffer, strlen(buffer));

}
