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
	printf("*******************�㷨�����ݽṹ******************\n");
	printf("* 1  ������Ļ���������Ӧ��                       *\n");
	printf("* 2  ջ�Ļ���������Ӧ��                           *\n");
	printf("* 3  ���еĻ���������Ӧ��                         *\n");
	printf("* 4  ���Ļ���������Ӧ��                           *\n");
	printf("* 5  ͼ�Ļ���������Ӧ��                           *\n");
	printf("* 6  �˳�                                         *\n");
	printf("***************************************************\n");
	printf("��ѡ��");
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