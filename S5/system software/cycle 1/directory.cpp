/*
 * directory.cpp
 *
 *  Created on: 05-09-2018
 *      Author:Abhijith N Raj
 */


#include<iostream>
#include<vector>
using namespace std;


int count=0; //Gives id to each and every file

/* Each node can be a file or a directory
 * which is determined by the type
 * if type is f, means file
 * if type is d, means directory
 * name contains the name of a file or directory
 * in is only used if there is directory
 */
struct node{
	char type;
	int id;
	string name;
	vector<node> *in;
};

/* To create a file,
 * id need to be assigned
 * name can be given as an argument,
 * returns a file ( node )
 */
node createFile(string name){
	node n ;
	//n.in=new vector<node>;
	n.id=count;
	count++;
	n.type='f';
	n.name=name;
	return n;
}

/* To create a directory,
 * id need to be assigned
 * name can be given as an argument,
 * returns a directory ( node )
 */
node createDirectory(string name){
	node n ;
	n.in=new vector<node>;
	n.id=count;
	count++;
	n.type='d';
	n.name=name;
	return n;
}

/* Creates a single level directory
 * populates it
 * returns a directory ( node )
 */
node singleLevel(){
	node masterDir=createDirectory("root");
	cout<<"Created master directory "<<count<<endl;
	cout<<"Enter number of files to create:";
	int temp;
	cin>>temp;
	for(int i=0;i<temp;i++){
		cout<<"Enter  name of a the file:";
		string name;
		cin>>name;
		bool detect=false;
		for(int j=0;j<masterDir.in->size();j++){
			if(masterDir.in->at(j).name==name){
				cout<<"Error adding file, name conflict"<<endl;
				i--;
				detect=true;
			}
		}
		if(!detect){
			masterDir.in->push_back(createFile(name));
		}
	}
	return masterDir;
}
node singleLevel(string rootName){
	node masterDir=createDirectory(rootName);
	cout<<"Created master directory "<<count<<endl;
	cout<<"Enter number of files to create:";
	int temp;
	cin>>temp;
	for(int i=0;i<temp;i++){
		cout<<"Enter  name of a the file:";
		string name;
		cin>>name;
		bool detect=false;
		for(int j=0;j<masterDir.in->size();j++){
			if(masterDir.in->at(j).name==name){
				cout<<"Error adding file, name conflict"<<endl;
				i--;
				detect=true;
			}
		}
		if(!detect){
			masterDir.in->push_back(createFile(name));
		}
	}
	return masterDir;
}
node multiLevel(){
	node masterDir=createDirectory("root");
	cout<<"Enter number of directories:";
	int temp;
	cin>>temp;
	bool detect=false;
	for(int i=0;i<temp;i++){
		cout<<"Enter  name of a the directory:";
		string name;
		cin>>name;
		bool detect=false;
		for(int j=0;j<masterDir.in->size();j++){
			if(masterDir.in->at(j).name==name){
				cout<<"Error adding directory, name conflict"<<endl;
				i--;
				detect=true;
			}
		}
		if(!detect){
			masterDir.in->push_back(singleLevel(name));
		}
	}
	return masterDir;
}
node insertDir(node masterDir,string name){
	bool detect=true;
	for(int i=0;i<masterDir.in->size();i++){
		if(masterDir.in->at(i).name==name){
			detect=false;
			break;
		}
	}
	if(detect){
		masterDir.in->push_back(singleLevel(name));
	}
	else{
		cout<<"Directory exists"<<endl;
	}
	return masterDir;
}
node insertFile(node masterDir,string name){
	bool detect=true;
	for(int i=0;i<masterDir.in->size();i++){
		if(masterDir.in->at(i).name==name){
			detect=false;
			break;
		}
	}
	if(detect){
		masterDir.in->push_back(createFile(name));
	}
	else{
		cout<<"File exists"<<endl;
	}
	return masterDir;
}
node insertFileMulti(node masterDir,string dirName,string fileName){
	for(int i=0;i<masterDir.in->size();i++){
		if(masterDir.in->at(i).name==dirName){
			bool detect = true;
			for(int j=0;j<masterDir.in->at(i).in->size();j++){
				if(masterDir.in->at(i).in->at(j).name==fileName){
					detect=false;
					break;
				}
			}
			if(detect){
				masterDir.in->at(i).in->push_back(createFile(fileName));
			}
		}
	}
	return masterDir;
}
void remDir(node * masterDir,string name){
	bool flag=true;
	for(int i=0;i<masterDir->in->size();i++){
		if(masterDir->in->at(i).name==name){
			cout<<"All files in this directory will be purged!!!"<<endl;
			cout<<"Do you want to continue?[y/n]:";
			char input;
			cin>>input;
			if(input=='y'||input=='Y'||input=='1'){
				masterDir->in->erase(masterDir->in->begin()+i);
				cout<<"Removed "<<name<<endl;
			}
			flag=false;
			break;
		}
	}
	if(flag){
		cout<<"No such directory"<<endl;
	}
}
void remFile(node * masterDir,string name){
	bool flag=true;
	for(int i=0;i<masterDir->in->size();i++){
		if(masterDir->in->at(i).name==name){
			masterDir->in->erase(masterDir->in->begin()+i);
			cout<<"Removed "<<name<<endl;
			flag=false;
			break;
		}
	}
	if(flag){
		cout<<"No such file"<<endl;
	}
}
void mvFile(node * masterDir,string from,string to){
	bool fromExists=false;
	int fromRelativeID=-1;
	int toRelativeID=-1;
	bool toExists=false;
	for(int i=0;i<masterDir->in->size();i++){
		if(masterDir->in->at(i).name==from){
			fromExists=true;
			fromRelativeID=i;
		}
		if(masterDir->in->at(i).name==to){
			toExists=true;
			toRelativeID=i;
		}
		if(fromExists && toExists){
			break;
		}
	}
	if(fromExists){
		if(toExists){
			cout<<"Replacing already existing!"<<endl;
			masterDir->in->at(toRelativeID)=masterDir->in->at(fromRelativeID);
			masterDir->in->at(toRelativeID).name=to;
			masterDir->in->erase(masterDir->in->begin()+fromRelativeID);
		}
		else{
			masterDir->in->at(fromRelativeID).name=to;
			masterDir->in->push_back(masterDir->in->at(fromRelativeID));
			masterDir->in->erase(masterDir->in->begin()+fromRelativeID);
		}
	}
	else{
		cout<<"No such file"<<endl;
		cout<<fromExists<<toExists<<endl;
	}
}
void mvFileMulti(node * masterDir,string from, string to){
	string fromDir= from.substr(0,from.find('/'));
	int fromDirRelativeID=-1;
	bool fromDirExists=false;
	string fromFile= from.substr(from.find('/')+1);
	int fromFileRelativeID=-1;
	bool fromFileExists=false;
	string toDir= to.substr(0,to.find('/'));
	int toDirRelativeID=-1;
	bool toDirExists=false;
	string toFile= to.substr(to.find('/')+1);
	int toFileRelativeID=-1;
	bool toFileExists=false;
	for(int i=0;i<masterDir->in->size();i++){
		if(masterDir->in->at(i).name==fromDir){
			fromDirExists=true;
			fromDirRelativeID=i;
			for(int j=0;j<masterDir->in->at(i).in->size();j++){
				if(masterDir->in->at(i).in->at(j).name==fromFile){
					fromFileExists=true;
					fromFileRelativeID=j;
				}
			}
		}
		if(masterDir->in->at(i).name==toDir){
			toDirExists=true;
			toDirRelativeID=i;
			for(int j=0;j<masterDir->in->at(i).in->size();j++){
				if(masterDir->in->at(i).in->at(j).name==toFile){
					toFileExists=true;
					toFileRelativeID=j;
				}
			}
		}
		if(fromDirExists && toDirExists){
			break;
		}
	}
	if(fromDirExists && fromFileExists && toDirExists && toFileExists){
		cout<<"Target file exists, Replacing"<<endl;
		masterDir->in->at(toDirRelativeID).in->at(toFileRelativeID)
				= masterDir->in->at(fromDirRelativeID).in->at(fromFileRelativeID);
		masterDir->in->at(fromDirRelativeID).in->erase(
				masterDir->in->at(fromDirRelativeID).in->begin()+fromFileRelativeID);
	}
	else if(fromDirExists && fromFileExists && toDirExists){
		masterDir->in->at(toDirRelativeID).in->push_back(
				masterDir->in->at(fromDirRelativeID).in->at(fromFileRelativeID));
		masterDir->in->at(fromDirRelativeID).in->erase(
					masterDir->in->at(fromDirRelativeID).in->begin()+fromFileRelativeID);
	}
	else if(fromDirExists && fromFileExists){
		cout<<"No such dir "<<toDir<<endl;
	}
	else if(fromDirExists){
		cout<<"No such file "<<fromFile<<endl;
	}
	else if(!fromDirExists){
		cout<<"No such dir "<<fromDir<<endl;
	}
	cout<<fromDirExists<<fromFileExists<<toDirExists<<toFileExists<<endl;
}
void remFileMulti(node * masterDir,string dirName,string fileName){
	bool flag=true;
	for(int i=0;i<masterDir->in->size();i++){
		if(masterDir->in->at(i).name==dirName){
			for(int j=0;j<masterDir->in->at(i).in->size();j++){
				if(masterDir->in->at(i).in->at(j).name==fileName){
					masterDir->in->erase(masterDir->in->at(i).in->begin()+j);
					cout<<"Removed "<<dirName<<"/"<<fileName<<endl;
					flag=false;
					break;
				}
			}
			break;
		}
	}
	if(flag){
		cout<<"No such file"<<endl;
	}
}
void print(node);
void processCMD(node  head){
	node current = head;
	cout<<"TWO LEVEL DIRECTORY"<<endl;
	cout<<"Please enter help or menu for displaying options"<<endl;
	while(true){
		cout<<">>";
		string in;
		getline(cin,in);
		if(in=="help" || in == "menu"){
			cout<<"chdir <path>        Change path"<<endl;
			cout<<"listdir <path>        List path"<<endl;
			cout<<"delete <path>        Removes path"<<endl;
			cout<<"move <path> <path> Moves File/Directory"<<endl;
			cout<<"create <path>        Creates dir"<<endl;
			cout<<"exit             Exits Interpreter"<<endl;
		}
		else if(in.substr(0,5)=="chdir"){
			string process=in.substr(6);
			if(process=="root"){
				current=head;
			}
			else if(process=="/"){
				cout<<"Use of / is depricated, use root instead"<<endl;
				cout<<"No change"<<endl;
			}
			else{
				node * temp;
				for(int i=0;i<current.in->size();i++){
					if(current.in->at(i).name==process){
						if(current.in->at(i).type=='d'){
							current=current.in->at(i);
							cout<<"Changing current dir"<<endl;
						}
						else{
							cout<<"Cant change directory to file"<<endl;
						}
						break;
					}
				}
			}
		}
		else if(in.substr(0,6)=="create"){
			if(current.name!="root"){ //In a dir
				insertFile(current,in.substr(7));
			}
			else{
				insertDir(current,in.substr(7));
			}
		}
		else if(in.substr(0,4)=="move"){
			string data=in.substr(5);
			string from=data.substr(0,data.find(' '));
			string to=data.substr(data.find(' ')+1);
			if(current.name=="root"){
				mvFileMulti(&current,from,to);
			}
			else{
				mvFile(&current,from,to);
			}
		}
		else if(in.substr(0,6)=="delete"){
			if(current.name=="root"){
				remDir(&current,in.substr(7));
			}
			else{
				remFile(&current,in.substr(7));
			}
		}
		else if(in=="listdir"){
			print(current);
		}
		if(in.substr(0,5)=="mkdir"){
			cout<<"Error: No such command has been identified"<<endl;
		}

		else if(in=="exit"){
			cout<<"Good Bye Random User"<<endl;
			break;
		}
	}
}
void printFile(node);
void processCMDTree(node  head){
	node current = head;
	cout<<"HIERARCHICAL DIRECTORY"<<endl;
	cout<<"Please enter menu or help for displaying the options"<<endl;
	while(true){
		cout<<">>";
		string in;
		getline(cin,in);
		if(in=="help" || in == "menu"){
			cout<<"chdir <path>        Change path"<<endl;
			cout<<"listdir <path>        List path"<<endl;
			cout<<"delete <path>        Removes path"<<endl;
			cout<<"move <path> <path> Moves File/Directory"<<endl;
			cout<<"mkdir <path>        Creates dir"<<endl;
			cout<<"touch <path>        Creates file"<<endl;
			cout<<"exit             Exits Interpreter"<<endl;
		}
		else if(in.substr(0,5)=="chdir"){
			string process=in.substr(6);
			if(process=="root"){
				current=head;
			}
			else if(process=="/"){
				cout<<"Use of / is depricated, use root instead"<<endl;
				cout<<"No change"<<endl;
			}
			else{
				node * temp;
				for(int i=0;i<current.in->size();i++){
					if(current.in->at(i).name==process){
						if(current.in->at(i).type=='d'){
							current=current.in->at(i);
							cout<<"Changing current dir"<<endl;
						}
						else{
							cout<<"Cant change directory to file"<<endl;
						}
						break;
					}
				}
			}
		}
		else if(in.substr(0,5)=="mkdir"){
			insertDir(current,in.substr(6));
		}
		else if(in.substr(0,5)=="touch"){
			insertFile(current,in.substr(6));
		}
		else if(in.substr(0,4)=="move"){
			string data=in.substr(5);
			string from=data.substr(0,data.find(' '));
			string to=data.substr(data.find(' ')+1);
			if(current.name=="root"){
				mvFileMulti(&current,from,to);
			}
			else{
				mvFile(&current,from,to);
			}
		}
		else if(in.substr(0,6)=="delete"){
			if(current.type=='d'){
				remDir(&current,in.substr(7));
			}
			else{
				remFile(&current,in.substr(7));
			}
		}
		else if(in=="listdir"){
			printFile(current);
		}
		else if(in=="exit"){
			cout<<"Good Bye Random User."<<endl	;
			break;
		}
	}
}
void processCMDSingle(node head){
	node current = head;
	cout<<"SINGLE LEVEL DIRECTORY"<<endl;
	cout<<"Please enter your choices as given below. Type menu for menu "<<endl;
	while(true){
		cout<<">>";
		string in;
		getline(cin,in);
		if(in=="menu" || in=="help"){
			cout<<"listdir <path>        List path"<<endl;
			cout<<"delete <path>        Removes path"<<endl;
			cout<<"move <path> <path> Moves File/Directory"<<endl;
			cout<<"touch <path>        Creates file"<<endl;
			cout<<"exit             Exits Interpreter"<<endl;
		}
		else if(in.substr(0,5)=="touch"){
			insertFile(current,in.substr(6));
		}
		else if(in.substr(0,4)=="move"){
			string data=in.substr(5);
			string from=data.substr(0,data.find(' '));
			string to=data.substr(data.find(' ')+1);
			mvFile(&current,from,to);
		}
		else if(in.substr(0,6)=="delete"){
			remFile(&current,in.substr(7));
		}
		else if(in.substr(0,7)=="listdir"){
			printFile(current);
		}
		else if(in=="exit"){
			cout<<"Thank you random user"<<endl;
			break;
		}
	}
}

