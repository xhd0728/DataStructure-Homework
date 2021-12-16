#include<bits/stdc++.h>
using namespace std;
const int N = 256;  //256个字符(ASCII) 

typedef struct node{
	int weight;  //权值 
	char c;  //字符 
	int p, l, r;  //父结点，左孩子，右孩子结点 
	node(int n, int m, char ch){
		weight = n;  //权值初始化
		p = l = r = m, c = ch;  //父结点，左孩子，右孩子结点初始化 
	}
}HTnode, *HufTree;  //结点数据结构 

typedef char **HufCode;  //哈夫曼编码字符串数组

HufTree HT;  //定义哈夫曼树

int n, m, sum = 0;
int cnt[N];  //统计频数 
string ss, s;
string ll;  //存二进制哈夫曼编码
char *sh;
int *ch, *p, *l, *r; 
string HC[256];

void count(){
	ifstream cin("input.txt");  //从硬盘读入文件
	if (!cin.is_open()){
		cout << "文件打开失败" << endl;
		exit(1);
	}
	while(getline(cin, s))
		ss += s;  //将文件中的字符读入到ss里面 
	int len = ss.length();  //预计算长度，节省时间 
	for (int i = 0; i < len; ++i){
		if (!cnt[ss[i]])
			++n;  // 
		cnt[ss[i]]++;  //对应的cnt数组的ASCII值位加一 ，统计字符数 
	}
	m = 2 * n;
	cin.close();  //关闭文件 
}  //打开输入文件 

int select(int n){
	int minv = 0x3f3f3f3f, min = 0;  //0x3f3f3f3f = 2122219134，但不超过32位int型最大值，近似作为无穷大使用 
	for (int i = 1; i <= n; i ++ )
		if (!HT[i].p && HT[i].weight < minv) minv = HT[i].weight, min = i;
	return min;
}  //计算权值，找到权值最小的字符 

void createHufTree(){
	HT = (HufTree)malloc(m * sizeof(HTnode));  //根结点 
	for(int i = 1, j = 0; i <= n; i++){
		while(!cnt[j])
			++j;
		HT[i] = HTnode(cnt[j], 0, (char)j);
		++j;
	}
	for(int i = n + 1; i < m; ++i)
		HT[i] = HTnode(0, 0, '#'); 
	for(int i = n + 1; i < m; ++i){
		int s1 = select(i - 1);
		HT[s1].p = i, HT[i].l = s1;  //左孩子选择 
		int s2 = select(i - 1);
		HT[s2].p = i, HT[i].r = s2;  //右孩子选择 
		HT[i].weight = HT[s1].weight + HT[s2].weight;  //权值处理 
	}
}  //创建哈夫曼树 

void createHufCode(){
	char *cd = (char *)malloc(n * sizeof(char)); 
	ofstream out("HufCode.txt");  //从内存到硬盘 
	if(!out.is_open()){
		cout << "文件打开失败" << endl;
		exit(1);
	}
	string rrr = "";
	for(int i = 1; i <= n; ++i){
		int start = n - 1;
		for(int c = i, f = HT[c].p; f != 0; c = f, f = HT[c].p){
			if(HT[f].l == c)
				cd[start--] = '0';  //指针前移 
			else
				cd[start--] = '1';  //指针前移
		}  //从叶子结点到根结点 
		for(int j = start + 1;j <= n - 1;++j){
			rrr += cd[j];
		}
		HC[(int)HT[i].c] = rrr;
		out << HT[i].c << ' ' << rrr << endl;
		rrr = "";
	}
    out.close();
}  //建立哈夫曼编码 

void createCodefile(){
	ofstream out("CodeFile.dat");//打开压缩文件 
    if (!out.is_open()) {
		cout << "文件打开失败" << endl;
		exit (1);
	}
	string lltt; 
	lltt = "";
	char ccc;
	int lenth = ss.length(); 
	for(int i = 0;i < lenth;++i){
		lltt += HC[(int)ss[i]];
	}
	out << lltt;
	out.close();
}  //文件压缩 

void getCodeFile(){
	ifstream in("CodeFile.dat");
	if(!in.is_open()){
		cout<<"文件打开失败"<<endl;
		exit(1);
	}
	string lll="";
	char mm;
	while(in >> mm)//从codefile里接收字符 
	{
		lll += mm;
		for(int i = 1;i <= 128;i++)//101001010
		{
			if(lll == HC[i]){
			  printf("%c",i);//向用户窗口输出字符
		      lll = "";//重置为空 
		      break;
			} 
		}
		
	}
	in.close();
}

void init(){
	cout << "请选择模式：" << endl;
	cout << "1：文件压缩" << endl;
	cout << "2：文件解压" << endl;
	cout << "0：退出" << endl; 
}  //输出提示

void work(){
	init();
	string op;  //选择参数option_number 
	while(cin >> op){
		if(op == "0") break;
		else if(op == "1"){
			createCodefile();
			cout << "文件已压缩完成" << endl;
			system("pause");
			system("cls");
		}
		else if(op == "2"){
			cout << "解压如下" << endl;
			getCodeFile();
			printf("\n");
			system("pause");
			system("cls");
		}
		else{
			printf("输入不合法，请重新输入！\n");
			system("pause");
			system("cls");
		}
		init();
	}
}  //选择模式函数 

void writeHufTree(){
	ofstream out("HufTree.dat");//以输入方式打开文件 
	if (!out.is_open()) {
		cout << "Error opening file" << endl;
		exit (1);
	}
	out << m<< endl;
	for(int i = 1;i < m;++i){
		out << HT[i].weight << ' ' << HT[i].c << ' ' << HT[i].p << ' ' << HT[i].l <<' ' << HT[i].r << endl;
	}
	out.close();
}  //写入文件  

void fileEmpty(const string fileName){
    fstream file(fileName, ios::out);
}  //清空指定文件内容但保留文件 

int main(){
	fileEmpty("CodeFile.dat");
	fileEmpty("HufCode.txt");
	fileEmpty("HufTree.dat");
	count();  //打开输入文件 
    createHufTree();  //创建哈夫曼树 
    createHufCode();  //创建哈夫曼编码
    writeHufTree();  //将哈夫曼树写入文件 
    work();  //运行向导
	return 0;
}
