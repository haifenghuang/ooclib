
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "class.h"
#include "new.h"
#include "list.h"



typedef struct node_struct node;



struct list_struct {
    const void * Class;
    node * head;
};



struct node_struct {
    void * item;
    node * next;
};




static void * list_ctor(void * _self, va_list * app) {
    List * self = _self;

    self->head = NULL;
    return self;
}



static void * list_dtor(void * _self) {
    List * self = _self;
    node * p = self->head, * n;

    while (p != NULL) {
        n = p->next;
        delete(p->item);
        free(p);
        p = n;
    }

    return self;
}



static void * list_clone(const void * _self) {
    const List * self = _self;
    node * p, * n;

    List * cl = new(List_t);

    p = self->head; n = cl->head;
    while (p != NULL) {
        n = malloc(sizeof(node));
        assert(n != NULL);
        n->item = clone(p->item);
        p = p->next;
        n = n->next;
    }

    return cl;
}



static int list_differ(const void * _self, const void * _b) {
    const List * self = _self, * b = _b;
    node * p, * n;

    if (self == b)
        return 0;
    if (!b || b->Class != List_t)
        return 1;

    p = self->head; n = b->head;
    while (p != NULL || n != NULL) {
        if (p == NULL || n == NULL)
            return 1;
        if (differ(p->item, n->item))
            return 1;
        p = p->next; n = n->next;
    }

    return 0;
}




static const struct Class _list = {
	sizeof(struct list_struct),
	list_ctor, list_dtor,
	list_clone, list_differ
};



const void * List_t = & _list;




void * list_head(const List * self) {
    node * p = self->head;

    if (p == NULL)
        return NULL;

    return clone(p->item);
}



const void * list_head_ro(const List * self) {
    node * p = self->head;

    if (p == NULL)
        return NULL;

    return p->item;
}



List * list_tail(List * self) {
    list_drop(self,1);
}



List * list_drop(List * self, unsigned long int num) {
    node * p = self->head, * n;

    while (num > 0 && p != NULL) {
        n = p->next;
        delete(p->item);
        free(p);
        p = n;
        num--;
    }

    self->head = p;
    return self;
}



List * list_take(List * self, unsigned long int num) {
    node * p = self->head, * n;

    while (num > 0 && p != NULL) {
        p = p->next;
        num--;
    }

    while (p != NULL) {
        n = p->next;
        delete(p->item);
        free(p);
        p = n;
    }

    return self;
}



List * list_cons(const void * element, List * self) {
    node * old, * new;

    old = self->head;
    new = malloc(sizeof(node));
    assert(new != NULL);

    self->head = new;
    new->item = clone(element);
    new->next = old;

    return self;
}



List * list_append(List * self, const List * b) {
    node ** p = &(self->head);
    node * n = b->head;

    while (*p != NULL) { p = &((*p)->next); }

    while (n != NULL) {
        (*p) = malloc(sizeof(node));
        assert((*p) != NULL);
        (*p)->item = clone(n->item);
        p = &((*p)->next);
        n = n->next;
    }

    return self;
}



void * list_lookup(const List * self, unsigned long int index) {
    node * p = self->head;

    while (index != 0) {
        if (p == NULL)
            return NULL;
        p = p->next;
        index--;
    }

    if (p == NULL || p->item == NULL)
        return NULL;

    return clone(p->item);
}



const void * list_lookup_ro(const List * self, unsigned long int index) {
    node * p = self->head;

    while (index != 0) {
        if (p == NULL)
            return NULL;
        p = p->next;
        index--;
    }

    if (p == NULL)
        return NULL;

    return p->item;
}

