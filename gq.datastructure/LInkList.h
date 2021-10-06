#include"Define.h"
//���Ա�ĵ�����洢�ṹ 
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
}LNode, * LinkList; //LinkList�����������ͷָ��  LNode����������

int CreateList_LNode(LinkList& L, int n);  //����������
int ListInsert_Sq(LinkList& L, int i, ElemType e);//�ڵ�i��λ��֮ǰ��������Ԫ��e
int ListDelete_Sq(LinkList& L, int i, ElemType& e);//ɾ����i��Ԫ�ز���e����
int GetElem_L(LinkList L, int i, ElemType& e);//���ҵ�i��Ԫ�ص�ֵ
void Show(LinkList& L);//���������������Ԫ�ص�ֵ
void Destroy_L(LinkList& L);
//��������
int CreateList_LNode(LinkList& L, int n)//��λ������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L
{
	int i;
	LinkList p;
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;//����һ����ͷ���ĵ�����
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
	while (p && j < i - 1) { p = p->next; ++j; }//Ѱ�ҵ�i-1�����
	if (!p || j > i - 1) return ERROR;//iС��1���ߴ��ڱ���1
	LinkList s = (LinkList)malloc(sizeof(LNode));//�����½��
	s->data = e; s->next = p->next;//����L��
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
	if (!(p->next) || j > i - 1) return ERROR;//ɾ��λ�ò�����
	LinkList q = p->next; p->next = q->next;//ɾ�����ͷŽڵ�
	e = q->data; free(q);
	return OK;
}//ListDelete_Sq

int GetElem_L(LinkList L, int i, ElemType& e)
{
	LinkList p = L->next; int j = 1;//pָ���һ����㣬jΪ������
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

//ͨѶ¼
Status BookCreat(TeleBook &L);
Status BookInsert(TeleBook& L,int &i);//�����������Ա𣬵绰
Status BookDelete(TeleBook& L,int &i);//ɾ����i���˵���Ϣ
Status Search(TeleBook& L, char name[]);//���ҽС�÷�ӡ�����
void ShowBook(TeleBook L);//չʾͨѶ¼
void TestBook();

Status BookCreat(TeleBook& L)
{
	int i; int n = 0;
	printf("������ϵ�˸�����");
	scanf("%d",&n);
	TeleBook p;
	L = (TeleBook)malloc(sizeof(Linkman));
	L->next = NULL;//����һ����ͷ���ĵ�����
	printf("������ϵ���������Ա𣬵绰���ո�������룩��");
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
	while (p && j < i - 1) { p = p->next; ++j; }//Ѱ�ҵ�i-1�����
	if (!p || j > i - 1) return ERROR;//iС��1���ߴ��ڱ���1
	TeleBook s = (TeleBook)malloc(sizeof(Linkman));//�����½��
	printf("���������ϵ�˵��������Ա𣬵绰��");
	scanf("%s", s->data.name, sizeof(s->data.name));
	scanf("%s", s->data.sex, sizeof(s->data.sex));
	scanf("%s", s->data.phone, sizeof(s->data.phone));
	s->next = p->next;//����L��
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
	if (!(p->next) || j > i - 1) return ERROR;//ɾ��λ�ò�����
	TeleBook q = p->next; p->next = q->next;//ɾ�����ͷŽڵ�
	free(q);
	return OK;
}
Status Search(TeleBook& L, char name[]){
	TeleBook p = L->next;
	while (p){
		if (!abs(strcmp(p->data.name , name)))
		{
			printf("���ҵ��˵���ϢΪ��%s %s %s", p->data.name, p->data.sex, p->data.phone); break;
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
	printf("**************ͨѶ¼�Ļ���������Ӧ��***************\n");
	printf("* 1  ����                                         *\n");
	printf("* 2  ����                                         *\n");
	printf("* 3  ɾ��                                         *\n");
	printf("* 4  ����                                         *\n");
	printf("* 5  ��ʾ                                         *\n");
	printf("* 6  �˳�                                         *\n");
	printf("***************************************************\n");
	while (1)
	{
		printf("\n��ѡ��");
		scanf("%d", &s);
		switch (s)
		{
		case 1:BookCreat(L); break;
		case 2:printf("�������λ��"); scanf("%d",&i); BookInsert(L, i); break;
		case 3:printf("����ɾ��λ��"); scanf("%d", &i); BookDelete(L, i); break;
		case 4:printf("���������ҵ���ϵ�˵�������"); scanf("%s", name,10); Search(L, name); break;
		case 5:ShowBook(L); break;
		case 6: printf("�˳�"); return;break;
		default:
			printf("ERROR!"); break;
		}
	}
	}while (s!=6);		
}
//��������
void Test_LinkList()
{

	LinkList L;
	int choice;
	ElemType e;
	int i = 0, n = 0;
	L = NULL;
	do{
	printf("\n");
	printf("**************������Ļ���������Ӧ��***************\n");
	printf("* 1  ����                                         *\n");
	printf("* 2  ����                                         *\n");
	printf("* 3  ɾ��                                         *\n");
	printf("* 4  ����                                         *\n");
	printf("* 5  ��ʾ                                         *\n");
	printf("* 6  ͨѶ¼��Ӧ�ã�                               *\n");
	printf("* 7  �˳�                                         *\n");
	printf("***************************************************\n");
	while (1)
	{
		printf("\n��ѡ��");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:printf("����������Ԫ�ظ�����Ԫ��ֵ(�ո��������)��");
			scanf("%d", &n); CreateList_LNode(L, n); break;
		case 2:printf("���������λ���Ԫ��ֵ(���Ÿ�������)��");
			scanf("%d,%d", &i, &e); ListInsert_Sq(L, i, e); break;
		case 3:printf("������ɾ��Ԫ�ص�λ��");
			scanf("%d", &i); ListDelete_Sq(L, i, e); break;
		case 4:printf("����������ҵ�Ԫ��λ��");
			scanf("%d", &i); GetElem_L(L, i, e);
			printf("��%d��Ԫ��ֵΪ:%d\n", i, e); break;
		case 5:printf("��ʾ����:"); Show(L); break;
		case 6:printf("ͨѶ¼��\n"); TestBook(); break;
		case 7:printf("�˳�"); return ; break;
		}
	}
	}while (choice!=7);	
}
