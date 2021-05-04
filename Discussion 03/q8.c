#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		printf("Fork error");
		return 1;
	}else if(pid == 0){
		execlp("/bin/ls", "ls", NULL);
		printf("LineJ\n");
	}else{
		wait(NULL);
		printf("Child Complete\n");
	}
	return 0;
}
