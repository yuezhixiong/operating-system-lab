#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>  //多线程编程的头文件

void* sub_thread_func(void *arg)
{
   char *var_str = (char *)arg;

	printf("\nI'm the child thread.\n");
	printf(" the arg is :%s\n", var_str);
	
	sleep(5);  //子线程可以做其他事情了   	
    
	printf("I'm dying.\n");
	pthread_exit(NULL);  //类似于进程编程中的exit() 
	return NULL;
}

int main(void)
{
   pthread_t tid;	   
   char *params = "Hello, SUSTC";
   printf("\nI'm the parent thread.\n");
   
   pthread_create(&tid, NULL,sub_thread_func, (void *)params); //类似于进程编程中的fork()
   
   pthread_join(tid, NULL);  //类似于进程编程中的wait()/waitpid()
   
   printf("\nI'm the parent thread. after pthread_join()\n");

	
	return 0;
}
