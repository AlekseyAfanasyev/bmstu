#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>

using namespace std;
string keyFileString, textFileString;
int* keyArray;
int textLen;

void error(const string msg) {
	cerr << msg << endl;
	exit(0);
}
short menu() {
	cout << "============================Menu===========================" << endl;
	cout << "| 1 - Создание из кодового блокнота массива ключей        |" << endl;
	cout << "| 2 - Просмотр массива ключей                             |" << endl;
	cout << "| 3 - Кодирование - декодирование текстового файла        |" << endl;
	cout << "| 4 - Сбор статистики по результатам кодирования символов |" << endl;
	cout << "| 5 - Выход                                               |" << endl;
	cout << "===========================================================" << endl;
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

void waitUntilKeyPressed() {
	while (!_kbhit());
}

string fileToString(string fileName) {
	ifstream fin(fileName, ios::binary);
	if (!fin.is_open()) {
		return "";
	}

	const string str((istreambuf_iterator<char>(fin)),
		istreambuf_iterator<char>());

	fin.close();
	return str;
}

vector <string> textToWords(string textString) {
	char* text = new char[textString.length() + 1];
	strcpy_s(text, textString.length() + 1, textString.c_str());
	vector <string> words;
	char* token = NULL;
	char* nextToken = NULL;
	const char* seps = " .,?!;:";
	token = strtok_s(text, seps, &nextToken);

	while (token != NULL) {
		words.push_back(token);
		token = strtok_s(NULL, seps, &nextToken);
	}

	delete[] text;
	return words;
}

int getWordSum(string word) {
	int sum = 0;
	for (char& c : word) {
		sum += c;
	}

	return sum % 256;
}
void fillKeyArray() {
	auto words = textToWords(keyFileString);

	const int wordsAmount = words.size();
	
	if (keyArray != nullptr)
		delete[] keyArray;

	keyArray = new int[textLen];

	for (size_t i = 0; i < textFileString.length(); ++i) {
		keyArray[i] = getWordSum(words[i % wordsAmount]);
	}

	cout << "Массив ключей готов." << endl;
	waitUntilKeyPressed();
}

void outputKeyArray() {
	const int number_len = to_string(textFileString.length()).length();
	const int code_len = 4;
	for (int i = 0; i < textFileString.length(); ++i) {
		cout << setw(number_len) << i << " " << textFileString[i] << " " << setw(code_len) << keyArray[i] << endl;
	}

	waitUntilKeyPressed();
}

string getCodedMessage(string text) {
	string msg;
	msg.resize(text.length());
	for (int i = 0; i < text.size(); ++i) {
		msg[i] = char(text[i] ^ keyArray[i]);
	}
	return msg;
}

void doDecoding() {
	string codedText = getCodedMessage(textFileString);
	cout << "Закодированный / расшифрованный текст сгенерирован." << endl;
	cout << codedText << endl;
	cout << "Сохранить в файл? [y/n]" << endl;
	char choice; cin >> choice;
	cin.ignore(32767, '\n');
	if (toupper(choice) == 'Y') {
		cout << "Введите имя файла:" << endl;
		string fileName;
		getline(cin, fileName);
		ofstream fout(fileName, ios::binary);
		
		if (!fout.is_open()) {
			cout << "Невозможно открыть файл" << " " << fileName << endl;
		}
		else {
			fout << codedText;
			fout.close();
			cout << "Файл создан!" << endl;
		}

		waitUntilKeyPressed();
	}
}

int* getStatsForChar(char c) {
	int* arr = new int[256];
	for (int i = 0; i < 256; ++i)
		arr[i] = 0;
	for (int i = 0; i <textLen; ++i) {
		if (textFileString[i] == c) {
			++arr[keyArray[i] ^ textFileString[i]];
		}
	}
	return arr;
}

//n от 1 до 16
inline char numberToHec(short int n) {
	return (n < 10 ? n + '0' : (n - 10) + 'A');
}

void printTable(const int* stat) {
	const int col_l = 5;
	cout << setw(col_l) << " ";
	for (int i = 1; i < 17; ++i) {
		cout << setw(col_l) << numberToHec(i);
	}
	cout << endl;
	for (int i = 1; i <= 16; ++i) {
		cout << setw(col_l) << numberToHec(i);
		for (int j = 1; j <= 16; ++j) {
			cout << setw(col_l) << stat[(i-1) * 16 + j - 1];
		}
		cout << endl;
	}
}

void showStatistics() {
	if (keyArray == nullptr) {
		cout << "Сначала заполниет массив ключей" << endl;
		waitUntilKeyPressed();
		return;
	}
	int choice = 0;
	while (true) {
		cout << "Введите код от 0 до 255" << endl;
		cout << "Чтобы выйти, нажмите -1" << endl;
		cin >> choice;
		if (choice == -1)
			return;
		int* stat = getStatsForChar(choice);
		printTable(stat);
		delete[] stat;
	}
}


int main(int argc, const char* argv[]) {
	system("chcp 1251 > nul");
	if (argc != 3) {
		error("Некорректные аргументы\nПример запуска: Lab8 KeyFilename TextFileName");
	} else if (!filesystem::exists(argv[1])) {
		error("Некорректное имя файла");
	}
	else if (!filesystem::exists(argv[2])) {
		error("Invalid textFileName");
	}


	keyFileString = fileToString(argv[1]);
	textFileString = fileToString(argv[2]);
	textLen = textFileString.length();


	while (true) {
		short choice = menu();
		system("cls");
		switch (choice) {
		case 1:
			fillKeyArray();
			break;
		case 2:
			outputKeyArray();
			break;
		case 3:
			doDecoding();
			break;
		case 4:
			showStatistics();
			break;
		case 5:
			return 0;
		default:
			cout << "Нет такой команды.";
			waitUntilKeyPressed();
			break;
		}
		system("cls");
	}


}