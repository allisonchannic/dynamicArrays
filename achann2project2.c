/* ----------------------------------------------------------------------------
 * Allison Channic
 * CS 211, Fall 2014
 * Project 2
 *
 *
 * NOTES
 * Oliver San Juan from the 11:00 lab proofred my binary search method because
 * there was a bug in which the element was always "-1" or the address would print
 * instead. He then found a missing '=' sign in the last else condition and fixed
 * my while loop condition
 *
 * I also had difficulty reallocating with "malloc" so I googled some solutions
 * and discovered "realloc" which made this project infinitely easier.
 * ----------------------------------------------------------------------------
 */
 
 //Include necessary C libraries
 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 
 
 /* Function to copy the contents of one array to another
  * Takes two array pointers and the array size as its parameters
  * Uses a loop to take the contents from the first array and put it
  * into the second array
  */
 void arrayCopy(int *fromArray, int *toArray, int size)
 {
 	//Copy the contents of fromArray to toArray using a for loop
	int i;
	for(i = 0; i < size; i++)
		toArray[i] = fromArray[i];
 }

 
 /* Function to sort the contents of an array into ascending order
  * Takes an integer array and its size as parameters
  * Uses selection sort to sort the array from low - high
  */
 void sortAscend(int array[], int size)
 {
 	//Loop variables
 	int i;
	int j;
	
	//Minimum value index
	int min;
	
	//Temporary value to swap values in the array
	int temp;
	
	//Selection sort algorithm
	for(i = 0; i < size-1; i++)
	{
		//Set the new minimum value
		min = i;
		
		//Look through the rest of the array
		for (j = i+1; j < size; j++)
		{
			//Look through the rest of the array for smaller values
			if (array[j] < array[min])
				min = j;
		}
		
		//Swap values if a smaller number has been found
		if (min != i)
		{
			temp = array[i];
			array[i] = array[min];
			array[min] = temp;
		}
	}

 }
 
 
 /* Function to search for a selected value in an array linearly
  * Takes an integer array, its size, the value to find, and the number of
  * comparisons it took to find that value as parameters
  * Looks at each element from first - last to see if it is the desired value
  * If not, the loop continues, and numComparisons is incremented
  * Returns the element in the array at which the value was found as an integer
  */
 int linearSearch(int array[], int size, int target, int *numComparisons)
 {
 	//Reset numComparisons to 0
 	*numComparisons = 0;
	
	//Loop counter
 	int i;
	
	//The element the target value was found
	//Initialized to -1 as a default if the value was not found in the array
	int targetElement = -1;
	
	//For loop to look through each element of the array
	for (i = 0; i < size; i++)
	{
		//If the current element is not the value, increment the number of comparisons
		//Continue through the loop
		if (array[i] != target)
		{
			*numComparisons+=1;
			continue;
		}
		
		//Else the target value has been found
		//Return the element it was found at and break from the loop	
		else
		{
			targetElement = i;
			return targetElement;
			break;
		}
	}
	
	//Return the target element if it wasn't returned in the loop
	return targetElement;
 }
 
 
 /* Function to search through a sorted array using binary search
  * Takes an integer array, its size, the value to be found, and the number of
  * comparisons it took to find that value as parameters
  * Looks at the middle value of the array to see if it is the desired value
  * Depending on whether the middle value is higher or lower in value than
  * the target value, the loop looks through only the lower half or right
  * half of the array respectively and the middle value is changed
  * numComparisons is incremented each time the middle value is changed
  * Returns the element the value was found as an integer
  */
 int binarySearch(int array[], int size, int target, int *numComparisons)
 {
 	//Reset the number of comparisons to 0
 	*numComparisons = 0;
	
	//Element the target value was found
	//Initialized to -1 as a default if the target value was not found in the array
	int targetElement = -1;
	
	//Variables to represent the first and last elements of the array
	int first = 0;
	int last = size-1;
	
	//Selection sort algorithm
	//Continue until the first element is the same as the last
	while (first <= last)
	{
		//Variable for the middle element of the array
		int middle = (first+last)/2;
		//Increment number of comparisons
		*numComparisons+=1;
		
		//If the middle value is less than the target
		//Cut the array in half and look through the higher values
		if (array[middle] < target)
			first = middle + 1;
		
		//If the middle value is greater than the target
		//Cut the array in half and look through the lower values
		else if (array[middle] > target)
			last = middle - 1;	
		
		//Else the middle value is the target value and return its element
		else
		{
			targetElement = middle;
			return targetElement;
		}	
	}
	
	//Return the target element in case it was not returned in the loop
	return targetElement;
	
 }
 
 /* Main method
  * Gets an unknown set of integers from the user
  * Takes these values and sets them to a dynamically allocated array
  * A copy of this array is made so the numbers can be sorted in ascending value
  * After the values have been sorted, the user enters the values he/she would
  * like to look for in the array
  * These values are stored in another dynamically allocated array
  * Once all values are stored, each value is looked for using linear search in
  * the unsorted array and binary search in the sorted array
  * The elements at which the values were found and the number of comparisons it
  * took to find them are printed to the user
  */
 int main()
 {
 	//Variable for the numbers the user will enter in
 	int num;
	
	//Initialize the array to store the values and a temporary array
	//For dynamic memory allocation
	int *tempArray = NULL;
	int *values = NULL;
	
	//Initialize the array size to 0
	int arraySize=0;
	
	//Prompt the user for values
 	printf("\nPlease enter a set of numbers. Enter -999 to stop:\n");
	
	scanf("%d", &num);
	
	//Do-while loop to get multiple values
	do
	{
		//Increment the array size
		arraySize++;
		
		//Reallocate memory for the array based on the new array size
		tempArray = (int*)realloc(values, arraySize * sizeof(int));
		values = tempArray;
		
		//Store the number the user entered and obtain a new value
		values[arraySize-1] = num;
		scanf("%d", &num);
		
	} while (num != -999); // do this until the user enters -999
	
	//Print the array size and the numbers entered to the user
	printf("\n\nThe array size is %d", arraySize);
	printf("\n\nThe numbers you entered are: ");
	
	//Loop counter
	int i;
	
	for(i = 0; i < arraySize; i++)
		printf("%d ", values[i]);
	
	//Dynaically allocate an array to store a copy of these values		
	int *values2 = (int*)malloc(arraySize*sizeof(int));	
	
	//Copy the values entered by the user into the new array	
	arrayCopy(values, values2, arraySize);	
	
	//Sort the values of the array	
	sortAscend(values2, arraySize);
	
	//Print the new array in ascending order to the user
	printf("\nThe values of the array in ascending order are: ");
	
	for(i = 0; i < arraySize; i++)
		printf("%d ", values2[i]);
	
	//Variable for the number the user would like to find
	int numToFind;
	
	//Variables for the number of comparisons in linear and binary search
	int linearComparisons;
	int binaryComparisons;
	
	//Variables for the element of the value in the sorted and unsorted array
	int unSortedElement;
	int sortedElement;
	
	//Initialize the array to store the values the user would like to find and
	//a temporary array for dynamic memory allocation
	int *numsToFind = NULL;
	int *tempArray2 = NULL;
	
	//Initialize the size of the array to 0
	int numsToFindSize = 0;
	
	//Prompt the user for the values they would like to search for in the array	
	printf("\nPlease enter the values you would like to search for in the array. Enter -999 to stop:\n");
	scanf("%d", &numToFind);
	
	//Store the values the user would like to search for in a dynanically allocated array
	do
	{
		//Increase array size
		numsToFindSize++;
		
		//Reallocate memory for the array based on its new size
		tempArray2 = (int*)realloc(numsToFind, numsToFindSize  *sizeof(int));
		numsToFind = tempArray2;
		
		//Store the values into the array and get more values
		numsToFind[numsToFindSize - 1] = numToFind;
		scanf("%d", &numToFind);
		
	} while (numToFind != -999); //do this until the user enters -999
	
	//Print to the user the values he/she would like to find
	printf("\nThe numbers you would like to find are: ");
	
	for(i = 0; i < numsToFindSize; i++)
		printf("%d ", numsToFind[i]);
	
	//Print a new line to make things look cleaner	
	printf("\n");	
	
	//For loop to search for each value in the sorted and unsorted arrays		
	for(i = 0; i < numsToFindSize; i++)
	{
		//Get the elements the value was found in the unsorted and sorted array
		unSortedElement = linearSearch(values, arraySize, numsToFind[i], &linearComparisons);
		sortedElement = binarySearch(values2, arraySize, numsToFind[i], &binaryComparisons);
		
		//Print the number the computer is searching for
		printf("\n%d: ", numsToFind[i]);
		
		//If the element in either array is -1, the value was not found
		//Indicate this to the user and move on to the next value
		if ((unSortedElement == -1) || (sortedElement == -1))
		{
			printf("Not found in the array.");
			continue;
		}
		
		//Else the element was found in both arrays
		//Print the element the value was found in both arrays and the number of comparisons it took
		else
		{
			printf("Found in the unsorted array at element %d. Number of comparisons: %d", unSortedElement, linearComparisons);
			printf("\n   Found in the sorted array at element %d. Number of comparisons: %d", sortedElement, binaryComparisons);
		}
	}	
 }