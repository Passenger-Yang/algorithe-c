#include <stdio.h>

void countDown(int i){
	printf("%d ", i);
	if(i <= 1)
		return;
	else
		countDown(i - 1);
}


int main(void){
	int i = 10;

	countDown(i);

	return 0;
}



