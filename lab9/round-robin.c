#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{	
	char name[10];   		/*进程名*/
	int count;         	/*计数器，判断是否=时间片的大小*/
	int cputime;       	/*占用cpu时间*/
	int needtime;     	/*要求运行时间*/
	char state;        	/*状态*/
	struct node *next;  /*指针*/
}PCB;

PCB *ready,*run,*finish,*tail;   /*就绪 执行 结束 尾指针*/
int N,round;

void prt()  /*输出函数，可以方便看到进程执行的演示*/
{	
	PCB *p;
	printf("   NAME  CPUTIME   NEEDTIME   COUNT   STATUS\n");
	if(run!=NULL)
		printf("  %-10s%-10d%-10d%-10d %c\n",run->name,run->cputime,run->needtime,run->count,run->state);   /*输出执行的进程的信息*/
	p=ready;
	while(p!=NULL)      
	{
		printf("  %-10s%-10d%-10d%-10d %c\n",p->name,p->cputime,p->needtime,p->count,p->state);      				/*输出就绪进程的信息*/
		p=p->next;
	}
	p=finish;  
	while(p!=NULL)
	{
		printf("  %-10s%-10d%-10d%-10d %c\n",p->name,p->cputime,p->needtime,p->count,p->state);     				/*输出结束队列的信息*/
		p=p->next;
	}
	getchar();  /*使用getchar()函数可以让输出时停留画面，等待人按回车继续*/
}

void insert(PCB *q)    /*在队尾插入新的进程*/
{ 	
	tail->next=q;  
	tail=q;   
	q->next=NULL; 
}

void create()                                   
{   
	PCB *p;
	int i;
	ready=NULL;   run=NULL;   finish=NULL;
	printf("Please enter the name and time of PCB:\n");   
	/*输入进程名、和*/
	for(i=0;i<N;i++)                                 
	{  
		p=malloc(sizeof(PCB));   			/*为新进程开辟空间*/
		scanf("%s",p->name);     			/*输入进程名*/
		scanf("%d",&(p->needtime));   /*输入进程要求运行时间*/
		p->cputime=0;      
		p->state='W';    /*表示就绪队列中未在队首先执行，但也是就绪状态*/
		if (ready!=NULL)  insert(p);   /*就绪队首不为NULL，插入新进程*/
		else {
			ready=p;
			tail=p; 
			tail->next=NULL;
		}  
	}      
		printf("           Display is going to start:          \n");
		printf("***********************************************\n");
		run=ready;   /*队列排好，run指向就绪队列队首*/
		ready=ready->next;      /*ready指向下一个进程*/
		run->state='R'; 
}   /*队首进程的状态为就绪*/

void count()
{  
	while(run!=NULL)
	{   
		prt();
		run->cputime=run->cputime+1;  	/*运行一次cpu占用时间加一*/
		run->needtime=run->needtime-1;  /*运行一次要求运行时间减一*/
		run->count=run->count+1;    		/*运行一次计数器加一*/
		if(run->needtime==0)     				/*若要求运行时间为0时*/
		{   
			run->next=finish;        			/*退出队列*/
			finish=run;              			/*finish为结束进程的队列 */
			run->state='E';           		/*修改状态为结束*/
			run=NULL;             				/*释放run指针*/
			if (ready!=NULL)         			/*创建新就绪队列的头指针*/
			{ run=ready;  run->state='R';  ready=ready->next; } 
		}
		else if(run->count==round)     	/*如果时间片到*/			
		{ 				
			run->count=0;  								/*计数器置0*/
			if(ready!=NULL)    						/*如就绪队列不空*/
			{ 
				run->state='W';    
				insert(run);   							/*在进程队列中重新插入原来的队首进程*/
				run=ready;      						/*重新置就绪队列的头指针*/
				run->state='R';
				ready=ready->next;  
			}
		}
	}
	prt();
}

int main()
{  
	printf("Please enter the total number of PCB:\n");
	scanf("%d",&N);
	printf("Please enter the timeround(don't be too big,1 or 2 is best):\n");  
	scanf("%d",&round);   					/*输入时间片的大小，不应太大*/
	create();   										/*模拟创建进程，并输入相关信息*/
	count();  
	return 0;
}   /*round-robin调度算法*/

