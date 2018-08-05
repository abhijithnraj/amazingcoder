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
				system("CLS"); 
				cout<<"Not a valid option";
	}

}
void round_robin(process *p,int n,int quantum){
	int t=0;
	int waiting_time=0;
	int turnaround_time=0;
	int pid=0;
	int tbt=total_burst_time(p,n);
	int temp_burst_time=0;
	for(int i=0;i<n;i++){	
		t=0;
		pid=0;
		temp_burst_time=p[i].burst_time;
		waiting_time=0;
		turnaround_time=0;
		do{
			if(p[pid].burst_time<=quantum){
				t+=p[pid].burst_time;
				
			}	
			else
				t+=quantum;
			
			if(pid==i){//the turn of our process
			//	cout<<"Executing process p"<<i+1<<endl;
				if(temp_burst_time>=quantum){
					temp_burst_time-=quantum;
			//		cout<<"temp burst time"<<temp_burst_time<<endl;
				}
				else{ //end of process execution
			//			cout<<"End of process"<<i+1<<": waiting time= "<<waiting_time<<endl;
						turnaround_time=t;
						break;
				}
			}
			else{// all process other than the current process
			//	cout<<"Executing process p"<<pid<<endl;
				if(temp_burst_time<=quantum){
					waiting_time+=p[pid].burst_time;
				}
				else
					waiting_time+=quantum;
			//	cout<<"waiting_time"<<waiting_time<<endl;
			}

			pid=(pid+1)%n; 
			
		}while(t<=p[i].burst_time);
	//	cout<<"going for next cycle time="<<t<<endl;
	cout<<"The waiting time of process "<<i+1<<" is : "<<waiting_time<<endl;
	cout<<"The turnaroud time of the process"<<i+1<<"is :"<<turnaround_time<<endl;
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
		menu(p,n);
		cout<<"Do you want to continue: ";
		cin>>choice;
		cout<<"Entered choice is"<<choice<<endl;
	}while(!strcmp(choice,"yes"));

}
