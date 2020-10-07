#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "figures.h"
#include "ui.h"
#include "cord_exception.h"

uil_command uil::main_cmd(){
	std::cout << "> ";
	static uil_command cmd;
	std::cin >> cmd;
	using pair_int = std::pair<int, int>;
	using pair_double = std::pair<double, double>;
	switch(uil::check_syntax(cmd)){
		case 0:
			break;
		case 1:{
			//square
			int type = uil::value_type();
			if(type == -1){
				std::cout << "Error: incorrect value type\n";
				break;
			}
			switch(type){
				case 0:{
					//int
					try{
						pair_int i1, i2;
						uil::get_square_cords(i1, i2);
						square<int> sq_int(i1, i2);
						uil::make_action(sq_int);
					}catch(WrongPointsException<int> &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}catch(WrongValueException &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}
					break;
				}
				case 1:{
					//double
					try{
						pair_double i1, i2;
						uil::get_square_cords(i1, i2);
						square<double> sq_int(i1, i2);
						uil::make_action(sq_int);
					}catch(WrongPointsException<double> &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}catch(WrongValueException &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}
					break;
				}
			}
			break;
		}
		case 2:{
			//rectangle
			int type = uil::value_type();
			if(type == -1){
				std::cout << "Error: incorrect value type\n";
				break;
			}
			switch(type){
				case 0:{
					//int
					try{
						pair_int i1, i2, i3;
						uil::get_rectangle_cords(i1, i2, i3);
						rectangle<int> rec_int(i1, i2, i3);
						uil::make_action(rec_int);
					}catch(WrongPointsException<int> &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}catch(WrongValueException &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}
					break;
				}
				case 1:{
					//double
					try{
						pair_double i1, i2, i3;
						uil::get_rectangle_cords(i1, i2, i3);
						rectangle<double> rec_double(i1, i2, i3);
						uil::make_action(rec_double);
					}catch(WrongPointsException<double> &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}catch(WrongValueException &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}
					break;
				}
			}
			break;
		}

		case 3:{
			//trapezoid
			int type = uil::value_type();
			if(type == -1){
				std::cout << "Error: incorrect value type\n";
				break;
			}
			switch(type){
				case 0:{
					//int
					try{
						pair_int i1, i2, i3, i4;
						uil::get_trapezoid_cords(i1, i2, i3, i4);
						trapezoid<int> tr_int(i1, i2, i3, i4);
						uil::make_action(tr_int);
					}catch(WrongPointsException<int> &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}catch(WrongValueException &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}
					break;
				}
				case 1:{
					//double
					try{
						pair_double i1, i2, i3, i4;
						uil::get_trapezoid_cords(i1, i2, i3, i4);
						trapezoid<double> tr_double(i1, i2, i3, i4);
						uil::make_action(tr_double);
					}catch(WrongPointsException<double> &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}catch(WrongValueException &ex){
						std::cout << "Exception in runtime: " << ex.what() << std::endl;
					}
					break;
				}
			}
			break;
		}

		case -1:
			std::cout << "Error: incorrect command\n";
			break;
	}
	return cmd;
}

int uil::check_syntax(const uil_command &cmd){
	std::vector<std::string> commands(0, std::string());
	commands.push_back("exit");
	commands.push_back("square");
	commands.push_back("rectangle");
	commands.push_back("trapezoid");

	for(size_t i = 0; i < commands.size(); i++){
		if(cmd == commands[i]) return i;
	}
	return -1;
}

int uil::check_command(const uil_command &cmd){
	std::vector<std::string> commands(0, std::string());
	commands.push_back("area");
	commands.push_back("center");
	commands.push_back("print");

	for(size_t i = 0; i < commands.size(); i++){
		if(cmd == commands[i]) return i;
	}
	return -1;
}

int uil::value_type(){
	std::cout << "> ";
	static std::string type;
	std::vector<std::string> types(0, std::string());
	types.push_back("int");
	types.push_back("double");

	std::cin >> type;
	for(size_t i = 0; i < types.size(); i++){
		if(type == types[i]) return i;
	}
	return -1;
}

bool uil::is_number(const std::string &str){
	short points = 0;

	if(str.empty()) return false;
	if(str[0] == '.' || str[str.size()-1] == '.') return false;
	for(auto ptr = str.begin(); ptr != str.end(); ptr++){
		if(*ptr == '.'){
			points++;
			continue;
		}
		if(*ptr < '0' || *ptr > '9') return false;
	}
	if(points >= 2) return false;
	return true;
}

void uil::welcome(){
	std::cout << "Welcome to the UI!\n";
	std::cout << "------------------------------------------\n";
	std::cout << "To create a figure type [figure name]\n";
	std::cout << "where [figure name] could be square, rectangle or trapezoid.\n";
	std::cout << "------------------------------------------\n";
	std::cout << "Add the coordinates.\n";
	std::cout << "------------------------------------------\n";
	std::cout << "Available commands for figure: area, center, print\n";
	std::cout << "To finish work with figure type anything except available commands\n";
	std::cout << "------------------------------------------\n";
	std::cout << "To exit the program type \"exit\"\n";
}

void uil::try_tuples(){
	std::cout << "\nExample with tuple usage:\n\n";
	using int_type = int;
	using double_type = double;

	using int_pair = std::pair<int_type, int_type>;
	using double_pair = std::pair<double_type, double_type>;

	std::tuple<double_pair, double_pair> tuple_double({0,0}, {3.5,3.5});
	print_cords(tuple_double);
	std::cout << calculate_area(tuple_double) << std::endl;
	std::cout << calculate_center(tuple_double) << std::endl;

	try{
		std::tuple<int_pair, int_pair, int_pair> tuple_int({0,0}, {0, 5}, {1, 9});
		calculate_area(tuple_int);
	}catch(WrongPointsException<int_type> &ex){
		std::cout << "Exception in runtime: " << ex.what() << std::endl;
	}
	std::cout << "\n";
}