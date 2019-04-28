// Standard includes.
#include <stdlib.h>
#include <string.h>

// Local includes.
#include "str_decrypt.h"

// Garbage collector.
sGarbage GC = {
    GC_BUFFER,
    0,
    NULL};

char *XOR(char *pEncrypted)
{
    // Define the decryption key.
    unsigned int key = 10;

    // Init GC.
    if (GC.n == 0)
        GC.ppList = malloc(GC_BUFFER * sizeof(char *));
    // Check if we need more memory for the GC.
    else if (GC.size - 1 <= GC.n)
    {
        GC.size *= 2;
        GC.ppList = realloc(GC.ppList, GC.size * sizeof(char *));
    }
    // The decrypted string.
    char *pDecrypted = malloc(strlen(pEncrypted) * sizeof(char) + 1);
    strcpy(pDecrypted, pEncrypted);

    // Add string to the garbage collection.
    GC.ppList[GC.n++] = pDecrypted;

    // Decrypt string.
    for (int i = 0; i < strlen(pEncrypted); i++)
        if (!forbidden(pEncrypted[i]))
        {
            char ch = pEncrypted[i] ^ key;
            if (!forbidden(ch))
                pDecrypted[i] = ch;
        }

    return pDecrypted;
}

int forbidden(char ch)
{
    // Forbidden characters.
    char ignoredChars[] = "%\"\\\n";

    // Check if the input character is forbidden.
    for (int i = 0; i <= strlen(ignoredChars); i++)
        if (ch == ignoredChars[i])
            return 1;

    return 0;
}

void freeGC()
{
    // Make sure the GC is not empty.
    if(GC.n == 0)
        return;
	
    GC.size = GC_BUFFER;

    // Delete decrypted strings.
    for (int i = 0; i < GC.n; i++)
        free(GC.ppList[i]);

    // Free memory.
    GC.n = 0;
    free(GC.ppList);
    GC.ppList = NULL;
}
