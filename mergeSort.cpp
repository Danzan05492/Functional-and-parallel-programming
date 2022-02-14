#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void Merge(int* A, int first, int last)
{
	int middle, start, final, j;
	int* mas = new int[100];
	middle = (first + last) / 2; 
	start = first; 
	final = middle + 1; 
#pragma omp parallel for
	for (j = first; j <= last; j++) 
		if ((start <= middle) && ((final > last) || (A[start] < A[final])))
		{
			mas[j] = A[start];
			start++;
		}
		else
		{
			mas[j] = A[final];
			final++;
		}
#pragma omp parallel for
	for (j = first; j <= last; j++) A[j] = mas[j];
	delete[]mas;
};

void MergeSort(int* A, int first, int last)
{
	{
		if (first < last)
		{
			MergeSort(A, first, (first + last) / 2); 
			MergeSort(A, (first + last) / 2 + 1, last); 
			Merge(A, first, last); 
		}
	}
};

void main()
{
	setlocale(LC_ALL, "Rus");
	int i, n;
	int* A = new int[100];
	cout << "Размер массива > "; cin >> n;
	for (i = 1; i <= n; i++)
	{
		cout << i << " элемент > "; cin >> A[i];
	}
	MergeSort(A, 1, n); 
	cout << "Упорядоченный массив: "; 
#pragma omp parallel for
	for (i = 1; i <= n; i++) cout << A[i] << " ";
	delete[]A;
	system("pause>>void");
}
