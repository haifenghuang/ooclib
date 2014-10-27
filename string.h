
#ifndef STRING_H
#define STRING_H

#include <stdio.h>



extern const void * String_t;


typedef struct string_struct String;



size_t string_fwrite(const String * self, FILE * stream);
size_t string_length(const String * self);
int string_max_size();
char string_at(const String * self, int pos);
String * string_append(const String * self, const String * b);


#endif
