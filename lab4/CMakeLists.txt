cmake_minimum_required(VERSION 3.5)
project(FourthLab)
add_executable(oop_exercise_04 main.cpp ui.cpp)
set_target_properties(oop_exercise_04 PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	)
