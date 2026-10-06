#include "file.h"

void free_detail(Detail* mass){
        if(mass -> name != NULL){
                free(mass -> name);
        }
}


char* my_readline(FILE *fptr){
        char buf[81] = {0};
        char *res = NULL;
        int len = 0;
        int n = 0;
        do{
                n = fscanf(fptr, "%80[^\n]", buf);
                if (n < 0){
                        if (!res){
                                return NULL;
                        }
                }
                else if (n == 1){
                        int chunk_len = strlen(buf);
                        int str_len = len + chunk_len;
                        res = realloc(res, str_len + 1);
                        memcpy(res + len, buf, chunk_len);
                        len = str_len;
                }
                else if (n == 0){
                        fscanf(fptr, "%*c");
                }
        }while (n > 0);
        if (len > 0){
                res[len] = '\0';
        }
        else{
                res = calloc(1, sizeof(char));
        }
        return res;
}


int input_keyboard(Detail** mass, size_t *size){
        *size = 0;
        int new_size;
        printf("Введите количество элементов массива: ");
        int a = scanf("%d", &new_size);
        if (a == EOF || new_size <= 0){
                return -1;
        }
        *size = (size_t)new_size;
        scanf("%*c");
        *mass = calloc(*size, sizeof(Detail));
        if (mass == NULL){
                return -2;
        }
        for (int i = 0; i < (int)*size; i++){
                char *id = NULL, *name = NULL;
                int n = 0;
                printf("Введите id: ");
                id = my_readline(stdin);
                if(id){
                        while(strlen(id) > 8){
                                printf("Повторите попытку: ");
                                char *new_id = my_readline(stdin);
                                if(new_id == NULL){
                                        free(id);
                                        for(int j = 0; j < i; j++){
                                                free_detail((*mass + j));
                                        }
                                        free(*mass);
                                        return -2;
                                }
                                free(id);
                                id = new_id;
                        }
                }
                else{
                        for(int j = 0; j < i; j++){
                                free_detail((*mass + j));
                        }
                        free(*mass);
                        return -2;
                }
                printf("Введите name: ");
                name = my_readline(stdin);
                if(name == NULL){
                        return -2;
                }
                printf("Введите n: ");
                a = scanf("%d", &n);
                if(a == EOF){
                        free(name);
                        free(id);
                        for(int j = 0; j < i; j++){
                                free_detail((*mass + i));
                        }
                        free(*mass);
                        return -1;
                }
                while(n < 1 && a != EOF){
                        scanf("%*[^\n]");
                        printf("Повторите попытку: ");
                        a = scanf("%d", &n);
                        if(a == EOF){
                                free(name);
                                free(id);
                                for(int j = 0; j < i; j++){
                                        free_detail((*mass + i));
                                }
                                free(*mass);
                                return -1;
                        }
                        if(n > 0 && a == 1){
                                break;
                        }
                }
                scanf("%*c");
                (*mass + i)->name = malloc(strlen(name) + 1);
                memcpy((*mass + i)->id, id, strlen(id) + 1);
                memcpy((*mass + i)->name, name, strlen(name) + 1);
                (*mass + i)->n = n;
                free(id);
                free(name);
        }
        return 1;
}

void printMass(Detail *mass, size_t size){
        for (int i = 0; i < size; i++){
                printf("INDEX: %d\nID: %s\nNAME: %s\nN: %d\n", i, (mass + i)->id, (mass + i)->name, (mass+i)->n);
        }
}


int write_txt(FILE *fptr, Detail *mass, size_t size){
        if(!fptr){
                return -3;
        }
        fprintf(fptr, "%ld\n", size);
        for (int i = 0; i < size; i++){
                fprintf(fptr, "%s\n%s\n%d\n", (mass + i)->id, (mass + i)->name, (mass+i)->n);
        }
        return 1;
}

