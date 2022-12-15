//
// DSTRING USEAGE EXAMPLE
//
// Some functions require a pointer to the dstring, other
// functions require the dstring to be passed by value.
// Use this file and 'dstring.h' as a reference to know how
// to use each function properly
//
#include <stdio.h>
#include "dstring.h"
int main() {

	// Variables
	size_t buffer = 0;
	char* str = NULL;

	// dstring instance
	dstring dstr;

	// Initialize the dstring using 'initdstr'
	// All dstrings you declare have to be initialized. Every other library function
	// relies on the dstring being initialized for use. Think of it like using fopen
	// to prepare a file pointer for use. 
	dstr = initdstr();

	// These are the initial values for the dstring once initialized.
	printf("INITIAL DSTRING ATTRIBUTES:\n");
	printf("dstrlen: %zu\n", dstrlen(dstr)); // The length of the string currently stored in the dstring.
	printf("dstrbuf: %zu\n", dstrbuf(dstr)); // The buffer, or the maximum length of the dstring.
	printf("getdstr:|%s|\n", getdstr(dstr)); // Returns the member char* of the dstring
	printf("\n");

	// Resize the dstring to a user specified value
	printf("CUSTOM ATTRIBUTES:\n");
	printf("Enter new dstring buffer: ");
	scanf("%zu", &buffer);
	fflush(stdin);
	dresize(&dstr, buffer);

	// Read a line of text from the user into the dstring
	// Pass 'stdin' into the function to get keyboard input. Use any other file pointer to read directly
	// from that file.
	printf("Enter a string of text: ");
	readdstr(&dstr, stdin);
	printf("\n");

	// Print the new user given attributes
	printf("NEW DSTRING ATTRIBUTES:\n");
	printf("dstrbuf: %zu\n", dstrbuf(dstr));
	printf("dstrlen: %zu\n", dstrlen(dstr));
	printf("getdstr:|%s|\n", getdstr(dstr));

	// Destroy the dstring using 'freedstr' once you're done using it.
	// This is basically a destructor that you have to call manually. Dstrings have
	// a char* member, and it needs to be freed at the end of the program.
	freedstr(&dstr);

	// End program
	return 0;
}