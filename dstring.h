/* DSTRING STRUCTURE */
typedef struct dstring {
    char* str;
    size_t buf;
} dstring;

/* you already know fr fr*/
#include <stdlib.h>

/* Getter functions */
char* get_dstr(dstring* dstr) { return dstr->str; }
size_t dstr_buf(dstring* dstr) { return dstr->buf; }
size_t dstr_len(dstring* dstr) {
    const char* end;
    for (end = dstr->str; *end != '\0'; ++end) {
        if (end - dstr->str == dstr->buf - 1) {
            return dstr->buf - 1;
        }
    }
    return end - dstr->str;
}

/* Returns a specific character from the dstring */
/* Acts as the [] operators. doing index(dstr, 0) returns dstr->str[0] */
/* might remove this idk if its going to be useful*/
int index_dstr(dstring* dstr, size_t i) {
    if (i < 0 || i > dstr->buf - 1) {
        return -1;
    }
    return dstr->str[i];
}

/* Returns a pointer to an initialized dstring */
dstring* init_dstr() {

    /* Allocate memory on the heap for dstring*/
    dstring* dstr = (dstring*)malloc(sizeof(dstring) * 1);

    dstr->buf = 1; /* Setup member values*/
    dstr->str = (char*)malloc(sizeof(char) * dstr->buf);
    dstr->str[dstr->buf - 1] = '\0';

    /* End*/
    return dstr;
}

/* Frees a single dstring* */
int free_dstr(dstring* dstr) {
    free(dstr->str);
    dstr->str = NULL;
    free(dstr);
    dstr = NULL;
    return 0;
}

/* Resizes the dstring. Keeps or cuts down pevious contents */
/* Still ensures that the last character is a null terminator*/
int resize_dstr(dstring* dstr, size_t newsize) {
    dstring* temp = dstr;
	if (newsize < 1) { return 1; }
	dstr->buf = newsize;
	dstr->str = (char*)realloc(dstr->str, newsize);
	dstr->str[dstr->buf - 1] = '\0';
    if (temp != dstr) { free_dstr(temp); }
	return 0;
}

/* Read a line from a stdin into dstring */
/* Does not resize the dstring           */
char* read_dstr(dstring* dstr) {

    /* Variables */
    size_t i = 0;

    /* read from stdin */
    if (fgets(dstr->str, dstr->buf, stdin) == NULL) {
        return NULL;
    }

    /* Get rid of trailing '\n' if it exists */
    /* Ensure that buf - 1 is also a newline*/
    for (i = 0; i < dstr->buf; i++) {
        if (dstr->str[i] == '\n' || dstr->str[i] == '\0') {
            dstr->str[i] = '\0';
            break;
        }
    }
    dstr->str[dstr->buf - 1] = '\0';

    /* End */
    return dstr->str;
}

/* Read a line from stdin into dstring */
/* Will resize the dstring if necessary*/
char* rread_dstr(dstring* dstr) {

    /* Variables */
    char c = (char)0;

    /* Use read_dstr to read from stdin */
    if (read_dstr(dstr) == NULL) {
        return NULL;
    }

    /* For every char leftover in stdin, increment
    the dstring and add the character. I have nightmares
    about people actually reading my code */
    while (feof(stdin) == 0) {
        c = fgetc(stdin);
        if (c == '\n') { break; }
        if (dstr_len(dstr) == dstr->buf - 1) {
            resize_dstr(dstr, dstr->buf + 1);
        }
        dstr->str[dstr->buf - 2] = c;
        dstr->str[dstr->buf - 1] = '\0';
    }

    /* End */
    return dstr->str;
}

/* Reads a line from a file, does not resize the dstring */
/* Includes the newline character at the end if found. */
/* This is basically a wrapper for fgets */
char* fread_dstr(dstring* dstr, FILE* fp) {

    /* Read from file */
    if (fgets(dstr->str, dstr->buf, fp) == NULL) {
        return NULL;
    }

    /* End */
    return dstr->str;
}

/* Reads a line from a file, resize the dstring if necessary */
/* Like the previous function, this wraps fgets and includes newlines */
/* If it encounters a newline or EOF is reached, then it stops reading*/
char* frread_dstr(dstring* dstr, FILE* fp) {

    /* Variables */
    char c = 0;

    /* Read from file */
    if (fread_dstr(dstr, fp) == NULL) {
        return NULL;
    }

    /* Keep adding characters until newline or EOF */
    /* Remember to include BOTH '\n' if found AND '\0' */
    while (feof(fp) == 0) {
        c = fgetc(fp);
        if (dstr_len(dstr) == dstr->buf - 1) {
            resize_dstr(dstr, dstr->buf + 1);
        }
        dstr->str[dstr->buf - 2] = c;
        dstr->str[dstr->buf - 1] = '\0';
        if (c == '\n') { break; }
    }
}
