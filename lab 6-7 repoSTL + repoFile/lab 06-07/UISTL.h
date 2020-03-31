#ifndef UISTL_H
#define UISTL_H

#include "RepositorySTL.h"
#include "Aplicatie.h"
#include "ServiceSTL.cpp"
class UISTL {
private:
	Service<Aplicatie> service;
public:
	UISTL();
	~UISTL();
	bool verificare(const char* nume, int memorie, const char* status);
	void add();
	void remove();
	void update();
	void getAll();
	void run();
};

void printMenu();
#endif // !UISTL_H