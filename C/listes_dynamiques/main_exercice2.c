#include "exercice2.h"

struct test {
    long long int a;
    long long int b;
    long long int c;
};

void afficher_structure(void* donnees) {
    struct test* donnees_traduites = donnees;
    printf("[%lli, %lli, %lli]", donnees_traduites->a,donnees_traduites->b,donnees_traduites->c);
}

void aleatoire_structure(void* ptr_donnees) {
    struct test* lastructure = malloc(sizeof(struct test));
    lastructure->a = (long long int) rand();
    lastructure->b = (long long int) rand();
    lastructure->c = (long long int) rand();
    memcpy(ptr_donnees,lastructure,sizeof(struct test));
    free(lastructure);
}

int compare_int(void* gint1,void* gint2){ //cette fonction permet de comparer deux int entre eux
    int int1 = *(int*) gint1;
    int int2 = *(int*) gint2;
    if (int1 < int2){
        return -1;
    }
    else if (int1 > int2){
        return 1;
    }
    else {
        return 0;
    }
}

void detruire_struct(void* donnees) {
    free(donnees);
}

void afficher_int(void* donnees) {
    printf("%d ",(*(int*) donnees));
}

void aleatoire_int(void* ptr_donnees) {
    *(int*)ptr_donnees = rand()%10;
}

void detruire_int(void* donnees) {
    free(donnees);
}

void push_int(void* ptr_donnees, void* element){
    *(int*)ptr_donnees = *(int*) element;
}

int main() {

    T_var tableau = aleatoire_var(8,sizeof(int),10,&aleatoire_int);
    T_var tableau_1 = aleatoire_var(8,sizeof(struct test),10,&aleatoire_structure);

    afficher_var(tableau,afficher_int); // affichage de tableau
    afficher_var(tableau_1,afficher_structure); // affichage de tableau_1

    int a = 8473843;
    int b = 1000000;
    push(tableau,&a);

    afficher_var(tableau,afficher_int); // affichage de tableau

    void* popped = pop(tableau);
    free(popped);
    popped = pop(tableau);
    free(popped);

    afficher_var(tableau,afficher_int);
    retirer_val(tableau,0);
    afficher_var(tableau,afficher_int);
    inserer_val(tableau,2,&b);
    afficher_var(tableau,afficher_int);
    int* max = maximum(tableau, &compare_int);
    printf("%d \n",*max);
    free(max);
    T_var tableau_slice = slice(tableau,2,6);
    afficher_var(tableau_slice,afficher_int);
    detruire_tout(tableau_slice,detruire_int);

    popped = pop(tableau_1);
    free(popped);
    popped = pop(tableau_1);
    free(popped);

    afficher_var(tableau_1,afficher_structure);

    detruire_tout(tableau,detruire_int); // destruction de tableau
    detruire_tout(tableau_1,detruire_struct); // destruction de tableau_1

   
    return EXIT_SUCCESS;
}
