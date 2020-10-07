#ifndef __FIGURES_H__
#define __FIGURES_H__
#include <exception>
#include <type_traits>
#include <string>
#include <tuple>
#include <cmath>
#include "cord_exception.h"
#include "ui.h"

template <class T>
bool collinear(const std::pair<T, T> &a, const std::pair<T, T> &b, const std::pair<T, T> &c){
	return (a.second-b.second)*(a.first-c.first) - (a.second-c.second)*(a.first-b.first) <= 1e-9;
}

template <int>
bool collinear(std::pair<int, int> &a, std::pair<int, int> &b, std::pair<int, int> &c){
	return (a.second-b.second)*(a.first-c.first) == (a.second-c.second)*(a.first-b.first);
}

template <class T>
bool perpendicular(const std::pair<T, T> &a, const std::pair<T, T> &b, const std::pair<T, T> &c){
	using vect = std::pair<T, T>;
	vect v1 = b-a;
	vect v2 = b-c;
	T scalarProduct = v1.first*v2.first + v1.second*v2.second;
	if(scalarProduct <= 1e-9 && v1.first*v2.first + v1.second*v2.second >= -1e-9){
		return true;
	}else{
		return false;
	}
}

template <class T>
class square{
public:
	using type = T;
	using point = std::pair<T, T>;
	point a, b;

	square(){}
	square(point &p1, point &p2){
		if(p1 == p2){
			throw WrongPointsException<T>(p1, p2);
		}else{
			if(p1.first > p2.first){
				a = p2;
				b = p1;
			}else{
				a = p1;
				b = p2;
			}
		}
	}
};

template <class T>
class rectangle{
public:
	using type = T;
	using point = std::pair<T, T>;
	point a, b, c;

	rectangle(){}
	rectangle(point &p1, point &p2, point &p3){
		if(p1 == p2 || p1 == p3 || p2 == p3 || collinear(p1, p2, p3) || !(perpendicular(p1, p2, p3))){
			throw WrongPointsException<T>(p1, p2, p3);
		}else{
			a = p1;
			b = p2;
			c = p3;
		}
	}
};

template <class T>
class trapezoid{
public:
	using type = T;
	using point = std::pair<T, T>;
	point a, b, c, d;

	trapezoid(){}
	trapezoid(point &p1, point &p2, point &p3, point &p4){
		if(p1 == p2 || p1 == p3 || p1 == p4 || p2 == p3 || p2 == p4 || p3 == p4 ||
		collinear(p1, p2, p3) || collinear(p1, p2, p4) || collinear(p1, p3, p4) || 
		collinear(p2, p3, p4)){
			throw WrongPointsException<T>(p1, p2, p3, p4);
		}else{
			a = p1;
			b = p2;
			c = p3;
			d = p4;
		}
	}
};

template <class T>
struct is_square{
	static const bool value = false;
};

template <class T>
struct is_square<square<T>>{
	static const bool value = true;
};

template <class T>
struct is_rectangle{
	static const bool value = false;
};

template <class T>
struct is_rectangle<rectangle<T>>{
	static const bool value = true;
};

template <class T>
struct is_trapezoid{
	static const bool value = false;
};

template <class T>
struct is_trapezoid<trapezoid<T>>{
	static const bool value = true;
};

template <class T>
using square_center = typename std::enable_if<is_square<T>::value, std::pair<typename T::type, typename T::type>>::type;

template <class T>
using rectangle_center = typename std::enable_if<is_rectangle<T>::value, std::pair<typename T::type, typename T::type>>::type;

template <class T>
using trapezoid_center = typename std::enable_if<is_trapezoid<T>::value, std::pair<typename T::type, typename T::type>>::type;

template <class T>
using square_cords = typename std::enable_if<is_square<T>::value, void>::type;

template <class T>
using rectangle_cords = typename std::enable_if<is_rectangle<T>::value, void>::type;

template <class T>
using trapezoid_cords = typename std::enable_if<is_trapezoid<T>::value, void>::type;

