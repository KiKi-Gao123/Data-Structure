#include"Define.h"
typedef struct BiTNode {
	TElemType data;
	struct BiTNode* rchild, * lchild;
}BiTNode, * BiTree;

Status InitBiTree(BiTree& T);
Status CreateBiTree(BiTree& T);
Status Preorder(BiTree T);
Status Inorder(BiTree T);
Status Postorder(BiTree T);
Status Tree_Depth(BiTree T);
Status Count_leaf(BiTree T);
void LeftChild(BiTree T, TElemType e);
void Parent(BiTree T, TElemType e);
void LeftSibling(BiTree T, TElemType e);

Status InitBiTree(BiTree& T) {
	T = NULL;
	return OK;
}
Status CreateBiTree(BiTree& T) {
	char c;
	scanf("%c", &c, 1);
	if (c == ' ') T = NULL;
	else {
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = c;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

Status Preorder(BiTree T) {
	if (T) {
		printf("%c", T->data);
		Preorder(T->lchild);
		Preorder(T->rchild);
	}
	return OK;
}
Status Inorder(BiTree T) {
	if (T) {
		Inorder(T->lchild);
		printf("%c", T->data);
		Inorder(T->rchild);
	}
	return OK;
}
Status Postorder(BiTree T) {
	if (T) {
		Postorder(T->lchild);
		Postorder(T->rchild);
		printf("%c", T->data);
	}
	return OK;
}
Status Tree_Depth(BiTree T) {
	int depth;
	int left;
	int right;
	if (!T) depth = 0;
	else if (!T->lchild && !T->rchild) depth = 1;
	else {
		left = Tree_Depth(T->lchild);
		right = Tree_Depth(T->rchild);
		depth = 1 + (left > right ? left : right);
	}
	return depth;
}
Status Count_leaf(BiTree T) {
	if (!T) return 0;
	if ((!T->lchild) && (!T->rchild)) return 1;
	else return (Count_leaf(T->lchild) + Count_leaf(T->rchild));
}

void LeftChild(BiTree T, TElemType e) {
	if (T) {
		if (T->data == e) {
			if (!T->lchild) printf("û�����ӣ�");
			if (T->lchild) printf("��Ԫ�ص�����Ϊ��%c", T->lchild->data);
		}
		LeftChild(T->lchild, e);
		LeftChild(T->rchild, e);
	}
}
void Parent(BiTree T, TElemType e) {
	if (T) {
		if ((T->lchild && T->lchild->data == e) || (T->rchild && T->rchild->data == e)) {
			printf("������ҵ�Ԫ�ص�˫�ף�%c", T->data);
			return;
		}
		Parent(T->lchild, e);
		Parent(T->rchild, e);
	}
}
void LeftSibling(BiTree T, TElemType e) {
	if (T) {
		if (T->lchild && T->lchild->data == e) printf("���ҵ�Ԫ��û�����ֵ�");
		if (T->rchild && T->rchild->data == e)
		{
			if (!T->lchild) printf("���ҵ�Ԫ��û�����ֵ�");
			else printf("���ҵ�Ԫ�ص����ֵ�Ϊ��%c", T->lchild->data);
			return;
		}
		LeftSibling(T->lchild, e);
		LeftSibling(T->rchild, e);
	}
}
void TestBiTree()
{
	int select;
	char e;
	int* w = NULL;
	char temp = 0;
  	BiTree T;
	InitBiTree(T);
	do{
	printf("\n");
	printf("**************�������Ļ���������Ӧ��***************\n");
	printf("* 1  ����������                                   *\n");
	printf("* 2  ��������������/��/��                       *\n");
	printf("* 3  �����������                                 *\n");
	printf("* 4  ����Ҷ�ӽ�����                             *\n");
	printf("* 5  ����˫��                                     *\n");
	printf("* 6  �������ֵ�                                     *\n");
	printf("* 7  Huffman���루Ӧ�ã�                          *\n");
	printf("* 8  �˳�\n");
	printf("***************************************************\n");
	while (1) {
		printf("\n----------------------------------------------------------------");
		printf("\n�������ѡ��");
		scanf("%d", &select);
		switch (select) {
		case 1:printf("���������������������(ABC__DE_G__F___):"); getchar(); CreateBiTree(T); break;
		case 2:printf("������������"); Preorder(T); printf("\n������������");Inorder(T);  printf("\n������������"); Postorder(T); break;
		case 3:printf("���ĸ߶ȣ�%d", Tree_Depth(T)); break;
		case 4:printf("Ҷ����Ŀ��%d", Count_leaf(T)); break;
		case 5:printf("����������ҵ�Ԫ�أ�"); scanf("%*c"); scanf("%c", &e, 1); Parent(T, e); break;
		case 6:printf("����������ҵ�Ԫ�أ�"); scanf("%*c"); scanf("%c", &e, 1); LeftSibling(T, e); break;
		case 8:printf("�˳�!");return; break;
		default:
			printf("ERROR!"); break;
		}
	}
	}while (select!=8);
}