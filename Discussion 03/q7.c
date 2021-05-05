#include <stdio.h>
#include <unistd.h>

int main(){
	for(int i=0 ; i<4 ; i++){
		fork();
	}
	printf("%d\n", getpid());
	return 0;
}
