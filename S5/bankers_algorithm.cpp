#include <iostream>
using namespace std;


void get_max(int max[][10],int np,int nr){
  for(int i=0;i<np;i++){
    for(int j=0;j<nr;j++){
        cout<<"Enter the no of Resources "<<j+1<<" maximum wanted by process "<<i+1<<": "<<endl;
        cin>>max[i][j];
    }

  }
}


void allocate(int allocated[][10],int np,int nr ){
  for(int i=0;i<np;i++){
    for(int j=0;j<nr;j++){
      cout<<"Enter the no of Resources "<<j+1<<" allocated for "<<"process "<<i+1<<": ";
      cin>>allocated[i][j];
    }
  }
}
void find_need(int max[][10],int allocated[][10],int need[][10],int np,int nr){
  for(int i=0;i<np;i++){
    for(int j=0;j<nr;j++){
      need[i][j]=max[i][j]-allocated[i][j];
    }
  }
}

void get_available_resources(int available[],int nr){
  for(int i=0;i<nr;i++){
    cout<<"Enter the no of resources available at max for Resource "<<i+1<<": ";
    cin>>available[i];
  }
}


int safety_algorithm( int finished[10],int max[10][10],int available[10],int allocated[10][10],int need[10][10],int np,int nr){
  int order[np];
  int work[10];
  for(int j=0;j<nr;j++){
    work[j]=available[j];
  }

  for (int i = 0; i < np; i++) {
    finished[i]=0;
  }

  int end=0,count=0,order_count=0;
  int previous_loop_count=0,current_loop_count=1;
  while(end!=1){
    count=0;
    for(int i=0;i<np;i++){
      int need_lessthan_work=1;
      for(int j=0;j<nr;j++){
        if(need[i][j]>work[j]){
          need_lessthan_work=0;
        }
      }
      if(finished[i]==0 && need_lessthan_work==1){
        finished[i]=1;
        for(int j=0;j<nr;j++){
          work[j]=work[j]+allocated[i][j];
        }
          count++;
        order[order_count]=i;
        order_count++;
      }
    }
    current_loop_count=count;
    if(previous_loop_count==current_loop_count){
      end=1;
    }
    previous_loop_count=count;
  }
  for(int i=0;i<np;i++){
    if(finished[i]!=1){
      cout<<"Safe state doesnt exist"<<endl;
      return 0;
    }
  }
  cout<<"safe state exists"<<endl;
  cout<<"The order of the resource allocation in the process for safe state is "<<endl;
  for(int i=0;i<np;i++){
    cout<<"process "<<order[i]<<endl;
  }
  return 1;

}
int request_algorithm( int finished[10],int max[10][10],int available[10],int allocated[10][10],int need[10][10],int np,int nr,int request[10],int process_no){
  for(int i=0;i<nr;i++){
    if(request[i]>available[i]){
      cout<<"The process requested more than avaiable resouces"<<endl;
      return -1;
    }
    if(request[i]>need[process_no][i]){
      cout<<"The process requested for more than needed amount of resources"<<endl;
      return -1;
    }
  }
  for(int i=0;i<nr;i++){
    available[i]-=request[i];
    allocated[process_no][i]+=request[i];
    need[process_no][i]-=request[i];
  }
  find_need(max,allocated,need,np,nr);
  return safety_algorithm(finished,max,available,allocated,need,np,nr);


}


int main(){
  int finished[10], max[10][10],available[10],allocated[10][10],need[10][10],np,nr;
  std::cout <<"Enter the no of processes"<<endl;
  std::cin>>np;
  std::cout << "Enter the no of Resources" << '\n';
  std::cin >> nr;
  int proc_no;
  int choice;
  get_available_resources(available,nr);
  get_max(max,np,nr);
  allocate(allocated,np,nr);
  find_need(max,allocated,need,np,nr);
  safety_algorithm(finished,max,available,allocated,need,np,nr);
  cout<<"Do you want to check for a request yes(1) or no(0)"<<endl;
  cin>>choice;
    if(choice==1){
        int request[10];
        cout<<"Enter which process out of";
        for(int i=0;i<nr;i++){
          cout<<i<<" ";
        }
        cout<<"is requesting for the resource"<<endl;
        cin>>proc_no;
        cout<<"Enter the resouces requested by process "<<proc_no<<endl;
        for(int i=0;i<nr;i++){
          cin>>request[i];
        }
        if(request_algorithm(finished,max,available,allocated,need,np,nr,request,proc_no)==1){
          cout<<"The request can be granted"<<endl;
        }
        else{
          cout<<"Request cannot be granted";
        }
    }
    else{
      cout<<"End of program"<<endl;
      cout<<"Thank you for using this program"<<endl;
      }
    return 0;
}
