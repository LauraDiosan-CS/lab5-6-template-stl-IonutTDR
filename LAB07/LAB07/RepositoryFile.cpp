#include "RepositoryFile.h"
#include <fstream>
using namespace std;

template <class T> RepositoryFile<T>::RepositoryFile()
{
	this->size = 0;
}
template <class T>RepositoryFile<T>::~RepositoryFile()
{
	this->size = 0;
}

template <class T>RepositoryFile<T>::RepositoryFile(const char* fileName)
{
	ifstream f(fileName);
	char* i1 = new char[101];
	int i2 = 0;
	char* i3 = new char[10];
	while (!f.eof())
	{
		f >> this->size >> i1 >> i2 >> i3;
		if (strcmp(i1, "") != 0 && strcmp(i3, "") != 0)
		{
			T t(i1, i2, i3);
			this->elem.insert(pair<int, T>(this->size++, t));
		}
	}
	delete[] i1;
	delete[] i3;
	f.close();
}

template <class T> void RepositoryFile<T>::loadFile(const char* fileName)
{
	this->elem.clear();
	this->size = 0;
	ifstream f(fileName);
	char* i1 = new char[101];
	int i2 = 0;
	char* i3 = new char[10];
	while (!f.eof())
	{
		f >> this->size >> i1 >> i2 >> i3;
		if (strcmp(i1, "") != 0 && strcmp(i3, "") != 0)
		{
			T t(i1, i2, i3);
			this->elem.insert(pair<int, T>(this->size++, t));
		}
	}
	delete[] i1;
	delete[] i3;
	f.close();
}

template <class T> void RepositoryFile<T>::saveFile(const char* fileName)
{
	ofstream f(fileName);
	typename map<int, T>::iterator itr;
	for (itr = this->elem.begin(); itr != this->elem.end(); itr++)
		f << itr->first << " " << itr->second;
	f.close();
}