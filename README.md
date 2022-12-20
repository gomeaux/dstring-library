# dstring-library

The dstring.h header file is a library I made partially for a fun exercise, and also
to vent some frustration with the way C strings are. A dstring can be dynamically
resized, and has its buffer size stored inside it. Check the main.c file for reference
on how to use the library and its functions. It should be pretty simple, considering a
dstring is just a char* and size_t inside a struct.

I also remade a bunch of the string.h functions to have a third argument, n. N is used 
to specify an upper limit to those functions and prevent buffer overflows. I think most
of these already exist in the C standard, but idk so I made them anyways

Let me know if something sucks. Might fix it, might not log on for another 4 months. idk.
