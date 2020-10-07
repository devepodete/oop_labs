#ifndef __PENTAGON_HPP__
#define __PENTAGON_HPP__

#include <iostream>

template <class T>
std::istream &operator>>(std::istream &is, std::pair<T,T> &p){
	is >> p.first >> p.second;
	return is;
}

template <class T>
class pentagon{
public:
	friend std::ostream &operator<<(std::ostream &os, pentagon<T> &p){
		os << "[";
		for(int i = 0; i < 4; i++){
			os << "(" << p.cords[i].first << ", " << p.cords[i].second << "), ";
		}
		os << "(" << p.cords[4].first << ", " << p.cords[4].second << ")";
		os << "]";
		return os;
	}

	friend std::istream &operator>>(std::istream &is, pentagon<T> &p){
		for(int i = 0; i < 5; i++){
			is >> p.cords[i];
		}
		return is;
	}

	pentagon(){};
	
	pentagon(std::pair<T, T> p0, std::pair<T, T> p1, std::pair<T, T> p2, std::pair<T, T> p3,
	std::pair<T, T> p4){
		cords[0] = p0;
		cords[1] = p1;
		cords[2] = p2;
		cords[3] = p3;
		cords[4] = p4;

		area_ = 0;
		for(int i = 0; i < 4; i++){
			area_ += cords[i].first*cords[i+1].second;
		}
		area_ += cords[4].first*cords[0].second;
		
		for(int i = 0; i < 4; i++){
			area_ -= cords[i+1].first*cords[i].second;
		}
		area_ -= cords[0].first*cords[4].second;
		area_ /= 2;
	}

	int area(){
		return area_;
	}

	~pentagon(){};
private:
	std::pair<T, T> cords[5];
	double area_;
};

#endif