#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE  1024


int main(void)
{
      int shm_id;
      key_t key;
      char *p;
      //获取key
			if((key = ftok("./",0xa)) < 0){
				perror("ftok");
		    exit(1);
      }
      //获得共享内存
      if((shm_id = shmget(key,SHM_SIZE,IPC_CREAT|0666)) < 0){
				perror("shmget");
				exit(1);
      }

      //将共享内存映射到当前进程的虚拟空间中
       if( (p  = shmat(shm_id,NULL,0)) == NULL){
				perror("shmat");
				exit(1);
       }
       while(1){
				 fgets(p,SHM_SIZE,stdin);
				 if(strncmp(p,"quit",4) == 0)
				 break;
       }

      if(shmdt(p) < 0){
				perror("shmdt");
				exit(1);
      }
	    return 0;
}
