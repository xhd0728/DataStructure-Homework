#include <iostream> 
#include <vector>
#include <cmath>

using namespace std;

const int N = 1000;//N的范围 
int X, Y;
int c;//船能承载的人数

struct node{
	int q[3];
};//三元组 

vector<node> s;
int q[N][3];
//用于存放搜索结点，q[][0]是左岸传教士人数
//q[][1]是左岸野蛮人人数，q[][2]是左岸船的数目
//q[][3]用于搜索中的父亲结点序号。
int ans = 0;

int op_num = 0;
int mv[N][2];//船 
int fx[N][N];

//安全状态：左岸中，传教士都在or都不在or传教士人数等于野人人数 
int is_safe(int state[3]){
	if((state[0] == 0 || state[0] == X || state[0] == state[1]) && (state[1] >= 0) && (state[1] <= Y)){
		return 1;
	}
	return 0;
}

//是否到达目标状态 
int is_success(int state[3]){
	if(state[0] == 0 && state[1] == 0)
		return 1;
	return 0;
}

//该状态是否已经访问过 
int vis(int state[3]){
	for(vector<node>::iterator it = s.begin(); it != s.end(); it++) 
		if((*it).q[0] == state[0] && (*it).q[1] == state[1] && (*it).q[2] == state[2])
			return 1;
	return 0;
}

//伪A*算法推到公式 
int f2(int state[3]){
	return state[0] + state[1] - c * state[2];
}

//找最小值 
int find_min(int cur){
	int min = 10000;
	int op = -1;
	for(int j = 0; j < op_num; j++){//分别考虑可能的动作
		if (fx[cur + 1][j] < min){
			min = fx[cur + 1][j];
			op = j;
		}
	}
	if(min == 10000)
		op = -1;
	return op;
}


//过河操作
int search(int cur){
	if(is_success(q[cur])){
		ans = cur;
		return 1;
	}
	int state[3];
	int j;
	//cout<<"第"<<cur<<"层搜索"<<endl;
	//获取当前搜索结点
	//cout<<"展开结点"<<cur<<":"<<q[cur][0]<<' '<<q[cur][1]<<' '<<q[cur][2]<<endl;
	if(q[cur][2]){//船在左边
		for(j = 0; j < op_num; j++){//分别考虑可能的动作
			state[0] = q[cur][0] - mv[j][0];
			state[1] = q[cur][1] - mv[j][1];
			state[2] = 0;//船到了右边
			fx[cur + 1][j] = f2(state);
		}
		j = find_min(cur);
		while(j != -1){
			fx[cur + 1][j] = 10000;
			state[0] = q[cur][0] - mv[j][0];
			state[1] = q[cur][1] - mv[j][1];
			state[2] = 0;//船到了右边
			if(is_safe(state) && !vis(state)){//如果是安全状态//判断与之前展开结点是否相同
				node nd;
				nd.q[0] = q[cur + 1][0] = state[0];
				nd.q[1] = q[cur + 1][1] = state[1];
				nd.q[2] = q[cur + 1][2] = state[2];
				s.push_back(nd);      
				if(search(cur + 1))
					return 1;
			}
			j = find_min(cur);
		}
	}
	else{    //船在右边
		for(j = 0; j < op_num; j++){//分别考虑可能的动作
			state[0] = q[cur][0] + mv[j][0];
			state[1] = q[cur][1] + mv[j][1];
			state[2] = 1;
			fx[cur + 1][j] = f2(state);
		}
		j = find_min(cur);
		while(j != -1){
			fx[cur + 1][j] = 10000;
			state[0] = q[cur][0] + mv[j][0];
			state[1] = q[cur][1] + mv[j][1];
			state[2] = 1; //船回到左边
			if(is_safe(state) && !vis(state)){//如果是安全状态且与之间状态不同
				node nd;
				nd.q[0] = q[cur + 1][0] = state[0];
			 	nd.q[1] = q[cur + 1][1] = state[1];
				nd.q[2] = q[cur + 1][2] = state[2];
				s.push_back(nd);
				if(search(cur + 1))
					return 1;
			}
			j = find_min(cur);
		}
	}
	return 0;
}

int main(){
	int n;
	cout << "请输入N：";
	cin >> n;
	cout << "请输入C：";
	cin >> c;
	X = Y = n;
	int state[3]; //初始状态 
	node nd;
	nd.q[0] = state[0] = q[0][0] = X;
	nd.q[1] = state[1] = q[0][1] = Y;
	nd.q[2] = state[2] = q[0][2] = 1;
	s.push_back(nd); //初始化操作
	cout << "合法的操作组有：" << endl;
	for(int i = 1; i <= c; i++)
		for(int j = 0; j <= i; j++){
			if(j >= i - j || j == 0){
				mv[op_num][0] = j;
				mv[op_num][1] = i - j;
				cout << mv[op_num][0] << ' ' << mv[op_num][1] << endl;
				op_num++;
			}
		}
	cout << endl;
	if(!search(0)){
		cout << "无解" << endl;
		return 0;
	}
	cout << "解决办法为:" << endl;
	cout << endl; 
	for(int i = 0; i <= ans; i++){
		if(i > 0){
			cout << abs(q[i][0] - q[i - 1][0]) << "个传教士和" << abs(q[i][1] - q[i - 1][1]) << "个野人";
			if (q[i][2])
				cout << "从右岸乘船至左岸" << endl;
			else
				cout << "从左岸乘船至右岸" << endl;
			cout << "左岸有" << q[i][0] << "个传教士和" << q[i][1] << "个野人" << endl;
			cout << "右岸有" << n - q[i][0] << "个传教士和" << n - q[i][1] << "个野人" << endl << endl;
		}
	}
	cout << "最短移动次数：" << ans << endl;
	return 0;
}

