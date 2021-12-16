#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

typedef struct{
	int id;  //��� 
	int time;  //����CPUʱ�� 
	int submit;  //�ύʱ�� 
}node;

node T[N];  //�ṹ������ 
queue<node> Q; //���� 

bool cmp(const node &a, const node &b){
	return a.time < b.time;
}  //������ִ��ʱ��������� 

bool cmp0(const node &a, const node &b){
	return a.submit < b.submit;
}  //���ύʱ��������� 

bool cmp1(const node &a, const node &b){
	if(a.time != b.time)
		return a.time < b.time;  //��ִ������cpuʱ��̵� 
	else
		return a.submit < b.submit;  //��ִ��ʱ����ͬ������ִ�����ύ�� 
}  //����������SJF�㷨 

void c1(){
	int t = 0;//start time
	int sum = 0;
	int n;
	printf("������Ҫ����������������\n");
	scanf("%d", &n);
	printf("������ÿ�������ִ��ʱ�䣺\n");
	for(int i = 1;i <= n;++i){
		scanf("%d", &T[i].time);
		T[i].id = i;
	}
	for(int i = 1;i <= n;++i)
		Q.push(T[i]);
	while(!Q.empty()){
		printf("��ţ�%d, ��ʼʱ��:%d, ��ֹʱ�䣺%d, �ȴ�ʱ�䣺%d\n", 
		Q.front().id, t, t + Q.front().time, t);
		t += Q.front().time;
		sum += t;
		Q.pop();	
	}
	printf("���������ƽ���ȴ�ʱ�䣺%.2lf s\n", ((double)sum)/((double)n));
}

void c2(){
	int t = 0;//start time
	int n, sum = 0;
	printf("������Ҫ����������������\n");
	scanf("%d", &n);
	printf("������ÿ�������ִ��ʱ�䣺\n");
	for(int i = 1;i <= n;++i){
		scanf("%d", &T[i].time);
		T[i].id = i;
	}
	sort(T + 1, T + n + 1, cmp);
	for(int i = 1;i <= n;++i)
		Q.push(T[i]);
	while(!Q.empty()){
		printf("��ţ�%d, ��ʼʱ��:%d, ��ֹʱ�䣺%d, �ȴ�ʱ�䣺%d\n",
		Q.front().id, t, t + Q.front().time, t);
		t += Q.front().time;
		sum += t;
		Q.pop();
	}
	printf("���������ƽ���ȴ�ʱ�䣺%.2lf s\n", ((double)sum)/((double)n));
}

void c3(){
	int t = 0;//start time
	int sum = 0;
	int n, start, wait;
	printf("������Ҫ����������������\n");
	scanf("%d", &n);
	printf("������ÿ��������ύʱ���ִ��ʱ�䣺\n");
	for(int i = 1;i <= n;++i){
		scanf("%d%d", &T[i].submit, &T[i].time);
		T[i].id = i;
	}
	sort(T + 1, T + 1 + n, cmp0);
	for(int i = 1;i <= n;++i) Q.push(T[i]);
	while(!Q.empty()){
		if(Q.front().submit < t) 
			start = t;
		else
			start = Q.front().submit;
		t = start + Q.front().time;
		wait = start - Q.front().submit;
		printf("��ţ�%d, �ύʱ�䣺%d����ʼʱ��:%d, ��ֹʱ�䣺%d, �ȴ�ʱ�䣺%d\n",
			Q.front().id, Q.front().submit, start, start + Q.front().time, wait);
		sum += wait;
		Q.pop();
	}
	printf("���������ƽ���ȴ�ʱ�䣺%.2lf s\n", ((double)sum)/((double)n));
}

void c4(){
	int t = 0;//start time
	int sum = 0;
	int n, start, wait;
	printf("������Ҫ����������������\n");
	scanf("%d", &n);
	printf("������ÿ��������ύʱ���ִ��ʱ�䣺\n");
	for(int i = 1;i <= n;++i){
		scanf("%d%d", &T[i].submit, &T[i].time);
		T[i].id = i;
	}
	sort(T + 1, T + 1 + n, cmp1);
	for(int i = 1;i <= n;++i)
		Q.push(T[i]);
	while(!Q.empty()){
		if(Q.front().submit < t) 
			start = t;
		else
			start = Q.front().submit;
		t = start + Q.front().time;
		wait = start - Q.front().submit;
		printf("��ţ�%d, �ύʱ�䣺%d����ʼʱ��:%d, ��ֹʱ�䣺%d, �ȴ�ʱ�䣺%d\n",
			Q.front().id, Q.front().submit, start, start + Q.front().time, wait);
		sum += wait;
		Q.pop(); 
	}
	printf("���������ƽ���ȴ�ʱ�䣺%.2lf s\n", ((double)sum)/((double)n));
}

int main(){
	printf("������ִ��ģʽ��\n");
	printf("1.������ͬʱ�ύ��\n");
	printf("2.������ͬʱ�ύ��\n");
	int n;
	scanf("%d", &n);
	if(n == 1){
		printf("������ִ��ģʽ��\n");
		printf("1.���ύ˳��ִ�У�\n");
		printf("2.��ƽ���ȴ�ʱ�����ִ�У�\n");
		scanf("%d", &n);
		if(n == 1)
			c1();
		else if(n == 2)
			c2();
		else
			printf("�������");
	}
	else if(n == 2){
		printf("������ִ��ģʽ��\n");
		printf("1.���ύ˳��ִ�У�\n");
		printf("2.��ƽ���ȴ�ʱ�����ִ�У�\n");
		scanf("%d", &n);
		if(n == 1)
			c3();
		else if(n == 2)
			c4();
		else
			printf("�������");
	}
	else printf("�������");
	return 0;
}
