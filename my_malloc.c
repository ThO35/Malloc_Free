#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"
#include <string.h>

#define POOL_SIZE 1000000000 /* 1 Giga */
static char _mem_pool[POOL_SIZE]; 


size_t get_size_t_from_pool(size_t position) {
    size_t result;
    memcpy(&result, &_mem_pool[position], sizeof(size_t));
    return result;
}




void* init_malloc(size_t size) {
    void* tab = _mem_pool;
    size_t* suiv = (size_t*)tab;
    *suiv = size + sizeof(size_t) * 3;
    size_t* prec = (size_t*)(tab + sizeof(size_t));
    *prec = 0;
    size_t* taille = (size_t*)(tab + 2 * sizeof(size_t));
    *taille = size;
    _mem_pool[size + sizeof(size_t) * 3] = EOF; 
    return (void*)(tab + 3 * sizeof(size_t));
}


void* allouer(size_t size, size_t position, size_t dernier) {
    size_t* suiv = (size_t*)(_mem_pool + position);
    *suiv = position + size + sizeof(size_t) * 3;
    size_t* prec = (size_t*)(_mem_pool + position + sizeof(size_t));
    *prec = dernier;
    size_t* taille = (size_t*)(_mem_pool + sizeof(size_t) * 2 + position);
    *taille = size;
    _mem_pool[position + size + sizeof(size_t) * 3] = EOF; 
    return (void*)(_mem_pool + sizeof(size_t) * 3 + position);
}

void* allouer_entre(size_t size, size_t position, size_t dernier) {
    size_t* suiv = (size_t*)(_mem_pool + position+24+get_size_t_from_pool(position+16));
    *suiv = dernier;
    size_t* prec = (size_t*)(_mem_pool + position  +24+get_size_t_from_pool(position+16)+sizeof(size_t));
    *prec = position;
    size_t* taille = (size_t*)(_mem_pool + sizeof(size_t) * 2 + position+24+get_size_t_from_pool(position+16));
    *taille = size;
    size_t* prec_suiv = (size_t*)(_mem_pool + position);
    *prec_suiv = position+24+get_size_t_from_pool(position+16);
    size_t* suiv_prec = (size_t*)(_mem_pool + get_size_t_from_pool(dernier +8));
    *suiv_prec = *prec_suiv;
    return (void*)(_mem_pool + sizeof(size_t) * 3 + position);
}


void* my_malloc(size_t size) {
    if (size == 0 || size >= POOL_SIZE) 
        return NULL;
    if (!_mem_pool[0])
        return init_malloc(size);
    size_t position = get_size_t_from_pool(0);
    size_t dernier = 0;
    int possible = 0; 
    size_t somme =0;
    while (position < POOL_SIZE) {
        somme = dernier+24+get_size_t_from_pool(dernier+16);
        if(position-somme >= size + 24){
            possible = 2;
            break;
        }
        if (_mem_pool[position] == EOF) {
            if (position+8+8+8+size>POOL_SIZE)return NULL;
            possible = 1;
            break;
        }
        dernier = position;
        position = get_size_t_from_pool(position);
    }
    if (possible==1) {
        return allouer(size, position, dernier);
    }
    if (possible==2) {
        return allouer_entre(size, dernier, position);
    }
    return NULL;
}

void my_free(void* pouet) {
    size_t suivant = get_size_t_from_pool(0);
    size_t precedent = 0;
    for (size_t i = 0; i < POOL_SIZE; i++) {
        if (i == suivant) {
            precedent = suivant;
            suivant = get_size_t_from_pool(suivant); 
        }
        if (_mem_pool + i == pouet) { 
            size_t *suiv_prec = (size_t*)(_mem_pool + get_size_t_from_pool(precedent+8));
            *suiv_prec = suivant;
            return;
        }
    }
}


