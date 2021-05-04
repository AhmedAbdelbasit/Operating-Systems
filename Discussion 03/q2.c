#include <stdio.h>
#include <unistd.h>

int value = 5;

int main(){
	fork();
	fork();
	fork();
	printf("C");
	return 0;
}
