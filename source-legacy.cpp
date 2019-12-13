#include<iostream.h>
#include<stdlib.h>
#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<string.h>
#include<stdio.h>
#include<iomanip.h>
//-----------------------------------------------------
const int WRD=12;  // size of word
char non_words[][WRD]={"is","an","the","has","have","a","are","there","their","not","can","cannot","if","or","and","become","because","in","on","above","below","they","due","to","it","its","of","which","at","also"};

const int N_FILES=9;
const int N_KEY=5;

//-----------------------------------------------------

struct node{
char data[WRD];
node *next;
    };
class queue{
node *rear,*front;

public:
    queue()
{
    rear=NULL;
    front=NULL;}
int id;

void qinsert(char a[]);
void wrd();
int search_wrd(char term[WRD] );
void search_generator(char[][WRD],int,int);
void destroy();

};
void input(); 
 
//--------------------------------------------------------
    
void queue::qinsert(char a[]){
node *temp;
temp=new node;
strcpy(temp->data,a);
temp->next=NULL;
if(rear==NULL)
{
    rear=temp;
    front=temp;

}
else{
    rear->next=temp;
    rear=temp;
}
}

void queue::destroy(){
    while(front!=NULL)
{
    node *temp=front;
    front=front->next;
    delete temp;

}
}

//--------------------------------------------------------


 void queue:: wrd(){

 char filename[30];
 char temp[WRD*WRD];
 char t[WRD];
 int flag;
 fstream fil;

 int i=id,j=0,k=0;

 itoa(i,filename,10);
 strcat(filename,".txt") ;
 fil.open(filename,ios::in);
  while (!fil.eof()){

fil.getline(temp,WRD*WRD);
for(i=0;temp[i]!='\0';i++)
 {
     k=0;
	 for(j=i;temp[j]!=' '&& temp[j]!='\0';j++)
     {
	if(!(temp[j]=='.'||temp[j]==','))
	    t[k]=temp[j];
    k++;
     }
    i=j;
	 t[k]='\0';
for(int k=0;k<(sizeof(non_words)/WRD);k++)  // compare with all nnwrds
{  flag=0;
    if(strcmp(t,non_words[k])==0)
    {
	flag=1;
	break;
    }
    else
	continue;
}
 if(flag==0)

    // valid key
 {
     qinsert(t);

 }


}

}

 fil.close();
 }


 int queue::search_wrd(char term[WRD] )
{
    int hits=0;

     node *temp=front;
    while(temp!=NULL)
    {
      if(  strcmp(temp->data,term)==0)
	hits++;

	temp=temp->next;

    }

return hits;
}

//-----------------------------------------------------

void header(){
clrscr();
cout<<"\n\n\n\t\t###########################################\n";
      cout<<"\t\t###         DATA SEARCH SYSTEM          ###\n";
      cout<<"\t\t###########################################\n\n\n";

}


//-----------------------------------------------------

void goodbye(){

header();
cout<<"\n\n\t A Computer Science Project By: \n\n\n";
cout<<"  Paul Joseph Robin\t\tSteve Masih\t\tYash Nimesh\n";
cout<<"  \t\t\tXII-B";
getch();
exit(0);

}

//-----------------------------------------------------

void display(int file_id)
{
char filename[30];

header();
if(file_id<=N_FILES)
  {

    fstream fil;
     itoa(file_id,filename,10);
	strcat(filename,".txt") ;
  fil.open(filename,ios::in);
cout<<"\n\n\t\t\t---OPEN FILE: "<<filename<<" ---\n\n\n\n";
  char str[80];
  while(fil.getline(str,80))
    cout<<str<<endl;
  fil.close();
  getch();
  }

  else goodbye();


}

//-----------------------------------------------------

void printh(){

header();
cout<<"\t _____________________________________________________________ \n";
cout<<"\t| File ID    |          	Search Results 		       | \n";
cout<<"\t ------------------------------------------------------------- \n";

}

//-----------------------------------------------------

