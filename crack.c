#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

// Alphabetic comparison method for the qsort function.
int alphabetic(const void *a, const void *b)
{
    char ** aa = (char**)a;
    char ** bb = (char**)b;

    return strcmp(*aa, *bb);
}

int main(int argc, char *argv[])
{
    // If less than 3 arguments are provided, print error message and exit the program.
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // Read the hashes file into an array.
    // Use the loadFile function from fileutil.c
    int size;
    char **hashes = loadFileAA(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort.
    qsort(hashes, size, sizeof(char *), alphabetic);

    // Open the dictionary file for reading.
    FILE *dictFile = fopen(argv[2], "r");
    if (!dictFile)
    {
        printf("ERROR: Cannot open dictionary file for reading.\n");
        exit(1);
    }

    // For each password, hash it, then use the array search
    char password[PASS_LEN];
    int hashCount = 0;
    while (fgets(password, PASS_LEN, dictFile) != NULL)
    {
        // Trim the newline character from the password
        char *nl = strchr(password, '\n');
        if (nl)
        {
            *nl = '\0';
        }
        // Hash the plaintext password
        char *hashWord = md5(password, strlen(password));

        // Use function from fileutil.h to find the hash.
        // CHALLENGE1: Use binary search instead of linear search.
        char *found = binaryStringSearchAA(hashWord, hashes, size);

        // If you find it, display the password and the hash.
        // Keep track of how many hashes were found.
        if (found)
        {
            printf("%s %s\n", hashWord, password);
            hashCount++;
        }
        free(hashWord);
    }

    // Close the file.
    // Display the number of hashes found.
    // Free up memory.
    fclose(dictFile);
    printf("Hashes found: %d\n", hashCount);
    freeAA(hashes, size);
}
