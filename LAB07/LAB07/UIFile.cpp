#include "UIFile.h"
#include "Service.cpp"
#include "RepositoryFile.cpp"
#include "RepositorySTL.cpp"


void printMenu1()
{
	cout << "1. Adauga aplicatie \n2. Sterge aplicatie\n3. Actualizeaza aplicatie\n4. Afisare aplicatii\nx. Iesire\n";
	cout << "\n";
}

UIFile::UIFile()
{
	this->ram = this->swap = 0;
}
UIFile::~UIFile() { this->ram = this->swap = 0; }

void UIFile::getMemory(const char* fileName)
{
	map<int, Aplicatie> apps = this->s.get(fileName);
	map<int, Aplicatie>::iterator itr;
	for (itr = apps.begin(); itr != apps.end(); itr++)
		if (strcmp(itr->second.getStatus(), "swap") == 0)
			this->swap += itr->second.getMemorie();
		else
			this->ram += itr->second.getMemorie();
}

void UIFile::updateStatusAfterX(const char* fileName, int X)
{
	typename map<int, Aplicatie>::iterator itr;
	map<int, Aplicatie> apps = this->s.get(fileName);
	if (this->ram > X)
	{
		for (itr = apps.begin(); itr != apps.end() && this->ram > X; itr++)
		{
			if (strcmp(itr->second.getStatus(), "ram") == 0)
			{
				this->ram -= itr->second.getMemorie();
				this->swap += itr->second.getMemorie();
				Aplicatie a(itr->second.getNume(), itr->second.getMemorie(), "swap");
				this->s.update(itr->first, a, fileName);
			}
		}
	}
	if (this->ram < X)
	{
		for (itr = apps.begin(); itr != apps.end(); itr++)
		{
			if (strcmp(itr->second.getStatus(), "swap") == 0)
				if (this->ram + itr->second.getMemorie() <= X)
				{
					this->ram += itr->second.getMemorie();
					this->swap -= itr->second.getMemorie();
					Aplicatie a(itr->second.getNume(), itr->second.getMemorie(), "ram");
					this->s.update(itr->first, a, fileName);
				}
		}
	}
}

void addStatusByX(Service<Aplicatie>& s, map<int, Aplicatie> elems, int& ram, int& swap, const char* nume, int memorie, const char* fileName, int X, int& gasit)
{
	typename map<int, Aplicatie>::iterator itr;
	if (ram + memorie <= X)
	{
		gasit = 0;
		ram += memorie;
		Aplicatie a(nume, memorie, "ram");
		s.add(a, fileName);
	}
	else
	{
		if (memorie <= X)
		{
			gasit = 1;
			for (itr = elems.begin(); itr != elems.end() && memorie + ram > X; itr++)
			{
				if (strcmp(itr->second.getStatus(), "ram") == 0)
				{
					ram -= itr->second.getMemorie();
					swap += itr->second.getMemorie();
					Aplicatie a(itr->second.getNume(), itr->second.getMemorie(), "swap");
					s.update(itr->first, a, fileName);
				}
			}
			Aplicatie a(nume, memorie, "ram");
			s.add(a, fileName);
			ram += memorie;
		}
		else
		{
			gasit = 2;
			Aplicatie a(nume, memorie, "swap");
			swap += memorie;
			s.add(a, fileName);
		}

	}
}


void removeByX(Service<Aplicatie>& s, map<int, Aplicatie> apps, int& ram, int& swap, const char* fileName, int X, int index)
{
	if (strcmp(apps[index].getStatus(), "ram") == 0)
		ram -= apps[index].getMemorie();
	else
		swap -= apps[index].getMemorie();

	typename map<int, Aplicatie>::iterator itr;
	for (itr = apps.begin(); itr != apps.end(); itr++)
		if (itr->first != index)
			if (strcmp(itr->second.getStatus(), "swap") == 0)
				if (itr->second.getMemorie() + ram <= X)
				{
					swap -= itr->second.getMemorie();
					ram += itr->second.getMemorie();
					Aplicatie a(itr->second.getNume(), itr->second.getMemorie(), "ram");
					s.update(itr->first, a, fileName);
				}
	s.remove(index, fileName);
}


