# SO

Per obtenir informacio del contingut de exam2lab/ podeu utilitzeu el programa queFa:

### EXEMPLES D'US:

**Linux**:~/Escritorio/SO/exam2lab$    ./queFa -h
```sh
Usage: queFa <options> [tag/file/key]

./queFa file		explains what the file does

./queFa tag		will search for tag in all documentation in the folder, if you don't know which tag you should use you can use '-t' option:
	-t		show all tags
	-t key		search for key in all tags
	-h		show Usage
```
**Linux**:~/Escritorio/SO/exam2lab$    ./queFa set_holes.c
```sh
_____ /clab2/set_holes.c:   Programa que recibe como primer parametro un fitxero con posiciones (enteros) y como segundo un fitxero de texto con enteros,
escribe 0 en el segundo fitxero en las posiciones leidas en el primero (TAGS: open-O_RDONLY-O_WRONLY, lseek, write, entero-representacion-interna)

```
**Linux**:~/Escritorio/SO/exam2lab$    ./queFa teoria
```sh
_____ /clab2_1/respuestas.txt:    Teoria    (TAGS: mknod, pipe, pipe_con_nombre, comunicacion_con_pipe)
_____ /clab2/answers.txt:   Teoria    (TAGS: inodo-libre, inodo-directorio, enlaces_a_inodo, lista_llamadas_a_sistema, syscalls, strace, df, numero_llamadas_sistema)
_____ /clab2_2/respuestas.txt:    Teoria    (TAGS: softlink, hardlink, inodo, sbrk, memoria, heap)
_____ /MrRobb/resumE-S_MrRobb.txt: Teoria resumida entrades i sortides del github de MrRobb
_____ /MrRobb/resumE-S_MrRobb.pdf: Teoria resumida entrades i sortides del github de MrRobb
```
#### Buscar per tags:
###### Exemple:

**Linux**:~/Escritorio/SO/exam2lab$    ./queFa pipe_sin_nombre
```sh
_____ /clab2_1/tachaVocales.c:    Programa que busca, mutando a buscaLetra, todas las vocales minusculas del fitxero que recibe por parametro y las tacha, mutando tachaCaracteres. La comunicacion necesaria se hace con pipes sin nombre enre procesos. (TAGS: pipe, close, dup2, fork, waitpid, execlp, pipe_sin_nombre, comunicacion_con_pipe)
_____ /clab2/race_cond.c:   Programa que recibe un entero por parametro, que servira para simcronizar los writes/read del padre y el hijo utilizando los bloqueos de write/read cuando se usa pipe sin nombre   (TAGS: pipe_sin_nombre, comunicacion_con_pipe, write, read, sincronizar, sync)
_____ /clab2_2/cuenta_lineas.c:   Programa que emula el comando: cat <parametro1> | grep <parametro2> | wc -l Para ello utiliza comunicacion entre procesos padre-hijo con pipes sin nombres.   (TAGS: sync, sincronizar, comunicacion_con_pipe, pipe_sin_nombre, fork, execlp, dup2, close)
```


**Linux**:~/Escritorio/SO/exam2lab$    ./queFa -t
```sh
TAGS:

char
close
comunicacion_con_pipe
control_errors
df
dup2
enlaces_a_inodo
entero-representacion-interna
execlp
exemple
fork
fork-concurrente
fork-sequencial
handlers
heap
inodo
inodo-directorio
inodo-libre
lista_llamadas_a_sistema
lseek
lseek-O_WRONLY
lseek-SEEK_END
lseek-SEEK_SET
lseek-SEEK_CUR
memoria
mknod
numero_llamadas_sistema
open-O_CREAT-O_TRUNC
open-O_RDONLY-O_WRONLY
permisos
pipe
pipe_con_nombre
pipe_sin_nombre
read
sbrk
sigaction
signals
sigprocmask
sincronizar
softlink
strace
strcmp
sync
syscalls
waitpid
write
```

**Linux**:~/Escritorio/SO/exam2lab$    ./queFa -t pipe
```sh
comunicacion_con_pipe
pipe
pipe_con_nombre
pipe_sin_nombre

```
