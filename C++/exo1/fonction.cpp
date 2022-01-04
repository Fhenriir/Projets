#include "fonction.hpp"

Kmeans::Kmeans(int nbrPoints,int nbrCentroides){
	this->nbrCentroides = nbrCentroides;
	for (int i; i < nbrPoints; i++){
		Point lepoint = Point(rand()%100,rand()%100);
		this->vectorP.push_back(lepoint);
	}
}

void Kmeans::initialiser(){
	int itt = 0;
	for(int u = 0; u < this->nbrCentroides; u++){
		while(itt < nbrCentroides){
			Point lebonpoint = this->vectorP[rand()%this->vectorP.size()];
			if(find(this->vectorC.begin(),this->vectorC.end(),lebonpoint)== this->vectorC.end()){
				this->vectorC.push_back(lebonpoint);
				itt++;
			}
		}
	}
	Point leplusproche;
	for(long unsigned int i = 0; i < this->vectorP.size();i++){
		leplusproche = vectorC[0];
		double laDistance = this->vectorP[i].distance(this->vectorC[0]);
		leplusproche.afficher();
		this->vectorP[i].afficher();
		std::cout << "distance initial " << laDistance << std::endl;
		for(long unsigned int u = 1; u < this->vectorC.size();u++){
			std::cout << laDistance <<" vs " << this->vectorP[i].distance(this->vectorC[u]);
			if (this->vectorP[i].distance(this->vectorC[u]) < laDistance){
				std::cout << " oui" << std::endl;
				laDistance = this->vectorP[i].distance(this->vectorC[u]);
				leplusproche = this->vectorC[u];
			}
			else{
				std::cout << " non" << std::endl;
			}
		}
		this->mapP[this->vectorP[i]] = leplusproche;
	}
}

void Kmeans::calculer(int iteration){
	for(int x = 0; x <iteration;x++){
		for(long unsigned int w = 0; w < this->vectorC.size();w++){
			int avrgX = 0;
			int avrgY = 0;
			int nbrPoints = 1;
			for(long unsigned int k = 0; k < this->vectorP.size();k++){
				if(this->mapP[this->vectorP[k]] == this->vectorC[w]){
					avrgX = avrgX + this->vectorP[k].getPointX();
					avrgY = avrgY + this->vectorP[k].getPointY();
					nbrPoints++;
				}
			}
			if(nbrPoints != 0){
				avrgX =(int)(avrgX / nbrPoints);
				avrgY =(int)(avrgY / nbrPoints);
			}
			this->vectorC[w].translater(avrgX,avrgY);
		}
		for(long unsigned int i = 0; i < this->vectorP.size();i++){
			Point leplusproche = this->vectorC[0];
			for(long unsigned int u = 0; u < this->vectorC.size();u++){
				if (this->vectorP[i].distance(this->vectorC[u]) < this->vectorP[i].distance(leplusproche)){
					leplusproche = this->vectorC[u];
				}
			}
			this->mapP[this->vectorP[i]] = leplusproche;
		}
	}
}

void Kmeans::afficher_stats(){
	for(long unsigned int x = 0; x < this->vectorP.size();x++){
		Point lepoint = this->vectorP[x];
		lepoint.afficher();
		std::cout << "|-->";
		this->mapP[lepoint].afficher();	
		std::cout << "\n";
	}
}

void Kmeans::exporter(){
	std::ofstream myfile;
	myfile.open ("output.csv");
	myfile << "x,y,c" << std::endl;
	for(long unsigned int x =0; x < this->vectorP.size(); x++){
		int groupeC = 99;
		Point lepoint = this->mapP[this->vectorP[x]];
		for(long unsigned int y =0; y < this->vectorC.size();y++){
			if(lepoint == vectorC[y]){
				groupeC = y;
			}
		}
		myfile << this->vectorP[x].getPointX() << "," << this->vectorP[x].getPointY() << "," << groupeC << std::endl;
	}
	myfile.close();
}