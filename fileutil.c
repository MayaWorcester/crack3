#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.


// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	// Open the file, print an error if the file cannot be opened.
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	int capacity = 100; // Initial capacity value
	int arrSize = 0;

	// TODO:
	// Allocate memory for an array of strings (arr).
	char ** arr = malloc(capacity * sizeof(char *));
	char buffer[1000];

	// Read the file line by line.
	while(fgets(buffer, 1000, in) != NULL)
    {
    	// Trim newline.
		char *nl = strchr(buffer, '\n');
    	if (nl)
    	{
     		*nl = '\0';
    	}

		// Expand array if necessary (realloc).
		if (arrSize == capacity)
		{
			capacity += 50;
			arr = realloc(arr, capacity * sizeof(char *));
		}

		// Allocate memory for the string (str).
		arr[arrSize] = malloc(strlen(buffer) + 1);

		// Copy each line into the string (use strcpy).
		// Attach the string to the large array (assignment =).
		strcpy(arr[arrSize], buffer);
		arrSize++;
	}
    // Close the file.
	fclose(in);
	
	// The size should be the number of entries in the array.
	*size = arrSize;

	// Return pointer to the array of strings.
	return arr;
}

char (*loadFile2D(char *filename, int *size))[COLS]
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	// Allocate memory for an 2D array, using COLS as the width.
	// Read the file line by line into a buffer.
    //   Trim newline.
	//   Expand array if necessary (realloc).
	//   Copy each line from the buffer into the array (use strcpy).
    // Close the file.
	
	// The size should be the number of entries in the array.
	*size = 0;
	
	// Return pointer to the array.
	return NULL;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **arr, int size)
{
	int found = 0;
	char *str;

	// Loop through the array
	for (int i = 0; i < size; i++)
	{
		str = arr[i];

		// If the target substring is found in a line, break the for-loop
		if (strstr(str, target) != NULL)
		{
			found = 1;
			break;
		}
	}
	
	// If substring was found, return the substring
	if (found == 1)
	{
		return str;
	}
	// otherwise return NULL
	else
	{
		return NULL;
	}
}

char * stringSearchAA(char *target, char **arr, int size)
{
	int found = 0;
	char *str;

	// Loop through the array
	for (int i = 0; i < size; i++)
	{
		str = arr[i];

		// If the target substring is found in a line, break the for-loop
		if (strcmp(str, target) == 0)
		{
			found = 1;
			break;
		}
	}
	
	// If string was found, return the substring
	if (found == 1)
	{
		return str;
	}
	// otherwise return NULL
	else
	{
		return NULL;
	}
}

char * substringSearch2D(char *target, char (*lines)[COLS], int size)
{
    
    return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	// Loop through the array to free every memory allocated string
	for (int i = 0; i < size; i++)
	{
		free(arr[i]);
	}
	// Free the array containing those strings
	free(arr);
}

void free2D(char (*arr)[COLS])
{

}