#include <stdlib.h>
#include <stdio.h>

// returns C string Length up to given limit
// does not count the null terminator
size_t my_strnlen(const char* start, size_t n) {
	const char* end;
	for (end = start; *end != '\0'; ++end) {
		if (end - start == n) {
			return n;
		}
	}
	return end - start;
}

// Dynamic string stucture
typedef struct dstring{
	char* str;
	size_t buf;
} dstring;

// Set all the members to something not garbage
dstring initdstr() {
	dstring out;
	out.buf = 1;
	out.str = malloc(sizeof(char) * out.buf);
	out.str[out.buf - 1] = '\0';
	return out;
}

// Returns the buffer size
size_t dstrbuf(dstring dstr) {
	return dstr.buf;
}

// Returns the length of the struct's C string
// Does not include null terminator
size_t dstrlen(dstring dstr) {
	return my_strnlen(dstr.str, dstr.buf);
}

// Resizes the dstring
int dresize(dstring* dstr, size_t newsize) {
	if (newsize < 1) {return 1;}
	dstr->buf = newsize;
	dstr->str = (char*)realloc(dstr->str, newsize);
	dstr->str[dstr->buf - 1] = '\0';
	return 0;
}

// Copy a source C string (src) into the dstring up to dstr.buf
int dstrcpy(dstring* des, char* src) {
	size_t i;
	for (i = 0; i < des->buf - 1; i++) {
		des->str[i] = src[i];
	}
	return i;
}

// Get the pointer to the dstrings member C string
char* getdstr(dstring dstr) {
	return dstr.str;
}

// gets() equivalent for dstr
int readdstr(dstring* dstr, FILE* fp) {
	
	// Variables
	char* input = (char*)malloc(sizeof(char) * dstr->buf);
	size_t i = 0;

	// Get input from the file
	fgets(input, dstr->buf, fp);

	// Copy input into dstring
	// if a newline is encountered,
	// insert a '\0' and break loop
	for (i = 0; i < dstr->buf; i++) {
		if (input[i] == '\n') {
			dstr->str[i] = '\0';
			break;
		} else {
			dstr->str[i] = input[i];
		}
	}

	// End function
	free(input);
	return 0;
}

// Destructor for the dstring
// Basically like fclose for file pointers
int freedstr(dstring* dstr) {
	free(dstr->str);
	return 0;
}