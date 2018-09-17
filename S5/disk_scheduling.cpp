#include<iostream>
#include<vector>
#include<bits/stdc++.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;

void FCFS(vector<int> locations){
  cout<<"FCFS"<<endl;
  vector<int> seek_order;
  seek_order=locations;
  for(int i=0;i<seek_order.size()-1;i++){
   cout<<seek_order[i]<<" -> ";
 }
 cout<<seek_order[seek_order.size()-1];
}

void SCAN(vector<int> locations,int starting_location,int direction,int limit){

  int current_location=starting_location;
  locations.insert(locations.begin(),0);
  locations.insert(locations.end(),limit);
  sort(locations.begin(),locations.end());
  int index_starting_location;
  for(int i=0;i<locations.size();i++){
    if(locations.at(i)==starting_location){
      index_starting_location=i;
      break;
    }
  }
  vector<int> seek_order;
  if(direction==0){
     int i=index_starting_location;
    while(1){
      seek_order.push_back(locations[i]);
      locations.erase(locations.begin()+i);
      i--;
      if(locations[i]==0){
        seek_order.push_back(0);
        locations.erase(locations.begin()+i);
        break;
      }
    }
    while(1){
      i++;
      seek_order.push_back(locations[i]);
      // locations.erase(locations.begin()+i);
      if(locations[i]==limit){
        // seek_order.push_back(limit);
        // locations.erase(locations.begin()+i);
        break;
      }
    }
  }
  else if(direction==1){
     int i=index_starting_location;
     while(1){
      seek_order.push_back(locations[i]);
      locations.erase(locations.begin()+i);
      i++;
      if(locations[i]==limit){
        break;
      }
    }
    while(1){
      i--;
      seek_order.push_back(locations[i]);
      locations.erase(locations.begin()+i);
      if(locations[i]==0){
        break;
      }
    }
  }
   cout<<"\n\nSCAN :"<<endl;
   for(int i=0;i<seek_order.size()-1;i++){
    cout<<seek_order[i]<<" -> ";
  }
  cout<<seek_order[seek_order.size()-1];
}
void CSCAN(vector<int> locations,int starting_location,int direction,int limit){
  int current_location=starting_location;
  int iterator=-1;
  locations.insert(locations.begin(),0);
  locations.insert(locations.end(),limit);
  sort(locations.begin(),locations.end());
  int index_starting_location;
  for(int i=0;i<locations.size();i++){
    if(locations.at(i)==starting_location){
      index_starting_location=i;
      break;
    }
  }
  vector<int> seek_order;
  int first_time=1;
  if(direction==0){
     int i=index_starting_location;
    while(1){
      seek_order.push_back(locations[i]);
      i--;
      if(locations[i]==0){
        i=locations.size();
      }
      if(i==index_starting_location){
        break;
      }
    }
  }
  else if(direction==1){
     int i=index_starting_location;
       while(1){
         seek_order.push_back(locations[i]);
         i++;
           if(locations[i]==limit){
             seek_order.push_back(locations[i]);
             i=0;
           }
           if(i==index_starting_location){
             break;
         }
     }
  }
   cout<<"\n\nCSCAN :"<<endl;
   for(int i=0;i<seek_order.size()-1;i++){
    cout<<seek_order[i]<<" -> ";
  }
  cout<<seek_order[seek_order.size()-1];
}


vector<int> get_locations(vector<int> locations,int starting_location){
  locations.push_back(starting_location);
  cout<<"Enter the locations\nEnter -1 to quit\n";
  int loc;
  while(1){
    cout<<"Enter the location: ";
    cin>>loc;
    if(loc==-1){
      break;
    }
    locations.push_back(loc);
  }
  return locations;
}
void menu(vector<int> loc,int starting_location,int end_limit){
  int choice,ch;
  int direction;
  while(1){
    cout<<"Enter what algorithm you want to simulate"<<endl;
    cout<<"\t1.FCFS\n\t2.SCAN\n\t3.CSCAN"<<endl;
    cin>>choice;
    switch(choice){
      case 1:
          FCFS(loc);
          break;
      case 2:
          cout<<"Enter the direction towards beginning(0)/towards end(1)"<<endl;
          cin>>direction;
          cout<<direction;
          if(direction==0 || direction==1){
            SCAN(loc,starting_location,direction,end_limit);
          }
          else{
            cout<<"Invalid direction given\n";
            return;
          }
          break;
      case 3:
          cout<<"Enter the direction towards beginning(0)/towards end(1)"<<endl;
          cin>>direction;
          cout<<direction;
          if(direction==0 || direction==1){
            CSCAN(loc,starting_location,direction,end_limit);
          }
          else{
            cout<<"Invalid direction given\n";
            return;
          }


          break;
      default:
          cout<<"Unknown Choice"<<endl;
          break;
    }
    cout<<"\nDo you want to try another algorithm yes(1)/no(0)"<<endl;
    cin>>ch;
    if(ch==0){
      cout<<"\nProgram ended"<<endl;
      cout<<"Thank you for using this program"<<endl;
      break;
    }
  }

}
int main(){
  int end_limit,starting_location;
  cout<<"Enter the starting location of the disk head"<<endl;
  cin>>starting_location;
  cout<<"Enter the end_limit of the disk"<<endl;
  cin>>end_limit;
  vector< int> loc;
  loc=get_locations(loc,starting_location);
  //loc={starting_location,95,180,34,119,11,123,62,64};
  menu(loc,starting_location,end_limit);
  return 0;
}
