#include <iostream>
#include <list>
#include <cmath>

class Point{
	private:
		double x;
		double y;
	public:
		Point();
		Point(int a, int b);
		void translater(int a, int b);
		void afficher();
		int getPointY();
		int getPointX();
		int getPointX() const;
		int getPointY() const;
		int distance(Point p);
		bool operator==(Point p);
		bool operator<(const Point p)const;
		std::list<Point*> droite(Point* p);
		void dessiner(Point* p);
		~Point();
};