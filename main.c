#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "detail.h"
#include "file.h"
#include "sort.h"
#include <unistd.h>

int main(int argc, char **argv){
        Detail *mass = NULL;
        size_t size = 0;
        char *input = NULL, *output = NULL;
        int opt = 0;
        int flag = 0;
        int sort = 0;
        while ((opt = getopt(argc, argv, "i:s:f:do:h")) != -1){
                switch(opt){
                        case 'i':
                                input = optarg;
                                break;
                        case 'o':
                                output = optarg;
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
        if (input){
                if(strcmp(input, "keyboard") == 0){
                        flag = input_keyboard(&mass, &size);
                        if(flag != 1){
                                printf("ОШИБКА ВВОДА\n");
                                return 0;
                        }
                }
                else{
                        FILE *fptr = NULL;
                        char *format = calloc(5, sizeof(char));
                        memcpy(format, input + strlen(input) - 4, 5);
                        if(strcmp(format, ".bin") == 0){
                                        fptr = fopen(input, "rb");
                                        if(!fptr){
                                                printf("ОШИБКА ОТКРЫТИЯ ФАЙЛА\n");
                                                return 0;
                                        }
                                        flag = read_bin(fptr, &mass, &size);
                                                                                                                       printf("flag%d\n", flag);
                        }
                        else if(strcmp(format, ".txt") == 0){
                                        fptr = fopen(input, "r");
                                        if(!fptr){
                                                printf("ОШИБКА ОТКРЫТИЯ ФАЙЛА\n");
                                                return 0;
                                        }
                                        flag = read_txt(fptr, &mass, &size);
                        }
                        free(format);
                        if(fptr){
                                fclose(fptr);
                        }
                }
                if(flag != 1){
                        printf("ОШИБКА ЧТЕНИЯ ФАЙЛА\n");
                        return 0;
                }
        }
        if (sort >= 0 && sort < 18){
                sort_mass(mass, sort, size);
        }
        if (output){
                if(strcmp(output, "screen") == 0){
                        printMass(mass, size);
                }
                else{
                        FILE *fptr = NULL;
                        char *format = calloc(5, sizeof(char));
                        memcpy(format, output + strlen(output) - 4, 5);
                        if(strcmp(format, ".bin") == 0){
                                        fptr = fopen(output, "wb");
                                        if(!fptr){
                                                printf("ОШИБКА ОТКРЫТИЯ ФАЙЛА\n");
                                                return 0;
                                        }
                                        flag = write_bin(fptr, mass, size);
                        }
                        else if(strcmp(format, ".txt") == 0){
                                        fptr = fopen(output, "w");
                                        if(!fptr){
                                                printf("ОШИБКА ОТКРЫТИЯ ФАЙЛА\n");
                                                return 0;
                                        }
                                        flag = write_txt(fptr, mass, size);
                        }
                        free(format);
                        if(fptr){
                                fclose(fptr);
                        }
                }
                if(flag != 1){
                        printf("ОШИБКА ЗАПИСИ ФАЙЛА\n");
                        return 0;
                }
        }
        for(int i = 0; i< size; i++){
                free_detail(mass+i);
        }
        free(mass);
        return 0;
}
