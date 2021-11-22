#include <iostream>
#include <time.h>

void swap (int* a, int* b)
{
	int temp{ 0 };
	temp = *b;
	*b = *a;
	*a = temp;
}

int* initArr(int length)
{
	int* arrPtr;
	return arrPtr = (int*)calloc(length, sizeof(int));
}

void fillArr(int* arrPtr, int length, int max)
{
	srand(time(NULL));
	for (int i = 0; i < length; i++)
		arrPtr[i] = rand() % max;
}

void printArr(int* arrPtr, int length)
{
	for (int i = 0; i < length; i++)
		printf("%3d", arrPtr[i]);
	printf("\n\n");
}

// Task 1 
void insertSort(int* arrPtr, int left, int right)
{
	for (int step = left + 1; step < right + 1; step++)
		for (int i = step; i > 0; i--)
			if (arrPtr[i - 1] > arrPtr[i])
				swap(&arrPtr[i - 1], &arrPtr[i]);
}

void quickSortImp(int* arrPtr, int left, int right)
{
	if (right - left > 10)
	{
		int mid = (left + right) / 2;
		if (arrPtr[left] > arrPtr[mid])
			swap(&arrPtr[left], &arrPtr[mid]);
		if (arrPtr[right] < arrPtr[mid])
			swap(&arrPtr[right], &arrPtr[mid]);
		if (arrPtr[left] > arrPtr[mid])
			swap(&arrPtr[left], &arrPtr[mid]);
		int x = arrPtr[mid];
		int l = left;
		int r = right;

		do
		{
			while (arrPtr[l] < x)
				l++;
			while (arrPtr[r] > x)
				r--;
			if (l <= r)
			{
				swap(&arrPtr[l], &arrPtr[r]);
				l++;
				r--;
			}
		} while (l <= r);
		if (l < right)
			quickSortImp(arrPtr, l, right);
		if (left < r)
			quickSortImp(arrPtr, left, r);
	}
	else
		insertSort(arrPtr, left, right);
}

//Task2
void blockSort(int* arrPtr, int length)
{
	
	bool sorted = false;
	const int b = 10;
	int** arr = (int**)calloc(b, sizeof(int*));
	for (int i = 0; i < b; i++)
	{
		arr[i] = initArr(length + 1);
		arr[i][length] = 0;
	}
	int dig = 1;
	
	int odd = 0;
	for (int i = 0; i < length; i++) // counting odd numbers
		if (arrPtr[i] % 2 == 1)
			odd++;

	while (!sorted && dig < INT16_MAX)
	{
		for (int i = 0; i < length; i++)
		{
			if (arrPtr[i] % 2 == 0)
			{
				int d = (arrPtr[i] / dig) % b;
				arr[d][arr[d][length]++] = arrPtr[i];
			}
		}

		if (arr[0][length] + odd == length) // true if array is sorted
			sorted = true;

		int idx = 0;
		for (int i = 0; i < b; i++)
		{
			for (int j = 0; j < arr[i][length]; j++)
			{
				while (arrPtr[idx] % 2 == 1)
					idx++;
				arrPtr[idx++] = arr[i][j];
			}
			arr[i][length] = 0;
		}

		dig *= 10;
	}
	
	for (int  i = 0; i < b; i++)
		free(arr[i]);
	free(arr);
}

int main()
{
	// Task 1
	const int LENGTH = 50;
	int* arrPtr = initArr(LENGTH);
	
	fillArr(arrPtr, LENGTH, 20);
	printArr(arrPtr, LENGTH);
	
	quickSortImp(arrPtr, 0, LENGTH - 1);
	
	printArr(arrPtr, LENGTH);
	
	// Task 2

	fillArr(arrPtr, LENGTH, 99);
	printArr(arrPtr, LENGTH);
	
	blockSort(arrPtr, LENGTH);
	printArr(arrPtr, LENGTH);
	
	free(arrPtr);
	return 0;
}