#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid, pid1;
	pid = fork();
	if(pid < 0){
		printf("Fork error");
		return 1;
	}else if(pid == 0){
		pid1 = getpid();
		printf("Child: pid = %d\n", pid);
		printf("Child: pid1 = %d\n", pid1);
	}else{
		pid1 = getpid();
		wait(NULL);
		printf("Parent: pid = %d\n", pid);
		printf("Parent: pid1 = %d\n", pid1);
		
	}
	return 0;
}
