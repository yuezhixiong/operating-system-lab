#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc,char **argv)
{
      int msg_id;

      if(argc != 2){
				fprintf(stderr,"Usage:%s <msgid>\n",argv[0]);
				exit(1);
      }
      msg_id = atoi(argv[1]);
      //删除消息队列
      if(msgctl(msg_id,IPC_RMID,NULL) < 0){
				perror("msgget");
				exit(1);
      }
      return 0;
}
