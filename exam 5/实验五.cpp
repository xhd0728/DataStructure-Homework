#include <iostream> 
#include <vector>
#include <cmath>

using namespace std;

const int N = 1000;//N�ķ�Χ 
int X, Y;
int c;//���ܳ��ص�����

struct node{
	int q[3];
};//��Ԫ�� 

vector<node> s;
int q[N][3];
//���ڴ��������㣬q[][0]���󰶴���ʿ����
//q[][1]����Ұ����������q[][2]���󰶴�����Ŀ
//q[][3]���������еĸ��׽����š�
int ans = 0;

int op_num = 0;
int mv[N][2];//�� 
int fx[N][N];

//��ȫ״̬�����У�����ʿ����or������or����ʿ��������Ұ������ 
int is_safe(int state[3]){
	if((state[0] == 0 || state[0] == X || state[0] == state[1]) && (state[1] >= 0) && (state[1] <= Y)){
		return 1;
	}
	return 0;
}

//�Ƿ񵽴�Ŀ��״̬ 
int is_success(int state[3]){
	if(state[0] == 0 && state[1] == 0)
		return 1;
	return 0;
}

//��״̬�Ƿ��Ѿ����ʹ� 
int vis(int state[3]){
	for(vector<node>::iterator it = s.begin(); it != s.end(); it++) 
		if((*it).q[0] == state[0] && (*it).q[1] == state[1] && (*it).q[2] == state[2])
			return 1;
	return 0;
}

//αA*�㷨�Ƶ���ʽ 
int f2(int state[3]){
	return state[0] + state[1] - c * state[2];
}

//����Сֵ 
int find_min(int cur){
	int min = 10000;
	int op = -1;
	for(int j = 0; j < op_num; j++){//�ֱ��ǿ��ܵĶ���
		if (fx[cur + 1][j] < min){
			min = fx[cur + 1][j];
			op = j;
		}
	}
	if(min == 10000)
		op = -1;
	return op;
}


//���Ӳ���
int search(int cur){
	if(is_success(q[cur])){
		ans = cur;
		return 1;
	}
	int state[3];
	int j;
	//cout<<"��"<<cur<<"������"<<endl;
	//��ȡ��ǰ�������
	//cout<<"չ�����"<<cur<<":"<<q[cur][0]<<' '<<q[cur][1]<<' '<<q[cur][2]<<endl;
	if(q[cur][2]){//�������
		for(j = 0; j < op_num; j++){//�ֱ��ǿ��ܵĶ���
			state[0] = q[cur][0] - mv[j][0];
			state[1] = q[cur][1] - mv[j][1];
			state[2] = 0;//�������ұ�
			fx[cur + 1][j] = f2(state);
		}
		j = find_min(cur);
		while(j != -1){
			fx[cur + 1][j] = 10000;
			state[0] = q[cur][0] - mv[j][0];
			state[1] = q[cur][1] - mv[j][1];
			state[2] = 0;//�������ұ�
			if(is_safe(state) && !vis(state)){//����ǰ�ȫ״̬//�ж���֮ǰչ������Ƿ���ͬ
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
	else{    //�����ұ�
		for(j = 0; j < op_num; j++){//�ֱ��ǿ��ܵĶ���
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
			state[2] = 1; //���ص����
			if(is_safe(state) && !vis(state)){//����ǰ�ȫ״̬����֮��״̬��ͬ
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
	cout << "������N��";
	cin >> n;
	cout << "������C��";
	cin >> c;
	X = Y = n;
	int state[3]; //��ʼ״̬ 
	node nd;
	nd.q[0] = state[0] = q[0][0] = X;
	nd.q[1] = state[1] = q[0][1] = Y;
	nd.q[2] = state[2] = q[0][2] = 1;
	s.push_back(nd); //��ʼ������
	cout << "�Ϸ��Ĳ������У�" << endl;
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
		cout << "�޽�" << endl;
		return 0;
	}
	cout << "����취Ϊ:" << endl;
	cout << endl; 
	for(int i = 0; i <= ans; i++){
		if(i > 0){
			cout << abs(q[i][0] - q[i - 1][0]) << "������ʿ��" << abs(q[i][1] - q[i - 1][1]) << "��Ұ��";
			if (q[i][2])
				cout << "���Ұ��˴�����" << endl;
			else
				cout << "���󰶳˴����Ұ�" << endl;
			cout << "����" << q[i][0] << "������ʿ��" << q[i][1] << "��Ұ��" << endl;
			cout << "�Ұ���" << n - q[i][0] << "������ʿ��" << n - q[i][1] << "��Ұ��" << endl << endl;
		}
	}
	cout << "����ƶ�������" << ans << endl;
	return 0;
}

