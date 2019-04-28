
# String encryption tool.
Parse a set of given source files and encrypt all strings located inside the 'ok-to-encrypt' areas, marked by the following comments: 

> // BEGIN_ENCRYPT  
> // STOP_ENCRYPT

## Usage:
Place `// BEGIN_ENCRYPT` to mark the beginning of an encryption area.

	Strings outside of the marked area will be ignored.
Place `// STOP_ENCRYPT` to mark the end of an encryption area.
Drag and drop your source files over `str_crypt.exe`.
All of the given source files are now encrypted.
**NOTE:** You need to specify the encryption key. This key will be used to encrypt/decrypt the strings.
### PLEASE NOTE:
You have to place the comments right at the beginning of a new line, with no additional spaces or tabs.
#### Example:

    #include <stdio.h>
    #include <string.h>
    #include "str_decrypt.h"
    
    int main()
    {
    
    // BEGIN_ENCRYPT
    
        printf(XOR("This is a test\n"));
        printf(XOR("This is a new line with an int %d\n"), 5);
        printf(XOR("This is another line with a string %s \n"), XOR("A string"));
        printf(XOR("This is a line with an int, float and a string: %d %f %s\n"), 5, 5.45, XOR("Hello"));
    
    // STOP_ENCRYPT
    
        freeGC();
        getchar();
        return 0;
    }

# Additional info:
I have implemented a very basic 'Garbage collector' for the decryption method in order to free all allocated memory. All you have to do to free the memory is call `freeGC()`. This will delete all of the previously decrypted strings.
The encryption method is XOR-ing, but you can easily implement your own.
This tool is just a very basic example of string obfuscation.

