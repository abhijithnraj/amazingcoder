#include <iostream>
#define N 5
using namespace std;
int chopsticks[N];
class Philosopher{
    public:
        int i;
        int STATUS=0;
        int LEFT_CHOPSTICK=0;
        int RIGHT_CHOPSTICK=0;
        void set_id(int id){
            i = id;
        }
        void pickup(){
            int flag=0;
            if(LEFT_CHOPSTICK==0){
               if(chopsticks[i]==1){
                    cout<<"Cannot pickup Left  chopstick"<<endl;
                    flag=1;
               }
               else{
                    chopsticks[i]=1;
                    LEFT_CHOPSTICK=1;
                    cout<<"Picked up the Left chopstick"<<endl;

               }
            }

            else{
                cout<<"Philosopher already have left chopstick"<<endl;
            }
            if(RIGHT_CHOPSTICK==0){
               if(chopsticks[(i+1)%N]==1){
                    cout<<"Cannot pickup Right chopstick"<<endl;
                    flag=1;
               }

               else{
                    chopsticks[(i+1)%N]=1;
                    RIGHT_CHOPSTICK=1;
                    cout<<"Picked up the Right chopstick"<<endl;
               }
            }
            else{
                    cout<<"Philosopher already have the Right chopstick"<<endl;
            }
            if(flag==1){
                cout<<"Philosopher cannot eat as he doesn't have both chopsticks"<<endl;
                return;
            }
            STATUS=1;
    }
        void putdown(){
                if(LEFT_CHOPSTICK==1){
                    chopsticks[i]=0;
                    LEFT_CHOPSTICK=0;
                }
                else{
                    cout<<"Dont have left chopstick to putdown"<<endl;
                }
                if(RIGHT_CHOPSTICK==1){
                    chopsticks[(i+1)%N]=0;
                    RIGHT_CHOPSTICK=0;
                }
                else{
                    cout<<"Dont have Right chopstick to put down"<<endl;
                }
                STATUS=0;

        }
//        void show_status(){
//            cout<<"status of philosopher "<<i<<endl;
//            cout<<"THINKING "<<THINKING<<endl;
//            cout<<"EATING "<<EATING<<endl;
//        }
};
void menu(){
    string choice;
    string status="THINKING";
    int option,philosopher_id,p_option;
    Philosopher p[N];
    for(int i=0;i<N;i++){
        p[i].set_id(i);
    }

    do{
        //displaying the status of 5 philosophers
        cout<<"The status of all "<<N<<" Philosophers are"<<endl;
            for(int i=0;i<N;i++){
                if(p[i].STATUS==1){
                    status="EATING  ";
                }
                else{
                    status="THINKING";
                }
                cout<<"Philosopher: "<<i<<"    STATUS:"<<status<<"   LEFT_CHOPSTICK:"<<p[i].LEFT_CHOPSTICK<<"   RIGHT_CHOPSTICK:"<<p[i].RIGHT_CHOPSTICK<<endl;
            }

        cout<<"Enter which philospher you want to control: ";
        cin>>philosopher_id;
        if(philosopher_id<0 || philosopher_id>N-1){
            cout<<"WARNING: you have entered a philosopher who is not present at the table"<<endl;
            cout<<"Do you want do continue(y/n) :"<<endl;
            cin>>choice;
            //system("clear");
            continue;
        }
        cout<<"choices\n"<<"1.pick up 2.putdown"<<endl;
        cin>>p_option;
        if(p_option==1){
            p[philosopher_id].pickup();
        }
        if(p_option==2){
            p[philosopher_id].putdown();
        }
        if(option==-1){
            cout<<"THANK YOU FOR TRYING THIS SIMULATOR"<<endl;
            return;

        }


        cout<<"Do you want do continue(y/n) :"<<endl;
        cin>>choice;
        //system("clear");

    }while(choice=="y"|| choice=="Y");
    cout<<"THANK YOU FOR TRYING THIS SIMULATOR"<<endl;

}
int main(){
menu();

}
