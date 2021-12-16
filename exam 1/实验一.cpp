#include<cstdio>
#include<cstdlib>
 
typedef struct Node{
	int data;
	int passwd;
	struct Node *next;
	
}Node, *LinkList;//定义链表 

void LinkList_Create(int n, LinkList &L){
	L = (LinkList)malloc(sizeof(Node));
	if(!L) exit(1);
	L->next = L;//构造循环链表 
	L->data = 0;//初始化头结点的值 
	LinkList p, q = L;
	int i;
	for(i = 1;i <= n;++i){
		p=(LinkList)malloc(sizeof(Node));
		p->data = i;//每个人对应的序号 
		q->next = p;
		q = p;//插入结点并赋值 
	}
	q->next = L;
}//建立循环链表 

void Calc(int m, LinkList &L){
	LinkList p = L, q;
	while(L->next->data != 0){
		int i = 1;
		while(i < m){//判断指针是否到达头结点
			if(p->next->data != 0){
				p = p->next;
				++i;
			}//如果是，那么跳过这个头结点 
			else
				p = p->next;//如果不是，则继续 
		}
		if(p->next->data == 0) p = p->next;
		printf("%d ", p->next->data);
		q = p->next;
		p->next = p->next->next;
		free(q);//删除出圈的人
	}
}

int main(){
	int m, n;
	printf("请输入人数和密码：\n");
	scanf("%d%d", &n, &m);
	if(m <= 0 || n <= 0){ 
		printf("输入不合法！\n");
		return 0;
	}
	LinkList L;
	LinkList_Create(n, L);
	printf("输出顺序：");
	Calc(m, L);
	return 0;
}

