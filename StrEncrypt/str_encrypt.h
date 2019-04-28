/*
* A tool used to parse and encrypt strings in a given source file.
* The output source file can then be compiled as usual.
*/
#ifndef __STR_ENCRYPT
#define __STR_ENCRYPT

/*
* The parser will only encrypt strings situated inside a specified area.
* To specify an 'ok to encrypt' area, you will have to add the following
* comments at the top/bottom of your wanted code blocks.
*/
#define START_AREA "// BEGIN_ENCRYPT"
#define STOP_AREA "// STOP_ENCRYPT"

// Local defines.
#define BUFFER 256

/*
* Read a file line by line and encrypt all strings.
* Parameters:
*   < char * > The path of the source file.
*   < unsigned int > The encryption key.
* Return values:
*   < 1 > All strings have been successfully encrypted.
*   < 0 > Something failed, either file reading or encryption.
*/
int encrypt(char *, unsigned int);

/*
* Check if the character needs to be ignored or not.
* Parameters:
*   < char > The character to check.
* Return values:
*   < 1 > The character is forbidden.
*   < 0 > The character is allowed.
*/
int forbidden(char);

#endif