#include "Repository.h"
#include <map>
#include <iterator>

template <class T> Repository<T>::Repository()
{
	this->size = 0;
}

template<class T>Repository<T>::Repository(const Repository<T>& repo)
{
	typename map<int, T>::iterator itr;
	for (itr = repo.elem.begin(); itr != repo.elem.end(); ++itr)
		this->elem.insert(pair<int, T>(itr->first, itr->second)), this->size++;
}

template<class T> void Repository<T>::addElem(const T& el)
{
	this->elem.insert(pair<int, T>(this->size++, el));
}

template<class T>T* Repository<T>::getAll()
{
	T* elemente = new T[10];
	int n = 0;
	typename map<int, T>::iterator i;
	for (i =this->elem.begin(); i != this->elem.end(); i++)
		elemente[n++] = i->second;
	return elemente;
}

template<class T> Repository<T>::~Repository()
{
	this->size = 0;
}

