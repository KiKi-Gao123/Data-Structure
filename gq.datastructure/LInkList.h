#include"Define.h"
//线性表的单链表存储结构 
typedef struct Content
{
	char name[20];
	char sex[MAX];
	char phone[MAX];
}Content;
typedef struct Linkman
{
	Content data;
	struct Linkman* next;
}Linkman,*TeleBook;
typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode, * LinkList; //LinkList常代表单链表的头指针  LNode常代表区块

int CreateList_LNode(LinkList& L, int n);  //创建新链表
int ListInsert_Sq(LinkList& L, int i, ElemType e);//在第i个位置之前插入数据元素e
int ListDelete_Sq(LinkList& L, int i, ElemType& e);//删除第i个元素并用e返回
int GetElem_L(LinkList L, int i, ElemType& e);//查找第i个元素的值
void Show(LinkList& L);//输出单链表中所有元素的值
void Destroy_L(LinkList& L);
//函数定义
int CreateList_LNode(LinkList& L, int n)//逆位序输入n个元素的值，建立带表头结点的单链线性表L
{
	int i;
	LinkList p;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;//建立一个带头结点的单链表
	for (i = n; i > 0; i--)
	{
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
	return OK;
}//CreateList L

int ListInsert_Sq(LinkList& L, int i, ElemType e)
{
	LinkList p = L; int j = 0;
	while (p && j < i - 1) { p = p->next; ++j; }//寻找第i-1个结点
	if (!p || j > i - 1) return ERROR;//i小于1或者大于表长加1
	LinkList s = (LinkList)malloc(sizeof(LNode));//生成新结点
	s->data = e; s->next = p->next;//插入L中
	p->next = s;
	return OK;
}//ListInsert_L

int ListDelete_Sq(LinkList& L, int i, ElemType& e)
{
	LinkList p = L;
	int j = 0;
	while (p->next && j < i - 1)
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1) return ERROR;//删除位置不合理
	LinkList q = p->next; p->next = q->next;//删除并释放节点
	e = q->data; free(q);
	return OK;
}//ListDelete_Sq

