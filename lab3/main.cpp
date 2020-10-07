/*
Написать программу с базовым классом Figure и производными 
классами квадрата, прямоугольника и трапеции, которые наследуются от класса 
Figure. Должна быть возможность вычисления центра фигуры и ее площади при помощи 
переопределения виртуальных функций родительского класса.

Черемисинов Максим
М8О-201Б-18
*/

#include <iostream>
#include <vector>
#include <cmath>

class Figure{
protected:
	double area_;
	double xCenter_, yCenter_;
	std::vector<double> X;
	std::vector<double> Y;
public:
	virtual void calculateCenter() = 0;
	virtual void calculateArea() = 0;
	virtual void printCords() = 0;
	
	void printCenter(){
		std::cout << xCenter_ << " " << yCenter_ << std::endl;
	}

	void printArea(){
		std::cout << area_ << std::endl;
	}

	double sideSquare(double x1, double y1, double x2, double y2){
		return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	}

	Figure(){}

	virtual ~Figure(){}
};

class Square: public Figure{
public:
	Square(){}

	Square(double X1, double Y1, double X2, double Y2, double X3, double Y3, double X4, double Y4){
		X.push_back(X1);
		X.push_back(X2);
		X.push_back(X3);
		X.push_back(X4);
	
		Y.push_back(Y1);
		Y.push_back(Y2);
		Y.push_back(Y3);
		Y.push_back(Y4);
	}

	~Square(){}

	void calculateArea()override{
		if(X.size() < 4){
			area_ = 0;
		}
		area_ = sideSquare(X[0], Y[0], X[1], Y[1]);
	}

	//через среднее арифметическое  
	void calculateCenter(){
		xCenter_ = yCenter_ = 0;
		for(int i = 0; i < X.size(); i++){
			xCenter_ += X[i];
			yCenter_ += Y[i];
		}
		xCenter_ = xCenter_/X.size();
		yCenter_ = yCenter_/Y.size();
	}

	void printCords(){
		std::cout << "Square: ";
		for(int i = 0; i < X.size(); i++){
			std::cout << "<" << X[i] << ", " << Y[i] << "> ";
		}
		std::cout << std::endl;
	}
};

class Rectangle: public Figure{
public:
	Rectangle(){}

	Rectangle(double X1, double Y1, double X2, double Y2, double X3, double Y3, double X4, double Y4){
		X.push_back(X1);
		X.push_back(X2);
		X.push_back(X3);
		X.push_back(X4);
	
		Y.push_back(Y1);
		Y.push_back(Y2);
		Y.push_back(Y3);
		Y.push_back(Y4);
	}

	~Rectangle(){}

	void calculateArea()override{
		if(X.size() < 4){
			return;
		}
		double area1 = abs((X[0]-X[2])*(Y[1]-Y[2])-(Y[0]-Y[2])*(X[1]-X[2]));
		double area2 = abs((X[0]-X[2])*(Y[3]-Y[2])-(Y[0]-Y[2])*(X[3]-X[2]));
		area_ = 0.5*(area1 + area2);
	}

	//через окружность
	void calculateCenter()override{
		if(X.size() < 4){
			return;
		}
		if(X[0] == X[1]){
			std::swap(X[1], X[2]);
			std::swap(Y[1], Y[2]);
		}
		yCenter_ = ((X[0]-X[1])*(X[0]*X[0]+Y[0]*Y[0]-X[2]*X[2]-Y[2]*Y[2])-(X[0]-X[2])*(X[0]*X[0]+Y[0]*Y[0]-X[1]*X[1]-Y[1]*Y[1]))/(2*((Y[0]-Y[2])*(X[0]-X[1])-(X[0]-X[2])*(Y[0]-Y[1])));
		xCenter_ = (X[0]*X[0]+Y[0]*Y[0]-X[1]*X[1]-Y[1]*Y[1]-2*yCenter_*(Y[0]-Y[1]))/(2*(X[0]-X[1]));
	}

	void printCords(){
		std::cout << "Rectangle: ";
		for(int i = 0; i < X.size(); i++){
			std::cout << "<" << X[i] << ", " << Y[i] << "> ";
		}
		std::cout << std::endl;
	}
};

class Trapezoid: public Figure{
public:
	Trapezoid(){}

	Trapezoid(double X1, double Y1, double X2, double Y2, double X3, double Y3, double X4, double Y4){
		X.push_back(X1);
		X.push_back(X2);
		X.push_back(X3);
		X.push_back(X4);
	
		Y.push_back(Y1);
		Y.push_back(Y2);
		Y.push_back(Y3);
		Y.push_back(Y4);
	}

	~Trapezoid(){}

