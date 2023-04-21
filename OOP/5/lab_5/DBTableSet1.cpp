//DBTableSet1
#pragma warning(disable : 4996)
#include <iostream>
#include <iomanip>
#include "dbmsLib_v2_1.h"
#include <string.h>
#include <fstream>
#include <filesystem>

using std::cout;
using namespace dbmsLib1;


const char* typeNames[] = { "NoType","Int32","Double","String","Date" };
const char* dbmsLib1::DBTable1::TypeName1(DBType type)
{
	return typeNames[type];
}


string FileType(string name)
{
	string FT;
	int len = 1;
	while (name[len] != '.') len++;
	for (int i = len; i < name.length(); i++)
		FT += name[i];
	return(FT);
}


void DBTableSet1::ReadDB1()
{
	string fn = "DBTables";

	string path = "..\\LibraryBin\\";
	//string path = "..\\LibraryTxt\\";
	fn = path + fn + ".txt"; // ..\\LibraryTxt\\DBTables.txt
	//fn = path + fn + ".txt";

	cout << "ReadDB1:" << endl;

	ifstream in(fn);
	if (!in.is_open()) {
		cout << "ReadDB1: Ошибка открытия файла " << fn << endl;
	}
	char line[200];
	in.getline(line, 200);
	char* token, * next_token = line;
	vector <string> strArray;
	int i = 0;

	string fileName;
	while ((token = strtok_s(next_token, "|", &next_token)) != NULL) {
		strArray.push_back(token);
	}
	i = 0;
	for (unsigned int i = 0; i < strArray.size(); i++) {
		string fileType = FileType(strArray[i]);
		//std::filesystem::path(strArray[i]).extension().string();
	//cout << fileType << endl;
		if (fileType == ".txt") {
			//инициализация DBTable* адресом DBTableTxt
			string str;
			int j = 0;
			while (strArray[i][j] != '.')
			{
				str += strArray[i][j];
				j++;
			}
			strArray[i] = str;
			//cout << strArray[i] << endl;
			db[strArray[i]] = new DBTableTxt1(strArray[i]);

			db[strArray[i]]->ReadDBTable1(path + strArray[i] + fileType);
		}
		else {
			if (fileType == ".bin")
				//инициализация DBTable* адресом DBTableBin
				db[strArray[i]] = new DBTableBin1(strArray[i]);
			else {
				std::cout << "ReadDB1: Ошибка имени БД" << endl;
				break;
			}

			db[strArray[i]]->ReadDBTable1(path + strArray[i]);
			//DBTableBin1::ReadDBTable1(path + strArray[i] + fileType);
		}
		//полиморфный вызов виртуальной функции
		//tab.db[strArray[i]]->PrintTable(80);
	}
	std::cout << endl;
}


void dbmsLib1::DBTableSet1::PrintDB1(int screenWidth)
{
	map <string, DBTable1*>::iterator iter;
	for (iter = db.begin(); iter != db.end(); iter++)
	{
		iter->second->PrintTable1(screenWidth);
	}
}
void dbmsLib1::DBTableSet1::WriteDB1()
{
	map <string, DBTable1*>::iterator iter;
	string path = "..\\LibraryTxt\\";
	std::cout << "\nWriteDB1:" << endl;
	for (iter = db.begin(); iter != db.end(); iter++)
	{
		string tabname = (iter->first);
		//cout << tabname << endl;
		string tabName1 = path + tabname;
		iter->second->WriteDBTable1(tabName1);
	}
	std::cout << endl;
}