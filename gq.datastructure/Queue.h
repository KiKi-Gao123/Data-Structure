#include"Define.h"
#include"iostream"
//存储结构 
struct queue{
	int data;
	struct queue *next;
};
int count=0;//计数 
struct queue front;
struct queue *newp;
struct queue *rear;

//进队列 
void pushqueue()
{
	if(count==0)
	{
	front.next=NULL;
	rear=&front;
	}
	printf("请输入要进队的新数据：");
	newp=(struct queue *)malloc(sizeof(struct queue));
	count++;
	scanf("%d",&newp->data);
	rear->next=newp;
	newp->next=NULL;
	rear=newp;
	printf("%d进队操作成功！\n",newp->data); 
	
}

//展示所有数据 
void showdata()
{
	if(count==0)
	printf("目前队列为空！\n");
	else
	{
	struct queue *searchp; 
	printf("队列中全部数据为：");
	searchp=front.next;
	printf("front->（");
	while(searchp!=NULL)
	{
		printf(" %d",searchp->data);
		searchp=searchp->next;
	}
	printf("）<-rear\n");
	printf("显示操作成功！\n");
	}
}

//出队 
void popqueue()
{
	if(count==0)
	printf("目前队列为空！\n");
	else
	{
	struct queue *searchp;
	searchp=front.next;
	printf("出队数据为：%d\n",searchp->data);
	front.next=searchp->next;
	count--;
	free(searchp);
	printf("出队操作成功！\n");
	}
}

//取队头 
void readFront()
{
	if(count==0)
	printf("目前队列为空！\n");
	else
	{
	printf("队头的数据为：%d\n",front.next->data);
	printf("读取操作成功！\n");
	}
}

//取队尾 
void readRear()
{
	if(count==0)
	printf("目前队列为空！\n");
	else
	{
	printf("队尾的数据为：%d\n",front.next->data);
	printf("读取操作成功！\n");
	}
}


//队列 
void Queue(){ 
int n;
do{
printf("\n");
printf("*************队列的基本操作及应用**************\n");
printf("* 1  入列                                     *\n");
printf("* 2  出列                                     *\n");
printf("* 3  取队头元素                               *\n");
printf("* 4  取队尾元素                               *\n");
printf("* 5  应用                                     *\n");
printf("* 6  退出                                     *\n");
printf("***********************************************\n");
printf("请选择：");
scanf("%d",&n);
switch(n){
		case 1:
			pushqueue();
			break;
		case 2:
			popqueue();
			break;
		case 3:
			readFront();
			break;
		case 4:
			readRear(); 
			break;
		case 5:
			break;
		case 6:
			printf("退出"); 
			return;
			break;
		default:
			printf("输入错误!");
			break;
		}
	}
	while(n!=6);
}
