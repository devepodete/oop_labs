/*
Написать программу по вычислению центра и площади квадрата, прямоугольника или трапеции, которые
задает пользователь, и по выводу их координат. Использовать вместо наследования шаблоны.

Сделать функции, которые принимают на вход кортежи. 


Черемисинов Максим
М8О-201Б-18
*/
#include "cord_exception.h"
#include "figures.h"
#include "ui.h"

auto main() -> int{
	
	uil::welcome();
	
	uil::try_tuples();
	
	uil_command cmd;
	
	while(cmd != UIL_COMMAND_EXIT){
		cmd = uil::main_cmd();
	}
}
