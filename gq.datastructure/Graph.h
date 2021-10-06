#include"Define.h"
#include"iostream"
using namespace std;
bool visited[MAX_VERTEX_NUM];

//图的领接表存储表示
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
//函数声明
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
//图的信息由用户输入
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
	printf("输入顶点数，弧数：");
	scanf("%d%d", &G.vexnum, &G.arcnum);//不带权，IncInfo为0
	printf("输入顶点值：");
	for (i = 0; i < G.vexnum; ++i) {//构造结点表
		scanf("%d", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	printf("输入各弧：");
	for (k = 0; k < G.arcnum; ++k) {//输入各弧，并构造弧链表
		scanf("%d%d", &v1, &v2);
		i = LocateVex(G, v1); j = LocateVex(G, v2);//确定v1,v2在结点表的位置
		ArcNode* p, * q;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j; p->nextarc = G.vertices[i].firstarc;//对弧结点赋值
		G.vertices[i].firstarc = p;//完成p的头插法
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
	printf("输入顶点数，弧数和是否带权：");
	scanf("%d%d%d", &G.vexnum, &G.arcnum, &IncInfo);//不带权，IncInfo为0
	printf("输入顶点值：");
	for (i = 0; i < G.vexnum; ++i) {//构造结点表
		scanf("%d", &G.vertices[i].data);
		G.vertices[i].firstarc = NULL;
	}
	printf("输入各弧及权值：");
	for (k = 0; k < G.arcnum; ++k) {//输入各弧，并构造弧链表
		scanf("%d%d%d", &v1, &v2,&w);
		i = LocateVex(G, v1); j = LocateVex(G, v2);//确定v1,v2在结点表的位置
		ArcNode* p, * q;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;  p->info = w;  //对弧结点赋值
		p->nextarc = G.vertices[i].firstarc; G.vertices[i].firstarc = p;//完成p的头插法
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

//深度优先遍历
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
	printf("第一个邻接点为:1");
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
	printf("下一个邻接点为:3");
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
		visited[v] = FALSE;//访问标志数组初始化
	for (v = 0; v < G.vexnum; ++v)
		if (!visited[v]) DFS(G, v);
}
Status InitStack1(Stack& S)//构造一个空栈
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	S.top = NULL;
	if (!S.base)return ERROR;
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
Status Push1(Stack& S, SElemType e)//插入元素e为新的栈顶元素
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
Status Pop1(Stack& S, SElemType& e)//删除S的栈顶元素
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
	printf("拓扑排序：");
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
	printf("****************图的基本操作及应用*****************\n");
	printf("* 1  创建邻接表                                    *\n");
	printf("* 2  遍历                                         *\n");
	printf("* 3  找第一个邻接点                                *\n");
	printf("* 4  找下一个邻接点                                *\n");
	printf("* 5  拓扑排序（应用）                               *\n");
	printf("* 6 退出                                          *\n");
	printf("***************************************************\n");
	while (1) {
		printf("\n请选择：");
		scanf("%d", &n);
		switch (n) {
		case 1:
			printf("---------创建无向图-------\n"); CreateGraph(G); ShowGraph(G); break;
		case 2:
			printf("---------遍历-------\n"); DFSGraph(G); break;
		case 3:
			printf("---------找第一个邻接点-------\n"); returnFirst();break;
		case 4:
			printf("---------找下一个邻接点-------\n"); returnNext(); break;
		case 5:
			printf("---------拓扑排序-------\n"); 
			printf("例如:1 2 1 3 1 4 3 2 3 5 4 5 6 4 6 5");
			 CreateGraph(G); TopologicalSort(G); break;
		case 6:printf("退出!");return; break;
		default:
			printf("ERROR!"); break;
		}
	}
	}while(n!=6);
}