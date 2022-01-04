#include "fonction.hpp"

int main(){
	srand(time(NULL));
	Kmeans* A = new Kmeans(500,10);
	A->initialiser();
	//A->calculer(1);
	A->afficher_stats();
	A->exporter();
}