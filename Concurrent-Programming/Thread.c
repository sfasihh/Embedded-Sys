#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Board_LED.h"

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
osThreadId_t tid1_Thread;
osThreadId_t tid2_Thread;
osThreadId_t tid3_Thread;

void Thread1(void *argument);
void Thread2(void *argument);
void Thread3(void *argument);

void delay(){
	int i = 0;
	int count = 0;
	for(i=0; i<100000; i++){
		count++;
	}
}
int draw1;  //User 1
int draw2;  //User 2

int Init_Thread (void) {

  tid1_Thread = osThreadNew(Thread1, NULL, NULL);						//creating thread1
	tid2_Thread = osThreadNew(Thread2, NULL, NULL);						//creating thread2
	tid3_Thread = osThreadNew(Thread3, NULL, NULL);						//creating thread3
  return(0);
	
}

void Thread1 (void *argument){

	osThreadId_t JThreads[2];
	osThreadAttr_t joinable;
	joinable.attr_bits = osThreadJoinable;
	
	for(;;){
	JThreads[0] = osThreadNew(Thread2, NULL, &joinable);
	JThreads[1] = osThreadNew(Thread3, NULL, &joinable);
	
	osThreadJoin(JThreads[0]);
	osThreadJoin(JThreads[1]);
				
	LED_Off(4);	
	LED_Off(5);	
	LED_Off(6);
	if(draw1<draw2){
			LED_On(4);
			printf("User2 draws a higher number.\n");
	}
	else if(draw1>draw2){
		LED_On(5);
		printf("User1 draws a higher number.\n");
	}
	else if (draw1 == draw2){
		LED_On(6);
		printf("Both users draw the same number.\n");
	}	
	delay();
	}
}

void Thread2 (void *argument){
		draw1 = ((rand() % 50));
		printf("User1 draws: %d\n", draw1);
		osThreadExit();
}

void Thread3 (void *argument){
		draw2 = ((rand() % 50));
		printf("User2 draws: %d\n", draw2);
		osThreadExit();
}