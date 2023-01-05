#include <stdio.h>
#include "dstring.h" // Just include this one file, thats all thats needed

int main() {
	
	/********************************************************************************************
	CREATING A DSTRING

	Always declare a 'dstring*' and not a 'dstring.' This is because it must be initialized
	with the 'init_dstr' function, which allocates heap memory for the dstring and its members.
	The buffer is set to 1, memory for the char* is allocated, and a '\0' is added to the end
	of the string. Unless you want to do that yourself, just set your dstrings to 'init_dstr.'
	********************************************************************************************/
	dstring* dstr = init_dstr();

	/********************************************************************************************
	READING FROM STDIN

	There are to ways to read stdin, the functions 'read_dstr' and 'rread_dstr.' Those functions
	respectively will either not resize the dstring, or resize it to fit the input (hence the
	extra 'r' in the name). Neither function will flush stdin, and 'rread_dstr' will not size
	down the dstring to fit the input as tightly as possible
	********************************************************************************************/
	printf("Enter a string of text. The dstring will dynamically resize to fit your input.\n:");
	rread_dstr(dstr);
	printf("\nDSTRING ATTRIBUTES:\n");
	printf("Length: %zu\n", dstr_len(dstr)); // Use these getter functions to get the dstrings
	printf("Buffer: %zu\n", dstr_buf(dstr)); // Length, buffer size, and the string itself.
	printf("String:|%s|\n\n", get_dstr(dstr));

	/********************************************************************************************
	RESIZING A DSTRING

	Simply use the 'resize_dstr' function. This function reallocates the dstrings member string
	to an area in memory where the newly sized string can fit. When sizing down, the content that
	was in the string before will remain, if it fits within the new buffer size. Whether sizing
	up or down, a null terminator is always set at [buffer size - 1].
	********************************************************************************************/
	int newbuf = 0;
	printf("Enter a new buffer size.\n:");
	scanf("%d", &newbuf);
	fflush(stdin);
	resize_dstr(dstr, newbuf);
	printf("Length: %zu\n", dstr_len(dstr));
	printf("Buffer: %zu\n", dstr_buf(dstr));
	printf("String:|%s|\n\n", get_dstr(dstr));

	// An example of the 'read_dstr" function
	printf("Enter a string of text. The dstring will not change its buffer size.\n:");
	read_dstr(dstr);
	printf("\nDSTRING ATTRIBUTES:\n");
	printf("Length: %zu\n", dstr_len(dstr));
	printf("Buffer: %zu\n", dstr_buf(dstr));
	printf("String:|%s|\n\n", get_dstr(dstr));

	/********************************************************************************************
	FREEING A DSTRING

	A dstring must be freed using the 'free_dstr' function. Using 'free' on a dstring will not
	free its member character pointer, which is also allocated on the heap. 'free_dstr' will free
	the dstring* and then the char*. You could do this yourself, it's like four lines of code,
	is this not easier?
	********************************************************************************************/
	free_dstr(dstr);

	// End
	return 0;
}