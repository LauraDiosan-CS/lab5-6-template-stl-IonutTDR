#ifndef SERVICEFILE_H
#define SERVICE_H
#include "RepositoryFile.h"

class ServiceFile {
private:
	RepositoryFile repo;
public:
	ServiceFile();
	ServiceFile(const RepositoryFile& r);
	void setRepo(const RepositoryFile& r);
	~ServiceFile();
	void add(const Aplicatie& a, const char* fileName);
	void remove(int poz,  const char* fileName);
	void update(int poz, const Aplicatie& a, const char* fileName);
	map<int, Aplicatie> get(const char* fileName);
};

#endif // !SERVICEFILE_H

