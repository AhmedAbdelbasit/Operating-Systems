#include <stdio.h>
#include <unistd.h>

int value = 5;

int main(){
	fork();
	if(fork() && fork()){
		fork();
	}
	printf("%d\n", getpid());
	return 0;
}


/*
Other examples:

fork();
if(fork()){
	fork();
}

fork();
if(fork() && fork()){
	fork();
}

*/

