//DBTableTxt1
#pragma warning(disable : 4996)
#include <iostream>
#include <iomanip>
#include "dbmsLib_v2_1.h"
#include <string.h>
#include <fstream>

using namespace dbmsLib1;

dbmsLib1::DBType DBTable1::GetType1(string typeName) {
	string a[] = { "NoType","Int32","Double","String","DBDate" };
	for (int i = 0; i < 5; i++) {
		if (typeName == a[i])
			return (dbmsLib1::DBType)i;
	}
}


void* GetValue1(string value, string columnName, Header hdr)
//возвращает значение переменной value, преобразованное из типа   
//string в тип typeName, имя которого указано в заголовке  
//столбца таблицы в C-файле.
{
	switch (hdr[columnName].colType)
	{
	case Int32:		return new int(stoi(value)); break;
	case Double:	return new double(stod(value)); break;
	case String:	return new string(value); break;
	case DBDate:		return new dbmsLib1::DBDate1(value); break;
	default: cout << "Недопустимый тип данных в столбце\n" << columnName << endl;
	}
	return 0;
}


string dbmsLib1::DBTableTxt1::ignoreBlanc(const string str) {
	string bufStr = str;
	int begStr = bufStr.find_first_not_of(' ');
	return bufStr.substr(begStr);
}


void DBTableTxt1::CreateTableMaket(Strip*& strips, int& nStrips, int screenWidth)
{
	Header::iterator headerIter, contHeaderIter;
	int nColumn = (int)columnHeaders.size();
	//Заполнение массива ширины полей для печати таблицы 
	int* fieldW = new int[nColumn];
	headerIter = columnHeaders.begin();
	for (int k = 0; k < nColumn; k++) {
		//что шире: заголовок или данные?
		fieldW[k] = headerIter->second.length > headerIter->first.size() ?
			headerIter->second.length + 8 : headerIter->first.size() + 5;
		headerIter++;
	}
	int currCol = 0;//порядковый номер столбца в таблице
	nStrips = 1;//число полос в распечатке таблицы
	int sumWidth = 0;//суммарная ширина столбцов в полосе
	int n = 0;//число столбцов в полосе
	int buff[40] = { 0 };//объявление и обнуление буфера для временного 
	//хранения числа столбцов в полосе (n<40)
	for (currCol = 0; currCol < nColumn; currCol++) {
		if (fieldW[currCol] >= screenWidth - 1) {
			cout << "Ширина столбца " << currCol << " больше ширины экрана\n";
			cout << "Таблицу нельзя распечатать" << endl;
			nStrips = 0;
			return;
		}
		sumWidth += fieldW[currCol];
		if ((sumWidth < screenWidth - 1) && (currCol < nColumn - 1)) {
			n++;
			continue;
		}
		if ((sumWidth >= screenWidth - 1)) {//выход за границу экрана 
			currCol--;
			buff[nStrips - 1] = n;
			nStrips++;
			n = 0;
			sumWidth = 0;
			continue;
		}
		if (currCol == nColumn - 1) {//последняя полоса
			n++;
			buff[nStrips - 1] = n;
		}
	}
	strips = new Strip[nStrips];
	int col = 0;
	for (int i = 0; i < nStrips; i++) {
		strips[i].nField = buff[i];
		strips[i].fieldWidth = new int[strips[i].nField];
		for (int j = 0; j < strips[i].nField; j++)
			strips[i].fieldWidth[j] = fieldW[col++];
	}
	//cout << "Количество полос:" << nStrips << endl;
}


Row DBTableTxt1::GetRow(int index) {
	return data[index];
}


string DBTableTxt1::valueToString1(Row& row, string columnName)
//возвращает значение переменной value, преобразованное из типа   
//typeName, имя которого указано в заголовке columnName столбца  
//таблицы, в тип string.
//!!! Вставить проверку наличия columnName в	DBTableTxt
{
	char buf[80] = { 0 };
	if (this->columnHeaders.find(columnName) != this->columnHeaders.end())
	{
		void* value = row[columnName];//потенциально опасная операция
		ostrstream os(buf, 80);
		switch (columnHeaders[columnName].colType) {
		case Int32: os << setw(8) << *(int*)value << '\0'; break;
		case Double: os << setw(12) << *(double*)value << '\0'; break;
		case String:os << setw(columnHeaders[columnName].length) <<
			ignoreBlanc(*(string*)value) << '\0'; break;
		case DBDate:
			return DateToStr(*(DBDate1*)value);
		default: cout << setw(8) << "NoType" << '\0';
			system("pause"); break;
		}
	}
	else
		cout << "column not found " << endl;
	return buf;
}


