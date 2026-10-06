#ifndef SORT_H
#define SORT_H

#include "detail.h"
#include <time.h>
#include "file.h"


int comp_id(const void*, const void*);
int comp_name(const void*, const void*);
int comp_n(const void*, const void*);
int comp_id_down(const void*, const void*);
int comp_name_down(const void*, const void*);
int comp_n_down(const void*, const void*);
void shaker_sort(Detail*, size_t, int (const void*, const void*));
void heap(Detail*, int, int,  int (const void*, const void*));
void heap_sort(Detail*, size_t, int (const void*, const void*));
void sort_mass(Detail*, int, size_t);
void generate_mass(int, Detail**);
double time_sort_mass(int, int, int);


#endif
