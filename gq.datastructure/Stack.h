#include "Define.h"
//ջ��˳��洢��ʾ
typedef struct
{
	SElemType* base;//��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType* top;//ջ��ָ��
	int stacksize;//��ǰ����Ĵ洢�ռ�
}SqStack;

//��������
Status InitStack(SqStack& S);
Status Push(SqStack& S, SElemType e);
Status Pop(SqStack& S, SElemType& e);
Status GetTop(SqStack S, SElemType& e);
Status GetTop(SqStack S);
Status Expression();

//1��ʵ��˳��ջ�Ļ��������������ջ����ջ����ջ��ȡջ��Ԫ�ء�
Status InitStack(SqStack& S)//����һ����ջ
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	S.top = NULL;
	if (!S.base)return ERROR;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
Status Push(SqStack& S, SElemType e)//����Ԫ��eΪ�µ�ջ��Ԫ��
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	};
	*S.top = e;
	S.top++;//*S.top++=e
	return OK;
}
Status Pop(SqStack& S, SElemType& e)//ɾ��S��ջ��Ԫ��
{
	if (S.top == S.base) return ERROR;
	S.top--;
	e = *(S.top);
	return TRUE;
}
Status GetTop(SqStack S, SElemType& e)//��e����S��ջ��Ԫ�أ���pop��ͬ���ǣ�����ɾ��ջ��Ԫ�أ�
{
	if (S.top == S.base)return ERROR;
	e = *(S.top - 1);
	return TRUE;
}

Status StackEmpty(SqStack S)
{
	if (S.base == S.top) return OK;
	else return FALSE;
}
Status GetTop(SqStack S)
{
	int e;
	if (S.top == S.base)return ERROR;
	e = *(S.top - 1);
	return e;
}
Status In(TElemType c) {
	int i;
	char operators[7] = { '+','-','*','/','(',')','#' };
	for (i = 0; i <=6; ++i) {
		if (operators[i] == c) return OK;
	}
	return 0;
}
char Precede(char c2,char c) {
	int i=0,j=0;
	char operators[7] = { '+','-','*','/','(',')','#' };
	char r[7][7] = { 
		'>','>','<','<','<','>','>',
	    '>','>','<','<','<','>','>',
    	'>','>','>','>','<','>','>',
		'>','>','>','>','<','>','>',
		'<','<','<','<','<','=',' ',
		'>','>','>','>',' ','>','>',
		'<','<','<','<','<',' ','=' 
	};
	while (i<7) {
		if (operators[i] == c2) break;
		i++;
	}
	while (i<7) {
		if (operators[j] == c); break;
		j++;
	}
	return r[i][j];
}
float Operate(int a, char theta, int b) {
	 float r=0;
	 switch (theta) {
	 case '+':r = a + b; break;
	 case '-': r = a - b; break;
	 case '*': r = a * b; break;
	 case '/': r = 1.0 * a / b; break; 
	 }
	 return r;
}
Status Expression(){	
	SqStack OPND, OPTR; char theta=NULL; int x,t; int b, a;
	char c;
	InitStack(OPTR); Push(OPTR, '#');//�����ջ
	InitStack(OPND); printf("������ʽ(��β��#)��"); c = getchar();//������ջ
	while (c != '#' || GetTop(OPTR) != 35) {
		if (!In(c)) {
			Push(OPND, c-'0'); c = getchar();
		}
		else 
			switch (Precede(GetTop(OPTR), c)) {
			case'<':Push(OPTR, c); c = getchar(); break;
			case'=':Pop(OPTR, x); c = getchar(); break;
			case'>':Pop(OPTR,t);
				theta = t;
				Pop(OPND, b); Pop(OPND, a);
				Push(OPND, Operate(a, theta, b));
				break;
		    }
	}
	return GetTop(OPND);
}


//��������
void Stack_Test()
{
	int choice;
	SqStack S;
	InitStack(S);
	int e;
	int n;
	do{
	printf("\n");
	printf("****************ջ�Ļ���������Ӧ��*****************\n");
	printf("* 1  ��ջ                                         *\n");
	printf("* 2  ��ջ                                         *\n");
	printf("* 3  ȡջ��Ԫ��                                   *\n");
	printf("* 4  ���ʽ��⣨Ӧ�ã�                           *\n");
	printf("* 5  �˳�                                         *\n");
	printf("***************************************************\n");
	while (1) {
		printf("\n�������ѡ��:");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: printf("��������ջ��Ԫ��:");
			scanf("%d", &e);
			if (Push(S, e))
			{
				printf("ѹջ�ɹ���\n");
			}
			else { printf("ѹջʧ�ܣ�\n"); }; break;
		case 2: Pop(S, e); printf("��ջ��Ԫ��Ϊ:%d\n", e); break;
		case 3: if (GetTop(S, e)) { printf("�õ�ջ��Ԫ��Ϊ:%d\n", e); }
			  else(printf("û��ջ��Ԫ�أ�\n")); break;
		case 4:printf("%d\n",Expression()); break;
		case 5:printf("�˳�");return; break;
		default:
			printf("ERROR!"); break;
		}
	}
	}while(choice!=5);
}
