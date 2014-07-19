
#ifndef CLASS_H
#define CLASS_H

#include <stddef.h>



typedef struct Class {
    size_t size;
    void * (* ctor) (void * _self, va_list * app);
    void * (* dtor) (void * _self);
    void * (* clone) (const void * _self);
    int (* differ) (const void * _self, const void * _b);
} Class;


#endif
