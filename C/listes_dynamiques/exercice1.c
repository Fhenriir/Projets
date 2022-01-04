#include "exercice1.h"

struct tableau{
	void* donnees;
	int tailleElements;
	int tailleTableaux;
};

T creer(int nbrElements,int placeElements){
	/*
	fonction de création d'un tableau générique en fonction:
	- du nombres d'éléments du tableau
	- de la taille d'un élément
	*/
	T Tab = malloc(sizeof(struct tableau));//allocation mémoire de la structure "tableau"
	Tab->donnees = malloc(nbrElements*placeElements);//allocation mémoire du tableau de données de "tableau"
	Tab->tailleElements = placeElements;//assignation de la taille individuel des éléments du tableau de données
	Tab->tailleTableaux = nbrElements;//assignation du nombre total d'élément du tableau de données
	return Tab;
}

void afficher(T tableau,void(*afficher_tout)(void*)){
	/*
	fonction d'affichage d'un tableau générique en fonction:
	- du tableau à afficher
	- de la fonction d'affichage à appliquer aux éléments du tableau
	*/
	char* donnes_bit = tableau->donnees;//transformation du tableau en un tableau de char (plus petit type de données dans la memoire)
	printf("[ ");//ouverture de l'affichage de la liste
	for (int i = 0; i < tableau->tailleTableaux; i ++){
		void* ptr_donnees = donnes_bit + (i * tableau->tailleElements);//on récupère la i ème données, pour cela on ce décale de i fois la taille d'un éléments
		(*afficher_tout)(ptr_donnees);//on applique la fonction d'affichage à l'élément séléctionné
	}
	printf("]\n");//retour à la ligne à la fin de l'affichage
}

T aleatoire(int nbrElements, int placeElements, void(*generer_random)()){
	/*
	fonction de génération d'un tableau aléatoire en fonction:
	- du nombre d'élément
	- de la taille d'un élément
	- d'un générateur d'éléments
	*/
	T tableau = creer(nbrElements,placeElements);//création de la structure tableau
	char* donnes_bit = tableau->donnees;//transformation du tableau en un tableau de char (plus petit type de données dans la memoire)
	for (int i = 0; i < tableau->tailleTableaux; i ++){
		void* ptr_donnees = donnes_bit + (i * tableau->tailleElements);//on récupère la i ème données, pour cela on ce décale de i fois la taille d'un éléments
		(*generer_random)(ptr_donnees);//on applique la fonction d'affichage à l'élément séléctionné
	}
	return tableau;
}

void detruire_tout(T tableau,void(*detruire_type)(void*)){
	/*
	fonction de suppréssion d'un tableau générique de la mémoire en fonction:
	- du tableau
	- d'un supprésseur d'éléments
	*/
	(*detruire_type)(tableau->donnees); 
	free(tableau);// libération de la mémoire alloué à la structure
}

T trier(T tableau, int(*compar)(void*,void*)){
	/*
	fonction de trie d'un tableau générique en fonction:
	- du tableau
	- d'un comparateur d'éléments
	*/
	char* donnes_bit = tableau->donnees;//transformation du tableau en un tableau de char (plus petit type de données dans la memoire)
	void* donnees_temporaire = malloc(tableau->tailleElements);
	for(int i = 1; i < tableau->tailleTableaux;i++){
		int j = i;
		void* ptr_donnees_0 = donnes_bit + (i * tableau->tailleElements);
		void* ptr_donnees_1 = donnes_bit + ((i-1) * tableau->tailleElements);
		while(((*compar)(ptr_donnees_0,ptr_donnees_1))<0){
			memcpy(donnees_temporaire,ptr_donnees_0,tableau->tailleElements);
			memcpy(ptr_donnees_0,ptr_donnees_1,tableau->tailleElements);
			memcpy(ptr_donnees_1,donnees_temporaire,tableau->tailleElements);
			if( j > 1){
				j = j-1;
				ptr_donnees_0 = donnes_bit + (j * tableau->tailleElements);
				ptr_donnees_1 = donnes_bit + ((j-1) * tableau->tailleElements);
			}
		}
	}
	free(donnees_temporaire);
	return tableau;
}