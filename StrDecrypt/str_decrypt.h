/*
* Decrypt certain strings that at run-time.
*/
#ifndef __STR_DECRYPT
#define __STR_DECRYPT

// The initial size of the garbage collector.
#define GC_BUFFER 256

/*
* A structure used to store all decrypted strings.
* This is used to free all allocated memory.
*/
typedef struct GARBAGE
{
    // Allocated memory.
    int size;

    // The number of stored strings.
    int n;

    // A list of strings.
    char **ppList;
} sGarbage;

/*
* Decrypt a given string.
* Parameters:
*   < char * > The encrypted string.
* Return values:
*   < char * > The decrypted string.
*/
char *XOR(char *);

/*
* Check if the character needs to be ignored or not.
* Parameters:
*   < char > The character to check.
* Return values:
*   < 1 > The character is forbidden.
*   < 0 > The character is allowed.
*/
int forbidden(char);

/*
* Free GC.
* Call this whenever you want to free the unused allocated memory.
*/
void freeGC();

#endif