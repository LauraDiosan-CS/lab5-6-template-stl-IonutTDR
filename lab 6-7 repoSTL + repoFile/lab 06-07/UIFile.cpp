#include <iostream>
#include <fstream>
#include "UIFile.h"
using namespace std;

void printMenu1()
{
	cout << "1. Adauga aplicatie \n2. Sterge aplicatie\n3. Actualizeaza aplicatie\n4. Afisare aplicatii\nx. Iesire\n";
	cout << "\n";
}

UIFile::UIFile() {}
UIFile::~UIFile(){}

/*	Verifica daca in fisierul curent exista deja o aplicatie cu acelasi nume, daca memoria > 0 sau daca statusul este ram sau swap intr-un fisier
	in: const char* nume - numele aplicatiei; int memorie - consumul memoriei; const char* status - statusul; const char* fileName - numele fisierului
*/
bool UIFile::verificare(const char* nume, int memorie, const char* status, const char* fileName)
{
	map<int, Aplicatie> elems = this->s.get(fileName);

	for (int i = 0; i < this->s.get(fileName).size(); i++)
		if (strcmp(elems[i].getNume(), nume) == 0)
			return 0;

	if (strcmp(status, "ram") != 0 && strcmp(status, "swap") != 0 || memorie <= 0)
		return 0;

	return 1;
}

/*	Adauga  o aplicatie in fisier
	in: const char* fileName - numele fisierului
*/
void UIFile::add(const char* fileName)
{
	char* nume = new char[100];
	int memorie = 0;
	char* status = new char[10];

	cout << "Numele aplicatiei: "; cin >> nume;
	cout << "Memoria consumata (trebuie sa fie mai mare decat 0): "; cin >> memorie;
	cout << "Statusul [ram/swap]: "; cin >> status;

	if (verificare(nume, memorie, status, fileName) == 0)
	{
		cout << "Date invalide!\n";
		cout << "\n";
		return;
	}
	Aplicatie a(nume, memorie, status);

	this->s.add(a, fileName);
	cout << "\n";
}


/*	Sterge o aplicatie din fisier de pe o pozitie data
	in: const char* fileName - numele fisierului
*/
void UIFile::remove(const char* fileName)
{
	int index;
	cout << "Se va sterge aplicatia cu ID-ul (ID-ul reprezinta pozitia acesteia in lista, indexarea fiind de la 0): ";
	cin >> index;
	this->s.remove(index, fileName);
	cout << "Aplicatie stearsa cu succes!\n";
	cout << "\n";
}


/*	Actualizeaza o aplicatie din fisier de pe o pozitie data
	in: const char* fileName - numele fisierului
*/
void UIFile::update(const char* fileName)
{
	int index;
	char* nume = new char[10];
	int memorie = 0;
	char* status = new char[10];
	cout << "Se va actualiza aplicatia cu ID-ul (ID-ul reprezinta pozitia acesteia in lista, indexarea fiind de la 0): ";
	cin >> index;

	cout << "Numele aplicatiei: "; cin >> nume;
	cout << "Memoria consumata (trebuie sa fie mai mare decat 0): "; cin >> memorie;
	cout << "Statusul [ram/swap]: "; cin >> status;

	if (verificare(nume, memorie, status, fileName) == 0)
	{
		cout << "Date invalide!\n";
		cout << "\n";
		return;
	}

	Aplicatie a(nume, memorie, status);

	this->s.update(index, a, fileName);
	cout << "\n";
}

/*	Afiseaza aplicatiile dintr-un fisier
	in: const char* fileName - numele fisierului
*/
void UIFile::getAll(const char* fileName)
{
	map<int, Aplicatie> a = this->s.get(fileName);
	int n = this->s.get(fileName).size();
	map<int, Aplicatie>::iterator itr;
	for (itr = a.begin(); itr != a.end(); itr++)
		cout << itr->first << " " << itr->second;
	cout << "\n";
}

void UIFile::run(const char* fileName)
{
	char op;
	int ok = 1;
	while (ok)
	{
		printMenu1();
		cout << "Alege optiunea: "; cin >> op;
		cout << "\n";
		if (op == '1')
			this->add(fileName);

		if (op == '2')
		{
			this->getAll(fileName);
			this->remove(fileName);
		}

		if (op == '3')
		{
			this->getAll(fileName);
			this->update(fileName);
		}

		if (op == '4')
		{
			this->getAll(fileName);
		}

		if (op == 'x')
			break;
	}
}