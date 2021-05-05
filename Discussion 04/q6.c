#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void* runner(void* param);

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
	}
	fork();
	printf("Process -pid: %d -tid: %lu\n", getpid(), pthread_self());
	return 0;
}

void* runner(void* param){
	printf("Thread -pid: %d -tid: %lu\n", getpid(), pthread_self());
	pthread_exit(0);
}
