#include"Define.h"
#include"iostream"
//�洢�ṹ 
struct queue{
	int data;
	struct queue *next;
};
int count=0;//���� 
struct queue front;
struct queue *newp;
struct queue *rear;

//������ 
void pushqueue()
{
	if(count==0)
	{
	front.next=NULL;
	rear=&front;
	}
	printf("������Ҫ���ӵ������ݣ�");
	newp=(struct queue *)malloc(sizeof(struct queue));
	count++;
	scanf("%d",&newp->data);
	rear->next=newp;
	newp->next=NULL;
	rear=newp;
	printf("%d���Ӳ����ɹ���\n",newp->data); 
	
}

//չʾ�������� 
void showdata()
{
	if(count==0)
	printf("Ŀǰ����Ϊ�գ�\n");
	else
	{
	struct queue *searchp; 
	printf("������ȫ������Ϊ��");
	searchp=front.next;
	printf("front->��");
	while(searchp!=NULL)
	{
		printf(" %d",searchp->data);
		searchp=searchp->next;
	}
	printf("��<-rear\n");
	printf("��ʾ�����ɹ���\n");
	}
}

//���� 
void popqueue()
{
	if(count==0)
	printf("Ŀǰ����Ϊ�գ�\n");
	else
	{
	struct queue *searchp;
	searchp=front.next;
	printf("��������Ϊ��%d\n",searchp->data);
	front.next=searchp->next;
	count--;
	free(searchp);
	printf("���Ӳ����ɹ���\n");
	}
}

//ȡ��ͷ 
void readFront()
{
	if(count==0)
	printf("Ŀǰ����Ϊ�գ�\n");
	else
	{
	printf("��ͷ������Ϊ��%d\n",front.next->data);
	printf("��ȡ�����ɹ���\n");
	}
}

//ȡ��β 
void readRear()
{
	if(count==0)
	printf("Ŀǰ����Ϊ�գ�\n");
	else
	{
	printf("��β������Ϊ��%d\n",front.next->data);
	printf("��ȡ�����ɹ���\n");
	}
}


//���� 
void Queue(){ 
int n;
do{
printf("\n");
printf("*************���еĻ���������Ӧ��**************\n");
printf("* 1  ����                                     *\n");
printf("* 2  ����                                     *\n");
printf("* 3  ȡ��ͷԪ��                               *\n");
printf("* 4  ȡ��βԪ��                               *\n");
printf("* 5  Ӧ��                                     *\n");
printf("* 6  �˳�                                     *\n");
printf("***********************************************\n");
printf("��ѡ��");
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
			printf("�˳�"); 
			return;
			break;
		default:
			printf("�������!");
			break;
		}
	}
	while(n!=6);
}
