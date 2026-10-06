#include "sort.h"


int comp_id(const void *mass1, const void *mass2) {
        Detail *mass_1 = (Detail *)mass1;
  Detail *mass_2 = (Detail *)mass2;
  return strcmp(mass_1->id, mass_2->id);
}

int comp_id_down(const void *mass1, const void *mass2) {
        Detail *mass_1 = (Detail *)mass1;
  Detail *mass_2 = (Detail *)mass2;
  return strcmp(mass_2->id, mass_1->id);
}

int comp_name(const void *mass1, const void *mass2) {
        Detail *mass_1 = (Detail *)mass1;
  Detail *mass_2 = (Detail *)mass2;
  return strcmp(mass_1->name, mass_2->name);
}

int comp_name_down(const void *mass1, const void *mass2) {
        Detail *mass_1 = (Detail *)mass1;
  Detail *mass_2 = (Detail *)mass2;
  return strcmp(mass_2->name, mass_1->name);
}


int comp_n(const void *mass1, const void *mass2) {
        Detail *mass_1 = (Detail *)mass1;
  Detail *mass_2 = (Detail *)mass2;
  return (mass_1->n - mass_2->n);
}

int comp_n_down(const void *mass1, const void *mass2) {
        Detail *mass_1 = (Detail *)mass1;
  Detail *mass_2 = (Detail *)mass2;
  return (mass_2->n - mass_1->n);
}



void shaker_sort(Detail *mass, size_t size, int (*comp)(const void *, const void *)) {
        if (size <= 1){
                return;
        }
        if(!comp){
                return;
        }
  size_t left = 0;
  size_t right = size - 1;
  int flag = 1;
  while (left < right && flag) {
                flag = 0;
    for (int i = left; i < right; i++) {
                        if (comp(&mass[i], &mass[i + 1]) > 0) {
                                Detail temp = mass[i];
        mass[i] = mass[i + 1];
        mass[i + 1] = temp;
        flag = 1;
                        }
    }
    right--;
    for (int i = right; i > left; i--) {
                        if (comp(&mass[i], &mass[i - 1]) < 0) {
                                Detail temp = mass[i];
        mass[i] = mass[i - 1];
        mass[i - 1] = temp;
        flag = 1;
      }
    }
    left++;
  }
}


void heap(Detail *mass, int n, int i, int (*comp)(const void*, const void*)){
        if (!comp){
                return;
  }
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < n && comp(&mass[left], &mass[largest]) > 0){
                largest = left;
  }
  if (right < n && comp(&mass[right], &mass[largest]) > 0){
                largest = right;
  }
  if (largest != i){
                Detail tmp = mass[i];
    mass[i] = mass[largest];
    mass[largest] = tmp;
    heap(mass, n, largest, comp);
  }
}


void heap_sort(Detail *mass, size_t size, int (*comp)(const void*, const void*)){
        if (!comp){
                return;
  }
  for (int i = size / 2 - 1; i >= 0; i--){
                heap(mass, size, i, comp);
  }
  for (int i = size - 1; i > 0; i--){
                Detail tmp = mass[0];
    mass[0] = mass[i];
    mass[i] = tmp;
    heap(mass, i, 0, comp);
  }
}

void sort_mass(Detail *mass, int sort, size_t size){
        int (*comp_mass[6])(const void*, const void*) = {comp_id, comp_id_down, comp_name, comp_name_down, comp_n, comp_n_down};
        if(sort / 6 == 0){
                        shaker_sort(mass, size, comp_mass[sort % 6]);
                }
        if(sort / 6 == 1){
                        heap_sort(mass, size, comp_mass[sort % 6]);
        }
        if(sort / 6 == 2){
                        qsort(mass, size, sizeof(Detail), comp_mass[sort % 6]);
                }
}

void generate_mass(int size, Detail **mass){
        *mass = realloc(*mass, size * sizeof(Detail));
        for (int i = 0; i < size; i++){
                const char *str = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
                const int id_len = 7;
                char *id = calloc(id_len+1, sizeof(char));
                for (int j = 0; j < id_len; j++){
                        id[j] = str[rand()%(strlen(str))];
                }
                memcpy((*mass + i) -> id, id, id_len);
                int name_len = (rand())%50 + 1;
                char *name = calloc(name_len + 1, sizeof(char));
                for (int j = 0; j < name_len; j++){
                        name[j] = str[rand()%(strlen(str))];
                }
                (*mass + i) -> name = malloc(name_len + 1);
                memcpy((*mass + i) -> name, name, name_len);
                int n = rand() + 1;
                (*mass + i) -> n = n;
                free(name);
                free(id);
        }
}


double time_sort_mass(int sort, int el, int num){
        double sred = 0;
        for (int i = 0; i < num; i++){
                Detail *mass = NULL;
                generate_mass(el, &mass);
                time_t first = clock();
                sort_mass(mass, sort, el);
                time_t end = clock();
                sred += end - first;
                for(int j = 0; j < el; j++){
                        free_detail(mass + j);
                }
                free(mass);
        }
        return (sred/num)/CLOCKS_PER_SEC;
}