void updateStatusByX(Service<Aplicatie>& s, map<int, Aplicatie> apps, int& ram, int& swap, const char* nume, int memorie, const char* fileName, int X, int& gasit, int index)
{
	typename map<int, Aplicatie>::iterator itr;
	if (strcmp(apps[index].getStatus(), "ram") == 0)
		ram -= apps[index].getMemorie();
	else
		if (strcmp(apps[index].getStatus(), "swap") == 0)
			swap -= apps[index].getMemorie();

	if (ram + memorie <= X)
	{
		gasit = 0;
		ram += memorie;
		Aplicatie a(nume, memorie, "ram");
		s.update(index, a, fileName);
	}
	else
	{
		if (memorie <= X)
		{
			for (itr = apps.begin(); itr != apps.end() && memorie + ram > X; itr++)
			{
				if (itr->first != index)
					if (strcmp(itr->second.getStatus(), "ram") == 0)
					{
						ram -= itr->second.getMemorie();
						swap += itr->second.getMemorie();
						Aplicatie a(itr->second.getNume(), itr->second.getMemorie(), "swap");
						s.update(itr->first, a, fileName);
					}
			}
			Aplicatie a(nume, memorie, "ram");
			s.update(index, a, fileName);
			ram += memorie;
		}
		else
		{
			gasit = 2;
			for (itr = apps.begin(); itr != apps.end(); itr++)
				if (itr->first != index)
					if (strcmp(itr->second.getStatus(), "swap") == 0)
						if (itr->second.getMemorie() + ram <= X)
						{
							swap -= itr->second.getMemorie();
							ram += itr->second.getMemorie();
							Aplicatie a(itr->second.getNume(), itr->second.getMemorie(), "ram");
							s.update(itr->first, a, fileName);
						}
			Aplicatie a(nume, memorie, "swap");
			swap += memorie;
			s.update(index, a, fileName);
		}

	}
}


/*	Adauga  o aplicatie in fisier
	in: const char* fileName - numele fisierului
*/
void UIFile::add(const char* fileName, int X)
{
	char* nume = new char[100];
	int memorie = 0;
	char* status = new char[10];

	cout << "Numele aplicatiei: "; cin >> nume;
	map<int, Aplicatie> elems = this->s.get(fileName);
	typename map<int, Aplicatie>::iterator itr;
	for (itr = elems.begin(); itr != elems.end(); itr++)
	{
		if (strcmp(itr->second.getNume(), nume) == 0)
		{
			cout << "Exista deja o aplicatie cu acest nume\n\n";
			return;
		}
	}

	cout << "Memoria consumata (trebuie sa fie mai mare decat 0): "; cin >> memorie;
	if (memorie <= 0)
	{
		cout << "Memoria consumata trebuie sa fie mai mare decat 0\n";
		return;
	}

	cout << "Statusul este: ";

	int gasit;

	addStatusByX(this->s, elems, this->ram, this->swap, nume, memorie, fileName, X, gasit);

	if (gasit == 0)
		cout << "ram\n";
	else
		if (gasit == 1)
			cout << "ram, dar se va modifica statusul unor aplicatii din RAM in SWAP\n";
		else
			cout << "swap\n";
	cout << "\n";
}


/*	Sterge o aplicatie din fisier de pe o pozitie data
	in: const char* fileName - numele fisierului
*/
void UIFile::remove(const char* fileName, int X)
{
	int index;
	cout << "Se va sterge aplicatia cu ID-ul (ID-ul se afla in stanga fiecarei aplicatii): ";
	cin >> index;

	typename map<int, Aplicatie>::iterator itr;
	map<int, Aplicatie>apps = this->s.get(fileName);
	itr = apps.find(index);
	if (itr == apps.end())
	{
		cout << "ID invalid\n\n";
		return;
	}

	removeByX(this->s, apps, this->ram, this->swap, fileName, X, index);

	cout << "Aplicatie stearsa cu succes!\n\n";
}