/* Print is still single level
 * moves into a directory
 * extracts the vector
 * treats as root and prints all the data
 */
void printFile(node masterDir){
	cout<<"_______________"<<masterDir.name<<" DIRECTORY_______________"<<endl;
	cout<<"PROPERTIES :"<<masterDir.in->size()<<endl;
	bool file=true;
	for(int i=0;i<masterDir.in->size();i++){
		node current=masterDir.in->at(i);
		cout<<current.name<<" ";
		if(current.type=='f'){
			cout<<"TYPE=FILE ";
		}
		else{
			cout<<"TYPE=DIRECTORY ";
		}
		cout<<"ID="<<current.id<<" ";
		cout<<endl;
	}
	cout<<"_____________END "<<masterDir.name<<" DIRECTORY_____________"<<endl<<endl;
	if(!file){
		for(int i=0;i<masterDir.in->size();i++){
			node current1=masterDir.in->at(i);
			cout<<"___________"<<current1.name<<" DIRECTORY____________"<<endl;
			for(int j=0;j<current1.in->size();j++){
					node current=current1.in->at(j);
					cout<<current.name<<" ";
					if(current.type=='f'){
						cout<<"TYPE=FILE ";
					}
					else{
						cout<<"TYPE=DIRECTORY ";
					}
					cout<<"ID="<<current.id<<" ";
					cout<<endl;
			}
			cout<<"________END "<<current1.name<<" DIRECTORY__________"<<endl<<endl;
		}
	}
}
void print(node masterDir){
	cout<<"_______________HOME DIR_______________"<<endl;
	cout<<"Inode :"<<masterDir.in->size()<<endl;
	bool file=true;
	if(masterDir.name=="root"){
		file=false;
	}
	for(int i=0;i<masterDir.in->size();i++){
		node current=masterDir.in->at(i);
		cout<<current.name<<" ";
		if(current.type=='f'){
			cout<<"TYPE=FILE ";
		}
		else{
			cout<<"TYPE=DIRECTORY ";
		}
		cout<<"id_"<<current.id<<" ";
		cout<<endl;
	}
	cout<<"_____________END HOME DIR_____________"<<endl<<endl;
	if(!file){
		for(int i=0;i<masterDir.in->size();i++){
			node current1=masterDir.in->at(i);
			cout<<"___________"<<current1.name<<" DIRECTORY____________"<<endl;
			for(int j=0;j<current1.in->size();j++){
					node current=current1.in->at(j);
					cout<<current.name<<" ";
					if(current.type=='f'){
						cout<<"TYPE=FILE ";
					}
					else{
						cout<<"TYPE=FILE ";
					}
					cout<<"ID="<<current.id<<" ";
					cout<<endl;
			}
			cout<<"________END "<<current1.name<<" DIRECTORY__________"<<endl<<endl;
		}
	}
}
int main() {
	cout<<"AUTHOR:     Abhijith N Raj"<<endl;
	cout<<"CREDENTIAL: STUDENT,R5,TKMCE"<<endl;
	cout<<"PURPOSE :   LAB CYCLE 1 , SYSTEM SOFTWARE"<<endl;
	cout<<"MENTOR :    PROF JINI"<<endl;
	cout<<"Please Enter single level(1), Two Level(2) or Multilevel(3) : ";
	int choice;
	cin>>choice;
	if(choice==2){
		node masterDir=multiLevel();
		processCMD(masterDir);
		//print(masterDir);
	}
	else if(choice==1){
		node masterDir=singleLevel();
		processCMDSingle(masterDir);
	}
	else{
		node masterDir=createDirectory("root");
		processCMDTree(masterDir);
	}
}
