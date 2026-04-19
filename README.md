# лабораторная работа 1
# Бакаринова Софья Андреевна ИДБ-25-02

0. Генерация массива
```
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void makearray(int*arr, int len) {	// TASK 0 MAKING ARRAY 
	for (int i = 0; i < len; i++) {
		arr[i] = rand() + clock();
	}
```

1. Проверка на наличие в массиве
 ```
#include<stdio.h>

int findtarget(int target, int* arr, int len) {	// TASK 1 IS/ISNT IN ARRAY (INT)
	for (int i = 0; i < len; i++) {
		if (target == arr[i]) { return 1; }
	}
	return 0;
}
 ```

2. Поиск второго по величине элемента
```
   #include<stdio.h>
   
   int secmax(int* arr, int len) {						//TASK 2 FIND SECOND MAX
	int* secar = (int*)malloc(len * sizeof(int));
	secar = arr;
	for (int i = 0; i < 2; i++) {
		int curmax = arr[i];
		int ind = i;
		for (int j = i + 1; j < len; j++) {
			if (arr[j] > curmax) {
				curmax = arr[j];
				ind = j;
			}
		}
		int c = arr[i];
		arr[i] = curmax;
		arr[ind] = c;
	}
	return secar[1];
			}
```
 3.1. Сортировка (selection sort)
```
 #include<stdio.h>

void sortarray(int* arr, int len) {
	for (int i = 0; i < len; i++) {
		int curmin = arr[i];
		int ind = i;
		for (int j = i + 1; j < len; j++) {
			if (arr[j] < curmin) {
				curmin = arr[j];
				ind = j;
			}
		}
		int c = arr[i];
		arr[i] = curmin;
		arr[ind] = c;
	}
}
```
 3.2. Бинарный поиск
```
 #include<stdio.h>
int binsearch(int target, int* arr, int len) {	//TASK 3 BIN SEARCH
	int left = 0;
	int right = len;
	int temp = 0;

	while (left <= right) {
		temp = (left + right) / 2;
		if (arr[temp] == target) return temp;
		else if (target < arr[temp]) {right = temp - 1;}
		else {left = temp + 1;}
	}
	return -1;
}
```
4. Таблица умножения
```

```

