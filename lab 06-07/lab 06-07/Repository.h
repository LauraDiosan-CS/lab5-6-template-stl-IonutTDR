#ifndef REPOSITORY_H
#define REPOSITORY_H

#include<iterator>
#include <map>
#include <iostream>
using namespace std;
template <class T>
class Repository {
private:
	map<int, T> elem;
	int size;
public:
	Repository();
	Repository(const Repository<T>& repo);
	~Repository();
	void addElem(const T& el);
	T* getAll();
};
#endif // !REPOSITORY_H