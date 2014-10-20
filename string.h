
#ifndef STRING_H
#define STRING_H



extern const void * String_t;


typedef struct string_struct String;



const char * string_gettext_ro(const String * self);
int string_length(const String * self);
int string_max_size();
char string_at(const String * self, int pos);


#endif
