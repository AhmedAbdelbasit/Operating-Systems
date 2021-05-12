#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>


int min_val, max_val, avg_val;
int* data;
int count;

void* get_min(void* param);
void* get_max(void* param);
void* get_avg(void* param);

int main(int argc, char* argv[]){
	count = argc-1;
	if(count == 0){
		printf("You must enter some numbers\n\n");
		return 1;
	}
	data = (int *) malloc(count * sizeof(int));
	for(int i=0 ; i<count ; i++){
		data[i] = atoi(argv[i+1]);
	}
	
	pthread_t tid_min, tid_max, tid_avg;
	pthread_create(&tid_min, NULL, get_min, NULL);
	pthread_join(tid_min, NULL);
	
	pthread_create(&tid_max, NULL, get_max, NULL);
	pthread_join(tid_max, NULL);
	
	pthread_create(&tid_avg, NULL, get_avg, NULL);
	pthread_join(tid_avg, NULL);
	
	printf("The average value is %d\n", avg_val);
	printf("The minimum value is %d\n", min_val);
	printf("The maximum value is %d\n", max_val);

	free(data);
	return 0;
}

void* get_min(void* param){
	min_val = data[0];	
	for (int i=0 ; i<count ; i++){
		min_val = min_val > data[i] ? data[i] : min_val;
	}
	pthread_exit(NULL);
}

void* get_max(void* param){
	max_val = data[0];	
	for (int i=0 ; i<count ; i++){
		max_val = max_val < data[i] ? data[i] : max_val;
	}
	pthread_exit(NULL);
}

void* get_avg(void* param){
	for (int i=0 ; i<count ; i++){
		avg_val += data[i];
	}
	avg_val /= count;
	pthread_exit(NULL);
}