template <class T>
using square_area = typename std::enable_if<is_square<T>::value, typename T::type>::type;

template <class T>
using rectangle_area = typename std::enable_if<is_rectangle<T>::value, typename T::type>::type;

template <class T>
using trapezoid_area = typename std::enable_if<is_trapezoid<T>::value, typename T::type>::type;


template <class T>
square_center<T> calculate_center(const T &sq){
	typename T::type x, y;
	x = sq.a.first + (sq.b.first-sq.a.first)/2;
	if(sq.a.second > sq.b.second){
		y = sq.b.second + (sq.a.second-sq.b.second)/2;
	}else{
		y = sq.a.second + (sq.b.second-sq.a.second)/2;
	}
	return {x, y};
}

template <class T>
rectangle_center<T> calculate_center(const T &rec){
	typename T::type x_center, y_center, x1, x3, y1, y3;
	x1 = rec.a.first;
	x3 = rec.c.first;
	y1 = rec.a.second;
	y3 = rec.c.second;
	x_center = x1 + (x3-x1)/2;
	if(y1 > y3){
		y_center = y3 + (y1-y3)/2;
	}else{
		y_center = y1 + (y3-y1)/2;
	}
	return {x_center, y_center};
}

template <class T>
trapezoid_center<T> calculate_center(const T &tr){
	typename T::type x1, x2, x3, x4, y1, y2, y3, y4, x_center, y_center;
	
	x1 = tr.a.first;
	x2 = tr.b.first;
	x3 = tr.c.first;
	x4 = tr.d.first;

	y1 = tr.a.second;
	y2 = tr.b.second;
	y3 = tr.c.second;
	y4 = tr.d.second;

	x_center = (x1+x2+x3+x4)/4;
	y_center = (y1+y2+y3+y4)/4;

	return {x_center, y_center};
}

template <class T>
std::pair<T, T> calculate_center(const std::tuple<std::pair<T, T>, std::pair<T, T>> &tp){
	std::pair<T,T> p1, p2;
	p1 = std::get<0>(tp);
	p2 = std::get<1>(tp);
	square<T> sq(p1, p2);
	return calculate_center(sq);
}

template <class T>
std::pair<T, T> calculate_center(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &tp){
	std::pair<T,T> p1, p2, p3;
	p1 = std::get<0>(tp);
	p2 = std::get<1>(tp);
	p3 = std::get<2>(tp);
	rectangle<T> rec(p1, p2, p3);
	return calculate_center(rec);
}

template <class T>
std::pair<T, T> calculate_center(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &tp){
	std::pair<T,T> p1, p2, p3, p4;
	p1 = std::get<0>(tp);
	p2 = std::get<1>(tp);
	p3 = std::get<2>(tp);
	p4 = std::get<3>(tp);
	trapezoid<T> tr(p1, p2, p3, p4);
	return calculate_center(tr);
}

template <class T>
square_cords<T> print_cords(const T &sq){
	std::cout << "Cords of square: " << sq.a << ", " << sq.b << std::endl; 
}

template <class T>
rectangle_cords<T> print_cords(const T &rec){
	std::cout << "Cords of rectangle: " << rec.a << ", " << rec.b << ", " << rec.c << std::endl; 
}

template <class T>
trapezoid_cords<T> print_cords(const T &tr){
	std::cout << "Cords of trapezoid: " << tr.a << ", " << tr.b << ", " << tr.c << ", " << tr.d << std::endl; 
}

template <class T>
void print_cords(const std::tuple<std::pair<T, T>, std::pair<T, T>> &tp){
	std::pair<T,T> p1, p2;
	p1 = std::get<0>(tp);
	p2 = std::get<1>(tp);
	square<T> sq(p1, p2);
	std::cout << "Tuple. ";
	print_cords(sq);
}

template <class T>
void print_cords(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &tp){
	std::pair<T,T> p1, p2, p3;
	p1 = std::get<0>(tp);
	p2 = std::get<1>(tp);
	p3 = std::get<2>(tp);
	rectangle<T> rec(p1, p2, p3);
	std::cout << "Tuple. ";
	print_cords(rec);
}

