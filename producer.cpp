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
#define SHM_KEY 0x12345
#define SHM_KEYY 0x1234567
#include<iostream>
#include<unistd.h>
#include<random>
using namespace std;

union semun {
   int val; /* val for SETVAL */
   struct semid_ds *buf; /* Buffer for IPC_STAT and IPC_SET */
   unsigned short *array; /* Buffer for GETALL and SETALL */
   struct seminfo *__buf; /* Buffer for IPC_INFO and SEM_INFO*/
};

void semSignal(int semid, unsigned short index){
    struct sembuf sem_unlock = {index,1,SEM_UNDO};
    int x = semop(semid,&sem_unlock,1);
}

void semWait(int semid, unsigned short index){
    struct sembuf sem_unlock = {index,-1,SEM_UNDO};
    int x = semop(semid,&sem_unlock,1);
}

int main(int argc,char** argv)
{
    const int buffersize=atoi(argv[5]);
    char* name=argv[1];
    double price_mean= atof(argv[2]);
    double standard_dev=atof(argv[3]);
    int time=atoi(argv[4]);
    int size2;
    default_random_engine generator;
    normal_distribution<double> distribution(price_mean,standard_dev);

    int i=1;
    unsigned int milliseconds=1000000;
    key_t key2 = ftok("kiro1",200);
    int shmid = shmget(key2,sizeof(double)*11*buffersize,0666|IPC_CREAT);
    key_t key3 = ftok("kiro2",400);
    int shmid1 = shmget(key3,sizeof(int)*11,0666|IPC_CREAT);
    key_t key = ftok("kiro",5);
    int semid=semget(key,3,0666);
    double price=distribution(generator);
    while(true){
  	price=distribution(generator);
  	cout << name << ": generated new value " << price <<"\n"; 
    	cout << name <<": trying to get the buffer"<<"\n";
        semWait(semid,2);
        semWait(semid,0);
        double *prices = (double*) shmat(shmid,0,0);
        int *indecies = (int*) shmat(shmid1,0,0);
        if(strcmp(name,"ALUMINIUM")==0){
            prices[buffersize*0+indecies[0]]=price;
            i=buffersize*0+indecies[0];
            indecies[0]=(indecies[0]+1)%buffersize;
        }
        else if(strcmp(name,"COPPER")==0){
            prices[buffersize*1+indecies[1]]=price;
            i=buffersize*1+indecies[1];
            indecies[1]=(indecies[1]+1)%buffersize;
        }
        else if(strcmp(name,"COTTON")==0){
            prices[buffersize*2+indecies[2]]=price;
            i=buffersize*2+indecies[2];
            indecies[2]=(indecies[2]+1)%buffersize;
        }
        else if(strcmp(name,"CRUDEOIL")==0){
            prices[buffersize*3+indecies[3]]=price;
            i=buffersize*3+indecies[3];
            indecies[3]=(indecies[3]+1)%buffersize;
        }
        else if(strcmp(name,"GOLD")==0){
            prices[buffersize*4+indecies[4]]=price;
            i=buffersize*4+indecies[4];
            indecies[4]=(indecies[4]+1)%buffersize;
        }
        else if(strcmp(name,"LEAD")==0){
            prices[buffersize*5+indecies[5]]=price;
            i=buffersize*5+indecies[5];
            indecies[5]=(indecies[5]+1)%buffersize;
        }
        else if(strcmp(name,"MENTHAOIL")==0){
            prices[buffersize*6+indecies[6]]=price;
            i=buffersize*6+indecies[6];
            indecies[6]=(indecies[6]+1)%buffersize;
        }
        else if(strcmp(name,"NATURALGAS")==0){
            prices[buffersize*7+indecies[7]]=price;
            i=buffersize*7+indecies[7];
            indecies[7]=(indecies[7]+1)%buffersize;
        }
        else if(strcmp(name,"NICKEL")==0){
            prices[buffersize*8+indecies[8]]=price;
            i=buffersize*8+indecies[8];
            indecies[8]=(indecies[8]+1)%buffersize;
        }
        else if(strcmp(name,"SILVER")==0){
            prices[buffersize*9+indecies[9]]=price;
            i=buffersize*9+indecies[9];
            indecies[9]=(indecies[9]+1)%buffersize;
        }
        else if(strcmp(name,"ZINC")==0){
            prices[buffersize*10+indecies[10]]=price;
            i=buffersize*10+indecies[10];
            indecies[10]=(indecies[10]+1)%buffersize;
        }
        cout << name << ": placed price " << prices[i] << "on shared buffer\n";
        semSignal(semid,0);
        semSignal(semid,1);
        cout << "sleeping for " << time << "ms\n";
        usleep(1000*time);


    }


    return 0;
}

