#include "point.hpp"

Point::Point(){
	this->x = 0;
	this->y = 0;
	}

Point::Point(int a, int b){
	this->x = a;
	this->y = b;
	}

void Point::translater(int a, int b){
	this->x = (double)a;
	this->y = (double)b;
}

void Point::afficher(){
	std::cout << "[" << x << "," << y << "]";
	}

int Point::getPointX(){
	return this->x;
	}

int Point::getPointY(){
	return this->y;
	}

int Point::getPointX() const{
	return this->x;
	}

int Point::getPointY() const{
	return this->y;
	}


bool Point::operator==(Point p){
	if(p.getPointX() == this->x && p.getPointY() == this->y){
		return true;
	}
	else{
		return false;
	}
}

bool Point::operator<(const Point p) const{
	if(p.getPointX() + p.getPointY() < this->x + this->y){
		return true;
	}
	else{
		return false;
	}
}

int Point::distance(Point p){
	double result = sqrt(pow((this->x - p.getPointX()),2)+pow((this->y - p.getPointY()),2));
	return result;
}

Point::~Point(){
	//std::cout << "Destructeur Point." << std::endl;
	}

std::list<Point*> Point::droite(Point* p){
	int x1 = this->x;
	int y1 = this->y;
	int x2 = p->x;
	int y2 = p->y;

	int e = x2 - x1;
	int dx = e*2;
	int dy = (y2 - y1)*2;
	std::list<Point*> points;
	while(x1 <= x2){
		points.push_back(new Point(x1,y1));
		e = e - dy;
		if(e<=0){
			y1++;
			e = e + dx;
		}
	}
	return points;
}

void Point::dessiner(Point* p){
	std::list<Point*> points = this->droite(p);
}