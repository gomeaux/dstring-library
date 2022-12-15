# dstring-library

dstring.h is a C header file I made as an exercise, and also because I don't like dealing with the garbage that are C strings. I modeled it
after the way you use file pointers in C. A dstring has to be initialized like a file pointer needs to be opened, and destroyed like a file
pointer needs to be closed. Resizing of the dstring is not automatic, but must be done by the user using a resize function. I should also
also mention it's called a "dstring" because its short for "dynamic string" since you can change it's size. Check main.c and dstring.h for
how to use a dstring.
