#ifndef DETAIL_H
#define DETAIL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  char id[9];
  char *name;
  int n;
} Detail;


void free_detail(Detail*);
void print_detail(Detail*);
int check_id(char*);
int check_n(char*);
Detail random_detail();

#endif
