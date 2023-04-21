#include <iostream>
#include <iomanip>
using namespace std;

const int dictionarySize = 1000;
const int l_word = 31;

enum {};
struct Word {
	char engl[l_word];	// слово по-английски
	char rus[l_word];	// слово по-русски
};

void fillWord(Word& dest, Word source) {
	for (int j = 0; j < l_word; ++j) {
		dest.engl[j] = source.engl[j];
		dest.rus[j] = source.rus[j];
	}
}
void addWordToDictionary(Word *& dictionary, Word word, int dictSize) {
	Word* newDict = new Word[dictSize + 1];
	
	for (int i = 0; i < dictSize)

	delete[] dictionary;
	dictionary = newDict;
}

void deleteWordFromDictionary(Word *& dict, int index, int dictSize) {
	Word* newDict = new Word[dictSize - 1];
	int curInd = 0;
	for (int i = 0; i < dictSize; ++i) {
		if (i == index) continue;
		fillWord(newDict[curInd], dict[i]);
		++curInd;
	}
	delete[] dict;
	newDict = dict;
}

char* translateRusToEng(Word* dict, char* word, int dictSize) {
	for (int i = 0; i < dictSize; ++i) {
		if (!strcmp(word, dict[i].rus)) {
			return dict[i].engl;
		}
	}
	return nullptr;
}

char* translateEngToRus(Word* dict, char* word, int dictSize) {
	for (int i = 0; i < dictSize; ++i) {
		if (!strcmp(word, dict[i].engl)) {
			return dict[i].rus;
		}
	}
	return nullptr;
}

void printDictionary(Word* dict, int dictSize) {
	cout << "Словарь" << endl;
	cout << "Размер словаря: " << dictSize << endl;
	cout << setw(l_word) << "Eng" << " " << setw(l_word) << "Rus" << endl;
	for (int i = 0; i < dictSize; ++i) {
		cout << setw(l_word) << string(dict[i].engl) << " " << setw(l_word) << string(dict[i].rus) << endl;
	}
}

void writeDictionaryToFile(string fileName, Word* dict) {

}

Word* readDictionaryFromFile(string fileName) {

}





short menu() {
	cout << "=====================Menu=====================" << endl;
	cout << "| 1 - Добавить слово в словарь               |" << endl;
	cout << "| 2 - Удалить слово из словаря               |" << endl;
	cout << "| 3 - Перевод слова с русского на английский |" << endl;
	cout << "| 4 - Перевод слова с английского на русский |" << endl;
	cout << "| 5 - Просмотр словаря                       |" << endl;
	cout << "| 6 - Вывод словаря в файл                   |" << endl;
	cout << "| 7 - Чтение словаря в файл                  |" << endl;
	cout << "| 8 - Выход                                  |" << endl;
	cout << "==============================================" << endl;
	cout << "Выберите номер:" << endl;
	int choice;
	cin >> choice;
	while (cin.fail()) {
		cout << "Ошибка ввода. Повторите ввод\n";
		cin.clear();
		cin.ignore(10, '\n');
		cin >> choice;
	}
	return choice;
}



int main()
{
	Word dictionary[dictionarySize];
	system("chcp 1251 > nul");
	while (true) {
		short choice = menu();
		system("cls");
		switch (choice) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:

			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			return 0;
		default:
			cout << "No such command.";
			system("pause");
			break;
		}
		system("pause & cls");
	}
}