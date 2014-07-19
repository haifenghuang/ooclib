
#ifndef LIST_H
#define LIST_H



extern const void * List_t;


typedef struct list_struct List;



void * list_head(const List * self);
const void * list_head_ro(const List * self);

List * list_tail(List * self);
List * list_drop(List * self, unsigned long int num);
List * list_take(List * self, unsigned long int num);

List * list_cons(const void * element, List * self);
List * list_append(List * self, const List * b);

void * list_lookup(const List * self, unsigned long int index);
const void * list_lookup_ro(const List * self, unsigned long int index);


#endif
