// Ana Le
// Chpt3 PA

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// a function that generates random ints in the range [min, max]
void randomNumbers(int min, int max, int count, int list[]) {
	srand(time(NULL)); 		// uses the computer's internal clock to control the choice of the seed
    for (int i = 0; i < count; i++) { 		// loop that generates and assigns the random integers into the list 
        int rd_num = rand() % (max - min + 1) + min; 		// generates a random number in the range [min, max]
		list[i] = rd_num; 		// assigns the random integer into the list
    }
}

// a function to bubble sort the array from smallest to largest 
int bubbleSort(int list[ ], int j, int i, int count) {
	int temp; 		// to place an int into when swapping two numbers
	for (j = 0; j < count - 2; j++) { 		// loops 23 times to compare all the numbers in the list 	// count - 1 to remain within the typical array and then another - 1 since two elements are being compared each loop
		for (i = 0; i < count - 1; i++) { 		// goes through the entire array starting from index 0
			if (list[i] > list[i + 1]) { 		// swaps if left is greater than right
			temp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = temp;
			}
		}
	}
}

// a function called printArray that prints the array of integers unsorted and sorted
int printArray(int list[], int count, int i) {
	for (i = 0; i < count; i++) { 		// for-loop that goes through the array
	printf("%d ", list[i]); 		// prints the list from the array
	}	
}


int main(void) {
// variables and the array
int list[25];
int min = 1; 		// min int that can be generated
int max = 1000; 		// max int that can be generated
int count = *(&list + 1) - list; 		// a clever trick to calculate the size of an array by using pointer math
int i;
int j;

// call function that generates random ints between 1-1000 or within range [min, max]
randomNumbers(min, max, count, list);

// displays the text and unsorted array, two newlines
printf("Unsorted Array:\n"); 
printArray(list, count, i);		 // call to print the array
printf("\n\n");

// call function to sort the array 		// must be after the unsorted array display
bubbleSort(list, j, i, count);

// displays the sorted array 
printf("Sorted Array:\n");
printArray(list, count, i);
printf("\n");

return 0;
}