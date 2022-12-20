#include <stdlib.h>
#include <stdio.h>

// Returns C string length up until a given limit
size_t strlen_n(const char* start, size_t n) {
	const char* end;
	for (end = start; *end != '\0'; ++end) {
		if (end - start == n) {
			return n;
		}
	}
	return end - start;
}

// Concatenates two C strings with given size of 'dest'
char* strcat_n(char* dest, const char* src, size_t n) {
    char* ptr = dest + strlen_n(dest, n);
    while (*src != '\0' && strlen_n(dest, n) < n) {
        //*ptr++ = *src++;
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';
    return dest;
}

// Searches for the first instance of 'c' in 'str' until n characters
char* strchr_n(const char* str, int c, size_t n) {
    size_t i = 0;
    while (i < n) {
        if (str[i] == c) {
            return (char*)&str[i];
        }
        i++;
    }
    return NULL;
}

// Compares the two strings until n characters
int strcmp_n( const char *s1, const char *s2, size_t n ) {
    const unsigned char *p1 = (const unsigned char*)s1;
    const unsigned char *p2 = (const unsigned char*)s2;
    size_t i = 0;
    while (( *p1 && *p1 == *p2 ) && (i < n) ){
        p1++;
        p2++;
        i++;
    }

    return ( *p1 > *p2 ) - ( *p2  > *p1 );
}

// Copies n characters from src into dest
char* strcpy_n(char *dest, const char *src, size_t n) {
    size_t i = 0;
    while (i < n) {
        dest[i] = src[i];
        if (src[i] == '\0') {
            break;
        }
        i++;
    }
    return dest;
}

// Dynamic string stucture
typedef struct dstring {
	char* str;
	size_t buf;
} dstring;

// Returns a pointer to an initialized dstring
dstring* initdstr() {
    dstring* dstr = (dstring*)malloc(sizeof(dstring) * 1);
    dstr->buf = 1;
    dstr->str = (char*)malloc(sizeof(char) * dstr->buf);
    dstr->str[dstr->buf - 1] = '\0';
    return dstr;
}

// Deletes the dstring
int freedstr(dstring* dstr) {
    //free(dstr->str);+++++++++++++++++++++++++
    free(dstr);
    free(dstr->str);
    return 0;
}

// Returns the dstrings buffer size
size_t dstrbuf(dstring* dstr) {
    return dstr->buf;
}

// Returns the length of the dstrings member C string
size_t dstrlen(dstring* dstr) {
    return strlen_n(dstr->str, dstr->buf);
}

// Resizes the dstring to a given new size
// Any previous characters that still fit in the newly sized string are kept
int dresize(dstring* dstr, size_t newsize) {
	if (newsize < 1) {return 1;}
	dstr->buf = newsize;
	dstr->str = (char*)realloc(dstr->str, newsize);
	dstr->str[dstr->buf - 1] = '\0';
	return 0;
}

// copies a C string into a dstring
int dstrcpy(dstring* des, char* src) {
	size_t i;
	for (i = 0; i < des->buf - 1; i++) {
		des->str[i] = src[i];
	}
	return i;
}

// Returns a pointer to the dstrings member C string
char* getdstr(dstring* dstr) {
    return dstr->str;
}

// Read a line from a file into the dstring
// set 'fp' to 'stdin' for keyboard input
int staticsize_readdstr(dstring* dstr, FILE* fp) {
	char* input = (char*)malloc(sizeof(char) * dstr->buf);
	size_t i = 0;
	fgets(input, dstr->buf, fp);
	for (i = 0; i < dstr->buf; i++) {
		if (input[i] == '\n') {
			dstr->str[i] = '\0';
			break;
		} else {
			dstr->str[i] = input[i];
		}
	}
	free(input);
	return 0;
}

// Same as 'readdstr' but it automatically resizes the
// dstring to fit the inputted string
// Returns how many by how many chars the dstring increased
int autoresize_readdstr(dstring* dstr, FILE* fp) {

    // Variables
    char* input = (char*)malloc(sizeof(char) * dstr->buf);
    size_t i = 0;
    char c = 0;

    // Read input from stdin
    fgets(input, dstr->buf, fp);
	for (i = 0; i < dstr->buf; i++) {
		if (input[i] == '\n') {
			dstr->str[i] = '\0';
			break;
		} else {
			dstr->str[i] = input[i];
		}
	}

    // Read any 'leftover characters from stdin
    // Automatically resize the dstring
    // Add the newly read char to the dstring and null terminator
    while (feof(fp) == 0) {
        c = fgetc(fp);
        if (c == '\n') {
            break;
        }
        dresize(dstr, dstr->buf + 1);
        dstr->str[dstr->buf - 2] = c;
        dstr->str[dstr->buf - 1] = '\0';
    }

    // Free input
    free(input);

    // End
    return 0;
}
