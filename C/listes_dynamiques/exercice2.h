#ifndef EXERCICE2_H
#define EXERCICE2_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <math.h>
#include <string.h>
#include <time.h>

typedef struct tableau_variable* T_var;
T_var creer_var(int nbrElements,int placeElements);
void afficher_var(T_var,void(*afficher_tout)(void*));
T_var aleatoire_var(int nbrElements, int placeElements,int tailleTotal, void(*generer_random)());
void detruire_tout(T_var,void(*detruire_type)(void*));
void push(T_var tableau,void* valeur);
void* pop(T_var tableau);
void retirer_val(T_var tableau,int indice);
void inserer_val(T_var tableau,int indice,void* valeur);
void* maximum(T_var tableau,int (*comparateur)(void*,void*));
T_var slice(T_var tableau,int indice_debut,int indice_fin);

#endif