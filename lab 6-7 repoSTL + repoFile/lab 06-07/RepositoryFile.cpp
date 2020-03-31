#include "RepositoryFile.h"
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

RepositoryFile::RepositoryFile()
{
	this->size = 0;
}
RepositoryFile::~RepositoryFile()
{
	this->size = 0;
}

RepositoryFile::RepositoryFile(const char* fileName)
{
	ifstream f(fileName);
	string linie;
	char* nume = new char[101];
	int memorie = 0;
	char* status = new char[10];
	while (!f.eof())
	{
		f >> this->size >> nume >> memorie >> status;
		if (strcmp(nume, "") != 0 && strcmp(status,"") != 0)
		{
			Aplicatie a(nume, memorie, status);
			this->elem.insert(pair<int, Aplicatie>(this->size++, a));
		}
	}
	delete[] nume;
	delete[] status;
	f.close();
}

void RepositoryFile::loadFile(const char* fileName)
{
	this->elem.clear();
	this->size = 0;
	ifstream f(fileName);
	int i = 0;
	char* nume = new char[101];
	int memorie = 0;
	char* status = new char[10];
	while (!f.eof())
	{
		f >> i >>  nume >> memorie >> status;
		if (strcmp(nume, "") != 0 && strcmp(status, "") != 0)
		{
			Aplicatie a(nume, memorie, status);
			this->elem.insert(pair<int, Aplicatie>(this->size++, a));
		}
	}
	delete[] nume;
	delete[] status;
	f.close();
}

void RepositoryFile::addElem(const Aplicatie& a)
{
	this->elem.insert(pair<int, Aplicatie>(this->size++, a));
}

void RepositoryFile::updateElem(int poz, const Aplicatie& a)
{
	this->elem[poz] = a;
}

void RepositoryFile::removeElem(int poz)
{
	this->elem.erase(poz);
	this->size--;
}

map<int, Aplicatie> RepositoryFile::getAll()
{
	return this->elem;
}

int RepositoryFile::getSize()
{
	return this->size;
}

void RepositoryFile::saveFile(const char* fileName)
{
	ofstream f(fileName);
	map<int, Aplicatie>::iterator itr;
	for (itr = elem.begin(); itr != elem.end(); itr++)
		f << itr->first << " " << itr->second;
	f.close();
}