int read_txt(FILE *fptr, Detail **mass, size_t *size){
        if(!fptr){
                return -3;
        }
        if(fscanf(fptr, "%ld\n", size) != 1 || *size <= 0){
                return -4;
        }
        *mass = calloc(*size, sizeof(Detail));
        if (mass == NULL){
                return -2;
        }
        int real = 0;
        for (int i = 0; i < *size; i++){
                char *id = my_readline(fptr);
                if (id == NULL){
                        return -2;
                }
                char *name = my_readline(fptr);
                if(name == NULL){
                        return -2;
                }
                int n = 0;
                if(fscanf(fptr, "%d\n", &n) != 1){
                        return -1;
                }
                if(n < 0 || strlen(id) > 8){
                        free(id);
                        free(name);
                        continue;
                }
                (*mass + real)->name = malloc(strlen(name) + 1);
                memcpy((*mass + real)->id, id, strlen(id) + 1);
                memcpy((*mass + real)->name, name, strlen(name) + 1);
                (*mass + real)->n = n;
                free(id);
                free(name);
                real++;
        }
        *size = real;
        *mass = realloc(*mass, *size * sizeof(Detail));
        return 1;
}


int write_bin(FILE *fptr, Detail *mass, size_t size){
        if(!fptr){
                return -3;
        }
        const char *mark = ".CAT";
        const char enter = '\n';
        fwrite(mark, 1, 4, fptr);
        fwrite(&size, 8, 1, fptr);
        for (int i = 0; i < size; i++){
                if(fwrite((mass + i)->id, 1, strlen((mass + i)->id), fptr) != strlen((mass + i)->id)){
                        return -4;
                }
                fwrite(&enter, 1, 1, fptr);
                if(fwrite((mass + i)->name, 1, strlen((mass + i)->name), fptr) != strlen((mass + i)->name)){
                        return -4;
                }
                fwrite(&enter, 1, 1, fptr);
                if(fwrite(&(mass + i)->n, 4, 1, fptr) != 1){
                        return -4;
                }
        }
        return 1;
}

int read_bin(FILE *fptr, Detail **mass, size_t *size){
        if(!fptr){
                return -3;
        }
        char mark[5] = {0};
        fread(&mark, 1, 4, fptr);
        if(strcmp(mark, ".CAT") != 0){
                return -5;
        }
        fread(size, 8, 1, fptr);
        *mass = calloc(*size, sizeof(Detail));
        if (mass == NULL){
                return -2;
        }
        int real = 0;
        for (int i = 0; i < *size; i++){
                char simv = ' ';
                char *id = calloc(1, sizeof(char));
                int id_len = 1;
                int name_len = 1;
                while(simv != '\n'){
                        id = realloc(id, id_len);
                        fread(&simv, 1, 1, fptr);
                        if(simv == '\n'){
                                id[id_len - 1] = '\0';
                                break;
                        }
                        memcpy(id + id_len - 1, &simv, 1);
                        id_len++;
                }
                simv = ' ';
                char *name = calloc(1, sizeof(char));
                while(simv != '\n'){
                        name = realloc(name, name_len);
                        fread(&simv, 1, 1, fptr);
                        if(simv == '\n'){
                                name[name_len - 1] = '\0';
                                break;
                        }
                        memcpy(name + name_len - 1, &simv, 1);
                        name_len++;
                }
                int n = 0;
                fread(&n, 4, 1, fptr);
                if(n < 0 || strlen(id) > 8){
                        free(id);
                        free(name);
                        continue;
                }
                (*mass + real)->name = calloc( name_len, sizeof(char));
                memcpy((*mass + real)->id, id, strlen(id) + 1);
                memcpy((*mass + real)->name, name, strlen(name) + 1);
                (*mass + real)->n = n;
                free(id);
                free(name);
                real++;
        }
        *size = real;
        *mass = realloc(*mass, *size * sizeof(Detail));
        return 1;
}
