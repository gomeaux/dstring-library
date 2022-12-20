#include <stdio.h>
#include "dstring.h"
int main() {

    // Create a dstring pointer. Think of them like FILE* types, you
    // never declare a FILE, instead its always a FILE*. A dstring
    // must be initialized with 'initdstr' before use.
    dstring* dstr = initdstr();

    // After initialization, resize the string to your desired size.
    // By default, dstrings are initialized to 1 character, and its
    // a null terminator.
    printf("Enter a buffer size: ");
    size_t buffer = 0;
    scanf("%zu", &buffer);
    fflush(stdin);
    dresize(dstr, buffer);

    // Now that the dstring is of a proper size, get some user input
    // readdstr gets a line from the file. use stdin to get keyboard
    // input from the user
    printf("Enter string: ");
    readdstr(dstr, stdin);

    // Use the getter functions to get the dstring attributes
    printf("\nString Attributes:\n");
    printf("String buffer: %zu\n", dstrbuf(dstr));
    printf("String length: %zu\n", dstrlen(dstr));
    printf("Member string:|%s|\n", getdstr(dstr));

    // Dstrings need to be freed, since the initdstr function heap
    // allocates the dstring pointer.
    freedstr(dstr);

    // End of program
    return 0;
}