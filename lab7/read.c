#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_SIZE 1024

int main(void)
{
      int shm_id;
      key_t key;
      char *p;

      int sem_id;
      struct sembuf sem_buf_p = {0, -1, SEM_UNDO};

      //获取key
      if ((key = ftok("./", 0xa)) < 0)
      {
            perror("ftok");
            exit(1);
      }

      //获得共享内存
      if ((shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0)
      {
            perror("shmget");
            exit(1);
      }

      //创建信号灯
      if ((sem_id = semget(key, 1, IPC_CREAT | 0666)) < 0)
      {
            perror("semget");
            exit(1);
      }

      //将共享内存映射到当前进程的虚拟空间中
      if ((p = shmat(shm_id, NULL, 0)) == NULL)
      {
            perror("shmat");
            exit(1);
      }
      while (1)
      {
            //P操作阻塞自己
            //puts("operation p chocking");
            semop(sem_id, &sem_buf_p, 1);
            //puts("done operation p");

            if (strncmp(p, "quit", 4) == 0)
            {
                  break;
            }

            printf("%s", p);
            sleep(1);
      }

      if (shmdt(p) < 0)
      {
            perror("shmdt");
            exit(1);
      }
      if (semctl(sem_id, 0, IPC_RMID, NULL) < 0)
      {
            perror("semctl");
            exit(1);
      }
      return 0;
}
