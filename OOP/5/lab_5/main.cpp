//Lab5_2_test

#pragma warning(disable : 4996)
#include "dbmsLib_v2_1.h";
#include <iostream>
#include <iomanip>
#include <array>
constexpr auto printSize = 120;

using namespace std;
using namespace dbmsLib1;

int menu() {
	cout << "============ СОЗДАНИЕ БИНАРНОЙ БД ============\n";
	cout << "\t1 - Чтение таблицы из текстовой БД\n";
	cout << "\t2 - Печать таблицы\n";
	cout << "\t3 - Запись таблицы в текстовую БД\n";
	cout << "\t4 - Создание бинарной версии текстовой БД\n";
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

void testing(string dbName, array <string, 3> tabNames) {

	string bufName = "buf.bin";
	dbmsLib1::DBTableTxt1 tab1, tab2;
	string path = "..\\" + dbName + "\\";

	for (auto& i : tabNames) {
		tab1.ReadDBTable1(path + i);
		tab1.WriteTableBin1(path + bufName);
		//tab1.PrintTable1(printSize);
		tab2.ReadTableBin1(path + bufName);
		tab2.PrintTable1(printSize);
	}

}


int main() {
	system("chcp 1251>nul");
	string dbName("LibraryTxt");
	array <string, 3> tabNames = { "Abonements.txt", "Books.txt", "Students.txt" };
	//string fileName("Students.txt");
	DBTableTxt1 tab;
	string path = "..\\" + dbName + "\\";
	while (true) {
		switch (menu()) {
			case 1:
				tab.ReadDBTable1(path + "Abonements.txt");
				break;
			case 2:
				tab.PrintTable1(printSize);
				break;
			case 3:
				tab.WriteTableBin1(path + "Abonements1.bin");
				break;

			case 4:

				break;
		case 8:
			testing(dbName, tabNames);
			break;
		case 10:
			return 0;
		}
	}
}