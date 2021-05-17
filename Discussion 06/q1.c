#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>


#define SIZE 20

int top;
int stack[SIZE];

volatile int lock = 0;
volatile int available_lock = 0;

void push(int x);
int pop();
int is_empty();
void* produce(void*);
void* consume(void*);

void acquire(char c);
void release(char c);

int main(){
	
	stack[0] = 5;
	stack[1] = 6;
	top = 2;
	pthread_t tid_producer;
	pthread_t tid_consumer;

	pthread_create(&tid_producer, NULL, produce, NULL);
	pthread_create(&tid_consumer, NULL, consume, NULL);

	pthread_join(tid_producer, NULL);
	pthread_join(tid_consumer, NULL);
	
	for(int i=0 ; i<top ; i++){
		printf("%d - ", stack[i]);
	}
	printf("\n");
	return 0;
}


void acquire(char c){
	while(atomic_compare_exchange_strong(&lock, &available_lock, 1)){
		printf("waiting in %c\n", c);
	}
	printf("acquired for %c \n", c);
}

void release(char c){
	printf("released from %c \n", c);	
	lock = 0;	
}

void push(int x){
	//sleep(0.1);
	acquire('s');
	if(top < SIZE){
		stack[top] = x;
		sleep(0.01);
		top ++;
	}else{
		printf("Stack is Full\n");
	}
	release('s');
}

int pop(){
	sleep(0.1);
	int val = -1;
	acquire('p');
	if(! is_empty() ){
		top--;
		sleep(0.01);
		val = stack[top];
	}else{
		printf("Stack is empty\n");
	}
	release('p');
	return val;
}

int is_empty(){
	return top==0;
}

void* produce(void* param){
	push(8);
	pthread_exit(NULL);
}

void* consume(void* param){
	printf("value poped = %d\n", pop());
	pthread_exit(NULL);
}


