#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	char name[10];	  	 /*进程名*/
	int prio;     	  	 /*优先数*/
	int cputime;    	   /*占用cpu时间*/
	int needtime;    		 /*要求运行时间*/
	char state;      		 /*状态*/
	struct node *next;   /*指针*/
}PCB;

PCB *ready,*run,*finish;   /*就绪 执行 结束指针*/
int N;

void prt()  /*输出函数，可以方便看到进程执行的演示*/
{
   PCB *p;
   printf("   NAME  CPUTIME   NEEDTIME   PRIORITY   STATUS\n");
   if(run!=NULL)
		 printf("  %-10s%-10d%-10d%-10d %c\n",run->name,run->cputime,run->needtime,run->prio,run->state);   /*输出执行的进程的信息*/
   p=ready;  
   while(p!=NULL)      
   {
	 	 printf("  %-10s%-10d%-10d%-10d %c\n",p->name,p->cputime,p->needtime,p->prio,p->state);      /*输出就绪进程的信息*/
      p=p->next;
	 }
   p=finish;  
   while(p!=NULL)
   {
	 	 printf("  %-10s%-10d%-10d%-10d %c\n",p->name,p->cputime,p->needtime,p->prio,p->state);     /*输出结束队列的信息*/
      p=p->next;
 	 }
  getchar();	/*使用getchar()函数可以让输出时停留画面，等待人按回车继续*/
}

void insert(PCB *q)   /*插入新进程，把进程按优先数大小排序*/
{
	PCB *p1,*s,*r;
	int b;
	s=q;       	/*指针s指向新要插入的进程*/
	p1=ready;   /*指针p1指向原来的进程队列的队首*/
	r=p1;       /*指针r是指向p1前面的进程*/
	b=1;
	while((p1!=NULL)&&b)
		if(p1->prio>=s->prio) { r=p1; p1=p1->next; }   /*新进程的优先数小，则p1指向下一个进程继续比*/
		else b=0;
  if(r!=p1)  { r->next=s; s->next=p1; } 	/*新进程找到位置，插在r和p1之间*//*if s has the same priority as p1, then s will line up after p1, added by yangyb*/
  else { s->next=p1; ready=s; }    			  /*新进程的优先数最大，插在队首，并修改就绪队首ready指针*/
}

void create()
{
	PCB *p;
  int i;
	ready=NULL;
	run=NULL;
	finish=NULL;
	printf("Please enter the name and time and priority of PCB:\n");   
	/*输入进程名、needed time, priority*/
	for(i=0;i<N;i++)                                 
     {
		 	 p=malloc(sizeof(PCB));			   	/*为新进程开辟空间*/
			 scanf("%s",p->name); 			   	/*输入进程名*/
 			 scanf("%d",&(p->needtime));   	/*输入进程要求运行时间*/
 			 scanf("%d",&(p->prio));   			/*输入进程优先数*/

 			 p->cputime=0;      
 			 p->state='W';    /*表示就绪队列中未在队首先执行，但也是就绪状态*/
 			 if (ready!=NULL)  insert(p);   		/*就绪队首不为NULL，插入新进程*/
// 			 else { p->next=ready; ready=p; }		/*否则先插在NULL前, here p->next=ready=NULL?*/
 			 else { p->next=NULL; ready=p; }		/*否则先插在NULL前*/
	 	 }
	 printf("           Display is going to start:          \n");
	 printf("***********************************************\n");
	 prt();   
	 run=ready;   						/*队列排好，run指向就绪队列队首*/
	 ready=ready->next;      	/*ready指向下一个进程，这样当进程执行时如果优先数小于其他的进程，应该先进行优先数最大的进程*/
	 run->state='R';					/*队首进程的状态为就绪*/
}

void prio()
{
	while(run!=NULL)
	{   
		prt();
		run->cputime=run->cputime+1;  	/*运行一次cpu占用时间加一*/
		run->needtime=run->needtime-1;  /*运行一次要求运行时间减一*/
		run->prio=run->prio-1;    		/*运行一次优先数减一*/
		if(run->needtime==0)     				/*若要求运行时间为0时*/
		{   
			run->next=finish;        			/*退出队列*/
			finish=run;              			/*finish为结束进程的队列 */
			run->state='E';           		/*修改状态为结束*/
			run=NULL;             				/*释放run指针*/
			if (ready!=NULL)         			/*创建新就绪队列的头指针*/
			{ run=ready;  run->state='R';  ready=ready->next; } 
		}
		else if(run->needtime>=0)     	/*如果时间片到*/			
		{ 				
			if(ready!=NULL && (run->prio<run->next->prio))    						/*如就绪队列不空*/
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

int main(void)
{
	printf("Please enter the total number of PCB:\n");
  scanf("%d",&N);
  create();   /*模拟创建进程，并输入相关信息*/
  prio();

	return 0;
}   /*优先数调度算法*/
