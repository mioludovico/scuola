#include <stdio.h>
#include <windows.h>
#include "altconio.h"
#include <time.h>
#define N 100

int buffer;
int full; //buffer pieno 

unsigned long WINAPI Produce_thread(void* arg);
unsigned long WINAPI Consume_thread(void* arg);
int RandomNumber(int from, int to);

int main()
{   int low, high;
    HANDLE P_thread, C_thread;
    
	low=1;   high=6;
	srand(time(NULL));
	printf("Produttore e Consumatore WIN\n");
	printf("We have 2 thread one produce other read from buffer\n");	

    full=FALSE; //dato non pronto
    
    // creazione dei thread corrispondenti alle funzioni di lettura, elaborazione e scrittura
    P_thread = CreateThread(NULL, 1024, &Produce_thread, NULL, 0, NULL);
    C_thread = CreateThread(NULL, 1024, &Consume_thread, NULL, 0, NULL);
    // attesa della terminazione dei thread
    WaitForSingleObject(P_thread, INFINITE);
    WaitForSingleObject(C_thread, INFINITE);
    printf("\n...END\n");
    return 0;
}
unsigned long WINAPI Produce_thread(void* arg) // Produttore
{	int r; int i;
	for(i=0;i<100;i++){
	    r=RandomNumber(1,6);	    	    
        while(full) printf("<P>"); //busy waiting 
        //delay(RandomNumber(1,3)*10);
		buffer=r; //scrivo sul buffer
		printf("-P:%d",r);
		full=TRUE; //segnalo anche che ora il buffer è pieno
		}
	ExitThread(0);
}

unsigned long WINAPI Consume_thread(void* arg) // Consumatore
{	int r; int i;
	for(i=0;i<100;i++){
		//delay(RandomNumber(1,3)*10);    
        while(!full) printf("<V>"); //busy waiting 
		r=buffer;//leggo dal buffer
        printf("-C:%d\n",r);
		full=FALSE;//segnalo che ho letto il dato 
		}
	ExitThread(0);
}



int RandomNumber(int from, int to)
{   int r;

    r=rand()%(to-from+1)+from;
	
	return r;
}
