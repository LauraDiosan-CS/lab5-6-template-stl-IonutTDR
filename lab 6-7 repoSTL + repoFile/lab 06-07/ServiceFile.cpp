#include "ServiceFile.h"

ServiceFile::ServiceFile(){}
ServiceFile::~ServiceFile() {}

ServiceFile::ServiceFile(const RepositoryFile& r)
{
	this->repo = r;
}

void ServiceFile::setRepo(const RepositoryFile& r)
{
	this->repo = r;
}

void ServiceFile::add(const Aplicatie& a, const char* fileName)
{
	this->repo.addElem(a);
	this->repo.saveFile(fileName);
}

void ServiceFile::remove(int poz, const char* fileName)
{
	this->repo.removeElem(poz);
	this->repo.saveFile(fileName);
}

void ServiceFile::update(int poz, const Aplicatie& a, const char* fileName)
{
	this->repo.updateElem(poz, a);
	this->repo.saveFile(fileName);
}

map<int, Aplicatie> ServiceFile::get(const char* fileName)
{
	this->repo.loadFile(fileName);
	return this->repo.getAll();
}