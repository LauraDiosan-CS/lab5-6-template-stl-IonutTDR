#include "Service.h"

template<class T>Service<T>::Service() {}
template<class T>Service<T>::~Service() {}

template<class T>Service<T>::Service(const RepositoryFile<T>& rf)
{
	this->repoF = rf;
}

template<class T> void Service<T>::add(const T a, const char* fileName)
{
	this->repoF.loadFile(fileName);
	this->repoF.addElem(a);
	this->repoF.saveFile(fileName);
}

template<class T>void Service<T>::remove(int poz, const char* fileName)
{
	this->repoF.loadFile(fileName);
	this->repoF.removeElem(poz);
	this->repoF.saveFile(fileName);
}

template<class T> void Service<T>::update(int poz, const T a, const char* fileName)
{
	this->repoF.loadFile(fileName);
	this->repoF.updateElem(poz, a);
	this->repoF.saveFile(fileName);
}

template<class T> map<int, T> Service<T>::get(const char* fileName)
{
	this->repoF.loadFile(fileName);
	return this->repoF.getAll();
}