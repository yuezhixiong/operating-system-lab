#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>
#include <semaphore.h>

/*1.定义mutex变量并做静态的初始化 */
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int gbl_var = 1;

void *write_thread(void *arg)
{
	while(1) {
		pthread_mutex_lock(&mutex); //加锁 
		//操作资源
 		gbl_var++;
 		printf("write thread: gbl_var =%d\n", gbl_var);
		sleep(1);  //故意增加占用资源的时间，正常项目中加锁时间越短越好

 		pthread_mutex_unlock(&mutex); //解锁
	}
	pthread_exit(NULL);
}

void *read_thread(void *arg)
{
    while(1) {

	pthread_mutex_lock(&mutex); //加锁 
        //操作资源
        printf("read thread: gbl_var =%d\n", gbl_var);
        sleep(2);  //故意增加占用资源的时间，正常项目中加锁时间越短越好

         pthread_mutex_unlock(&mutex); //解锁
    }

	pthread_exit(NULL);
}

int main(void)
{
  

    pthread_t rtid, wtid;
    printf("multithread progarm starting....\n");
   
   /*2.初始化mutex: 实质上，对系统来说，互斥锁是一种系统的资源，此处分配系统资源 */
    pthread_mutex_init(&mutex, NULL);
	 
    pthread_create(&wtid, NULL, write_thread, NULL);
    pthread_create(&rtid, NULL, read_thread, NULL);

    pthread_join(rtid, NULL);
    pthread_join(wtid, NULL);

    /* 4. 释放互斥锁的资源*/    
    pthread_mutex_destroy(&mutex);

    printf("multithread progarm end.\n");


    return 0;
}