	void calculateArea()override{
		area_ = 0;
		for(int i = 0; i < X.size()-1; i++){
			area_ += X[i]*Y[i+1]-X[i+1]*Y[i];
		}
		area_ *= 0.5;
	}

	//общая формула для n-угольника
	void calculateCenter()override{
		if(area_ == 0){
			return;
		}
		xCenter_ = yCenter_ = 0;
		for(int i = 0; i < X.size(); i++){
			if(i == X.size()-1){
				xCenter_ += (X[i]+X[0])*(X[i]*Y[0]-X[0]*Y[i]);
				yCenter_ += (Y[i]+Y[0])*(X[i]*Y[0]-X[0]*Y[i]);
			}else{
				xCenter_ += (X[i]+X[i+1])*(X[i]*Y[i+1]-X[i+1]*Y[i]);
				yCenter_ += (Y[i]+Y[i+1])*(X[i]*Y[i+1]-X[i+1]*Y[i]);
			}
		}
		xCenter_ = xCenter_/(6*area_);
		yCenter_ = yCenter_/(6*area_);
	}

	void printCords(){
		std::cout << "Trapezoid: ";
		for(int i = 0; i < X.size(); i++){
			std::cout << "<" << X[i] << ", " << Y[i] << "> ";
		}
		std::cout << std::endl;
	}
};

void printMenu(){
	std::cout << "Доступные команды:" << std::endl;
	std::cout << "0. Выход" << std::endl;
	std::cout << "1. Добавить фигуру" << std::endl;
	std::cout << "2. Вызвать функцию для всех фигур" << std::endl;
	std::cout << "3. Удалить фигуру по индексу" << std::endl;
	std::cout << "4. Вывести это меню" << std::endl;
}

int main(){
	std::vector<Figure*> v;
	printMenu();
	while(true){
		std::cout << "Номер: ";
		int k;
		std::cin >> k;

		switch(k){
			case 0:{
				for(size_t i = 0; i < v.size(); i++){
					delete v[i];
				}
				return 0;
			}
			case 1:{
				std::cout << "1. Квадрат" << std::endl;
				std::cout << "2. Прямоугольник" << std::endl;
				std::cout << "3. Трапеция" << std::endl;
				std::cout << "Номер: ";
				
				int a;
				std::cin >> a;
				
				if(a < 1 || a > 3){
					std::cout << "Неверный номер" << std::endl;
					break;
				}

				std::cout << "Введите координаты: ";
				double x1, y1, x2, y2, x3, y3, x4, y4;
				std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

				Figure *s;
				switch(a){
					case 1:
						s = new Square(x1, y1, x2, y2, x3, y3, x4, y4);
						break;
					case 2:
						s = new Rectangle(x1, y1, x2, y2, x3, y3, x4, y4);
						break;
					case 3:
						s = new Trapezoid(x1, y1, x2, y2, x3, y3, x4, y4);
						break;
				}
				v.push_back(s);
				break;
			}
			case 2:{
				std::cout << "1. Посчитать площадь" << std::endl;
				std::cout << "2. Посчитать центр" << std::endl;
				std::cout << "3. Распечатать площадь" << std::endl;
				std::cout << "4. Распечатать центр" << std::endl;
				std::cout << "5. Распечатать координаты" << std::endl;
				std::cout << "Номер: ";

				int a;
				std::cin >> a;
				if(a < 1 || a > 5){
					std::cout << "Неверный номер" << std::endl;
					break;
				}

				switch(a){
					case 1:{
						for(int i = 0; i < v.size(); i++){
							(*v[i]).calculateArea();
						}
						break;
					}
					case 2:{
						for(int i = 0; i < v.size(); i++){
							(*v[i]).calculateCenter();
						}
						break;
					}
					case 3:{
						for(int i = 0; i < v.size(); i++){
							(*v[i]).printArea();
						}
						break;
					}
					case 4:{
						for(int i = 0; i < v.size(); i++){
							(*v[i]).printCenter();
						}
						break;
					}
					case 5:{
						for(int i = 0; i < v.size(); i++){
							(*v[i]).printCords();
						}
						break;
					}
				}
				break;
			}
			case 3:{
				std::cout << "Индекс: ";
				size_t id;
				std::cin >> id;

				if(id < 0 || id > v.size()-1){
					std::cout << "Индекс выходит за границы массива" << std::endl;
					break;
				}

				std::vector<Figure*> next;
				for(int i = 0; i < v.size(); i++){
					if(i == id){
						continue;
					}
					next.push_back(v[i]);
				}
				std::swap(v, next);
				break;
			}
			case 4:{
				printMenu();
				break;
			}
		}
	}
}
