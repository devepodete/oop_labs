#ifndef __CORD_EXCEPTION_H__
#define __CORD_EXCEPTION_H__
#include <exception>
#include <string>

template <class T>
class WrongPointsException: public std::exception{
private:
	short sq = 0;
	short rec = 1;
	short trap = 2;
	std::pair<T, T> a, b, c, d;
	short type;
public:
	WrongPointsException(const std::pair<T, T> &x, const std::pair<T,T> &y){
		a = x;
		b = y;
		type = sq;
	}
	WrongPointsException(const std::pair<T, T> &x, const std::pair<T,T> &y,
		const std::pair<T, T> &z){
		a = x;
		b = y;
		c = z;
		type = rec;
	}
	WrongPointsException(const std::pair<T, T> &x, const std::pair<T,T> &y,
		const std::pair<T, T> &z, const std::pair<T, T> &w){
		a = x;
		b = y;
		c = z;
		d = w;
		type = trap;
	}

	const char *what()const noexcept override{
		if(type == sq){
			static std::string str;
			str = "Wrong points: ";

			str += "<";
			str += std::to_string(a.first);
			str += ", ";
			str += std::to_string(a.second);
			str += ">, ";

			str += "<";
			str += std::to_string(b.first);
			str += ", ";
			str += std::to_string(b.second);
			str += ">";
			return str.c_str();
		}else if (type == rec){
			static std::string str("Wrong points: ");

			str += "<";
			str += std::to_string(a.first);
			str += ", ";
			str += std::to_string(a.second);
			str += ">, ";

			str += "<";
			str += std::to_string(b.first);
			str += ", ";
			str += std::to_string(b.second);
			str += ">, ";

			str += "<";
			str += std::to_string(c.first);
			str += ", ";
			str += std::to_string(c.second);
			str += "> ";

			return str.c_str();
		}else{
			static std::string str;
			str = "Wrong points: ";

			str += "<";
			str += std::to_string(a.first);
			str += ", ";
			str += std::to_string(a.second);
			str += ">, ";

			str += "<";
			str += std::to_string(b.first);
			str += ", ";
			str += std::to_string(b.second);
			str += ">, ";

			str += "<";
			str += std::to_string(c.first);
			str += ", ";
			str += std::to_string(c.second);
			str += ">, ";

			str += "<";
			str += std::to_string(d.first);
			str += ", ";
			str += std::to_string(d.second);
			str += ">";
			return str.c_str();
		}
	}
};

class WrongValueException: public std::exception{
private:
	std::string str;
public:
	WrongValueException(const std::string &a): str(a){}

	const char *what()const noexcept override{
		static std::string error;
		error = "Wrong value: ";
		error += str;
		return error.c_str();
	}
};

#endif