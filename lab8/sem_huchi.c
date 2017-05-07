#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>
#include <semaphore.h>

sem_t sem; //无名信号量
int gbl_var = 1;

void *write_thread(void *arg)
{
	while(1) {
 		sem_wait(&sem);
		//操作资源
 		gbl_var++;
 		printf("write thread: gbl_var =%d\n", gbl_var);
		sleep(1);  //故意增加占用资源的时间，正常项目中加锁时间越短越好
 		//sem_post(&sem);
	}
	pthread_exit(NULL);
}

void *read_thread(void *arg)
{
    while(1) {
        //sem_wait(&sem);
        //操作资源
        printf("read thread: gbl_var =%d\n", gbl_var);
        sleep(2);  //故意增加占用资源的时间，正常项目中加锁时间越短越好
        sem_post(&sem);
    }

	pthread_exit(NULL);
}

int main(void)
{
  

    pthread_t rtid, wtid;
	printf("multithread progarm starting....\n");
    sem_init(&sem, 0, 1); //初始化化信号量

    pthread_create(&wtid, NULL, write_thread, NULL);
    pthread_create(&rtid, NULL, read_thread, NULL);

    pthread_join(rtid, NULL);
    pthread_join(wtid, NULL);
    printf("multithread progarm end.\n");


    return 0;
}



