//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<windows.h>
using namespace std;
const int N = 20;
int arr[N];
int brr[N];
int t = 0;
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
	}
}

void init_array(){
	for(int i = 0; i < N; ++i){
		brr[i] = arr[i];
	}
}

void display(int *a, int size){
	for(int i = 0; i < size; ++i){
		printf("%5d", a[i]);
	}
	cout << endl;
}

void InsertSort(int *array, int size){
    for(int i = 1; i < size; ++i){
        int tmp = array[i];
        int j = i - 1;
        while(j >= 0 && array[j] > tmp){
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = tmp;
		cout << "step" << i << ":\t";
        display(array, size);
        Sleep(80);
    }
}

void QuickSort(int* array, int left, int right){
	if(left >= right)
		return;
	int i, j, base, tmp;
	i = left;
	j = right;
	base = array[left];
	while (i < j){
		while (array[j] >= base && i < j)
			j--;
		while (array[i] <= base && i < j)
			i++;
		if(i < j){
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
		}
	}
	array[left] = array[i];
	array[i] = base;
	cout << "step" << ++t << ":\t";
	display(brr, N);
	Sleep(80);
	QuickSort(array, left, i - 1);
	QuickSort(array, i + 1, right);
}

void SelectSort(int* array, int n){
	t = 0;
    for(int i = 0; i < n; ++i){
        int minn = i;
        for(int j = i + 1; j < n; ++j){
            if(array[j] < array[minn]){
                minn = j;
            }
        }
        if(minn != i){
            int tmp = array[i];
            array[i] = array[minn];
            array[minn] = tmp;
        }
        cout << "step" << ++t << ":\t";
        display(array, N);
        Sleep(80);
    }
    cout << endl;
}

int main(){
	rand_arr();
	cout << "当前随机生成的数组元素为：" << endl;
	for(int i = 0; i < N; ++i)
		cout << arr[i] << " ";
	cout << endl;
	system("pause"); 
	cout << "1.直接插入排序" << endl;
	init_array();
	InsertSort(brr, N);
	system("pause");
	cout << "2.快速排序" << endl;
	init_array();
	QuickSort(brr, 0, N - 1);
	system("pause");
	cout << "3.直接选择排序" << endl;
	init_array();
	SelectSort(brr, N);
	return 0; 
}
