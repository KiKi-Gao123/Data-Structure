#include"LinkList.h"
#include"Stack.h"
#include"Queue.h"
#include"BiTree.h"
#include"Graph.h"
void ShowMainMenu() {

	int select; 
	do
	{
	printf("\n");
	printf("*******************算法与数据结构******************\n");
	printf("* 1  单链表的基本操作及应用                       *\n");
	printf("* 2  栈的基本操作及应用                           *\n");
	printf("* 3  队列的基本操作及应用                         *\n");
	printf("* 4  树的基本操作及应用                           *\n");
	printf("* 5  图的基本操作及应用                           *\n");
	printf("* 6  退出                                         *\n");
	printf("***************************************************\n");
	printf("请选择：");
	scanf("%d", &select);
	switch (select) {
	case 1:
		Test_LinkList(); break;
	case 2:
		Stack_Test(); break;
	case 3:
		Queue(); break;
	case 4:
		TestBiTree(); break;
	case 5:
		TestGraph(); break;
	case 6:exit(0); break;
	default:
		printf("ERROR!"); break;
	}
	} 	while (select!=6);
	
}
int main() {
	ShowMainMenu();
}