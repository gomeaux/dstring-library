# dstring-library

The dstring.h header is a fun project and exercise born out of
my personal frustration with how C strings generally are. I
basically wanted to see if I can make strings safe(r) in C.

The name "dstring" is short for "dynamic string" and consists
of a struct with just two elements, a character pointer and a
size_t for its buffer size. By doing this, every function that
interacts with a dstring has access to its buffer size, even
if its changed used 'resize_dstr.'

See 'main.c' for more information on how to use a dstring and
the functions used to interact with one. Let me know if you
find anything horribly wrong and I'll attempt to fix it.