void dbmsLib1::DBTableTxt1::ReadDBTable1(string fileName)
{
	//cout << "ReadDBTable1" << fileName << endl;
	ifstream in(fileName);
	if (!in.is_open()) {
		cout << "ReadDBTable1: Ошибка открытия файла " << fileName << endl;
		return;
	}
	char line[200];
	in.getline(line, 200);
	char* token, * next_token = line;
	tableName = strtok_s(next_token, "|", &next_token);
	primaryKey = next_token;
	cout << "tableName: " << tableName << "; primaryKey: " << primaryKey << endl;
	in.getline(line, 200);
	next_token = line;
	ColumnDesc colHdr;
	pair<string, ColumnDesc> parHdr;
	columnHeaders.clear();
	while ((token = strtok_s(next_token, "|", &next_token)) != NULL) {
		strcpy_s(colHdr.colName, token);
		token = strtok_s(next_token, "|", &next_token);
		colHdr.colType = GetType1(token);
		token = strtok_s(next_token, "|", &next_token);
		colHdr.length = stoi(token);
		parHdr.first = colHdr.colName;
		parHdr.second = colHdr;
		columnHeaders.insert(parHdr);
	}
	data.clear();
	Header::iterator hdrIter;
	pair<string, void*> parRow;
	while (in.getline(line, 200)) {
		Row row = *(new Row());
		next_token = line;
		for (hdrIter = columnHeaders.begin(); hdrIter != columnHeaders.end(); hdrIter++)
		{
			token = strtok_s(next_token, "|", &next_token);
			parRow.first = hdrIter->first;
			parRow.second = GetValue1(token, hdrIter->first, columnHeaders);
			//if (hdrIter->first == "OutDate" || hdrIter->first == "InDate") cout << token << endl;//cout << *(DBDate1*)parRow.second << endl;
			row.insert(parRow);
		}
		data.push_back(row);
	}
}


void DBTableTxt1::PrintTable1(int screenWidth)
{
	cout << "Таблица " << tableName << endl;

	Strip* strips;
	int nStrip;
	Header::iterator headerIter, contHeaderIter;
	Row::iterator rowIter, contRowIter;
	CreateTableMaket(strips, nStrip, screenWidth);
	contHeaderIter = columnHeaders.begin();
	if (data.begin() != data.end()) {

		contRowIter = data[0].begin();

		for (int r = 0; r < nStrip; r++)
		{
			if (r > 0)
				cout << "Продолжение таблицы" << endl;
			cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;
			headerIter = contHeaderIter;
			for (int j = 0; j < strips[r].nField; j++)
			{
				cout << setfill(' ') << setw(strips[r].fieldWidth[j]) << headerIter->first;
				headerIter++;
			}
			cout << endl;
			headerIter = contHeaderIter;
			for (int j = 0; j < strips[r].nField; j++)
			{
				cout << setfill(' ') << setw(strips[r].fieldWidth[j]) << TypeName1(headerIter->second.colType);
				headerIter++;
			}
			cout << endl;
			cout << setfill('-') << setw(screenWidth - 1) << '-' << setfill(' ') << endl;
			for (int i = 0; i < data.size(); i++)
			{
				rowIter = contRowIter;
				for (int j = 0; j < strips[r].nField; j++)
				{
					//cout << " <- " << valueToString1(data[i], rowIter->first) << " -> " << endl;
					//cout << " <- " << valueToString1(data[i], rowIter->first) << " -> " << endl;
					cout << setw(strips[r].fieldWidth[j]) << valueToString1(data[i], rowIter->first);
					rowIter++;
				}
				cout << endl;
			}
			cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl << endl;
			contHeaderIter = headerIter;
			contRowIter = rowIter;
		}
	}
	else
	{
		headerIter = contHeaderIter;
		for (int r = 0; r < nStrip; r++)
		{
			if (r > 0)
				cout << "Продолжение таблицы" << endl;
			cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;

			for (int j = 0; j < strips[r].nField; j++)
			{
				cout << setfill(' ') << setw(strips[r].fieldWidth[j]) << headerIter->first;
				headerIter++;
			}
			cout << endl;
			headerIter = contHeaderIter;
			for (int j = 0; j < strips[r].nField; j++)
			{
				cout << setfill(' ') << setw(strips[r].fieldWidth[j]) << TypeName1(headerIter->second.colType);
				headerIter++;
			}
			cout << endl;
			cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl << endl;
		}
	}
	delete strips;
}


