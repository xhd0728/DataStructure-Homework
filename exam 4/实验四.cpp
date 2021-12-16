#include<bits/stdc++.h>
using namespace std;
const int N = 256;  //256���ַ�(ASCII) 

typedef struct node{
	int weight;  //Ȩֵ 
	char c;  //�ַ� 
	int p, l, r;  //����㣬���ӣ��Һ��ӽ�� 
	node(int n, int m, char ch){
		weight = n;  //Ȩֵ��ʼ��
		p = l = r = m, c = ch;  //����㣬���ӣ��Һ��ӽ���ʼ�� 
	}
}HTnode, *HufTree;  //������ݽṹ 

typedef char **HufCode;  //�����������ַ�������

HufTree HT;  //�����������

int n, m, sum = 0;
int cnt[N];  //ͳ��Ƶ�� 
string ss, s;
string ll;  //������ƹ���������
char *sh;
int *ch, *p, *l, *r; 
string HC[256];

void count(){
	ifstream cin("input.txt");  //��Ӳ�̶����ļ�
	if (!cin.is_open()){
		cout << "�ļ���ʧ��" << endl;
		exit(1);
	}
	while(getline(cin, s))
		ss += s;  //���ļ��е��ַ����뵽ss���� 
	int len = ss.length();  //Ԥ���㳤�ȣ���ʡʱ�� 
	for (int i = 0; i < len; ++i){
		if (!cnt[ss[i]])
			++n;  // 
		cnt[ss[i]]++;  //��Ӧ��cnt�����ASCIIֵλ��һ ��ͳ���ַ��� 
	}
	m = 2 * n;
	cin.close();  //�ر��ļ� 
}  //�������ļ� 

int select(int n){
	int minv = 0x3f3f3f3f, min = 0;  //0x3f3f3f3f = 2122219134����������32λint�����ֵ��������Ϊ�����ʹ�� 
	for (int i = 1; i <= n; i ++ )
		if (!HT[i].p && HT[i].weight < minv) minv = HT[i].weight, min = i;
	return min;
}  //����Ȩֵ���ҵ�Ȩֵ��С���ַ� 

void createHufTree(){
	HT = (HufTree)malloc(m * sizeof(HTnode));  //����� 
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
		HT[s1].p = i, HT[i].l = s1;  //����ѡ�� 
		int s2 = select(i - 1);
		HT[s2].p = i, HT[i].r = s2;  //�Һ���ѡ�� 
		HT[i].weight = HT[s1].weight + HT[s2].weight;  //Ȩֵ���� 
	}
}  //������������ 

void createHufCode(){
	char *cd = (char *)malloc(n * sizeof(char)); 
	ofstream out("HufCode.txt");  //���ڴ浽Ӳ�� 
	if(!out.is_open()){
		cout << "�ļ���ʧ��" << endl;
		exit(1);
	}
	string rrr = "";
	for(int i = 1; i <= n; ++i){
		int start = n - 1;
		for(int c = i, f = HT[c].p; f != 0; c = f, f = HT[c].p){
			if(HT[f].l == c)
				cd[start--] = '0';  //ָ��ǰ�� 
			else
				cd[start--] = '1';  //ָ��ǰ��
		}  //��Ҷ�ӽ�㵽����� 
		for(int j = start + 1;j <= n - 1;++j){
			rrr += cd[j];
		}
		HC[(int)HT[i].c] = rrr;
		out << HT[i].c << ' ' << rrr << endl;
		rrr = "";
	}
    out.close();
}  //�������������� 

void createCodefile(){
	ofstream out("CodeFile.dat");//��ѹ���ļ� 
    if (!out.is_open()) {
		cout << "�ļ���ʧ��" << endl;
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
}  //�ļ�ѹ�� 

void getCodeFile(){
	ifstream in("CodeFile.dat");
	if(!in.is_open()){
		cout<<"�ļ���ʧ��"<<endl;
		exit(1);
	}
	string lll="";
	char mm;
	while(in >> mm)//��codefile������ַ� 
	{
		lll += mm;
		for(int i = 1;i <= 128;i++)//101001010
		{
			if(lll == HC[i]){
			  printf("%c",i);//���û���������ַ�
		      lll = "";//����Ϊ�� 
		      break;
			} 
		}
		
	}
	in.close();
}

void init(){
	cout << "��ѡ��ģʽ��" << endl;
	cout << "1���ļ�ѹ��" << endl;
	cout << "2���ļ���ѹ" << endl;
	cout << "0���˳�" << endl; 
}  //�����ʾ

void work(){
	init();
	string op;  //ѡ�����option_number 
	while(cin >> op){
		if(op == "0") break;
		else if(op == "1"){
			createCodefile();
			cout << "�ļ���ѹ�����" << endl;
			system("pause");
			system("cls");
		}
		else if(op == "2"){
			cout << "��ѹ����" << endl;
			getCodeFile();
			printf("\n");
			system("pause");
			system("cls");
		}
		else{
			printf("���벻�Ϸ������������룡\n");
			system("pause");
			system("cls");
		}
		init();
	}
}  //ѡ��ģʽ���� 

void writeHufTree(){
	ofstream out("HufTree.dat");//�����뷽ʽ���ļ� 
	if (!out.is_open()) {
		cout << "Error opening file" << endl;
		exit (1);
	}
	out << m<< endl;
	for(int i = 1;i < m;++i){
		out << HT[i].weight << ' ' << HT[i].c << ' ' << HT[i].p << ' ' << HT[i].l <<' ' << HT[i].r << endl;
	}
	out.close();
}  //д���ļ�  

void fileEmpty(const string fileName){
    fstream file(fileName, ios::out);
}  //���ָ���ļ����ݵ������ļ� 

int main(){
	fileEmpty("CodeFile.dat");
	fileEmpty("HufCode.txt");
	fileEmpty("HufTree.dat");
	count();  //�������ļ� 
    createHufTree();  //������������ 
    createHufCode();  //��������������
    writeHufTree();  //����������д���ļ� 
    work();  //������
	return 0;
}
