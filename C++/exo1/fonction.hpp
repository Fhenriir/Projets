#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include "point.hpp"

class Kmeans{
	private:
		std::vector<Point> vectorP;
		std::vector<Point> vectorC;
		std::map<Point,Point> mapP;
		int nbrCentroides;
	public:
		Kmeans(int nbrPoints,int nbrCentroides);
		void afficher_stats();
		void afficher();
		void initialiser();
		void calculer(int iteration);
		void exporter();
};