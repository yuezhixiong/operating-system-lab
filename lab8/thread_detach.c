#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>  //header file for thread programming

#define NAME_LEN  64 
#define USER_NAME "stephenyee"
struct stud_stru {
	char name[NAME_LEN];
	int age;
	//... 
};

void* sub_thread_func(void *arg)
{ 
  struct stud_stru *pStud  = NULL;
 
   char *var_str = (char *)arg;

	printf("I'm the child thread.\n");
	printf(" the arg is :%s\n", var_str);
	

	pStud = (struct stud_stru *)malloc(sizeof(struct stud_stru));
        if(!pStud) {
		return NULL;
	}
	
       strncpy(pStud->name, USER_NAME ,sizeof(USER_NAME));
       pStud->age = 18;
           
	
	sleep(15);  //the son thread can do other job	now   	
    
	pthread_exit((void *)pStud);  //similar as exit() in process programming 
//	return NULL;
}

void *detach_thread_demo(void *arg)
{
	int i;
	
	pthread_detach(pthread_self());	
	for(i =0; i<10; i++) {
		sleep(1);
		printf("I'm the detach demo thread, i=%d\n",i);
	        if(i==5) {
			printf("Cancel the detatch demo thread.\n");
			pthread_cancel(pthread_self());
		}
	}
        printf("My God, I'll die.\n");
        pthread_exit(NULL);
}

int main(void)
{
   pthread_t tid, tid2;	   
   char *params = "Hello, SUSTC";
   struct stud_stru *pStud  = NULL;	
   
   printf("I'm the parent thread.\n");
   
   pthread_create(&tid, NULL,sub_thread_func, (void *)params); //similar as fork() in process programming
   pthread_create(&tid2, NULL,detach_thread_demo, NULL);
 
   pthread_join(tid, (void *)&pStud);  //similar as wait()/waitpid() in process programming

  // pthread_join(tid2, NULL);
   
   printf("I'm the parent thread. after pthread_join()\n");
  
  if(!pStud) {
	printf("the Child thread no return value\n");
	exit(1);
   }
   
   printf("name =%s, age=%d\n", pStud->name, pStud->age);
   if (pStud) {
	free(pStud);
	pStud = NULL;
   }	
   return 0;
}
