
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "class.h"
#include "new.h"
#include "string.h"



struct string_struct {
    const void * Class;
    char * text;
    size_t size;
};



static void * string_ctor(void * _self, va_list * app) {
    String * self = _self;

    // because null terminated strings suck
    const size_t s = va_arg(* app, const size_t);
    const char * t = va_arg(* app, const char *);

    self->text = malloc(s);
    assert(self->text);
    memcpy(self->text, t, s);
    self->size = s;

    return self;
}



static void * string_dtor(void * _self) {
    String * self = _self;
    free(self->text);
    return self;
}



static void * string_clone(const void * _self) {
    const String * self = _self;
    return new(String_t, self->size, self->text);
}



static int string_differ(const void * _self, const void * _b) {
    const String * self = _self, * b = _b;

    if (self == b)
    	return 0;
    if (!b || b->Class != String_t || self->size != b->size)
    	return 1;
    return memcmp(self->text, b->text, self->size);
}




static const struct Class _string = {
    sizeof(struct string_struct),
    string_ctor, string_dtor,
    string_clone, string_differ
};



const void * String_t = & _string;




size_t string_fwrite(const String * self, FILE * stream) {
    return fwrite(self->text, sizeof(char), self->size, stream);
}



size_t string_length(const String * self) {
    return self->size;
}



int string_max_size() {
    return INT_MAX;
}



char string_at(const String * self, int pos) {
    return *(self->text + pos % self->size);
}



String * string_append(const String * self, const String * b) {
    s = new(String_t, self->size, self->text);

    s->size = self->size + b->size;
    s->text = realloc(s->text, s->size);
    assert(s->text);

    memcpy(s->text + self->size, b->text);

    return s;
}

