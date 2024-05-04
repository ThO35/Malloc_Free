#ifndef MY_MALLOC_H
#define MY_MALLOC_H

#include <stddef.h>

/**
 * @brief Alloue une zone de mémoire de la taille spécifiée.
 *
 * Cette fonction alloue une zone de mémoire de la taille spécifiée en
 * paramètre. Elle retourne un pointeur vers la zone allouée, ou NULL en cas
 * d'échec.
 *
 * @param size La taille de la zone de mémoire à allouer.
 * @return Un pointeur vers la zone allouée, ou NULL en cas d'échec.
 */
void* my_malloc(size_t size);

/**
 * @brief Libère une zone de mémoire précédemment allouée.
 *
 * Cette fonction libère la zone de mémoire pointée par le pointeur passé en
 * paramètre. Après son exécution, la zone de mémoire est disponible pour
 * être réallouée.
 *
 * @param ptr Le pointeur vers la zone de mémoire à libérer.
 */
void my_free(void* ptr);

#endif /* MY_MALLOC_H */
