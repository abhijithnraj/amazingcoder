#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;


class process{
	public:
		int burst_time;
		int priority;
		void get_data(){
			cout<<"Enter the burst time: ";
            cin>>burst_time;
			cout<<"Enter the priority: ";
			cin>>priority;
		}
		void display_data(){
		     cout<<"Burst time: "<<burst_time<<endl;
		     cout<<"Priority: "<<priority<<endl;
		}
};
void round_robin(process*,int,int);
void swap(process *p1, process *p2){
        process temp=*p1;
        *p1=*p2;
        *p2=temp;
}
int total_burst_time(process *p,int n){
	int tbt=0;
	for(int i=0;i<n;i++){
		tbt+=(p+i)->burst_time;
	}
	return tbt;
}
void fcfs(process *p,int n){
	int time=0;
	int tbt=total_burst_time(p,n);
	int i=0;
	do{
		cout<<"The waiting time of process"<<i+1<<": "<<time<<endl;
		time+=p[i].burst_time;
		cout<<"The turnaround time of process"<<i+1<<": "<<time<<endl;
		i++;
	}while(time!=tbt);
}
process *bubble_sort(process *p,int n,int compare_variable){ //0 for burst_time and 1 for priority
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(compare_variable==0){
				if(p[i].burst_time <= p[j].burst_time){
					swap(p+i,p+j);
				}
			}
			else if(compare_variable==1){
				if(p[i].priority<=p[j].priority){
					swap(p+i,p+j);
				}
			}
		}
	}
	return p;
}

void round_robin(process *p,int n,int quantum){
	int remaining_bt[n];
	int waiting_time[n];
	for(int i=0;i<n;i++){
		remaining_bt[i]=p[i].burst_time;
	}
	int t=0;
	while(1){
		int completed=1;
		for(int i=0;i<n;i++){
			if(remaining_bt[i]>0){
				completed=0;
				if(remaining_bt[i]>quantum){
					t+=quantum;
					remaining_bt[i]-=quantum;
				}
				else{
					t=t+remaining_bt[i];
					waiting_time[i]=t-p[i].burst_time;
					remaining_bt[i]=0;
				}
			}

			}
		if(completed==1){
				break;
		}
	}
	int turnaround_time[n];
	for(int i=0;i<n;i++){
		turnaround_time[i]=p[i].burst_time+waiting_time[i];
	}
	cout<<"\n";
	for(int i=0;i<n;i++){
		cout<<"waiting time of process p"<<i<<" is "<<waiting_time[i]<<endl;
		cout<<"Turnaround time of process p"<<i<<" is "<<turnaround_time[i]<<endl;
	}
}
void menu(process *p,int n){
	int option;
	cout<<"What scheduling algorithm you want to simluate"<<endl;
	cout<<"1.FCFS 2.SJF 3.Priority 4.Round Robin\n";
	cin>>option;
	switch(option){
		case 1:
				cout<<"\nThe FCFS sheduling\n"<<endl;
        		fcfs(p,n);
				break;
		case 2:
				cout<<"\nThe shortjest job first scheduling\n"<<endl;
		   		process *p2;
        		p2=bubble_sort(p,n,0);
       			fcfs(p2,n);
				break;
		case 3:
        		cout<<"\nFor priority scheduling\n"<<endl;
        		process *p3;
       			p3=bubble_sort(p,n,1);
        		fcfs(p3,n);
				break;
		case 4:
				cout<<"\n For round robin scheduling\n"<<endl;
				int tq;
				cout<<"Enter the time quantum"<<endl;
				cin>>tq;
				round_robin(p,n,tq);
				break;
		default:
				system("clear");
				cout<<"Not a valid option";
	}

}
int main(){
	int n;
	process p[10];
	char choice[10];
	cout<<"Enter the no of process";
	cin>>n;
	//to read the data
	for(int i=0;i<n;i++){
		cout<<"For process: "<<i+1<<endl;
		(p+i)->get_data();
	}
	//to display the data
	for(int i=0;i<n;i++){
		(p+i)->display_data();
	}
	do{
		system("clear");
		menu(p,n);
		cout<<"Do you want to continue: ";
		cin>>choice;
		cout<<"Entered choice is"<<choice<<endl;
	}while(!strcmp(choice,"yes"));

}
