// Ana Le
// Chpt2 PA

#include <stdio.h>
#include <string.h>

char* ReverseString(char* stringToReverse, int fstart, int fend) {
	/* TODO: Complete recursive ReverseString() function here. */
	char temp;
   
   // Base case or when the pointer reaches the middle
	if (fstart >= fend) {
		return 0;
	}
	
	// Swapping of two characters on opposite ends
	temp = stringToReverse[fstart];
	stringToReverse[fstart] = stringToReverse[fend];
	stringToReverse[fend] = temp;
    
	// Recursive method call - the pointer will point to the next two characters within the array
	ReverseString(stringToReverse, fstart + 1, fend - 1);
	
}

int main(void) {
	char inStr[50];
	char* resultStr;
  	
	// New variables that the pointer uses to point to the correct characters to swap
  	int start = 0;
  	int end = -1;
   
	printf("Enter the string to be reversed: ");
	fgets(inStr, 20, stdin);
	strtok(inStr, "\n");  // Remove newline character from input.
	
	// Finds the last character in the string that isn't '\0'
  	end = strlen(inStr) - 1;
  
	// Turned the assignment into a call function and added start and end as parameters
	ReverseString(inStr, start, end);
	
	// The method I came up with to make use of the variable resultStr because the assignment would print "(null)"			// Why was it returning "(null)"?
	strcpy(resultStr, inStr);

	printf("Reversed: %s\n", resultStr);

   return 0;
}