#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<string.h>
using namespace std;

union semun
{
    int val; /* val for SETVAL */
    struct semid_ds *buf; /* Buffer for IPC_STAT and IPC_SET */
    unsigned short *array; /* Buffer for GETALL and SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO and SEM_INFO*/
};

void semSignal(int semid, unsigned short index)
{
    struct sembuf sem_unlock = {index,1,SEM_UNDO};
    int x = semop(semid,&sem_unlock,1);
}

void semWait(int semid, unsigned short index)
{
    struct sembuf sem_unlock = {index,-1,SEM_UNDO};
    int x = semop(semid,&sem_unlock,1);
}
void printPrice(string current_price,string average_price)
{
    if(current_price[current_price.length()-1]=='Z'){
    	current_price.pop_back();
    	if(current_price.length()<5)
        	cout<<"    "<<"\033[1;32m"<< current_price<<"↑  "<<"\033[0m";
       	else if (current_price.length()<6)
       		cout<<"   "<<"\033[1;32m"<< current_price<<"↑  "<<"\033[0m";
       	else if (current_price.length()<7)
       		cout<<"  "<<"\033[1;32m"<< current_price<<"↑  "<<"\033[0m";
       	else
       		cout<<" "<<"\033[1;32m"<< current_price<<"↑  "<<"\033[0m";
     }
    else if(current_price[current_price.length()-1]=='A'){
    	current_price.pop_back();
        if(current_price.length()<5)
        	cout<<"    "<<"\033[1;31m"<< current_price<<"↓  "<<"\033[0m";
       	else if (current_price.length()<6)
       		cout<<"   "<<"\033[1;31m"<< current_price<<"↓  "<<"\033[0m";
       	else if (current_price.length()<7)
       		cout<<"  "<<"\033[1;31m"<< current_price<<"↓  "<<"\033[0m";
       	else
       		cout<<" "<<"\033[1;31m"<< current_price<<"↓  "<<"\033[0m";
       }
    else{
    	current_price.pop_back();
        if(current_price.length()<5)
        	cout<<"    "<<"\033[1;34m"<< current_price<<"   "<<"\033[0m";
       	else if (current_price.length()<6)
       		cout<<"   "<<"\033[1;34m"<< current_price<<"   "<<"\033[0m";
       	else if (current_price.length()<7)
       		cout<<"  "<<"\033[1;34m"<< current_price<<"  "<<"\033[0m";
       	else
       		cout<<" "<<"\033[1;34m"<< current_price<<"  "<<"\033[0m";
        }
    cout<<"| ";
    if(average_price[average_price.length()-1]=='Z'){
    	average_price.pop_back();
    	if(average_price.length()<5)
        	cout<<"    "<<"\033[1;32m"<< average_price<<"↑  "<<"\033[0m";
       	else if (average_price.length()<6)
       		cout<<"   "<<"\033[1;32m"<< average_price<<"↑  "<<"\033[0m";
       	else if (average_price.length()<7)
       		cout<<"  "<<"\033[1;32m"<< average_price<<"↑  "<<"\033[0m";
       	else
       		cout<<" "<<"\033[1;32m"<< average_price<<"↑  "<<"\033[0m";
     }
    else if(average_price[average_price.length()-1]=='A'){
    	average_price.pop_back();
        if(average_price.length()<5)
        	cout<<"    "<<"\033[1;31m"<< average_price<<"↓  "<<"\033[0m";
       	else if (average_price.length()<6)
       		cout<<"   "<<"\033[1;31m"<< average_price<<"↓  "<<"\033[0m";
       	else if (average_price.length()<7)
       		cout<<"  "<<"\033[1;31m"<< average_price<<"↓  "<<"\033[0m";
       	else
       		cout<<" "<<"\033[1;31m"<< average_price<<"↓  "<<"\033[0m";
       }
    else{
    	average_price.pop_back();
        if(average_price.length()<5)
        	cout<<"    "<<"\033[1;34m"<< average_price<<"   "<<"\033[0m";
       	else if (average_price.length()<6)
       		cout<<"   "<<"\033[1;34m"<< average_price<<"   "<<"\033[0m";
       	else if (average_price.length()<7)
       		cout<<"  "<<"\033[1;34m"<< average_price<<"  "<<"\033[0m";
       	else
       		cout<<" "<<"\033[1;34m"<< average_price<<"  "<<"\033[0m";
        }
    cout <<"|\n";
}
int main(int argc,char** argv)
{
    const int buffersize=atoi(argv[1]);
    unsigned int milliseconds = 1000000;
    key_t key2 = ftok("kiro1",200);
    int shmid = shmget(key2,sizeof(double)*11*buffersize,0666|IPC_CREAT);
    key_t key3 = ftok("kiro2",400);
    int shmid1 = shmget(key3,sizeof(int)*11,0666|IPC_CREAT);
    key_t key = ftok("kiro",5);
    int semid=semget(key,3,0666 | IPC_CREAT | IPC_EXCL);
    struct sembuf *semops;
    size_t siz=20;
    union semun value_s;
    value_s.val=1;
    int semvalue_s=semctl(semid,0,SETVAL,value_s);
    union semun value_n;
    value_n.val=0;
    int semvalue_n=semctl(semid,1,SETVAL,value_n);
    union semun value_e;
    value_e.val=buffersize;
    int semvalue_e=semctl(semid,2,SETVAL,value_e);
    int *index1 = (int*) shmat(shmid1,0,0);
    double *prices = (double*) shmat(shmid,0,0);
    int i,j;
    for (i=0; i<11; i++)
        index1[i]=0;
    for (i=0; i<11*buffersize; i++)
        prices[i]=0.0;
    cout<<"\033[1;31m";
    cout << semid <<" "<< shmid <<" "<< shmid1 << "\n\n";
    cout << "\033[0m\n";
    double prev_prices[11];
    double prev_avg_price[11];
    int prev_index[11];
    string average_price[11];
    string current_price[11];
    for (i=0; i<11; i++)
    {
        prev_prices[i]=0;
        prev_avg_price[i]=0;
        prev_index[0];
        average_price[i]="0.00 ";
    	current_price[i]="0.00 ";
    }
    double curent_price;
    double total_price;
    double avg_price;
    int index;
    int counter=0;
    string up="↑";
    string down="↑";
    while(true)
    {
        semWait(semid,1);
        semWait(semid,0);
	system("clear");
        double *prices = (double*) shmat(shmid,0,0);
        int *indecies = (int*) shmat(shmid1,0,0);
        cout<<"+----------------------------------------+\n";
        cout<<"| Currency      |  Price    |  AvgPrice  |\n";
        cout<<"+----------------------------------------+\n";

        for(i=0; i<11; i++)
        {
            if(indecies[i]!=0)
                index=indecies[i]-1+buffersize*i;
            else
                index=buffersize-1+buffersize*i;
            curent_price=prices[index];
            total_price=curent_price;
            counter=0;
            for(j=0; j<4; j++)
            {
                if(index>buffersize*i)
                    index--;
                else
                    index=index+buffersize*i-1;
                total_price+=prices[index];
                if(prices[index]>0)
                    counter++;
            }
            avg_price=total_price/(counter+1);
            if(indecies[i]!=prev_index[i]){
            if(avg_price>prev_avg_price[i]){
                 average_price[i]=to_string(avg_price);
                 average_price[i]=average_price[i].substr(0, average_price[i].find(".")+3);
                 average_price[i]=average_price[i]+"Z";
                }
            else if (avg_price<prev_avg_price[i]){
                 average_price[i]=to_string(avg_price);
                 average_price[i]=average_price[i].substr(0, average_price[i].find(".")+3);
                 average_price[i]=average_price[i]+"A";
                }
            else{
                 average_price[i]=to_string(avg_price);
                 average_price[i]=average_price[i].substr(0, average_price[i].find(".")+3);
                 average_price[i]=average_price[i]+" ";
                }
            if(curent_price>prev_prices[i]){
                 current_price[i]=to_string(curent_price);
                 current_price[i]=current_price[i].substr(0, current_price[i].find(".")+3);
                 current_price[i]=current_price[i]+"Z";
                }
            else if (curent_price<prev_prices[i]){
                 current_price[i]=to_string(curent_price);
                 current_price[i]=current_price[i].substr(0, current_price[i].find(".")+3);
                 current_price[i]=current_price[i]+"A";
                }
            else{
                 current_price[i]=to_string(curent_price);
                 current_price[i]=current_price[i].substr(0, current_price[i].find(".")+3);
                 current_price[i]=current_price[i]+" ";
                }
            }
            if(i==0)
            {
                cout << "| ALUMINUIM     |";
            }
            else if(i==1)
            {
                cout << "| COPPER        |";
            }
            else if(i==2)
            {
                cout << "| COTTON        |";
            }
            else if(i==3)
            {
                cout << "| CRUDEOIL      |";
            }
            else if(i==4)
            {
                cout << "| GOLD          |";
            }
            else if(i==5)
            {
                cout << "| LEAD          |";
            }
            else if(i==6)
            {
                cout << "| MENTHAOIL     |";
            }
            else if(i==7)
            {
                cout << "| NATURAL GAS   |";
            }
            else if(i==8)
            {
                cout << "| NICKEL        |";
            }
            else if(i==9)
            {
                cout << "| SILVER        |";
            }
            else if(i==10)
            {
                cout << "| ZINC          |";
            }
            printPrice(current_price[i],average_price[i]);


            prev_prices[i]=curent_price;
            prev_avg_price[i]=avg_price;
            prev_index[i]=indecies[i];
        }
        cout<<"+----------------------------------------+\n";
        semSignal(semid,0);
        semSignal(semid,2);
        cout<<"\n";
       

    }


    return 0;
}
