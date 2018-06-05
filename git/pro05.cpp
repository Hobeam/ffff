// pro05.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#pragma warning(disable:4996)
#define MAX 100
void p01(){
	int array[MAX];
	int n, k;
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &array[i]);
	}
	scanf_s("%d", &k);
	int index = -1, min =-9999999;
	for (int i = 0; i < n; i++) {
		if (array[i] > min && array[i] <= k) {
			min = array[i];
			index = i;
		}
	}
	if (index == -1)
		printf("-1");
	else
		printf("%d %d %d", index, min, k - min);
}
void p03() {
	int array[MAX];
	int n;
	double temp,sum = 0;
	scanf_s("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &array[i]);
		sum += array[i];
	}
	double av = sum / n;
	
	sum = 0;
	for (int i = 0; i < n; i++) {
		temp = (array[i] - av);
		sum += temp * temp;
	}
	double sd = sqrt(sum/n);
	
	printf("%lf %lf", av, sd);
}
void p04() {
	int array[10] = { 0 };
	int N;
	scanf_s("%d", &N);
	
	while (N > 0) {
		array[N % 10]++;
		N /= 10;
	}
	
	for (int i = 0; i < 10; i++)
		printf("%d, ", array[i]);
}
void p09() {
	int data[MAX] = { 0 };
	int n = 0,leader;

	FILE *fp = fopen("input9.txt", "r");
	fscanf_s(fp, "%d", &leader);
	data[n++] = leader;
	while (fscanf_s(fp, "%d", &data[n]) !=EOF) {
		if (data[n] >= leader)
			leader = data[n++];
	}
	fclose(fp);
	printf("%d: ", n);
	for (int i = 0; i < n; i++)
		printf("%d ", data[i]);
}
void p10() {
	int data[MAX] = { 0 };
	int n = 0, sum = 0;
	FILE *fp = fopen("input10.txt", "r");
	fscanf_s(fp, "%d", &data[n++]);
	while (fscanf_s(fp, "%d", &data[n]) != EOF) {
		if (data[n - 1] < data[n])
			sum += data[n] - data[n - 1];
		n++;
	}
	fclose(fp);
	printf("%d", sum);
}
int main()
{
	//while (true)
		p10();
		getchar();
		getchar();
    return 0;
}

