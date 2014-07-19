
#ifndef MAP_H
#define MAP_H



extern const void * Map_t;


typedef struct map_struct Map;



Map * map_insert(Map * self, unsigned long int index, const void * element);
Map * map_remove(Map * self, unsigned long int index);
void * map_lookup(const Map * self, unsigned long int index);
const void * map_lookup_ro(const Map * self, unsigned long int index);


#endif
