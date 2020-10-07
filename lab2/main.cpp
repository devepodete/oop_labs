/*
Создать класс TimePoint для работы с моментами времени в формате «час:минута:секунда».
Обязательными операциями являются: вычисление разницы между двумя моментами времени, сумма
моментов времени, сложение момента времени и заданного количества секунд, вычитание из момента
времени заданного количества секунд, вычисление во раз сколько один момент времени больше (меньше)
другого, сравнение моментов времени, перевод в секунды и обратно, перевод в минуты (с округлением до
минуты) и обратно.
Операции сложения и вычитания TimePoint, а так же сравнения (больше, меньше и равно) необходимо реализовать в виде перегрузки операторов.
Необходимо реализовать пользовательский литерал для работы с константами типа TimePoint.
*/
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class TimePoint{
	int time;

public:
	TimePoint(){
		time = 0;
	}
	TimePoint(int sec){
		if(sec < 0){
			time = -sec;
		}else{
			time = sec;
		}
	}
	TimePoint(int hrs, int min, int sec){
		hrs = hrs < 0 ? -hrs : hrs;
		min = min < 0 ? -min : min;
		sec = sec < 0 ? -sec : sec;
		time = hrs*3600 + min*60 + sec;
	}

	int time_get();
	void time_set(int t);
	friend void show(TimePoint a);

	void operator=(TimePoint a);
	TimePoint operator+(TimePoint a);
	TimePoint operator+(int t);
	friend TimePoint operator+(int t, TimePoint a);
	TimePoint operator-(TimePoint a);
	TimePoint operator-(int t);
	friend TimePoint operator-(int t, TimePoint a);

	bool operator<(TimePoint a);
	bool operator<=(TimePoint a);
	bool operator>(TimePoint a);
	bool operator>=(TimePoint a);
	bool operator!=(TimePoint a);
	bool operator==(TimePoint a);

	friend double gt(TimePoint a, TimePoint b); //во сколько раз больше
	friend double lt(TimePoint a, TimePoint b); //во сколько раз меньше

};

TimePoint operator "" _hrs(unsigned long long x){
	return TimePoint(x*60*60);
}

TimePoint operator "" _min(unsigned long long x){
	return TimePoint(x*60);
}

TimePoint operator "" _sec(unsigned long long x){
	return TimePoint(x);
}


//парсер строки
TimePoint parse(const char *str, size_t size){
	int arr[3] = {0};
	int cur = 0;

	for(size_t i = 0; i < size; i++){
		if(str[i] == ':'){
			cur++;
			continue;
		}
		arr[cur] *= 10;
		arr[cur] += str[i]-'0';
	}

	if(cur != 2){
		cout << "Неверный формат строки. Установлено время по-умолчанию 00:00:00" << endl;
		cout << "Верный формат: ЧАСЫ:МИНУТЫ:СКУНДЫ" << endl;
		return TimePoint(0);
	}
	return TimePoint(arr[0], arr[1], arr[2]);
}

//полный формат времени
TimePoint operator "" _full(const char *str, size_t size){
	return parse(str, size);
}

int TimePoint::time_get(){
	return time;
}

void TimePoint::time_set(int t){
	time = t;
}

void show(TimePoint a){
	int temp = a.time;
	if(temp < 0){
		temp = -temp;
	}
	cout << temp/3600;
	temp = temp%3600;
	cout << ":" << temp/60;
	temp = temp%60;
	cout << ":" << temp << endl;
}

void TimePoint::operator=(TimePoint a){
	this->time = a.time;
}

TimePoint TimePoint::operator+(TimePoint a){
	TimePoint res(this->time + a.time);
	return res;
}

TimePoint TimePoint::operator-(TimePoint a){
	TimePoint res(this->time - a.time);
	return res;
}


TimePoint TimePoint::operator+(int t){
	TimePoint res(this->time + t);
	return res;
}

TimePoint TimePoint::operator-(int t){
	TimePoint res(this->time - t);
	return res;
}

TimePoint operator+(int t, TimePoint a){
	TimePoint res(t+a.time);
	return res;
}

TimePoint operator-(int t, TimePoint a){
	TimePoint res(t-a.time);
	return res;
}

bool TimePoint::operator<(TimePoint a){
	return(this->time < a.time);
}

bool TimePoint::operator>(TimePoint a){
	return(this->time > a.time);
}

bool TimePoint::operator<=(TimePoint a){
	return(this->time <= a.time);
}

