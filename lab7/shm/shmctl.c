#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE  1024


int main(int argc,char **argv)
{
      int shm_id;

      if(argc != 2){
		fprintf(stderr,"Usage:%s <shmid>\n",argv[0]);
		exit(1);
      }
      shm_id = atoi(argv[1]);
      //删除共享内存
      if(shmctl(shm_id,IPC_RMID,NULL) < 0){
		perror("shmget");
		exit(1);
      }
      return 0;
}
