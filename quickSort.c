#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void swap(int *x, int *y){
	int t = *x;
	*x = *y;
	*y = t;
	return;
}

void quickSort(int *arr, int left, int right){
	if(left > right){
		return;
	}

	int temp = arr[left];
	int i = left;
	int j = right;

	while(i < j){
		while(arr[j] >= temp && j > i){
			j--;
		}

		while(arr[i] <= temp && i < j){
			i++;
		}

		if(i < j){
			swap(&arr[i], &arr[j]);
		}
	}
	arr[left] = arr[i];
	arr[i] = temp;

	quickSort(arr, left, i-1);
	quickSort(arr, i+1, right);

	return;
}


int main(void)
{
	int arr[15] = {0};
	int i;
	int num = sizeof(arr) / sizeof(arr[0]);

	srand(time(NULL));

	for(i = 0; i < num; i++){
		arr[i] = rand() % 20;
	}
	printf("%d\n", num);

	for(i = 0; i < num; i++){
		printf("%d ", arr[i]);
	}

	quickSort(arr, 0, num - 1);

	printf("\r\n-----------quick sorted--------\n");
	for(i = 0; i < num; i++){
		printf("%d ", arr[i]);
	}


	return 0;
}


