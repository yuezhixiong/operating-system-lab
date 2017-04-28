#include "msg.h"

int main(void)
{
      int msg_id;
      key_t key;
      //获取key
      if((key = ftok("./",0xa)) < 0){
			perror("ftok");
			exit(1);
      }

      //获得消息队列
      if((msg_id = msgget(key,IPC_CREAT|0666)) < 0){
			perror("msgget");
			exit(1);
      }

      //发送消息
      struct msgbuf m;
       while(1){
				 bzero(&m,sizeof(m));
				 printf("请输入要发送的消息类型:");
				 scanf("%ld",&m.mtype);
				 while(getchar() != '\n');
				 printf("输入消息:");
				 fgets(m.mtext,MSG_SIZE,stdin);
				 if(msgsnd(msg_id,&m,strlen(m.mtext),0) < 0){
					 perror("msgsnd");
					 exit(1);
				 }
				 if(strncmp(m.mtext,"quit",4) == 0)
					 break;
       }

	    return 0;
}
