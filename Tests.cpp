#include "Tests.h"
#include "RepositorySTL.cpp"
#include "RepositoryFile.h"
#include "ServiceSTL.h"
#include "ServiceFile.h"
#include "Aplicatie.h"
#include "UISTL.h"
#include <assert.h>
#include <cassert>
#include <fstream>
using namespace std;

void test_repositorySTL()
{
	const Aplicatie a1("Poker", 60, "ram");
	const Aplicatie a2("AppStore", 30, "swap");
	const Aplicatie a3("Zynga", 80, "ram");

	Repository<Aplicatie> repo;
	//testeaza adaugarea 
	repo.addElem(a1);
	repo.addElem(a2);
	repo.addElem(a3);

	int n = repo.getSize();
	assert(n == 3);
	//testeaza preluarea aplicatiilor
	map<int, Aplicatie> elems = repo.getAll();

	assert(elems[0] == a1);
	assert(elems[1] == a2);
	assert(elems[2] == a3);
	//testeaza stergerea unei aplicatii
	repo.removeElem(0);
	elems = repo.getAll();

	assert(elems[0] == a2);
	assert(elems[1] == a3);
	n = repo.getSize();
	assert(n == 2);
	//testeaza actualizarea unei aplicatii
	Aplicatie a4("Defender", 400, "swap");
	repo.updateElem(1, a4);
	elems = repo.getAll();
	assert(elems[1] == a4);

	cout << "TEST REPO\n";

}

void test_repositoryFile()
{
	//sterge continutul fisierului
	std::ofstream ofs;
	ofs.open("TestRepo.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	RepositoryFile repo("TestRepo.txt");
	assert(repo.getSize() == 0);

	const Aplicatie a1("Poker", 60, "ram");
	const Aplicatie a2("AppStore", 30, "swap");
	const Aplicatie a3("Zynga", 80, "ram");
	//testeaza adaugarea aplicatiilor
	repo.addElem(a1);
	repo.addElem(a2);
	repo.addElem(a3);
	assert(repo.getSize() == 3);
	//testeaza stergerea aplicatiilor din fisier
	repo.removeElem(2);
	assert(repo.getSize() == 2);
	int n = repo.getSize();

	//testeaza actualizarea unei aplicatii si preluarea acestora din fisier
	Aplicatie a4("Facebook", 2000, "swap");
	repo.updateElem(0, a4);
	map<int, Aplicatie> elem = repo.getAll();
	assert(elem[0] == a4);

	assert(elem.size() == 2);
	//testeaza salvarea in fisier
	repo.saveFile("TestRepo.txt");

	RepositoryFile repo2;
	repo2.loadFile("TestRepo.txt");
	assert(repo2.getSize() == n);
	

}

void test_aplicatie()
{
	Aplicatie a1("AppStore", 30, "ram");
	Aplicatie a2;

	assert(strcmp(a1.getNume(),"AppStore") == 0);
	assert(a1.getMemorie() == 30);
	assert(strcmp(a1.getStatus(),"ram") == 0);

	a1.setNume("Facebook");
	a1.setMem(2000);
	a1.setStatus("swap");

	assert(strcmp(a1.getNume(), "Facebook") == 0);
	assert(a1.getMemorie() == 2000);
	assert(strcmp(a1.getStatus(), "swap") == 0);

	a2 = a1;
	assert(a2.getMemorie() == 2000);
	assert(a1 == a2);

	cout << "TEST APLICATIE\n";
}

void test_serviceSTL()
{
	const Aplicatie a1("Poker", 60, "ram");
	const Aplicatie a2("AppStore", 30, "swap");
	const Aplicatie a3("Zynga", 80, "ram");

	Service<Aplicatie> s;
	s.addAp(a1);
	s.addAp(a2);
	s.addAp(a3);

	assert(s.getSize() == 3);
	map<int, Aplicatie> elems = s.getAps();

	assert(elems[0] == a1);
	assert(elems[1] == a2);
	assert(elems[2] == a3);

	s.removeAp(1);
	assert(s.getSize() == 2);

	Aplicatie a4("Defender", 400, "swap");
	s.updateAp(0, a4);
	elems = s.getAps();
	assert(elems[0] == a4);

	cout << "TEST SERVICE\n";
}

void test_serviceFile()
{
	std::ofstream ofs;
	ofs.open("TestService.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	const Aplicatie a1("Poker", 60, "ram");
	const Aplicatie a2("AppStore", 30, "swap");
	const Aplicatie a3("Zynga", 80, "ram");

	ServiceFile s;

	s.add(a1, "TestService.txt");
	s.add(a2, "TestService.txt");
	s.add(a3, "TestService.txt");
	assert(s.get("TestService.txt").size() == 3);
	
	s.remove(2, "TestService.txt");
	assert(s.get("TestService.txt").size() == 2);
	assert(s.get("TestService.txt")[0] == a1 && s.get("TestService.txt")[1] == a2);

	Aplicatie a4("Facebook", 2000, "swap");
	s.update(0, a4, "TestService.txt");
	assert(s.get("TestService.txt")[0] == a4);

}

void test_addX()
{
	Aplicatie a1("Poker", 30, "ram");
	Aplicatie a2("AppStore", 30, "swap");
	Aplicatie a3("Zynga", 10, "ram");

	Service<Aplicatie> s;
	s.addAp(a1);
	s.addAp(a2);
	s.addAp(a3);
	int ram = 40;
	int swap = 30;
	int gasit = 0;
	addByX(s, 40, "FB", 20, "ram", ram, swap, gasit);
	assert(gasit == 0);
	assert(ram == 30);
	assert(swap == 60);
	map<int, Aplicatie> apps = s.getAps();
	assert(strcmp(apps[0].getStatus(), "swap") == 0);
	cout << "TEST ADDBYX\n";
}

void myTests()
{
	test_aplicatie();
	test_repositoryFile();
	test_repositorySTL();
	test_serviceSTL();
	test_serviceFile();
	test_addX();
	cout << "DONE\n";
}