int GetElem_L(LinkList L, int i, ElemType& e)
{
	LinkList p = L->next; int j = 1;//p指向第一个结点，j为计数器
	while (p && j < i)
	{
		p = p->next; ++j;
	}
	if (!p || j > i) return ERROR;
	e = p->data;
	return OK;
}//GetElem_L
void Show(LinkList& L)
{
	LinkList p = L->next;
	while (p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
}//Show

void Destroy_L(LinkList& L)
{
	LinkList p = L->next;
	LinkList q = L->next;
	while (p)
	{
		p = p->next; free(q);
		q = p;
	}
	L = NULL;
}

//通讯录
Status BookCreat(TeleBook &L);
Status BookInsert(TeleBook& L,int &i);//插入姓名，性别，电话
Status BookDelete(TeleBook& L,int &i);//删除第i个人的信息
Status Search(TeleBook& L, char name[]);//查找叫“梅子”的人
void ShowBook(TeleBook L);//展示通讯录
void TestBook();

Status BookCreat(TeleBook& L)
{
	int i; int n = 0;
	printf("输入联系人个数：");
	scanf("%d",&n);
	TeleBook p;
	L = (TeleBook)malloc(sizeof(Linkman));
	L->next = NULL;//建立一个带头结点的单链表
	printf("输入联系人姓名，性别，电话（空格隔开输入）：");
	for (i = n; i > 0; i--)
	{
		p = (TeleBook)malloc(sizeof(Linkman));
		scanf("%s", p->data.name,sizeof(p->data.name));
		scanf("%s", p->data.sex, sizeof(p->data.sex));
		scanf("%s", p->data.phone, sizeof(p->data.phone));
		p->next = L->next;
		L->next = p;
	}
	return OK;
}
Status BookInsert(TeleBook& L, int& i) {

    TeleBook p = L; int j = 0;
	while (p && j < i - 1) { p = p->next; ++j; }//寻找第i-1个结点
	if (!p || j > i - 1) return ERROR;//i小于1或者大于表长加1
	TeleBook s = (TeleBook)malloc(sizeof(Linkman));//生成新结点
	printf("输入插入联系人的姓名，性别，电话：");
	scanf("%s", s->data.name, sizeof(s->data.name));
	scanf("%s", s->data.sex, sizeof(s->data.sex));
	scanf("%s", s->data.phone, sizeof(s->data.phone));
	s->next = p->next;//插入L中
	p->next = s;
	return OK;
}
Status BookDelete(TeleBook& L, int& i) {
	TeleBook p = L;
	int j = 0;
	while (p->next && j < i - 1)
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1) return ERROR;//删除位置不合理
	TeleBook q = p->next; p->next = q->next;//删除并释放节点
	free(q);
	return OK;
}
Status Search(TeleBook& L, char name[]){
	TeleBook p = L->next;
	while (p){
		if (!abs(strcmp(p->data.name , name)))
		{
			printf("查找的人的信息为：%s %s %s", p->data.name, p->data.sex, p->data.phone); break;
		}
		p = p->next;
	}
	return OK;
}
void ShowBook(TeleBook L) {
	TeleBook p = L->next;
	while (p)
	{
		printf("%s %s %s\n", p->data.name,p->data.sex,p->data.phone);
		p = p->next;
	}
}
void TestBook()
{
	TeleBook L; int s,n; int i = 0; char name[20] = { };
	L = NULL;
	do{
	printf("\n");
	printf("\n");
	printf("**************通讯录的基本操作及应用***************\n");
	printf("* 1  创建                                         *\n");
	printf("* 2  插入                                         *\n");
	printf("* 3  删除                                         *\n");
	printf("* 4  查找                                         *\n");
	printf("* 5  显示                                         *\n");
	printf("* 6  退出                                         *\n");
	printf("***************************************************\n");
	while (1)
	{
		printf("\n请选择：");
		scanf("%d", &s);
		switch (s)
		{
		case 1:BookCreat(L); break;
		case 2:printf("输入插入位序："); scanf("%d",&i); BookInsert(L, i); break;
		case 3:printf("输入删除位序："); scanf("%d", &i); BookDelete(L, i); break;
		case 4:printf("输入你想找的联系人的姓名："); scanf("%s", name,10); Search(L, name); break;
		case 5:ShowBook(L); break;
		case 6: printf("退出"); return;break;
		default:
			printf("ERROR!"); break;
		}
	}
	}while (s!=6);		
}
//函数测试
void Test_LinkList()
{

	LinkList L;
	int choice;
	ElemType e;
	int i = 0, n = 0;
	L = NULL;
	do{
	printf("\n");
	printf("**************单链表的基本操作及应用***************\n");
	printf("* 1  创建                                         *\n");
	printf("* 2  插入                                         *\n");
	printf("* 3  删除                                         *\n");
	printf("* 4  查找                                         *\n");
	printf("* 5  显示                                         *\n");
	printf("* 6  通讯录（应用）                               *\n");
	printf("* 7  退出                                         *\n");
	printf("***************************************************\n");
	while (1)
	{
		printf("\n请选择：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:printf("请输入链表元素个数和元素值(空格隔开输入)：");
			scanf("%d", &n); CreateList_LNode(L, n); break;
		case 2:printf("请输入插入位序和元素值(逗号隔开输入)：");
			scanf("%d,%d", &i, &e); ListInsert_Sq(L, i, e); break;
		case 3:printf("请输入删除元素的位序：");
			scanf("%d", &i); ListDelete_Sq(L, i, e); break;
		case 4:printf("请输入待查找的元素位序：");
			scanf("%d", &i); GetElem_L(L, i, e);
			printf("第%d个元素值为:%d\n", i, e); break;
		case 5:printf("显示链表:"); Show(L); break;
		case 6:printf("通讯录：\n"); TestBook(); break;
		case 7:printf("退出"); return ; break;
		}
	}
	}while (choice!=7);	
}
