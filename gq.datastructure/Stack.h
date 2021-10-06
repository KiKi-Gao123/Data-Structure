#include "Define.h"
//栈的顺序存储表示
typedef struct
{
	SElemType* base;//在栈构造之前和销毁之后，base的值为NULL
	SElemType* top;//栈顶指针
	int stacksize;//当前分配的存储空间
}SqStack;

//函数声明
Status InitStack(SqStack& S);
Status Push(SqStack& S, SElemType e);
Status Pop(SqStack& S, SElemType& e);
Status GetTop(SqStack S, SElemType& e);
Status GetTop(SqStack S);
Status Expression();

//1、实现顺序栈的基本操作：构造空栈、入栈、出栈、取栈顶元素。
Status InitStack(SqStack& S)//构造一个空栈
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	S.top = NULL;
	if (!S.base)return ERROR;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
Status Push(SqStack& S, SElemType e)//插入元素e为新的栈顶元素
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
Status Pop(SqStack& S, SElemType& e)//删除S的栈顶元素
{
	if (S.top == S.base) return ERROR;
	S.top--;
	e = *(S.top);
	return TRUE;
}
Status GetTop(SqStack S, SElemType& e)//用e返回S的栈顶元素（与pop不同的是，并不删除栈顶元素）
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
	InitStack(OPTR); Push(OPTR, '#');//运算符栈
	InitStack(OPND); printf("输入表达式(结尾加#)："); c = getchar();//运算数栈
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


//函数测试
void Stack_Test()
{
	int choice;
	SqStack S;
	InitStack(S);
	int e;
	int n;
	do{
	printf("\n");
	printf("****************栈的基本操作及应用*****************\n");
	printf("* 1  进栈                                         *\n");
	printf("* 2  出栈                                         *\n");
	printf("* 3  取栈顶元素                                   *\n");
	printf("* 4  表达式求解（应用）                           *\n");
	printf("* 5  退出                                         *\n");
	printf("***************************************************\n");
	while (1) {
		printf("\n输入你的选择:");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: printf("请输入入栈的元素:");
			scanf("%d", &e);
			if (Push(S, e))
			{
				printf("压栈成功！\n");
			}
			else { printf("压栈失败！\n"); }; break;
		case 2: Pop(S, e); printf("出栈的元素为:%d\n", e); break;
		case 3: if (GetTop(S, e)) { printf("得到栈顶元素为:%d\n", e); }
			  else(printf("没有栈顶元素！\n")); break;
		case 4:printf("%d\n",Expression()); break;
		case 5:printf("退出");return; break;
		default:
			printf("ERROR!"); break;
		}
	}
	}while(choice!=5);
}