void options(){
cout<<"  \n\t __________________________________________________________________\n";
cout<<"\n\t\t Options:";
cout<<"\n\t 1. Open a File ";
cout<<"\n\t 2. Perform another Search";
cout<<"\n\t 3. Exit\n";


}

//-----------------------------------------------------

struct result{
char i[WRD];
int n;
}R[N_KEY];

class output
{
public:
    int h;
    int i;
};

//-----------------------------------------------------

void out(result r[N_KEY],int file,int ctr){
output obj;

int hit_ratio=0;

for(int i=0;i<ctr;i++)
hit_ratio+=r[i].n;

obj.h=hit_ratio;
obj.i=file;
ofstream fout("record.dat",ios::binary|ios::app);
if(!fout)
    cout<<"Unable to open\n";

if(obj.h>0)
fout.write((char*)&obj,sizeof(obj));
fout.close();
}

void queue:: search_generator(char terms[N_KEY][WRD],int ctr,int i)
{
id=i;
       wrd();
       for(int j=0;j<ctr;j++){
	strcpy( R[j].i,terms[j]);
	R[j].n=search_wrd(R[j].i);  // gets the no of hits

       }

     out(R,i,ctr);
    }

//-----------------------------------------------------

void print(output O[N_FILES]){
	 header();
	 cout<<"-----------------------------------------------------\n";
	 printh();
char filename[20];
for(int i=0;i<5;i++) 		// Restrict to Top Five Search Results
{         if(O[i].i>0)
{
    cout<<"\t"<<O[i].i<<"\t";


    fstream fil;
     itoa(O[i].i,filename,10);
	strcat(filename,".txt") ;
  fil.open(filename,ios::in);
  char str[80];
  fil.getline(str,78);
  cout.setf(ios::left);
  cout<<"  "<<setw(50)<<str<<"..."<<endl;
  fil.close();

}
}
}

//-----------------------------------------------------

void sort(){

fstream f;
f.open("record.dat",ios::binary|ios::in);
output O[N_FILES];
int n=0;
while(f.read((char*)&O[n],sizeof(output)))
n++;
output temp;
int i,j;
if(n==0)	cout<<"\nNO RESULTS FOUND!\n";
for(i=1;i<n;i++)
    for(j=0;j<n-i;j++)
    if(O[j].h < O[j+1].h)
{
    temp=O[j];
    O[j]=O[j+1];
    O[j+1]=temp;
}
f.close();
print(O);
}

//-----------------------------------------------------

void major(char terms[N_KEY][WRD],int ctr){
  for(int i=1;i<=N_FILES;i++)
    {
  queue words;
words.search_generator(terms, ctr,i);
words.destroy();
}
sort();
int choice;
options();
cin>>choice;

header();
switch(choice)
{
case 1:
    cout<<"Enter File-Id";
    cin>>choice;
    display(choice);
    break;
case 2:
  input();
     break;
default:
    goodbye();
    break;


}

}

//-----------------------------------------------------

void input(){
    header();
cout<<"Welcome! \n  Enter your desired search keywords.\n"<<endl;
ofstream fout("record.dat",ios::binary);
 fout.close();
char search_term[N_KEY*WRD];
gets(search_term);
char terms[N_KEY][WRD];
int ctr=0;
int i,j,k=0;


 for(i=0;search_term[i]!='\0';i++)
 {
     k=0;
     for(j=i;search_term[j]!=' '&&search_term[j]!='\0';j++)
     {

	    terms[ctr][k]=search_term[j];
	    k++;
     }

     i=j--;
     terms[ctr][k]='\0';
     ctr++;  // no ofterms
}
for(i=0;i<ctr;i++)
for(j=0;j<(sizeof(non_words)/WRD);j++)  // compare with all nnwrds
{   if(strcmp(terms[i],non_words[j])==0)
    {
	ctr--;
	 for(int k=i;k<ctr;k++)
	strcpy(terms[k],terms[k+1]);
	i--;
	break;
    }
    else
	continue;
}

major(terms,ctr);

}

//-----------------------------------------------------

int main()
{

    input();
    return 0;

}
