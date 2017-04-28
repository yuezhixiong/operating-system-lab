#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE  1024
void fun(int sig)
{}

int main(void)
{
      int shm_id;
      pid_t pid;
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
 
 			//fork child process
      if((pid = fork()) < 0){
				perror("fork");
				exit(1);
      }else if( pid > 0){  //父进程:向共享内存中写数据
				//将共享内存映射到当前进程的虚拟空间中
				if( (p  = shmat(shm_id,NULL,0)) == NULL){
					perror("shmat");
					exit(1);
				}
				//向共享内存中写数据
				while(1){
					fgets(p,SHM_SIZE,stdin);
					if(strncmp(p,"quit",4) == 0){
						kill(pid,SIGUSR1);
						break;
					}
					
					kill(pid,SIGUSR1);
				}


				if(shmdt(p) < 0){
					perror("shmdt");
					exit(1);
				}
	
/*				if(shmctl(shm_id,IPC_RMID,NULL) < 0){ 
					perror("parent shmctl");
					exit(1);
				}   */

				exit(0);

      }else{  //子进程:从共享内存中读数据
				//将共享内存映射到当前进程的虚拟空间中
				signal(SIGUSR1,fun);
				if( (p  = shmat(shm_id,NULL,0)) == NULL){
					perror("shmat");
					exit(1);
				}
				//从共享内存中读数据
				while(1){
					if(strncmp(p,"quit",4) == 0)
					break;
					printf("%s",p);
					pause();
				}

				if(shmdt(p) < 0){
					perror("shmdt");
					exit(1);
				}
			
				if(shmctl(shm_id,IPC_RMID,NULL) < 0){ 
					perror("child shmctl");
					exit(1);
				}   

				exit(0);
      }


      return 0;
}
