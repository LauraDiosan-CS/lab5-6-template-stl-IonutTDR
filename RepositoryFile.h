#ifndef REPOSITORYFILE_H
#define REPOSITORYFILE_H

#include "Aplicatie.h"
#include <map>
#include <iterator>
#include "RepositorySTL.h"

class RepositoryFile: public Repository<Aplicatie>{
public:
	RepositoryFile();
	RepositoryFile(const char* fileName);
	void loadFile(const char* fileName);
	void saveFile(const char* fileName);
	~RepositoryFile();
};

#endif // !REPOSITORYFILE_H
