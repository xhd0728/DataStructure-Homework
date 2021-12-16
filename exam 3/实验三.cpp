/*
·首先将1写在第一行的中间
·之后，按如下方式从小到大依次填写每个数K(K=2,3,...,N*N)
·若(K-1)在第一行但不在最后一列，则将K填在最后一行，(K-1)所在列的右一列
·若 (K-1)在最后一列但不在第一行，则将K填在第一列，(K-1)所在行的上一行
·若 (K-1)在第一行最后一列，则将K填在(K-1)的正下方
·若 (K-1)既不在第一行，也不在最后一列，如果(K-1)的右上方还未填数，则将K填在 (K-1)的右上方，否则将K填在(K-1)的正下方
*/

#include<bits/stdc++.h>
using namespace std;
const int N = 10000;
int arr[N][N] = {0};  //将二维数组先全部初始化为零

void MagicSquare(int m){
	arr[0][m / 2] = 1;  //首先将1写在第一行的中间
	int row = 0;  //初始化行row
	int col = m / 2;  //初始化列column 
	for(int i = 2 ; i <= m * m ; ++i){
		row = (row - 1 + m) % m;  //上移
		col = (col + 1) % m;  //右移 
		if(arr[row][col] != 0){  //判断该格子是否被别的数占了。
			row = (row + 2) % m;  //下移 
			col = (col - 1 + m) % m;  //左移 
		}
		arr[row][col] = i;  //依次编号 
	}
	for(int i = 0 ; i < m ; ++ i){
		for(int j = 0 ; j < m ; ++ j)
			printf("%-4d ", arr[i][j]);  //输出的时候每个数字占4个位置
		printf("\n");  //输出二维矩阵 
	}
 
}

int main(){
	int m;
	printf("请输入魔方阵的阶数(m为奇数)：\n");
	scanf("%d", &m);
	if(m % 2 == 0)
		printf("阶数不为奇数，输入不合法\n");
	else{
		printf("得到的魔方阵为：\n");
		MagicSquare(m);
	}
	return 0;
}