template <class T>
void print_cords(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &tp){
	std::pair<T,T> p1, p2, p3, p4;
	p1 = std::get<0>(tp);
	p2 = std::get<1>(tp);
	p3 = std::get<2>(tp);
	p4 = std::get<3>(tp);
	trapezoid<T> tr(p1, p2, p3, p4);
	std::cout << "Tuple. ";
	print_cords(tr);
}

template <class T>
square_area<T> calculate_area(const T &sq){
	typename T::type x1, x2, y1, y2;
	x1 = sq.a.first;
	x2 = sq.b.first;
	y1 = sq.a.second;
	y2 = sq.b.second;
	return ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/2;
}

template <class T>
rectangle_area<T> calculate_area(const T &rec){
	typename T::type x1, x2, x3, y1, y2, y3;
	x1 = rec.a.first;
	x2 = rec.b.first;
	x3 = rec.c.first;
	y1 = rec.a.second;
	y2 = rec.b.second;
	y3 = rec.c.second;

	auto side1 = std::sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	auto side2 = std::sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
	return side1*side2;	
}

template <class T>
trapezoid_area<T> calculate_area(const T &tr){
	typename T::type x1, x2, x3, x4, y1, y2, y3, y4;
	
	x1 = tr.a.first;
	x2 = tr.b.first;
	x3 = tr.c.first;
	x4 = tr.d.first;

	y1 = tr.a.second;
	y2 = tr.b.second;
	y3 = tr.c.second;
	y4 = tr.d.second;

	auto area = (x1*y2-x2*y1)+(x2*y3-x3*y2)+(x3*y4-x4*y3);
	area /= 2;
	if(area < 0) return -area;
	return area;
}

template <class T>
T calculate_area(const std::tuple<std::pair<T, T>, std::pair<T, T>> &tp){
	std::pair<T,T> p1, p2;
	p1 = std::get<0>(tp);
	p2 = std::get<1>(tp);
	square<T> sq(p1, p2);
	return calculate_area(sq);
}

template <class T>
T calculate_area(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &tp){
	std::pair<T,T> p1, p2, p3;
	p1 = std::get<0>(tp);
	p2 = std::get<1>(tp);
	p3 = std::get<2>(tp);
	rectangle<T> rec(p1, p2, p3);
	return calculate_area(rec);
}

template <class T>
T calculate_area(const std::tuple<std::pair<T, T>, std::pair<T, T>, std::pair<T, T>, std::pair<T, T>> &tp){
	std::pair<T,T> p1, p2, p3, p4;
	p1 = std::get<0>(tp);
	p2 = std::get<1>(tp);
	p3 = std::get<2>(tp);
	p4 = std::get<3>(tp);
	trapezoid<T> tr(p1, p2, p3, p4);
	return calculate_area(tr);
}

template <class T>
std::istream& operator>>(std::istream &is, std::pair<T, T> &p){
	std::string checker;
	
	is >> checker;
	if(uil::is_number(checker) == false){
		throw WrongValueException(checker);
	}
	p.first = static_cast<T>(std::stod(checker));
	
	is >> checker;
	if(uil::is_number(checker) == false){
		throw WrongValueException(checker);
	}
	p.second = static_cast<T>(std::stod(checker));
	
	return is;
}

template <class T>
std::ostream& operator<<(std::ostream &o, const std::pair<T, T> &p){
	o << "<" << p.first << ", " << p.second << ">";
	return o;
}

template <class T>
std::ostream& operator<<(std::ostream &o, const std::pair<T, T> &&p){
	o << "<" << p.first << ", " << p.second << ">";
	return o;
}

template <class T>
bool operator==(const std::pair<T, T> &a, const std::pair<T, T> &b){
	return (a.first == b.first) && (a.second == b.second);
}

template <class T>
std::pair<T, T> operator-(const std::pair<T, T> &p1, const std::pair<T, T> &p2){
	return {p1.first-p2.first, p1.second-p2.second};
}

#endif
