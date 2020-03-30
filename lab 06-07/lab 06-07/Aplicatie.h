#pragma once
#include <iostream>
using namespace std;
#include <ostream>
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
	Aplicatie& operator=(const Aplicatie& g);
	bool operator==(const Aplicatie& g);
	//friend ostream& operator<<(ostream& os, const Aplicatie& g);
};