#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <string.h>
#include "detail.h"

void free_detail(Detail*);
void printMass(Detail*, size_t);
int input_keyboard(Detail**, size_t *);
char* my_readline(FILE*);
int write_txt(FILE*, Detail*, size_t);
int read_txt(FILE*, Detail**, size_t*);
int write_bin(FILE*, Detail*, size_t);
int read_bin(FILE*, Detail**, size_t*);

#endif
