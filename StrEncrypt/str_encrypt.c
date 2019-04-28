// Standard includes.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Local includes.
#include "str_encrypt.h"

/*
* The main routine.
* Takes as arguments the path to the source files.
*/
int main(int argc, char *argv[])
{
    // Get the encryption key.
    unsigned int key;
    printf("Please enter the encryption key: ");
    scanf("%u", &key);

    // Create log file.
    FILE *pLog = fopen("str_encrypt_log.txt", "a");

    fprintf(pLog, "--- BEGIN SESSION ---\n");
    for (int i = 1; i < argc; i++)
    {
        // Get current file.
        char *pPath = argv[i];

        // Encrypt all given source files.
        if (encrypt(pPath, key))
            fprintf(pLog, "%s [SUCCESS]\n", pPath);
        else
            fprintf(pLog, "%s [ERROR]\n", pPath);
    }
    fprintf(pLog, "--- END SESSION ---\n");

    fclose(pLog);
    return 0;
}

int encrypt(char *pPath, unsigned int key)
{
    // Open source file for reading/writting.
    FILE *pSource = fopen(pPath, "r+");
    if (pSource == NULL)
        return 0;

    // Create a buffer used to read each line.
    char *read = calloc(BUFFER, sizeof(char));

    // Create a buffer used to store the encrypted source file.
    char *buffer = calloc(BUFFER, sizeof(char));
    int bufferSize = BUFFER;

    // A boolean used to mark the beginning/end of an encryption area.
    unsigned int bArea = 0;

    // A boolean used to mark the beginning/end of a string.
    unsigned int bString = 0;

    // Read source file.
    while (fgets(read, BUFFER, pSource))
    {
        // Get the length of the current text.
        unsigned int length = strlen(read);

        // Find the beginning of an encryption area.
        if (strncmp(read, START_AREA, strlen(START_AREA)) == 0)
            bArea = 1;
        // Find the end of an encryption area.
        else if (strncmp(read, STOP_AREA, strlen(STOP_AREA)) == 0)
            bArea = 0;

        // If we are inside an encryption area, start encrypting strings.
        else if (bArea)
        {
            // Find strings and encrypt them.
            for (int i = 0; i < length; i++)
                // Mark the beginning of a string.
                if (read[i] == '"' && !bString)
                    bString = 1;
                // Mark the end of a string.
                else if (read[i] == '"' && bString)
                    bString = 0;
                // Encrypt character.
                else if (bString == 1)
                {
                    // Check new line.
                    if (read[i] == '\\' && read[i + 1] == 'n')
                        i++;
                    // Check forbidden characters.
                    else if (!forbidden(read[i]))
                    {
                        // Encrypt allowed characters.
                        char ch = read[i] ^ key;
                        if (!forbidden(ch))
                            read[i] = ch;
                    }
                }
        }

        // Copy current text inside the output buffer.
        if (bufferSize <= strlen(buffer) + length)
        {
            bufferSize *= 2;
            buffer = realloc(buffer, bufferSize * sizeof(char));
        }
        strcat(buffer, read);
    }

    // Free the buffer used to read from file.
    free(read);

    // Source file has been encrypted.
    rewind(pSource);
    fprintf(pSource, "%s", buffer);

    // Free the buffer used to store the encrypted file.
    free(buffer);

    // Close file handle.
    fclose(pSource);

    return 1;
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