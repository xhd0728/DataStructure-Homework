#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

typedef struct{
	int id;  //编号 
	int time;  //所需CPU时间 
	int submit;  //提交时间 
}node;

node T[N];  //结构体数组 
queue<node> Q; //队列 

bool cmp(const node &a, const node &b){
	return a.time < b.time;
}  //按所需执行时间递增排序 

bool cmp0(const node &a, const node &b){
	return a.submit < b.submit;
}  //按提交时间递增排序 

bool cmp1(const node &a, const node &b){
	if(a.time != b.time)
		return a.time < b.time;  //先执行所需cpu时间短的 
	else
		return a.submit < b.submit;  //若执行时间相同，则先执行先提交的 
}  //并不完美的SJF算法 

void c1(){
	int t = 0;//start time
	int sum = 0;
	int n;
	printf("请输入要处理的任务的数量：\n");
	scanf("%d", &n);
	printf("请输入每个任务的执行时间：\n");
	for(int i = 1;i <= n;++i){
		scanf("%d", &T[i].time);
		T[i].id = i;
	}
	for(int i = 1;i <= n;++i)
		Q.push(T[i]);
	while(!Q.empty()){
		printf("序号：%d, 开始时间:%d, 终止时间：%d, 等待时间：%d\n", 
		Q.front().id, t, t + Q.front().time, t);
		t += Q.front().time;
		sum += t;
		Q.pop();	
	}
	printf("所有任务的平均等待时间：%.2lf s\n", ((double)sum)/((double)n));
}

void c2(){
	int t = 0;//start time
	int n, sum = 0;
	printf("请输入要处理的任务的数量：\n");
	scanf("%d", &n);
	printf("请输入每个任务的执行时间：\n");
	for(int i = 1;i <= n;++i){
		scanf("%d", &T[i].time);
		T[i].id = i;
	}
	sort(T + 1, T + n + 1, cmp);
	for(int i = 1;i <= n;++i)
		Q.push(T[i]);
	while(!Q.empty()){
		printf("序号：%d, 开始时间:%d, 终止时间：%d, 等待时间：%d\n",
		Q.front().id, t, t + Q.front().time, t);
		t += Q.front().time;
		sum += t;
		Q.pop();
	}
	printf("所有任务的平均等待时间：%.2lf s\n", ((double)sum)/((double)n));
}

void c3(){
	int t = 0;//start time
	int sum = 0;
	int n, start, wait;
	printf("请输入要处理的任务的数量：\n");
	scanf("%d", &n);
	printf("请输入每个任务的提交时间和执行时间：\n");
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
		printf("序号：%d, 提交时间：%d，开始时间:%d, 终止时间：%d, 等待时间：%d\n",
			Q.front().id, Q.front().submit, start, start + Q.front().time, wait);
		sum += wait;
		Q.pop();
	}
	printf("所有任务的平均等待时间：%.2lf s\n", ((double)sum)/((double)n));
}

void c4(){
	int t = 0;//start time
	int sum = 0;
	int n, start, wait;
	printf("请输入要处理的任务的数量：\n");
	scanf("%d", &n);
	printf("请输入每个任务的提交时间和执行时间：\n");
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
		printf("序号：%d, 提交时间：%d，开始时间:%d, 终止时间：%d, 等待时间：%d\n",
			Q.front().id, Q.front().submit, start, start + Q.front().time, wait);
		sum += wait;
		Q.pop(); 
	}
	printf("所有任务的平均等待时间：%.2lf s\n", ((double)sum)/((double)n));
}

int main(){
	printf("请输入执行模式：\n");
	printf("1.各任务同时提交：\n");
	printf("2.各任务不同时提交：\n");
	int n;
	scanf("%d", &n);
	if(n == 1){
		printf("请输入执行模式：\n");
		printf("1.按提交顺序执行：\n");
		printf("2.按平均等待时间最短执行：\n");
		scanf("%d", &n);
		if(n == 1)
			c1();
		else if(n == 2)
			c2();
		else
			printf("输入错误！");
	}
	else if(n == 2){
		printf("请输入执行模式：\n");
		printf("1.按提交顺序执行：\n");
		printf("2.按平均等待时间最短执行：\n");
		scanf("%d", &n);
		if(n == 1)
			c3();
		else if(n == 2)
			c4();
		else
			printf("输入错误！");
	}
	else printf("输入错误！");
	return 0;
}
