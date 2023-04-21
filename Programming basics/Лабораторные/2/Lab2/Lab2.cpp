#include <iostream>
#include <string>
using namespace std;

struct time {
	int h; //hours
	int m; //minutes
};

string getTimeOfDay(int h) {
	if (h < 5)
		return "ночи";
	else if (h < 12)
		return "утра";
	else if (h < 18)
		return "дня";
	else
		return "вечера";
}

string getHPadeg(int h) {
	if (h == 1)
		return "час";
	else if (h > 1 && h < 5)
		return "часа";
	else
		return "часов";
}
string getMPadeg(int m) {
	if ((m != 11) && (m % 10 == 1))
		return "минута";
	else if ((!(m > 10 && m < 20)) && (m % 10 > 1) && (m % 10 < 5))
		return "минуты";
	else
		return "минут";
}

string getHourString(int h) {
	if (h > 12)
		h -= 12;
	else if (!h)
		h = 12;

	return to_string(h) + " " + getHPadeg(h);
}
string getMinuteString(int m) {
	return to_string(m) + " " + getMPadeg(m);
}

bool checkTime(struct time t) {
	return (t.h >= 0) && (t.h < 24) && (t.m >= 0) && (t.m < 61);
}
void getTimeFromConsole(struct time& t) {
	cout << "Введите время в 24х часовом формате через пробел:\n";
	cin >> t.h >> t.m;
}
string getTimeString(struct time t) {
	if (!checkTime(t))
		return "Неверный формат данных.";

	if (!t.m) {
		switch (t.h) {
			case 12:
				return "Полдень";
			case 0:
				return "Полночь";
		}
	}

	string timeOfDay = getTimeOfDay(t.h);
	string hourString = getHourString(t.h);

	if (!t.m)
		return hourString + " " + timeOfDay + " ровно";
	else {
		string minuteString = getMinuteString(t.m);
		return hourString + " " + minuteString + " " + timeOfDay;
	}

}

int main() {
	system("chcp 1251 > nul");

	struct time userInput;
	getTimeFromConsole(userInput);

	cout << getTimeString(userInput) << endl;

	return 0;
}