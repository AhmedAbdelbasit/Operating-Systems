#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void* runner(void* param);
int value = 0;

int main(){
	pid_t pid;
	pthread_t tid;
	pthread_attr_t attr;

	pid = fork();
	if(pid ==0){
		fork();
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, runner, NULL);
		pthread_join(tid, NULL);
		printf("Child: value=%d\n", value);
	}else if(pid >0){
		wait(NULL);
		printf("Parent: value=%d\n", value);
	}
	return 0;
}

void* runner(void* param){
	value = 5;
	pthread_exit(0);
}
