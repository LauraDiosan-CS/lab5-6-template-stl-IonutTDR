#include "RepositorySTL.h"


template <class T> Repository<T>::Repository()
{
	this->elem.clear();
	this->size = 0;
}

template<class T> void Repository<T>::addElem(const T el)
{
	this->elem.insert(pair<int, T>(this->size++, el));
}

template<class T> void Repository<T>::removeElem(int poz)
{
	typename map<int, T>::iterator itr;
	itr = this->elem.find(poz);
	if (itr != this->elem.end())
		this->elem.erase(itr);
}

template<class T> void Repository<T>::updateElem(int poz, const T newElem)
{
	this->elem[poz] = newElem;
}

template<class T>map<int, T> Repository<T>::getAll()
{
	return this->elem;
}

template<class T> Repository<T>::~Repository()
{
	this->elem.clear();
	this->size = 0;
}

template<class T> int Repository<T>::getSize()
{
	return this->elem.size();
}



