#include <stdio.h>
#include <stdlib.h>


typedef struct{
	int index;
	float arrival_time;
	float starting_time;
	float burst_time;
	float termination_time;
	int priority_value;
}Process;


void print_table(Process *list, int length);
void schedule_FCFS(Process *list, int length);
void print_statistics(Process* queue, int length);


int main(int argc, char const *argv[])
{
	int count = 0;
	printf("# Num of Processes: ");
	scanf("%d", &count);
	
	printf("# Enter Arrival, Burst and Priority of each process: \n");
	Process *processes =malloc(count * sizeof(Process));
	float a, b;
	int p;
	for(int i=0 ; i<count ; i++){
		printf("\t>P%d: ", i);
		scanf("%f %f %d", &a,&b,&p);
		(processes+i)->index = i+1;
		(processes+i)->arrival_time = a;
		(processes+i)->burst_time = b;
		(processes+i)->priority_value = p;
		(processes+i)->starting_time = -1;
		(processes+i)->termination_time = -1;
	}

	print_table(processes, count);
	schedule_FCFS(processes, count);
	print_statistics(processes, count);

	free(processes);
	return 0;
}

void print_table(Process *list, int length){
	printf("-%-12s-%-12s-%-12s-%-12s%c\n", "------------", "------------", "------------", "------------",191);
	printf("|%-12s|%-12s|%-12s|%-12s|\n", "Process", "Arrival", "Burst", "Priority");
	printf("|%-12s-%-12s-%-12s-%-12s|\n", "------------", "------------", "------------", "------------");
	for(int i=0 ; i<length ; i++){
		printf("|P%-11d|%-12.2f|%-12.2f|%-12d|\n", i+1, list[i].arrival_time, list[i].burst_time, list[i].priority_value);
	}
	printf("-%-12s-%-12s-%-12s-%-12s-\n", "------------", "------------", "------------", "------------");
	printf("\n");
}

void schedule_FCFS(Process *list, int length){
	float timer=0;
	printf("%-12s:\n\t>> ", "FCFS chart");
	
	Process* queue[length];
	for(int i=0 ; i<length ; i++){
		queue[i] = list+i;
	}

	Process *temp;
	for(int i=0 ; i<length-1 ; i++){
		for(int j=i+1 ; j<length ; j++){
			if(queue[i]->arrival_time > queue[j]->arrival_time){
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}
		}
	}

	for(int i=0 ; i<length ; i++){
		for(int n=0 ; n<queue[i]->burst_time ; n++){
			printf("%d",queue[i]->index);
		}
		queue[i]->starting_time = timer;
		timer+=queue[i]->burst_time;
		queue[i]->termination_time = timer;
	}
	printf("\n");

	
}

void print_statistics(Process* queue, int length){
	printf("%-8s%-12s%-12s%-12s%-12s%-12s%-12s\n","--------","------------","------------","------------","------------","------------","------------");
	printf("%8s%-12s%-12s%-12s%-12s%-12s%-12s\n","","Arrival","Burst","Response","Termination","Turnaround","Waiting");
	printf("%-8s%-12s%-12s%-12s%-12s%-12s%-12s\n","--------","------------","------------","------------","------------","------------","------------");
	float arrive, burst, response, terminate,turnaround,waiting;
	float t_response=0, t_turnaround=0, t_waiting=0;
	for(int i=0 ; i<length ; i++){
		arrive = queue[i].arrival_time;
		burst = queue[i].burst_time;
		response = queue[i].starting_time - arrive;
		terminate = queue[i].termination_time;
		turnaround = terminate - arrive;
		waiting = turnaround - burst;
		t_response += response;
		t_turnaround += turnaround;
		t_waiting += waiting;

		printf("P%-7d%-12.2f%-12.2f%-12.2f%-12.2f%-12.2f%-12.2f\n",i+1,arrive,burst,response,terminate,turnaround,waiting);
	}
	printf("%-8s%-12s%-12s%-12s%-12s%-12s%-12s\n","--------","------------","------------","------------","------------","------------","------------");
	printf("%-8s%-12s%-12s%-12.2f%-12s%-12.2f%-12.2f\n","Average","","",t_response/length,"",t_turnaround/length,t_waiting/length);
	printf("%-8s%-12s%-12s%-12s%-12s%-12s%-12s\n","--------","------------","------------","------------","------------","------------","------------");

}