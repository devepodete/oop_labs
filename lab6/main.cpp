/*
Добавление пятиугольников в стек на умных указателях с использованием итераторов и
собственного аллокатора.

Черемисинов Максим

М8О-201Б-18
*/

#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <memory>
#include <exception>
#include <map>
#include <list>

//#define Debug

#include "allocator_with_stack.hpp"
#include "pentagon.hpp"

const double PI  = 3.1415926;

void print_actions(){
	std::cout << "0. \"exit\" - exit\n";
	std::cout << "1. \"push\" - push figure to stack\n";
	std::cout << "2. \"pop\" - pop figure from stack\n";
	std::cout << "3. \"print\" - print stack\n";
	std::cout << "4. \"random N\" - push to stack N automatically generated figures\n";
	std::cout << "5. \"insert N\" - insert item to pos N\n";
	std::cout << "6. \"erase N\" - delete item from pos N\n";
	std::cout << "7. \"count AREA\" - count figures with area less then AREA\n";
}

int main(){
	//std::map<int, double, std::less<int>, myAllocator<std::pair<int, double>,500>> m;
	//std::list<int, myAllocator<int, 50>> l;
	//stack<int, myAllocator<int, 50>> s;
	std::srand(std::time(NULL));

	stack<pentagon<double>, myAllocator<pentagon<double>, 100>> st;

	print_actions();
	std::string action(" ");
	
	std::cout << "> ";
	std::cin >> action;
	while(action != "exit"){
		if(action == "push"){
			std::cout << "figure cords: ";
			pentagon<double> temp;
			std::cin >> temp;
			st.push(temp);
			goto end;
		}
		if(action == "pop"){
			try{
				st.pop();
			}catch(std::exception &ex){
				std::cout << "Exception with pop(): " << ex.what() << "\n";
			}
			goto end;
		}
		if(action == "print"){
			st.print();
			goto end;
		}
		if(action == "random"){
			int k;
			std::cin >> k;
			for(int i = 0; i < k; i++){
				double x0 = rand()%100;
				double y0 = rand()%100;
				double r = rand()%10+1;
				std::pair<double, double> c[5];
				for(int j = 0; j < 5; j++){
					c[j].first = x0 + r*cos(2*PI*j/5);
					c[j].second = y0 + r*sin(2*PI*j/5);
				}
				pentagon<double> temp(c[0], c[1], c[2], c[3], c[4]);
				st.push(temp);
			}
			goto end;
		}
		if(action == "insert"){
			int k;
			std::cin >> k;
			try{
				auto it = st.at(k);
				std::cout << "figure cords: ";
				pentagon<double> temp;
				std::cin >> temp;
				st.insert(it, temp);
			}catch(std::exception &ex){
				std::cout << "Exception with insert(): " << ex.what() << "\n";
			}
			goto end;
		}
		if(action == "erase"){
			int k;
			std::cin >> k;
			try{
				auto it = st.at(k);
				st.erase(it);
			}catch(std::exception &ex){
				std::cout << "Exception with erase(): " << ex.what() << "\n";
			}
			goto end;
		}
		if(action == "count"){
			double k;
			std::cin >> k;
			int ans = std::count_if(st.begin(), st.end(), [&, k](pentagon<double> pd){return pd.area() < k;});
			std::cout << "res = " << ans << "\n";
			goto end;
		}
		end:
		std::cout << "> ";
		std::cin >> action;
	}
}
