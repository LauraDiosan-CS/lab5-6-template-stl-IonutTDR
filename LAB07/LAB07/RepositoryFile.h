#ifndef REPOSITORYFILE_H
#define REPOSITORYFILE_H

#include "RepositorySTL.h"

template <class T>
class RepositoryFile : public Repository<T> {
public:
	RepositoryFile();
	RepositoryFile(const char* fileName);
	void loadFile(const char* fileName);
	void saveFile(const char* fileName);
	~RepositoryFile();
};

#endif // !REPOSITORYFILE_H
