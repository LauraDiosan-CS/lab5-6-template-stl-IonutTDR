#include "ServiceSTL.h"

template<class T> Service<T>::Service(){}
template<class T> Service<T>::~Service(){}

template<class T> Service<T>::Service(const Service<T>& s)
{
	this->repo = s.repo;
}

template<class T>void Service<T>::addAp(const T& t)
{
	this->repo.addElem(t);
}

template<class T>void Service<T>::removeAp(int poz)
{
	this->repo.removeElem(poz);
}

template<class T>void Service<T>::updateAp(int poz, const T& t)
{
	this->repo.updateElem(poz, t);
}

template<class T>map<int, T> Service<T>::getAps()
{
	return this->repo.getAll();
}

template<class T>int Service<T>::getSize()
{
	return this->repo.getSize();
}
