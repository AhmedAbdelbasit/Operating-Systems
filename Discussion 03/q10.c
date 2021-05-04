#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE 5
int num[SIZE] = {0, 1, 2, 3, 4};

int main(){
	int i;
	pid_t pid;
	pid = fork();
	if(pid == 0){
		for(i=0 ; i<SIZE ; i++){
			num[i] *= -i;
			printf("CHILD: %d\n", num[i]);
		}
	}else if(pid > 0){
		wait(NULL);
		for(i=0 ; i<SIZE ; i++){
			printf("PARENT: %d\n", num[i]);
		}
	}
	return 0;
}