/*	Actualizeaza o aplicatie din fisier de pe o pozitie data
	in: const char* fileName - numele fisierului
*/
void UIFile::update(const char* fileName, int X)
{
	int index;
	cout << "Se va actualiza aplicatia cu ID-ul (ID-ul reprezinta pozitia acesteia in lista, indexarea fiind de la 0): ";
	cin >> index;
	typename map<int, Aplicatie>::iterator itr;
	map<int, Aplicatie>apps = this->s.get(fileName);
	itr = apps.find(index);
	if (itr == apps.end())
	{
		cout << "ID invalid\n\n";
		return;
	}
	if (strcmp(apps[index].getStatus(), "ram") == 0)
		this->ram -= apps[index].getMemorie();
	else
		this->swap -= apps[index].getMemorie();

	char* nume = new char[100];
	int memorie = 0;
	char* status = new char[10];

	cout << "Numele aplicatiei: "; cin >> nume;
	for (itr = apps.begin(); itr != apps.end(); itr++)
	{
		if (strcmp(itr->second.getNume(), nume) == 0 && itr->first != index)
		{
			cout << "Exista deja o aplicatie cu acest nume\n\n";
			return;
		}
	}

	cout << "Memoria consumata (trebuie sa fie mai mare decat 0): "; cin >> memorie;
	if (memorie <= 0)
	{
		cout << "Memoria consumata trebuie sa fie mai mare decat 0\n";
		return;
	}

	cout << "Statusul este: ";

	int gasit = 0;

	updateStatusByX(this->s, apps, this->ram, this->swap, nume, memorie, fileName, X, gasit, index);
	if (gasit == 0)
		cout << "ram\n";
	else
		if (gasit == 1)
			cout << "ram, dar se va modifica statusul unor aplicatii din RAM in SWAP\n";
		else
			cout << "swap\n";
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
	this->getMemory(fileName);
	cout << "Memoria predefinita: ";
	int X = 0;
	cin >> X;

	updateStatusAfterX(fileName, X);
	cout << "Statusuri actualizate cu succes\n";
	cout << "RAM: " << this->ram << "/" << X << " | " << "SWAP: " << this->swap << "\n";
	cout << "Aplicatii: \n";
	this->getAll(fileName);

	while (ok)
	{
		printMenu1();
		cout << "Alege optiunea: "; cin >> op;
		cout << "\n";
		if (op == '1')
		{
			cout << "RAM: " << this->ram << "/" << X << " | " << "SWAP: " << this->swap << "\n";
			cout << "Aplicatii inainte de adaugare: \n";
			this->getAll(fileName);
			this->add(fileName, X);
			cout << "RAM: " << this->ram << "/" << X << " | " << "SWAP: " << this->swap << "\n";
			cout << "Aplicatii dupa adaugare: \n";
			this->getAll(fileName);
		}

		if (op == '2')
		{
			cout << "RAM: " << this->ram << "/" << X << " | " << "SWAP: " << this->swap << "\n";
			cout << "Aplicatii inainte de stergere: \n";
			this->getAll(fileName);
			this->remove(fileName, X);
			cout << "RAM: " << this->ram << "/" << X << " | " << "SWAP: " << this->swap << "\n";
			cout << "Aplicatii dupa stergere: \n";
			this->getAll(fileName);
		}

		if (op == '3')
		{
			cout << "RAM: " << this->ram << "/" << X << " | " << "SWAP: " << this->swap << "\n";
			cout << "Aplicatii inainte de actualizare: \n";
			this->getAll(fileName);
			this->update(fileName, X);
			cout << "RAM: " << this->ram << "/" << X << " | " << "SWAP: " << this->swap << "\n";
			cout << "Aplicatii dupa actualizare: \n";
			this->getAll(fileName);
		}

		if (op == '4')
		{
			this->getAll(fileName);
		}

		if (op == 'x')
			break;
	}
}
