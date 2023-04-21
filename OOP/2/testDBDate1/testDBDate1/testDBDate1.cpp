#include <iostream>
#include "dbmsLib1.h"
using namespace std;	
int menu() {
	cout << "============Разработка и тестирование класса DBDate1 ===================\n";
	cout << "\t1 - Создание объектов DBDate1 и проверка конструкторов\n";
	cout << "\t2 - Перегрузка и тестирование логических операторов сравнения\n";
	cout << "\t3 - Перегрузка и тестирование оператора DBDate1& operator+=(int days)\n"; 
	cout << "\t4 - Перегрузка и тестирование оператора DBDate1& operator-=(int days)\n"; 
	cout << "\t5 - Перегрузка и тестирование оператора int operator-(DBD1ate& date)\n"; 
	cout << "\t8 - Тестирование\n";
	cout << "\t10 - Выход\n";
	int choice;
	cout << "Выберите действие\n";
	cin >> choice;
	while (cin.fail()) {
		cout << "Ошибка ввода. Повторите ввод\n";
		cin.clear();
		cin.ignore(10, '\n');
		cin >> choice;
	}
	return choice;
}

dbmsLib::DBDate1 getDateFromConsole() {
	cout << "input date string\n";
	string dateStr; cin >> dateStr;
	return dbmsLib::DBDate1(dateStr);
}
void testing() {
	string str2("29.2.2021");
	dbmsLib::DBDate1 datStr2(str2);
	cout << "str2=" << str2 << " dat2=" << datStr2 << endl;
	cout << endl;
	dbmsLib::DBDate1 datStr;
	cout << "str2=" << str2 << " dat2=" << datStr << endl;
	cout << endl;
}

void testConstr() {
	cout << "default constr" << endl;
	dbmsLib::DBDate1 date1; cout << date1 << endl;
	cout << "create using 3 int's" << endl;
	dbmsLib::DBDate1 date2(9, 11, 2001); cout << date2 << endl;
	cout << "Create using string" << endl;
	dbmsLib::DBDate1 date3("9.11.2001"); cout << date3 << endl;
	cout << "copy constructor" << endl;
	dbmsLib::DBDate1 date4(date1); cout << date4 << endl;
}

void testBoolOperators() {
	dbmsLib::DBDate1 date1 = getDateFromConsole();
	dbmsLib::DBDate1 date2 = getDateFromConsole();
	
	cout << date1 << " " << date2 << endl;
	cout << "date1 > date2 = " << (date1 > date2) << endl;
	cout << "date1 < date2 = " << (date1 < date2) << endl;
	cout << "date1 == date2 = " << (date1 == date2) << endl;
	cout << "date1 >= date2 = " << (date1 >= date2) << endl;
	cout << "date1 <= date2 = " << (date1 <= date2) << endl;
	cout << "date1 != date2 = " << (date1 != date2) << endl;
}

void testPlusEqual() {
	dbmsLib::DBDate1 date = getDateFromConsole();
	cout << "input days amount:" << endl;
	int days; cin >> days;
	date += days;
	cout << "date + days = " << date << endl;
}

void testMinusEqual() {
	dbmsLib::DBDate1 date = getDateFromConsole();
	cout << "input days amount:" << endl;
	int days; cin >> days;
	date -= days;
	cout << "date + days = " << date << endl;
}

void testMinus() {
	dbmsLib::DBDate1 date1 = getDateFromConsole();
	dbmsLib::DBDate1 date2 = getDateFromConsole();
	cout << "date1 - date2 = " << date1 - date2 << endl;
}
int main() {
	system("chcp 1251 > nul");
	while (true) {
		short choice = menu();
		system("cls");
		switch (choice) {
		case 1:
			testConstr();
			break;
		case 2:
			testBoolOperators();
			break;
		case 3:
			testPlusEqual();
			break;
		case 4:
			testMinusEqual();
			break;
		case 5:
			testMinus();
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			testing();
			break;
		case 9:
			break;
		case 10:
			return 0;
		}
		system("pause & cls");
	}
}