void DBTableTxt1::WriteDBTable1(string fileName) {
	cout << fileName << endl;
	//ofstream out (fileName, ios::app);
	ofstream out;
	out.open(fileName, ofstream::out | ofstream::trunc);
	if (!out.is_open()) {
		cout << "WriteDBTable8: Ошибка открытия файла " << fileName << endl;
		return;
	}

	out << tableName << "|" << primaryKey << endl;
	Header::iterator headerIter;
	Row::iterator rowIter;
	for (headerIter = columnHeaders.begin(); headerIter != columnHeaders.end(); headerIter++)
	{
		if (headerIter == columnHeaders.begin())
		{
			out << headerIter->first << "|" << TypeName1(headerIter->second.colType) << "|" << headerIter->second.length;
		}
		else
		{
			out << "|" << headerIter->first << "|" << TypeName1(headerIter->second.colType) << "|" << headerIter->second.length;
		}
	}
	out << endl;
	for (int i = 0; i < data.size(); i++)
	{
		for (rowIter = data[i].begin(); rowIter != data[i].end(); rowIter++)
		{
			if (rowIter == data[i].begin())
				out << valueToString1(data[i], rowIter->first);
			else
				out << "|" << valueToString1(data[i], rowIter->first);
		}
		out << endl;
	}
}


void dbmsLib1::DBTableTxt1::WriteTableBin1(string fileName)
{
	cout << "WriteTableBin1" << endl;
	ofstream fout;
	fout.open((fileName).c_str(), ios::binary | ios::out);
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла " << fileName << endl;
		system("pause");
		return;
	}
	Header::iterator iter;
	Row::iterator dataIter;

	//Запись в бинарный файл первой строки .txt-файла:
	//имени таблицы  и
	//(длины имён таблиц и столбцов фиксированы и равны 24 байтам, включая \0)
	char buf[80];
	strcpy_s(buf, 80, this->tableName.c_str());
	int len = LENGTH1;
	fout.write((char*)&len, 4);
	fout.write(buf, len);
	//Запись имени столбца primaryKey
	//
	strcpy_s(buf, 80, this->primaryKey.c_str());
	fout.write((char*)&len, 4);
	fout.write(buf, len);
	//
	//Запись в бинарный файл заголовка таблицы (вторая строка.txt-файла)
	int size = this->columnHeaders.size();
	fout.write((char*)&size, 4);
	size = sizeof(ColumnDesc);
	for (iter = this->columnHeaders.begin(); iter != this->columnHeaders.end(); iter++)
		fout.write((char*)&(iter->second), size);
	//Запись строк таблицы.
	int nRows = (int)this->data.size();
	fout.write((char*)&nRows, 4);
	char sep = '.';
	int day, month, year;
	DBDate1 date;
	for (int i = 0; i < nRows; i++) {
		dataIter = this->data[i].begin();
		for (iter = this->columnHeaders.begin(); iter != this->columnHeaders.end(); dataIter++, iter++)
		{//iter->second указывает на ColumnDesc, dataIter->second указывает на void*.
			//cout << (dataIter->second) << endl;
			switch ((iter->second).colType) {
			case Int32:
				//cout << *(int*)(dataIter->second) << endl;
				fout.write((char*)((dataIter->second)), sizeof(int));
				break;
			case Double:
				fout.write((char*)(dataIter->second), sizeof(double));
				break;
			case DBDate:
				date = *(DBDate1*)dataIter->second;
				day = date.GetDay(), month = date.GetMonth(), year = date.GetYear();
				fout.write((char*)(&day), sizeof(int));
				fout.write((char*)&sep, sizeof(char));
				fout.write((char*)(&month), sizeof(int));
				fout.write((char*)&sep, sizeof(char));
				fout.write((char*)(&year), sizeof(int));
				/*str = DateToStr(*(DBDate1*)(dataIter->second));
				strcpy_s(buf, 80, str.c_str());
				fout.write((char*)(dataIter->second), iter->second.length);*/
				break;
			case String:
				strcpy_s(buf, 80, (*(string*)(dataIter->second)).c_str());
				fout.write(buf, iter->second.length);
				//buf+1 - для того, чтобы length не обрубал конец строки '\0'
				break;
			default:
				cout << "Недопустимый тип данных в БД\n";
				return;
			}
		}
	}
}


