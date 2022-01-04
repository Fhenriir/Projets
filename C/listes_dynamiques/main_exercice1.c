#include "exercice1.h"

struct test {
    long long int a;
    long long int b;
    long long int c;
};

void afficher_structure(void* donnees) {
    struct test* donnees_traduite = donnees;
    printf("[%lli,%lli,%lli] ",donnees_traduite->a,donnees_traduite->b,donnees_traduite->c);
}

void aleatoire_structure(void* ptr_donnees) {
    struct test* lastructure = ptr_donnees;
    lastructure->a =(long long int) rand();
    lastructure->b =(long long int) rand();
    lastructure->c =(long long int) rand();
}

void detruire_struct(void* donnees) {
    free(donnees);
}

void afficher_int(void* donnees) {
    printf("%d ",(*(int*) donnees));
}

void aleatoire_int(void* ptr_donnees) {
    *(int*) ptr_donnees = rand()%20;
}

void detruire_int(void* donnees) {
    free(donnees);
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

int main() {

    srand(time(NULL));
    T array = aleatoire(20,sizeof(int),&aleatoire_int);
    T array_1 = aleatoire(3,sizeof(struct test),&aleatoire_structure);

    afficher(array,&afficher_int); // affichage de array
    afficher(array_1,&afficher_structure); // affichage de array_1

    array = trier(array, &compare_int);
    afficher(array,&afficher_int); // affichage de array

    detruire_tout(array,&detruire_int); // destruction de array
    detruire_tout(array_1,&detruire_struct); // destruction de array_1

    return EXIT_SUCCESS;
}
