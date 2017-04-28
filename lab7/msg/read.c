#include "msg.h"


int main(void)
{
      int msg_id;
      key_t key;
      //get key
      if((key = ftok("./",0xa)) < 0){
				perror("ftok");
				exit(1);
      }

			//get message queue
      if((msg_id = msgget(key,IPC_CREAT|0666)) < 0){
				perror("msgget");
				exit(1);
      }

      //receive message
      struct msgbuf m;
      while(1){
				bzero(&m,sizeof(m));
				printf("请输入要接收消息的类型:");
				scanf("%ld",&m.mtype);
				if(msgrcv(msg_id,&m,MSG_SIZE,m.mtype,0) < 0){
					perror("msgget");
					exit(1);
				}
				if(strncmp(m.mtext,"quit",4) == 0)
				break;
				printf("%s",m.mtext);
      }

      return 0;
}
