#include "Aplicatie.h"
#include <cstring>

Aplicatie::Aplicatie()
{
	this->nume = NULL;
	this->consumMemorie = 0;
	this->status = NULL;
}

Aplicatie::Aplicatie(const char* name, int consum, const char* status)
{
	this->nume = new char[strlen(name) + 1];
	strcpy_s(this->nume, strlen(name) + 1, name);
	this->consumMemorie = consum;
	this->status = new char[strlen(status) + 1];
	strcpy_s(this->status, strlen(status) + 1, status);
}

Aplicatie::Aplicatie(const Aplicatie& a)
{
	this->nume = new char[strlen(a.nume) + 1];
	strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);

	this->consumMemorie = a.consumMemorie;

	this->status = new char[strlen(a.status) + 1];
	strcpy_s(this->status, strlen(a.status) + 1, a.status);
}

Aplicatie::~Aplicatie()
{
	if (this->nume)
	{
		delete[] this->nume;
		this->nume == NULL;
	}
	if (this->status)
	{
		delete[] this->status;
		this->status = NULL;
	}
}

char* Aplicatie::getNume()
{
	return this->nume;
}

int Aplicatie::getMemorie()
{
	return this->consumMemorie;
}

char* Aplicatie::getStatus()
{
	return this->status;
}

Aplicatie& Aplicatie::operator=(const Aplicatie& a)
{
	if (this->nume)
	{
		delete[] this->nume;
		this->nume == NULL;
	}
	if (this->status)
	{
		delete[] this->status;
		this->status = NULL;
	}

	this->nume = new char[strlen(a.nume) + 1];
	strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);

	this->consumMemorie = a.consumMemorie;

	this->status = new char[strlen(a.status) + 1];
	strcpy_s(this->status, strlen(a.status) + 1, a.status);

	return*this;
}

void Aplicatie::setNume(const char* newName)
{
	this->nume = new char[strlen(newName) + 1];
	strcpy_s(this->nume, strlen(newName) + 1, newName);
}

void Aplicatie::setMem(int newMem)
{
	this->consumMemorie = newMem;
}

void Aplicatie::setStatus(const char* newStatus)
{
	this->status = new char[strlen(newStatus) + 1];
	strcpy_s(this->status, strlen(newStatus) + 1, newStatus);
}

bool Aplicatie::operator==(const Aplicatie& a)
{
	return strcmp(this->nume, a.nume) == 0 && this->consumMemorie == a.consumMemorie && strcmp(this->status, a.status) == 0;
}

ostream& operator<<(ostream& os, const Aplicatie& a)
{
	os << a.nume << " " << a.consumMemorie << " " << a.status << "\n";
	return os;
}