#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "detail.h"
#include "file.h"
#include "sort.h"
#include <unistd.h>

int main(int argc, char **argv){
        int num = 0;
        int opt = 0;
        int elements = 0;
        int sort = 0;
        while ((opt = getopt(argc, argv, "e:n:f:ds:h")) != -1){
                switch(opt){
                        case 'e':
                                elements = atoi(optarg);
                                break;
                        case 'n':
                                num = atoi(optarg);
                                break;
                        case 'h':
                                printf("помощь\n");
                                break;
                        case 's':
                                if(strcmp(optarg, "shacer") == 0){
                                        sort += 0;
                                        break;
                                }
                                if(strcmp(optarg, "heap") == 0){
                                        sort += 6;
                                        break;
                                }
                                if(strcmp(optarg, "qsort") == 0){
                                        sort += 12;
                                        break;
                                }
                        case 'f':
                                if(strcmp(optarg, "id") == 0){
                                        sort += 0;
                                }
                                if(strcmp(optarg, "name") == 0){
                                        sort += 2;
                                }
                                if(strcmp(optarg, "n") == 0){
                                        sort += 4;
                                }
                                break;
                        case 'd':
                                sort += 1;
                                break;
                        default:
                                break;
                }
        }
        if (sort >= 0 && sort < 18){
                printf("Количество массивов: %d\n", num);
                printf("Элементов: %d\n", elements);
                double time = time_sort_mass(sort, elements, num);
                printf("Время: %lf\n", time);
        }
        return 0;
}
