#include <iostream>
#include <cstring>
#include "UISTL.h"
#include "Aplicatie.h"
#include "RepositorySTL.h"
#include "ServiceSTL.h"
using namespace std;

void printMenu()
{
	cout << "1. Adauga aplicatie \n2. Sterge aplicatie\n3. Actualizeaza aplicatie\n4. Afisare aplicatii\nx. Iesire\n";
	cout << "\n";
}

UISTL::UISTL(){}
UISTL::~UISTL(){}

bool UISTL::verificare(const char* nume, int memorie, const char* status)
{
	map<int, Aplicatie> elems = this->service.getAps();

	for (int i = 0; i < this->service.getSize(); i++)
		if (strcmp(elems[i].getNume(), nume) == 0)
			return 0;

	if (strcmp(status, "ram") !=0 && strcmp(status, "swap") != 0 || memorie <= 0)
		return 0;

	return 1;
}

void UISTL::add()
{
	char* nume = new char[100];
	int memorie = 0;
	char* status = new char[10];
	
	cout << "Numele aplicatiei: "; cin >> nume;
	cout << "Memoria consumata (trebUISTLe sa fie mai mare decat 0): "; cin >> memorie;
	cout << "Statusul [ram/swap]: "; cin >> status;

	if (verificare(nume, memorie, status) == 0)
	{
		cout << "Date invalide!\n";
		cout << "\n";
		return;
	}
	Aplicatie a(nume, memorie, status);

	this->service.addAp(a);
	cout << "\n";
}

void UISTL::remove()
{
	int index;
	cout << "Se va sterge aplicatia cu ID-ul (ID-ul reprezinta pozitia acesteia in lista, indexarea fiind de la 0): ";
	cin >> index;
	this->service.removeAp(index);
	cout << "Aplicatie stearsa cu succes!\n";
	cout << "\n";
}

void UISTL::update()
{
	int index;
	char* nume = new char[10];
	int memorie = 0;
	char* status = new char[10];
	cout << "Se va actualiza aplicatia cu ID-ul (ID-ul reprezinta pozitia acesteia in lista, indexarea fiind de la 0): ";
	cin >> index;

	cout << "Numele aplicatiei: "; cin >> nume;
	cout << "Memoria consumata (trebUISTLe sa fie mai mare decat 0): "; cin >> memorie;
	cout << "Statusul [ram/swap]: "; cin >> status;

	if (verificare(nume, memorie, status) == 0)
	{
		cout << "Date invalide!\n";
		cout << "\n";
		return;
	}

	Aplicatie a(nume, memorie, status);

	this->service.updateAp(index, a);
}

void UISTL::getAll()
{
	map<int, Aplicatie> a = this->service.getAps();
	int n = this->service.getSize();
	map<int, Aplicatie>::iterator itr;
	for (itr = a.begin(); itr != a.end(); itr++)
		cout << itr->first << " " << itr->second;
	cout << "\n";
}

void UISTL::run()
{
	char op;
	int ok = 1;
	while (ok)
	{
		printMenu();
		cout << "Alege optiunea: "; cin >> op;

		if (op == '1')
			this->add();

		if (op == '2')
		{
			this->getAll();
			this->remove();
		}

		if (op == '3')
		{
			this->getAll();
			this->update();
		}

		if (op == '4')
		{
			this->getAll();
		}

		if (op == 'x')
			break;
	}
}