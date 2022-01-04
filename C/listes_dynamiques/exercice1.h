#ifndef EXERCICE1_H
#define EXERCICE1_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <math.h>
#include <string.h>
#include <time.h>

typedef struct tableau* T;
T creer(int nbrElements,int placeElements);
void afficher(T,void(*afficher_tout)(void*));
T aleatoire(int nbrElements, int placeElements, void(*generer_random)());
void detruire_tout(T,void(*detruire_type)(void*));
T trier(T tableau, int(*compar)(void*,void*));

#endif