bool TimePoint::operator>=(TimePoint a){
	return(this->time >= a.time);
}

bool TimePoint::operator!=(TimePoint a){
	return(this->time != a.time);
}

bool TimePoint::operator==(TimePoint a){
	return(this->time == a.time);
}

double gt(TimePoint a, TimePoint b){
	if(b.time == 0){
		throw overflow_error("Value of second argument is equal to 0. Can not compare.");
	}
	return static_cast<double> (a.time) / b.time;
}

double lt(TimePoint a, TimePoint b){
	if(a.time == 0){
		throw overflow_error("Value of first argument is equal to 0. Can not compare.");
	}
	return static_cast<double> (b.time) / a.time;
}

int in_minutes(int sec){
	return sec/60;
}

int main(){

	cout << "Следующие моменты времени созданы с помощью пользовательских";
	cout << " литералов:" << endl;
	cout << "----------------" << endl;
	show("23:50:45"_full);
	show(20_hrs);
	show(100_min);
	show(999_sec);
	cout << "----------------" << endl;
	
	vector<TimePoint*> array;
	int k = -1;
	cout << "Доступные действия:" << endl;
	cout << "0. Выход" << endl;
	cout << "1. Создать объект" << endl;
	cout << "2. Вывести список всех объектов" << endl;
	cout << "3. Вывести время в стандартном формате" << endl;
	cout << "4. Вывести время в минутах" << endl;
	cout << "5. Вывести время в секундах" << endl;
	cout << "6. Найти сумму моментов времени" << endl;
	cout << "7. Найти разницу между моментами времени" << endl;
	cout << "8. Прибавить ко времени заданное количество секунд" << endl;
	cout << "9. Сравнить два объекта времени" << endl;
	cout << "10. Во сколько раз один момент времени больше/меньше другого" << endl;
	cout << "11. Вывести этот список" << endl;
	while(k != 0){
		begin:
		cout << "Введите действие [0 - 11]: ";
		cin >> k;
		switch(k){
			case 0:
				return 0;
			case 1:{
				cout << "Введите время в стандартном формате: ЧАСЫ МИНУТЫ СЕКУНДЫ" << endl;
				int a, b, c;
				cin >> a >> b >> c;
				TimePoint *T = new TimePoint(a, b, c);
				array.push_back(T);
				break;
			}
			case 2:{
				cout << "Список объектов:" << endl;
				for(int i = 0; i < array.size(); i++){
					cout << i << ". ";
					show(*array[i]);
				}
				break;
			}
			case 3:{
				if(array.size() == 0){
					cout << "Ошибка: нет моментов времени" << endl;
					break;
				}
				cout << "Доступные индексы: [" << 0 << " - " << array.size()-1 << "]" << endl;
				cout << "Введите индекс: ";
				int a;
				cin >> a;
				while(a < 0 || a >= array.size()){
					cout << "Неверно введён индекс. Для выхода введите -1" << endl;
					cin >> a;
					if(a == -1){
						goto begin;
					}
				}
				cout << "Момент времени: ";
				show(*array[a]);
				break;
			}
			case 4:{
				if(array.size() == 0){
					cout << "Ошибка: нет моментов времени" << endl;
					break;
				}
				cout << "Доступные индексы: [" << 0 << " - " << array.size()-1 << "]" << endl;
				cout << "Введите индекс: ";
				int a;
				cin >> a;
				while(a < 0 || a >= array.size()){
					cout << "Неверно введён индекс. Для выхода введите -1" << endl;
					cin >> a;
					if(a == -1){
						goto begin;
					}
				}
				cout << "Момент времени в минутах: ";
					cout << in_minutes(array[a]->time_get());
				cout << endl;
				break;
			}
			case 5:{
				if(array.size() == 0){
					cout << "Ошибка: нет моментов времени" << endl;
					break;
				}
				cout << "Доступные индексы: [" << 0 << " - " << array.size()-1 << "]" << endl;
				cout << "Введите индекс: ";
				int a;
				cin >> a;
				while(a < 0 || a >= array.size()){
					cout << "Неверно введён индекс. Для выхода введите -1" << endl;
					cin >> a;
					if(a == -1){
						goto begin;
					}
				}
				cout << "Момент времени в секундах: ";
					cout << array[a]->time_get();
				cout << endl;
				break;
			}
			case 6:{
				int k;
				cout << "Выберите действие:" << endl;
				cout << "1. Ввести два момента времени" << endl;
				cout << "2. Выбрать два уже введенных момента времени" << endl;
				cin >> k;
				while(k < 1 || k > 2){
					cout << "Неверно введено действие. Для выхода введите -1" << endl;
					cin >> k;
					if(k == -1){
						goto begin;
					}
				}
				if(k == 1){
					cout << "Введите время в стандартном формате: ЧАСЫ МИНУТЫ СЕКУНДЫ" << endl;
					int a, b, c;
					cin >> a >> b >> c;
					TimePoint t1(a, b, c);
					cin >> a >> b >> c;
					TimePoint t2(a, b, c);
					show(t1+t2);
				}else{
					if(array.size() == 0){
						cout << "Ошибка: нет моментов времени" << endl;
						break;
					}
					cout << "Введите два индекса уже заведенных элементов.";
					cout << "Доступные индексы: [" << 0 << " - " << array.size()-1 << "]" << endl;
					int a, b;
					cin >> a >> b;
					if(a < 0 || a >= array.size() || b < 0 || b >= array.size()){
						cout << "Неверно введён один из индексов. Для выхода введите -1 -1" << endl;
						cin >> a >> b;
						if(a == -1 && b == -1){
							goto begin;
						}
					}
					show(*array[a]+*array[b]);
				}
				break;
			}
			case 7:{
				int k;
				cout << "Выберите действие:" << endl;
				cout << "1. Ввести два момента времени" << endl;
				cout << "2. Выбрать два уже введенных момента времени" << endl;
				cin >> k;
				while(k < 1 || k > 2){
					cout << "Неверно введено действие. Для выхода введите -1" << endl;
					cin >> k;
					if(k == -1){
						goto begin;
					}
				}
				if(k == 1){
					cout << "Введите время в стандартном формате: ЧАСЫ МИНУТЫ СЕКУНДЫ" << endl;
					int a, b, c;
					cin >> a >> b >> c;
					TimePoint t1(a, b, c);
					cin >> a >> b >> c;
					TimePoint t2(a, b, c);
					show(t1-t2);
				}else{
					if(array.size() == 0){
						cout << "Ошибка: нет моментов времени" << endl;
						break;
					}
					cout << "Введите два индекса уже заведенных элементов.";
					cout << "Доступные индексы: [" << 0 << " - " << array.size()-1 << "]" << endl;
					int a, b;
					cin >> a >> b;
					if(a < 0 || a >= array.size() || b < 0 || b >= array.size()){
						cout << "Неверно введён один из индексов. Для выхода введите -1 -1" << endl;
						cin >> a >> b;
						if(a == -1 && b == -1){
							goto begin;
						}
					}
					show(*array[a]-*array[b]);
				}
				break;
			}
			case 8:{
				int k;
				cout << "Выберите действие:" << endl;
				cout << "1. Ввести момент времени" << endl;
				cout << "2. Выбрать уже введенный момент времени" << endl;
				cin >> k;
				while(k < 1 || k > 2){
					cout << "Неверно введено действие. Для выхода введите -1" << endl;
					cin >> k;
					if(k == -1){
						goto begin;
					}
				}
				if(k == 1){
					cout << "Введите время в стандартном формате: ЧАСЫ МИНУТЫ СЕКУНДЫ" << endl;
					int a, b, c;
					cin >> a >> b >> c;
					TimePoint t1(a, b, c);
					cout << "Введите время в секундах: ";
					int sec;
					cin >> sec;
					show(t1+sec);
				}else{
					if(array.size() == 0){
						cout << "Ошибка: нет моментов времени" << endl;
						break;
					}
					cout << "Введите индес уже заведенного элемента.";
					cout << "Доступные индексы: [" << 0 << " - " << array.size()-1 << "]" << endl;
					int a;
					cin >> a;
					if(a < 0 || a >= array.size()-1){
						cout << "Неверно введён индекс. Для выхода введите -1 -1" << endl;
						cin >> a;
						if(a == -1){
							goto begin;
						}
					}
					cout << "Изменить элемент? y/n: ";
					char c;
					cin >> c;
					cout << "Введите время в секундах: ";
					int sec;
					cin >> sec;
					cout << "Результат: ";
					if(c == 'y'){	
						array[a]->time_set(array[a]->time_get()+sec);
						show(*array[a]);
					}else{
						show(*array[a]+sec);
					}
				}
				break;
			}
			case 9:{
				int k;
				cout << "Выберите действие:" << endl;
				cout << "1. Ввести моменты времени" << endl;
				cout << "2. Выбрать уже введенные моменты времени" << endl;
				cin >> k;
				while(k < 1 || k > 2){
					cout << "Неверно введено действие. Для выхода введите -1" << endl;
					cin >> k;
					if(k == -1){
						goto begin;
					}
				}
				if(k == 1){
					cout << "Введите время в стандартном формате: ЧАСЫ МИНУТЫ СЕКУНДЫ" << endl;
					int a, b, c;
					cin >> a >> b >> c;
					TimePoint t1(a, b, c);
					cin >> a >> b >> c;
					TimePoint t2(a, b, c);
					if(t1 < t2){
						cout << "Первый момент меньше второго" << endl;
					}else if(t1 == t2){
						cout << "Моменты времени равны" << endl;
					}else{
						cout << "Первый момент больше второго" << endl;
					}
				}else{
					if(array.size() == 0){
						cout << "Ошибка: нет моментов времени" << endl;
						break;
					}
					cout << "Введите два индекса уже заведенных элементов.";
					cout << "Доступные индексы: [" << 0 << " - " << array.size()-1 << "]" << endl;
					int a, b;
					cin >> a >> b;
					if(a < 0 || a >= array.size() || b < 0 || b >= array.size()){
						cout << "Неверно введён один из индексов. Для выхода введите -1 -1" << endl;
						cin >> a >> b;
						if(a == -1 && b == -1){
							goto begin;
						}
					}
					if(*array[a] < *array[b]){
						cout << "Первый момент меньше второго" << endl;
					}else if(*array[a] == *array[b]){
						cout << "Моменты времени равны" << endl;
					}else{
						cout << "Первый момент больше второго" << endl;
					}
				}
				break;
			}
			case 10:{
				cout << "Больше или меньше? g/l: ";
				char c;
				cin >> c;
				int k;
				cout << "Выберите действие:" << endl;
				cout << "1. Ввести два момента времени" << endl;
				cout << "2. Выбрать два уже введенных момента времени" << endl;
				cin >> k;
				while(k < 1 || k > 2){
					cout << "Неверно введено действие. Для выхода введите -1" << endl;
					cin >> k;
					if(k == -1){
						goto begin;
					}
				}
				if(k == 1){
					cout << "Введите время в стандартном формате: ЧАСЫ МИНУТЫ СЕКУНДЫ" << endl;
					int a, b, c;
					cin >> a >> b >> c;
					TimePoint t1(a, b, c);
					cin >> a >> b >> c;
					TimePoint t2(a, b, c);
					if(c == 'g'){
						cout << gt(t1, t2) << endl;
					}else{
						cout << lt(t1, t2) << endl;
					}
				}else{
					if(array.size() == 0){
						cout << "Ошибка: нет моментов времени" << endl;
						break;
					}
					cout << "Введите два индекса уже заведенных элементов.";
					cout << "Доступные индексы: [" << 0 << " - " << array.size()-1 << "]" << endl;
					int a, b;
					cin >> a >> b;
					if(a < 0 || a >= array.size() || b < 0 || b >= array.size()){
						cout << "Неверно введён один из индексов. Для выхода введите -1 -1" << endl;
						cin >> a >> b;
						if(a == -1 && b == -1){
							goto begin;
						}
					}
					if(c == 'g'){
						cout << gt(*array[a], *array[b]) << endl;
					}else{
						cout << lt(*array[a], *array[b]) << endl;
					}
				}
				break;
			}
			case 11:
				cout << "Доступные действия:" << endl;
				cout << "0. Выход" << endl;
				cout << "1. Создать объект" << endl;
				cout << "2. Вывести список всех объектов" << endl;
				cout << "3. Вывести время в стандартном формате" << endl;
				cout << "4. Вывести время в минутах" << endl;
				cout << "5. Вывести время в секундах" << endl;
				cout << "6. Найти сумму моментов времени" << endl;
				cout << "7. Найти разницу между моментами времени" << endl;
				cout << "8. Прибавить ко времени заданное количество секунд" << endl;
				cout << "9. Сравнить два объекта времени" << endl;
				cout << "10. Во сколько раз один момент времени больше/меньше другого" << endl;
				cout << "11. Вывести этот список" << endl;
				break;
			default:
				cout << "Неверно введено действие" << endl;
		}
	}
}
