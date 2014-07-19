
#include <stdarg.h>
#include <stddef.h>
#include <Judy.h>
#include <assert.h>
#include "class.h"
#include "new.h"
#include "map.h"



struct map_struct {
    const void * Class;
    void * jarray;
};




static void * map_ctor(void * _self, va_list * app) {
    Map * self = _self;
    
    self->jarray = NULL;
    return self;
}



static void * map_dtor(void * _self) {
	Map * self = _self;
	void * pvalue; unsigned long int index, count; int rc, i;

    JLC(count, self->jarray, 0, -1);
    for (i=1; i<=count; i++) {
    	JLBC(pvalue, self->jarray, i, index);
    	delete(*(struct Class **)pvalue);
    }

    JLFA(rc, self->jarray);
    return self;
}



static void * map_clone(const void * _self) {
	const Map * self = _self;
	void * pva, * pvb; unsigned long int index, count; int i;

	Map * cl = new(Map_t);

	JLC(count, self->jarray, 0, -1);
	for (i=1; i<=count; i++) {
		JLBC(pva, self->jarray, i, index);
		JLI(pvb, cl->jarray, index);
		assert(pvb != PJERR);
		*(struct Class **)pvb = clone(*(struct Class **)pva);
	}

	return cl;
}



static int map_differ(const void * _self, const void * _b) {
	const Map * self = _self, * b = _b;
    void * pv_self, * pv_b; unsigned long int count_self, count_b, index_self, index_b;
    int i;

	if (self == b)
		return 0;
	if (!b || b->Class != Map_t)
		return 1;

    JLC(count_self, self->jarray, 0, -1);
    JLC(count_b, b->jarray, 0, -1);
    if (count_self != count_b)
    	return 1;

    for (i=1; i<=count_self; i++) {
    	JLBC(pv_self, self->jarray, i, index_self);
    	JLBC(pv_b, b->jarray, i, index_b);
    	if (index_self != index_b)
    		return 1;
    	if (differ(*(struct Class **)pv_self, *(struct Class **)pv_b) == 1)
    		return 1;
    }

	return 0;
}




static const struct Class _map = {
    sizeof(struct map_struct),
    map_ctor, map_dtor,
    map_clone, map_differ
};



const void * Map_t = & _map;




Map * map_insert(Map * self, unsigned long int index, const void * element) {
    void * pvalue;
	
	JLI(pvalue, self->jarray, index);
	assert(pvalue != PJERR);

    *(struct Class **)pvalue = clone(element);

    return self;
}



Map * map_remove(Map * self, unsigned long int index) {
    void * pvalue; int rc;
    
    JLG(pvalue, self->jarray, index);
    assert(pvalue != PJERR);
    if (pvalue != NULL)
        delete(*(struct Class **)pvalue);

	JLD(rc, self->jarray, index);
	assert(rc != JERR);

	return self;
}



void * map_lookup(const Map * self, unsigned long int index) {
	void * pvalue;

	JLG(pvalue, self->jarray, index);
	assert(pvalue != PJERR);

	if (pvalue == NULL)
        return NULL;

    return clone(*(struct Class **)pvalue);
}



const void * map_lookup_ro(const Map * self, unsigned long int index) {
    void * pvalue;

    JLG(pvalue, self->jarray, index);
    assert(pvalue != PJERR);

    if (pvalue == NULL)
        return NULL;

    return *(struct Class **)pvalue;
}

