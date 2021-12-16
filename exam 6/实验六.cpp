#include<bits/stdc++.h>
using namespace std;
const int N = 30;
const int M = 1e6 + 10;
int arr[N];
int brr[N];
int a[M];
char hash_ans[M];
int sum = 1;//重复字符串计数器 
const int base = 127;//基底
const int mod = 842097523;//除留余数法模量

int calc_hash(char *s){
    int len = strlen(s);
    int ans = 0;
    for(int i = 0; i < len; ++i)
        ans = (ans * base + (int)s[i]) % mod;
    return ans;
}

void rand_arr(){
	for(int i = 0; i < N; ++i){
	int tmp;
		while(1){
			int flag = 0;
			tmp = rand() % N;
			for(int j = 0; j < i; ++j){
				if(tmp == arr[j]){
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				arr[i] = tmp;
				break;
			}
		}
		cout  << arr[i] << " ";
	}
	cout << endl;
} 

struct node{
	int data;
	node *lchild, *rchild;
	node(int m) : data(m), lchild(NULL), rchild(NULL){};
	node() : lchild(NULL), rchild(NULL){}
};

node *head, *cur;

void search(int x){
	cout << "1.使用顺序查找：" << endl;
	for(int i = 0; i < N; ++i){
		if(arr[i] == x){
			cout << "找到目标元素：" << endl;
			cout << "序号：" << i + 1 << endl;
			return;
		}
	}
	cout << "未找到目标元素" << endl;
}

void binary_search(int x){
	cout << "2.使用折半查找:" << endl;
	for(int i = 0; i < N; ++i)
		brr[i] = arr[i];
	int l = 0, r = N, m;
	sort(brr, brr + N);
	while(l <= r){
		m = (l + r) / 2;
		if(brr[m] == x){
			cout << "找到目标元素：" << endl;
			cout << "返回m值：" << m << endl;
			return;
		}
		else if(brr[m] > x){
			r = m - 1;
		}
		else{
			l = m + 1;
		}
	}
	cout << "未找到目标元素" << endl;
	return;
}

void create_binary_sort_tree(){
	cout << "3.使用二叉排序树" << endl;
	for(int i = 0; i < N; ++i){
		node *tmp = new node(arr[i]);
		if(i == 0){
			head = tmp;
			cur = tmp;
			continue;
		}
		while(1){
			if(cur->data <= tmp->data && cur->rchild == NULL){
				cur->rchild = tmp;
				cur = head;
				break;
			}
			else if(cur->data <= tmp->data){
				cur = cur->rchild;
			}
			if(cur->data > tmp->data && cur->lchild == NULL){
				cur->lchild = tmp;
				cur = head;
				break;
			}
			else if(cur->data > tmp->data){
				cur = cur->lchild;
			}
		}
	}
}

void dfs(node *tmp){
    if(tmp != NULL){
        dfs(tmp->lchild);
        cout << tmp->data << " ";
        dfs(tmp->rchild);
    }
}

void hash_de_duplication(){
	int n;
	cout << "4.哈希去重" << endl;
	cout << "请输入要处理的字符串的数量：" << endl;
    cin >> n;
    for(int i = 1; i <= n; ++i){
    	cin >> hash_ans;
        a[i] = calc_hash(hash_ans);
    }
    sort(a + 1, a + n + 1);
    for(int i = 2; i <= n; ++i)
        if(a[i] != a[i - 1])
            ++sum;
    cout << "不重复的字符串个数：" << endl;
	cout << sum << endl; 
}

int main(){
	rand_arr();
	cout << "请输入要查找的元素：" << endl;
	int op;
	cin >> op;
	search(op);
	binary_search(op);
	create_binary_sort_tree();
	dfs(head);
	cout << endl;
	hash_de_duplication();
	return 0;
}
