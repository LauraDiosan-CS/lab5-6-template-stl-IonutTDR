#ifndef SERVICE_H
#define SERVICE_H
#include "RepositoryFile.h"

template <class T>
class Service {
private:
	RepositoryFile<T> repoF;
public:
	Service();
	Service(const RepositoryFile<T>& rF);
	~Service();
	void add(const T t, const char* fileName);
	void remove(int poz, const char* fileName);
	void update(int poz, const T t, const char* fileName);
	map<int, T> get(const char* fileName);
};

#endif // !SERVICEFILE_H

