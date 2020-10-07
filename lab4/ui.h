#ifndef __UI_H__
#define __UI_H__

#include <iostream>

using uil_command = std::string;

const uil_command UIL_COMMAND_EXIT = "exit";

namespace uil{
	int check_syntax(const uil_command &cmd);
	int check_command(const uil_command &cmd);

	bool is_number(const std::string &str);	
	int value_type();

	uil_command main_cmd();

	template <class T>
	void make_action(const T &figure);

	template <class T>
	void get_square_cords(T &i1, T &i2);

	template <class T>
	void get_rectangle_cords(T &i1, T &i2, T &i3);

	template <class T>
	void get_trapezoid_cords(T &i1, T &i2, T &i3, T &i4);


	void try_tuples();
	void welcome();
}

template <class T>
void uil::get_square_cords(std::pair<T, T> &i1, std::pair<T, T> &i2){
	std::cout << "cords(2): ";
	std::cin >> i1 >> i2;
}

template <class T>
void uil::get_rectangle_cords(std::pair<T, T> &i1, std::pair<T, T> &i2, std::pair<T, T> &i3){
	std::cout << "cords(3): ";
	std::cin >> i1 >> i2 >> i3;
}

template <class T>
void uil::get_trapezoid_cords(std::pair<T, T> &i1, std::pair<T, T> &i2, std::pair<T, T> &i3, std::pair<T, T> &i4){
	std::cout << "cords(4): ";
	std::cin >> i1 >> i2 >> i3 >> i4;
}

template <class T>
void uil::make_action(const T &figure){

	while(true){
		std::cout << "action: ";
		uil_command command;
		std::cin >> command;
		int result = uil::check_command(command);
		switch(result){
			case -1:
				return;
			case 0:
				//area
				std::cout << calculate_area(figure) << std::endl;
				break;
			case 1:
				//center
				std::cout << calculate_center(figure) << std::endl;
				break;
			case 2:
				//print
				print_cords(figure);
				break;
		}
	}
}

#endif