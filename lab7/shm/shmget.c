#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE  1024


int main(void)
{
      int shm_id;
      key_t key;
      //获取key
      if((key = ftok("./",0xa)) < 0){
				perror("ftok");
				exit(1);
      }
      //创建共享内存
				if((shm_id = shmget(key,SHM_SIZE,IPC_CREAT|0666)) < 0){
				perror("shmget");
				exit(1);
      }

	    return 0;
}