void dbmsLib1::DBTableTxt1::ReadTableBin1(string tabName)
{
	//begin
	cout << "ReadTableBin1" << endl;


	//open file
	ifstream fin;
	fin.open((tabName).c_str(), ios::binary | ios::in);


	//check if opened
	if (!fin.is_open())
	{
		cout << "Ошибка открытия файла\n" << endl;
		system("pause");
		return;
	}







	//Прочитать имя таблицы и имя столбца с primaryKey из первой строки файла
	int len;
	char buf[80];
	fin.read((char*)&len, 4);
	fin.read((char*)buf, len);
	if (len > 79) {
		cout << "Ошибка: длина имени таблицы " << tabName << endl;
		return;
	}
	buf[len] = '\0';
	this->tableName = buf;
	//Прочитать имя столбца с primaryKey
	//
	fin.read((char*)&len, 4);
	fin.read((char*)buf, len);
	if (len > 79) {
		cout << "Ошибка: длина имени primaryKey" << tabName << endl;
		return;
	}
	buf[len] = '\0';
	this->primaryKey = buf;
	//
	//Прочитать из файла заголовок таблицы и записать его в table.columnHeaders
	int size = 0;	//число столбцов в заголовке таблицы
	fin.read((char*)&size, sizeof(int));
	len = sizeof(ColumnDesc);
	ColumnDesc colDesc;
	this->columnHeaders.clear();
	for (int i = 0; i < size; i++) {
		fin.read((char*)&colDesc, len);
		this->columnHeaders[colDesc.colName] = colDesc;
	}


	//Чтение строк таблицы

	Header::iterator hdrIter;
	data.clear();
	int nRows;
	int day=0, month=0, year=0;
	char sep = ' ';
	fin.read((char*)&nRows, 4);
	
	len = sizeof(colDesc.colName);//длина имени столбца (=24 байта)
	for (int i = 0; i < nRows; i++)
	{
		Row row;//буфер для формирования строки таблицы
		pair<string, void*> pr;
		for (hdrIter = columnHeaders.begin(); hdrIter != columnHeaders.end(); hdrIter++) {
			pr.first = hdrIter->first;
			switch ((hdrIter->second).colType) {//чтение данных
			case Int32:	pr.second = new int;
				fin.read((char*)pr.second, sizeof(int));
				//cout << *(int*)pr.second << endl;
				row.insert(pr);
				break;
			case Double:
				fin.read((char*)pr.second, sizeof(double));
				row.insert(pr);
				break;
			case DBDate:
				fin.read((char*)&day, sizeof(int));
				fin.read((char*)&sep, sizeof(char));
				fin.read((char*)&month, sizeof(int));
				fin.read((char*)&sep, sizeof(char));
				fin.read((char*)&year, sizeof(int));
				pr.second = new DBDate1(day, month, year);
				//cout << *(DBDate1*)pr.second << endl;
				row.insert(pr);
				break;
			case String:
				if (hdrIter->second.length > 79) {
					cout << "Ошибка: длина поля " << hdrIter->second.colName <<
						" таблицы " << tabName << endl;
					return;
				}
				fin.read(buf, hdrIter->second.length);
				buf[hdrIter->second.length] = '\0';
				pr.second = new string(ignoreBlanc(buf));
				row.insert(pr);
				//cout<<*(string*)row[pr.first]<<endl;
				break;
			default:
				cout << "Недопустимый тип данных в БД\n";
				return;
			}
		}
		data.push_back(row);
	}



	//close file
	fin.close();
}
