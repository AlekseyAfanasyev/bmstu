#include <iostream>
#include <cstdlib>
#include <cstring>
#include <conio.h>

#include "lib.h"
using namespace std;

const char* clearScreen = "cls";
const int textLen = 1000;

struct Sentence {
	char** words;//массив из указателей на слова в предложении
	int size;	//размер массива (число слов в предложении)
};

struct Text {
	Sentence* sentences;//массив из предложений в тексте
	int size;		 //размер массива (число предложений)
};

char* loadText()
{
	char* str = new char[strlen(testText) + 1];
	for (int i = 0; i < strlen(testText); ++i) {
		str[i] = testText[i];
	}
	str[strlen(str) + 1] = '\0';
	return str;

}

inline bool isPunctuation(char c) {
	for (const char& i : punctiationSymbols) {
		if (c == i)
			return true;
	}
	return false;
}
inline bool isLetter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
inline bool isCorrect(char c) {
	return isLetter(c) || isPunctuation(c);
}
char* getTextInput() {
	char* str = new char[textLen];
	cout << "Input text" << endl;
	char c;
	int index = 0;
	while ((c = _getch()) != char(26)) {
		if (c == char(8)) {
			cout << "\b \b";
			--index;
		}
		else if (isCorrect(c)) {
			str[index++] = c;
			_putch(c);
		}
		else {
			cout << char(7);
		}
	}

	str[index] = '\0';

	int size = strlen(str) + 1;
	char* new_str = new char[size];
	for (int i = 0; i < index; ++i)
		new_str[i] = str[i];
	new_str[size - 1] = '\0';

	delete[]str;
	return new_str;

}
void print(Text& text)
{
	for (int sentCount = 0; sentCount < text.size; sentCount++) {
		for (int wordCount = 0; wordCount < text.sentences[sentCount].size; wordCount++) {
			cout << text.sentences[sentCount].words[wordCount] << " ";
		}
		cout << "\n";
	}
	system("pause");
}
void execTask18(Text& text)
{

}
void execTask20(Text& text)
{

}

short menu() {
	cout << "================Домашняя Работа==================" << endl;
	cout << "| 1 - Начать ввод текста                        |" << endl;
	cout << "| 2 - Загрузить тестовый пример                 |" << endl;
	cout << "| 3 - Заполнить структуру текст                 |" << endl;
	cout << "| 4 - Выполнить 18 вариант                      |" << endl;
	cout << "| 5 - Выполнить 20 вариант                      |" << endl;
	cout << "| 6 - Начать печать текста                      |" << endl;
	cout << "| 7 - Выход                                     |" << endl;
	cout << "=================================================" << endl;
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

void setupOutput() {
	system("chcp 1251 > nul");
	system(clearScreen);
	cout << fixed << showpoint;
}

int main() {

	char* input = nullptr;
	Text text;
	setupOutput();
	while (true) {
		short choice = menu();
		system(clearScreen);
		switch (choice)
		{
		case 1:
			input = getTextInput();
			break;
		case 2:
			input = loadText();
			break;
		case 3:
			break;
		case 4:
			execTask18(text);
			break;
		case 5:
			execTask20(text);
			break;
		case 6:
			print(text);
			break;
		case 7:
			return 0;
		default:
			break;
		}
		system("cls");
	}
}
