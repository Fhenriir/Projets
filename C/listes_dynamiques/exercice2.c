#include "exercice2.h"

struct tableau_variable{
    void* donnees;
    int tailleElements;
    int tailleTableaux;
    int placePrises;
};

T_var creer_var(int nbrElements,int placeElements){
    T_var Tab = malloc(sizeof(struct tableau_variable));
    Tab->donnees = malloc(nbrElements*placeElements);
    Tab->tailleElements = placeElements;
    Tab->tailleTableaux = nbrElements;
    Tab->placePrises = 0;
    return Tab;
}

void afficher_var(T_var tableau,void(*afficher_tout)(void*)){
    char* donnes_bit = tableau->donnees;
    printf("[ ");
    for (int i = 0; i < tableau->placePrises; i ++){
        void* ptr_donnees = donnes_bit + (i * tableau->tailleElements);
        (*afficher_tout)(ptr_donnees);

    }
    printf("[%d/%d] ",tableau->placePrises,tableau->tailleTableaux);
    printf("]\n");
}

T_var aleatoire_var(int nbrElements, int placeElements,int tailleTotal, void(*generer_random)()){
    T_var tableau = creer_var(tailleTotal,placeElements);
    char* donnes_bit = tableau->donnees;
    for (int i = 0; i < nbrElements; i ++){
        void* ptr_donnees = donnes_bit + (i * tableau->tailleElements);
        (*generer_random)(ptr_donnees);
        tableau->placePrises = tableau->placePrises + 1;
    }
    return tableau;
}

void push(T_var tableau,void* valeur){
    void* nouvelleValeur = malloc(tableau->tailleElements);
    if(tableau->placePrises == tableau->tailleTableaux){
        tableau->donnees = realloc(tableau->donnees,((tableau->tailleTableaux+1)*tableau->tailleElements));
        tableau->tailleTableaux++;
    }
    char* donnes_bit = tableau->donnees;
    void* ptr_donnees = donnes_bit + (tableau->placePrises * tableau->tailleElements);
    memcpy(ptr_donnees,valeur,tableau->tailleElements);
    tableau->placePrises++;
    free(nouvelleValeur);
}

void* pop(T_var tableau){
    void* nouvelleValeur = malloc(tableau->tailleElements);
    char* donnes_bit = tableau->donnees;
    void* ptr_donnees = donnes_bit + ((tableau->placePrises - 1 ) * tableau->tailleElements);
    memcpy(nouvelleValeur,ptr_donnees,tableau->tailleElements);
    if(tableau->placePrises == tableau->tailleTableaux){
        tableau->donnees = realloc(tableau->donnees,((tableau->tailleTableaux-1)*tableau->tailleElements));
        tableau->tailleTableaux--;
    }
    tableau->placePrises--;
    return nouvelleValeur;
}

void detruire_tout(T_var tableau,void(*detruire_type)(void*)){
    (*detruire_type)(tableau->donnees); 
    free(tableau);
}

void retirer_val(T_var tableau,int indice){
    char* donnes_bit = tableau->donnees;
    void* ptr_donnees_0 = donnes_bit + (indice * (tableau->tailleElements));
    void* ptr_donnees_1 = donnes_bit + ((indice+1) * (tableau->tailleElements));
    int taille = ((tableau->placePrises -1 -indice)*tableau->tailleElements);
    memcpy(ptr_donnees_0,ptr_donnees_1,taille);
    if(tableau->placePrises == tableau->tailleTableaux){
        tableau->donnees = realloc(tableau->donnees,((tableau->tailleTableaux-1)*tableau->tailleElements));
        tableau->tailleTableaux--;
    }
    tableau->placePrises--;
}

void inserer_val(T_var tableau,int indice,void* valeur){
    if(tableau->placePrises == tableau->tailleTableaux){
        tableau->donnees = realloc(tableau->donnees,((tableau->tailleTableaux+1)*tableau->tailleElements));
        tableau->tailleTableaux++;
    }
    char* donnes_bit = tableau->donnees;
    void* ptr_donnees_0 = donnes_bit + (indice * (tableau->tailleElements));
    void* ptr_donnees_1 = donnes_bit + ((indice+1) * (tableau->tailleElements));
    int taille = ((tableau->placePrises -indice)*tableau->tailleElements);
    memcpy(ptr_donnees_1,ptr_donnees_0,taille);
    memcpy(ptr_donnees_0,valeur,tableau->tailleElements);
    tableau->placePrises++;
}

void* maximum(T_var tableau,int (*comparateur)(void*,void*)){
    void* retour = malloc(tableau->tailleElements);
    char* donnes_bit = tableau->donnees;
    void* ptr_donnees = donnes_bit;
    memcpy(retour,ptr_donnees,tableau->tailleElements);
    for(int i = 1; i < (tableau->placePrises);i++){
        ptr_donnees = donnes_bit + (i*(tableau->tailleElements));
        if(((*comparateur)(ptr_donnees,retour))>0){
            memcpy(retour,ptr_donnees,tableau->tailleElements);
        }
    }
    return retour;
}

T_var slice(T_var tableau,int indice_debut,int indice_fin){
    T_var retour = creer_var((indice_fin-indice_debut),tableau->tailleElements);
    retour->placePrises = (indice_fin-indice_debut);
    char* donnes_bit = tableau->donnees;
    void* ptr_donnees = (donnes_bit + (indice_debut*(tableau->tailleElements)));
    memcpy(retour->donnees,ptr_donnees,(indice_fin-indice_debut)*tableau->tailleElements);
    return retour;
}