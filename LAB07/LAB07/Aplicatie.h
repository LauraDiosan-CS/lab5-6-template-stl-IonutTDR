#ifndef APLICATIE_H
#define APLICATIE_H

#include "Aplicatie.h"
#include <iostream>
#include <ostream>
using namespace std;

class Aplicatie {
private:
	char* nume;
	int consumMemorie;
	char* status;
public:
	Aplicatie();
	Aplicatie(const char* nume, int consumMemorie, const char* status);
	Aplicatie(const Aplicatie& apl);
	~Aplicatie();
	char* getNume();
	int getMemorie();
	char* getStatus();
	void setNume(const char* newName);
	void setMem(int newMem);
	void setStatus(const char* newStatus);
	Aplicatie& operator=(const Aplicatie& a);
	bool operator==(const Aplicatie& a);
	friend ostream& operator<<(ostream& os, const Aplicatie& a);
};
#endif