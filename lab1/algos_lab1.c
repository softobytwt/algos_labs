#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


void makearray(int*arr, int len) {	// TASK 0 MAKING ARRAY 
	for (int i = 0; i < len; i++) {
		arr[i] = rand() + clock();
	}
}	

void printarray(int* arr, int len) {	//TASK 0 PRINTING ARRAY
	//printf("array: ");
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

int findtarget(int target, int* arr, int len) {	// TASK 1 IS/ISNT IN ARRAY (BOOL)
	for (int i = 0; i < len; i++) {
		if (target == arr[i]) { return 1; }
	}
	return 0;
}

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

void sortarray(int* arr, int len) {					//TASK SORT ARRAY
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


void multable(int len) {							//TASK 4 MULTIPLICATION TABLE
	int* arr = (int*)malloc(len * sizeof(int));
	for (int i = 0; i < len; i++) {
		arr[i] = i+1;
	}

	int** table = (int**)malloc(len * sizeof(int*));
	for (int i = 0; i < len; i++) {
		table[i] = (int*)malloc(len * sizeof(int));
		for (int j = 0; j < len; j++) {
			if (!i) { table[i][j] = arr[j]; }
			else { table[i][j] = arr[i] * table[0][j]; }
		}
	}

	for (int i = 0; i < len; i++) {
		printarray(table[i], len);
	}

}

void measuretime(void (*function)(int*, int), int*arr, int len) {
	float t;
	t = clock();
	function(arr, len);
	t = clock()-t;
	printf("size: %d\ttime: %f ms\n", len, 1000*t/CLOCKS_PER_SEC);
}
void measuretime(int (*function)(int*, int), int* arr, int len) {
	float t;
	t = clock();
	function(arr, len);
	t = clock() - t;
	printf("size: %d\ttime: %f ms\n", len, 1000 * t / CLOCKS_PER_SEC);
}
void measuretime(int (*function)(int, int*, int),int target, int* arr, int len) {
	float t;
	t = clock();
	function(target, arr, len);
	t = clock() - t;
	printf("size: %d\ttime: %f ms\n", len, 1000 * t / CLOCKS_PER_SEC);
}
void measuretime(void (*function)( int), int len) {
	float t;
	t = clock();
	function( len);
	t = clock() - t;
	printf("size: %d\ttime: %f ms\n", len, 1000 * t / CLOCKS_PER_SEC);
}


void main() {
	int flflfl;
	printf("input any number to begin ");
	scanf_s("%d", &flflfl);
	int** arr = (int**)malloc(4 * sizeof(int*));
	int n[4] = { 1000, 10000, 50000, 100000 };			//size of array
	//{ 5, 6, 7, 8 };

	printf("GENERATING ARRAYS + TIME MEASURE\n");
	for (int i = 0; i < 4; i++) {
		arr[i] = (int*)malloc(n[i] * sizeof(int));
		measuretime(makearray, arr[i], n[i]);
	}

	printf("\nTASK 1: CHECK IF IN ARRAY\n");
	int target;
	for (int i = 0; i < 4; i++) {
		target = arr[i][n[i] - 1];
		printf("size: %d\tin array?:\t%d\n", n[i], findtarget(target, arr[i], n[i]));
		measuretime(findtarget, target, arr[i], n[i]);
	}

	
	printf("\nTASK 2: FIND SECOND MAX\n");
	for (int i = 0; i < 4; i++) {
		measuretime(secmax, arr[i], n[i]);
		printf("sec max:\t%d\n", secmax(arr[i], n[i]));

	}

	printf("\nTASK SELECTION SORT (TIME MEASURE)\n");
	for (int i = 0; i < 4; i++) {
		measuretime(sortarray, arr[i], n[i]);
		printf("sorting...\n");
		sortarray(arr[i], n[i]);
	}


	printf("\nTASK 3: BINARY SEARCH (TIME MEASURE)\n");

	for (int i = 0; i < 4; i++) {
		target = arr[i][10];
		measuretime(binsearch, target, arr[i], n[i]);
	}


	printf("\nTASK 4: MULTIPLICATION TABLE\n");
	int len;
	printf("input size: ");
	scanf_s("%d", &len);
	measuretime(multable, len);
}
