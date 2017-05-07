#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>  //多线程编程的头文件

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
           
	
	sleep(5);  //子线程可以做其他事情了   	
    
	pthread_exit((void *)pStud);  //类似于进程编程中的exit() 
//	return NULL;
}

int main(void)
{
   pthread_t tid;	   
   char *params = "Hello, 1503";
   struct stud_stru *pStud  = NULL;	
   
   printf("I'm the parent thread.\n");
   
   pthread_create(&tid, NULL,sub_thread_func, (void *)params); //类似于进程编程中的fork()
   
   pthread_join(tid, (void *)&pStud);  //类似于进程编程中的wait()/waitpid()
   
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
