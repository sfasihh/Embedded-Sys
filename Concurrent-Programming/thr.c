#define osObjectsPublic
#include "cmsis_os2.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Board_LED.h"

int draw1;
int draw2;

osThreadId_t tid1_thread;
osThreadId_t tid2_thread;
osThreadId_t tid3_thread;

void Thread_1(void *argument);
void Thread_2(void *argument);
void Thread_3(void *argument);



void delay(){
	int i = 0;
	int count = 0;
	for(i=0; i<1000000; i++){
		count++;
	}
}

void Thread_1 (void *argument){

	osThreadId_t JThreads[2];
	osThreadAttr_t joinable;
	joinable.attr_bits = osThreadJoinable;
	
	for(;;){
	JThreads[0] = osThreadNew(Thread_2, NULL, &joinable);
	JThreads[1] = osThreadNew(Thread_3, NULL, &joinable);
	
	srand(rand());
	osThreadJoin(JThreads[0]);
	osThreadJoin(JThreads[1]);
	
		
	LED_Off(4);	
	LED_Off(5);	
	LED_Off(6);			
	
	if(draw1<draw2){
			LED_On(4);
	}
	else if(draw1>draw2){
		LED_On(5);
	}
	else if (draw1 == draw2){
		LED_On(6);
	}
	
		
	delay();
	}
}

void Thread_2 (void *argument){
		draw1 = ((rand() % 20));
		osThreadExit();
}

void Thread_3 (void *argument){
		draw2 = ((rand() % 20));
		osThreadExit();
}

int main (void) {
  osKernelInitialize ();                   
	LED_Initialize();
	
	tid1_thread = osThreadNew(Thread_1, NULL, NULL);
	tid2_thread = osThreadNew(Thread_2, NULL, NULL);
	tid3_thread = osThreadNew(Thread_3, NULL, NULL);

  osKernelStart ();      
	osDelay(5);
}
