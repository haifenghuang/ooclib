
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "class.h"
#include "new.h"
#include "string.h"



struct string_struct {
    const void * Class;
    char * text;
};



static void * string_ctor(void * _self, va_list * app) {
    String * self = _self;
    const char * t = va_arg(* app, const char *);

    self->text = malloc(strlen(t) + 1);
    assert(self->text);
    strcpy(self->text, t);
    return self;
}



static void * string_dtor(void * _self) {
    String * self = _self;
    free(self->text);
    return self;
}



static void * string_clone(const void * _self) {
    const String * self = _self;
    return new(String_t, self->text);
}



static int string_differ(const void * _self, const void * _b) {
    const String * self = _self, * b = _b;

    if (self == b)
    	return 0;
    if (!b || b->Class != String_t)
    	return 1;
    return strcmp(self->text, b->text);
}




static const struct Class _string = {
    sizeof(struct string_struct),
    string_ctor, string_dtor,
    string_clone, string_differ
};



const void * String_t = & _string;




const char * string_gettext_ro(const String * self) {
    return self->text;
}

