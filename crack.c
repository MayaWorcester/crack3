#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.


int alphabetic(const void *a, const void *b)
{
    char ** aa = (char**)a;
    char ** bb = (char**)b;

    return strcmp(*aa, *bb);
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size;
    //char (*hashes)[HASH_LEN] = loadFile2D(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort.
    qsort(hashes, size, sizeof(char *), alphabetic);

    // TODO
    // Open the dictionary file for reading.
    FILE *dictFile = fopen(argv[2], "r");
    if (!dictFile)
    {
        printf("ERROR: Cannot open dictionary file for reading.\n");
        exit(1);
    }

    // TODO
    // For each password, hash it, then use the array search
    char password[PASS_LEN];
    int hashCount = 0;
    while (fgets(password, PASS_LEN, dictFile) != NULL)
    {
        // Hash the plaintext
        char *hashWord = md5(password, strlen(password));

        // function from fileutil.h to find the hash.
        char *found = stringSearchAA(hashWord, hashes, size);

        // If you find it, display the password and the hash.
        // Keep track of how many hashes were found.
        if (found != NULL)
        {
            printf("%s %s\n", hashWord, password);
            hashCount++;
        }
        free(hashWord);
    }
        // CHALLENGE1: Use binary search instead of linear search.

    // TODO
    // When done with the file:
    //   Close the file
    //   Display the number of hashes found.
    //   Free up memory.
    fclose(dictFile);
    printf("Hashes found: %d\n", hashCount);
    freeAA(hashes, size);
}
