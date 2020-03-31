#ifndef REPOSITORYFILE_H
#define REPOSITORYFILE_H

#include "Aplicatie.h"
#include <map>
#include <iterator>

class RepositoryFile {
private:
	map<int, Aplicatie> elem;
	int size;
public:
	RepositoryFile();
	RepositoryFile(const char* fileName);
	void loadFile(const char* fileName);
	void addElem(const Aplicatie& a);
	void updateElem(int poz, const Aplicatie& newApl);
	void removeElem(int poz);
	map<int, Aplicatie> getAll();
	int getSize();
	void saveFile(const char* fileName);
	~RepositoryFile();
};

#endif // !REPOSITORYFILE_H
