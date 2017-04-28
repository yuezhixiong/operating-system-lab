#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
      int msg_id;
      key_t key;
      //获取key
      if((key = ftok("./",0xa)) < 0){
				perror("ftok");
				exit(1);
      }

      //创建/获得消息队列
      if((msg_id = msgget(key,IPC_CREAT|0666)) < 0){
				perror("msgget");
				exit(1);
      }

	    return 0;
}
