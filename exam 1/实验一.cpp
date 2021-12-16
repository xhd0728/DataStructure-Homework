#include<cstdio>
#include<cstdlib>
 
typedef struct Node{
	int data;
	int passwd;
	struct Node *next;
	
}Node, *LinkList;//�������� 

void LinkList_Create(int n, LinkList &L){
	L = (LinkList)malloc(sizeof(Node));
	if(!L) exit(1);
	L->next = L;//����ѭ������ 
	L->data = 0;//��ʼ��ͷ����ֵ 
	LinkList p, q = L;
	int i;
	for(i = 1;i <= n;++i){
		p=(LinkList)malloc(sizeof(Node));
		p->data = i;//ÿ���˶�Ӧ����� 
		q->next = p;
		q = p;//�����㲢��ֵ 
	}
	q->next = L;
}//����ѭ������ 

void Calc(int m, LinkList &L){
	LinkList p = L, q;
	while(L->next->data != 0){
		int i = 1;
		while(i < m){//�ж�ָ���Ƿ񵽴�ͷ���
			if(p->next->data != 0){
				p = p->next;
				++i;
			}//����ǣ���ô�������ͷ��� 
			else
				p = p->next;//������ǣ������ 
		}
		if(p->next->data == 0) p = p->next;
		printf("%d ", p->next->data);
		q = p->next;
		p->next = p->next->next;
		free(q);//ɾ����Ȧ����
	}
}

int main(){
	int m, n;
	printf("���������������룺\n");
	scanf("%d%d", &n, &m);
	if(m <= 0 || n <= 0){ 
		printf("���벻�Ϸ���\n");
		return 0;
	}
	LinkList L;
	LinkList_Create(n, L);
	printf("���˳��");
	Calc(m, L);
	return 0;
}

