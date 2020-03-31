#ifndef SERVICE_H
#define SERVICE_H

#include "RepositorySTL.h";
#include "Aplicatie.h";
template <class T>
class Service {
private:
	Repository<T> repo;
public:
	Service();
	Service(const Service<T>& s);
	~Service();
	void addAp(const T& t);
	void removeAp(int poz);
	void updateAp(int poz, const T& t);
	int getSize();
	map<int, T> getAps();

};

#endif