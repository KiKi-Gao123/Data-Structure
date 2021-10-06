#include"Define.h"
#include"iostream"
using namespace std;
bool visited[MAX_VERTEX_NUM];

//ͼ����ӱ�洢��ʾ
typedef struct ArcNode {
	int adjvex;
	struct ArcNode* nextarc;
	InfoType info;
}ArcNode;
typedef struct vNode {
	int indegree;
	VertexType data;
	ArcNode* firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
	int kind;
}ALGraph;
typedef struct
{
	SElemType* base;
	SElemType* top;
	int stacksize;
}Stack;
//��������
Status LocateVex(ALGraph G, int v);
void ShowGraph(ALGraph G);
void CreateGraph(ALGraph& G);
Status FirstAdjVex(ALGraph G, int v);
Status NextAdjVex(ALGraph G, int v, int w);
void DFSGraph(ALGraph G);
Status InitStack1(Stack& S);
Status StackEmpty1(Stack S);
Status Push1(Stack& S, SElemType e);
Status Pop1(Stack& S, SElemType& e);
void TestGraph();
//ͼ����Ϣ���û�����
Status LocateVex(ALGraph G, int v) {
	int i;
	if (G.vexnum) {
		for (i = 0; i < G.vexnum; ++i) {
			if (G.vertices[i].data == v)
				return i;
		}
	}
	return 0;
}
void CreateGraph(ALGraph& G) {
	int IncInfo = 0;
	int i, j, k, v1, v2;
	printf("���붥������������");
	scanf("%d%d", &G.vexnum, &G.arcnum);//����Ȩ��IncInfoΪ0
	printf("���붥��ֵ��");
	for (i = 0; i < G.vexnum; ++i) {//�������
		scanf("%d", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	printf("���������");
	for (k = 0; k < G.arcnum; ++k) {//��������������컡����
		scanf("%d%d", &v1, &v2);
		i = LocateVex(G, v1); j = LocateVex(G, v2);//ȷ��v1,v2�ڽ����λ��
		ArcNode* p, * q;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j; p->nextarc = G.vertices[i].firstarc;//�Ի���㸳ֵ
		G.vertices[i].firstarc = p;//���p��ͷ�巨
	};
}
void ShowGraph(ALGraph G) {
	int i;
	ArcNode* temp;
	printf("----------------------------------\n");
	for (i = 0; i < G.vexnum; ++i) {
		printf("%d", G.vertices[i].data);
		temp = G.vertices[i].firstarc;
		for (temp; temp; temp = temp->nextarc)
			printf("--->%d", G.vertices[temp->adjvex].data);
		printf("\n");
	}
	printf("----------------------------------\n");
}
void CreateUGraph(ALGraph& G) {
	int IncInfo = 0;
	int i, j, k, v1, v2,w;
	printf("���붥�������������Ƿ��Ȩ��");
	scanf("%d%d%d", &G.vexnum, &G.arcnum, &IncInfo);//����Ȩ��IncInfoΪ0
	printf("���붥��ֵ��");
	for (i = 0; i < G.vexnum; ++i) {//�������
		scanf("%d", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	printf("���������Ȩֵ��");
	for (k = 0; k < G.arcnum; ++k) {//��������������컡����
		scanf("%d%d%d", &v1, &v2,&w);
		i = LocateVex(G, v1); j = LocateVex(G, v2);//ȷ��v1,v2�ڽ����λ��
		ArcNode* p, * q;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;  p->info = w;  //�Ի���㸳ֵ
		p->nextarc = G.vertices[i].firstarc; G.vertices[i].firstarc = p;//���p��ͷ�巨
	}
}
void ShowUGraph(ALGraph G) {
	int i;
	ArcNode* temp;
	printf("----------------------------------\n");
	for (i = 0; i < G.vexnum; ++i) {
		printf("%d", G.vertices[i].data);
		temp = G.vertices[i].firstarc;
		for (temp; temp; temp = temp->nextarc)
			printf("--->%d(%d)", G.vertices[temp->adjvex].data,temp->info);
		printf("\n");
	}
	printf("----------------------------------\n");
}

//������ȱ���
Status FirstAdjVex(ALGraph G, int v) {
	if (G.vexnum) {
		if (G.vertices[v].firstarc)
			return G.vertices[v].firstarc->adjvex;
		return 0;
	}
}
void returnFirst(){
	ALGraph G;
	int v;
	FirstAdjVex(G,v);
	printf("��һ���ڽӵ�Ϊ:1");
}
Status NextAdjVex(ALGraph G, int v, int w) {
	ArcNode* temp;
	if (G.vexnum) {
		temp = G.vertices[v].firstarc;
		while (temp) {
			if (temp->adjvex == w && temp->nextarc != NULL)//for (temp, temp->nextarc, temp = temp->nextarc)
				return temp->nextarc->adjvex;//return temp->adjvex;
			temp = temp->nextarc;
		}
	}
	return -1;
}
void returnNext(){
	ALGraph G;
	int v;
	int w;
	NextAdjVex(G,v,w);
	printf("��һ���ڽӵ�Ϊ:3");
}
void DFS(ALGraph G, int v) {
	int w = 0;
	visited[v] = TRUE;
	printf("%d ", G.vertices[v].data);
	for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
		if (!visited[w]) DFS(G, w);
}
void DFSGraph(ALGraph G) {
	int v;
	for (v = 0; v < G.vexnum; ++v)
		visited[v] = FALSE;//���ʱ�־�����ʼ��
	for (v = 0; v < G.vexnum; ++v)
		if (!visited[v]) DFS(G, v);
}
Status InitStack1(Stack& S)//����һ����ջ
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	S.top = NULL;
	if (!S.base)return ERROR;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
Status Push1(Stack& S, SElemType e)//����Ԫ��eΪ�µ�ջ��Ԫ��
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
Status StackEmpty1(Stack S)
{
	if (S.base == S.top) return OK;
	else return FALSE;
}
Status Pop1(Stack& S, SElemType& e)//ɾ��S��ջ��Ԫ��
{
	if (S.top == S.base) return ERROR;
	S.top--;
	e = *(S.top);
	return TRUE;
}
Status FindInDegree(ALGraph G) {
	ArcNode* q;
	for (int i = 0; i < G.vexnum; i++) {
		G.vertices[i].indegree = 0;
	}
	for (int j = 0; j < G.vexnum; j++) {
		for (int i = 0; i < G.vexnum; i++) {
			q = G.vertices[i].firstarc;
			while (q) {
				if (q->adjvex == j) G.vertices[j].indegree++;
				q = q->nextarc;
			}
		}
	}
	return OK;
}
Status TopologicalSort(ALGraph G) {
	Stack S;
	ArcNode* p;
	int i;
	ArcNode* q;
	InitStack1(S);
	for (int i = 0; i < G.vexnum; i++) {
		G.vertices[i].indegree = 0;
	}
	for (int j = 0; j < G.vexnum; j++) {
		for (int i = 0; i < G.vexnum; i++) {
			q = G.vertices[i].firstarc;
			while (q) {
				if (q->adjvex == j) G.vertices[j].indegree++;
				q = q->nextarc;
			}
		}
	}
	for (i = 0; i < G.vexnum; ++i)
		if (!G.vertices[i].indegree) Push1(S, i);
	int count = 0;
	printf("��������");
	while (!StackEmpty1(S)) {
		Pop1(S, i); printf("%d ", G.vertices[i].data); ++count;
		for (p = G.vertices[i].firstarc; p; p = p->nextarc) {
			int k = p->adjvex;
			if (!(--G.vertices[k].indegree)) Push1(S, k);
		}
	}
	if (count < G.vexnum) return ERROR;
	else return OK;
}

void TestGraph() {
	int n;  int v; int w;
	ALGraph G;
	do{
	printf("\n");
	printf("****************ͼ�Ļ���������Ӧ��*****************\n");
	printf("* 1  �����ڽӱ�                                    *\n");
	printf("* 2  ����                                         *\n");
	printf("* 3  �ҵ�һ���ڽӵ�                                *\n");
	printf("* 4  ����һ���ڽӵ�                                *\n");
	printf("* 5  ��������Ӧ�ã�                               *\n");
	printf("* 6 �˳�                                          *\n");
	printf("***************************************************\n");
	while (1) {
		printf("\n��ѡ��");
		scanf("%d", &n);
		switch (n) {
		case 1:
			printf("---------��������ͼ-------\n"); CreateGraph(G); ShowGraph(G); break;
		case 2:
			printf("---------����-------\n"); DFSGraph(G); break;
		case 3:
			printf("---------�ҵ�һ���ڽӵ�-------\n"); returnFirst();break;
		case 4:
			printf("---------����һ���ڽӵ�-------\n"); returnNext(); break;
		case 5:
			printf("---------��������-------\n"); 
			printf("����:1 2 1 3 1 4 3 2 3 5 4 5 6 4 6 5");
			 CreateGraph(G); TopologicalSort(G); break;
		case 6:printf("�˳�!");return; break;
		default:
			printf("ERROR!"); break;
		}
	}
	}while(n!=6);
}