#include "Tests.h"

void test_aplicatie()
{
	Aplicatie a1("AppStore", 30, "ram");
	Aplicatie a2;

	assert(strcmp(a1.getNume(), "AppStore") == 0);
	assert(a1.getMemorie() == 30);
	assert(strcmp(a1.getStatus(), "ram") == 0);

	a1.setNume("Facebook");
	a1.setMem(2000);
	a1.setStatus("swap");

	assert(strcmp(a1.getNume(), "Facebook") == 0);
	assert(a1.getMemorie() == 2000);
	assert(strcmp(a1.getStatus(), "swap") == 0);

	a2 = a1;
	assert(a2.getMemorie() == 2000);
	assert(a1 == a2);
}

void test_repositorySTL()
{
	Aplicatie a1("Poker", 60, "ram");
	Aplicatie a2("AppStore", 30, "swap");
	Aplicatie a3("Zynga", 80, "ram");

	Repository<Aplicatie> repo;
	//testeaza adaugarea 
	repo.addElem(a1);
	repo.addElem(a2);
	repo.addElem(a3);

	int n = repo.getSize();
	assert(repo.getSize() == 3);

	//testeaza preluarea aplicatiilor
	map<int, Aplicatie> elems = repo.getAll();

	assert(elems[0] == a1);
	assert(elems[1] == a2);
	assert(elems[2] == a3);
	//testeaza stergerea unei aplicatii
	repo.removeElem(0);
	elems = repo.getAll();

	assert(elems[1] == a2);
	assert(elems[2] == a3);
	n = repo.getSize();
	assert(n == 2);
	//testeaza actualizarea unei aplicatii
	Aplicatie a4("Defender", 400, "swap");
	repo.updateElem(1, a4);
	elems = repo.getAll();
	assert(elems[1] == a4);

	repo.removeElem(1);
	repo.removeElem(2);
	assert(repo.getSize() == 0);
	
}

void test_repositoryFile()
{
	std::ofstream ofs;
	ofs.open("TestRepo.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	RepositoryFile<Aplicatie> repo("TestRepo.txt");
	assert(repo.getSize() == 0);

	Aplicatie a1("Poker", 60, "ram");
	Aplicatie a2("AppStore", 30, "swap");
	Aplicatie a3("Zynga", 80, "ram");
	//testeaza adaugarea aplicatiilor
	repo.addElem(a1);
	repo.addElem(a2);
	repo.addElem(a3);
	assert(repo.getSize() == 3);
	//testeaza stergerea aplicatiilor din fisier
	repo.removeElem(1);
	assert(repo.getSize() == 2);
	int n = repo.getSize();

	//testeaza actualizarea unei aplicatii si preluarea acestora din fisier
	Aplicatie a4("Facebook", 2000, "swap");
	repo.updateElem(0, a4);
	map<int, Aplicatie>::iterator itr;
	map<int, Aplicatie> elem = repo.getAll();
	assert(elem[0] == a4);
	assert(elem[2] == a3);
	assert(elem.size() == 2);

	//testeaza salvarea in fisier
	repo.saveFile("TestRepo.txt");

	RepositoryFile<Aplicatie> repo2;
	repo2.loadFile("TestRepo.txt");
	assert(repo2.getSize() == n);
}

void test_service()
{
	std::ofstream ofs;
	ofs.open("TestService.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	Aplicatie a1("Poker", 60, "ram");
	Aplicatie a2("AppStore", 30, "swap");
	Aplicatie a3("Zynga", 80, "ram");

	Service<Aplicatie> s;

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
	s.remove(1, "TestService.txt");
	s.remove(0, "TestService.txt");

	assert(s.get("TestService.txt").size() == 0);

	int X = 40;
	int ram = 0, swap = 0;
	int gasit = 0;
	map<int, Aplicatie> elems = s.get("TestService.txt");

	addStatusByX(s, elems, ram, swap, "Facebook", 10, "TestService.txt", X, gasit);
	assert(gasit == 0);
	assert(strcmp(s.get("TestService.txt")[0].getNume(), "Facebook") == 0);
	assert(s.get("TestService.txt")[0].getMemorie() == 10);
	assert(strcmp(s.get("TestService.txt")[0].getStatus(), "ram") == 0);
	assert(ram == 10 && swap == 0);

	elems = s.get("TestService.txt");
	addStatusByX(s, elems, ram, swap, "Skate", 40, "TestService.txt", X, gasit);
	assert(strcmp(s.get("TestService.txt")[0].getStatus(), "swap") == 0);
	assert(strcmp(s.get("TestService.txt")[1].getNume(), "Skate") == 0);
	assert(s.get("TestService.txt")[1].getMemorie() == 40);
	assert(strcmp(s.get("TestService.txt")[1].getStatus(), "ram") == 0);
	assert(ram == 40 && swap == 10);


	elems = s.get("TestService.txt");
	removeByX(s, elems, ram, swap, "TestService.txt", X, 1);
	assert(s.get("TestService.txt").size() == 1);
	assert(strcmp(s.get("TestService.txt")[0].getNume(), "Facebook") == 0);
	assert(s.get("TestService.txt")[0].getMemorie() == 10);
	assert(strcmp(s.get("TestService.txt")[0].getStatus(), "ram") == 0);
	assert(ram == 10 && swap == 0);

	elems = s.get("TestService.txt");

	addStatusByX(s, elems, ram, swap, "Skate", 60, "TestService.txt", X, gasit);
	assert(strcmp(s.get("TestService.txt")[0].getStatus(), "ram") == 0);
	assert(strcmp(s.get("TestService.txt")[1].getNume(), "Skate") == 0);
	assert(s.get("TestService.txt")[1].getMemorie() == 60);
	assert(strcmp(s.get("TestService.txt")[1].getStatus(), "swap") == 0);
	assert(ram == 10 && swap == 60);

	elems = s.get("TestService.txt");
	updateStatusByX(s, elems, ram, swap, "Facebook", 60, "TestService.txt", X, gasit, 0);
	assert(s.get("TestService.txt").size() == 2);
	assert(strcmp(s.get("TestService.txt")[0].getNume(), "Facebook") == 0);
	assert(s.get("TestService.txt")[0].getMemorie() == 60);
	assert(strcmp(s.get("TestService.txt")[0].getStatus(), "swap") == 0);
	assert(swap == 120);

	elems = s.get("TestService.txt");
	updateStatusByX(s, elems, ram, swap, "Facebook", 40, "TestService.txt", X, gasit, 0);
	assert(s.get("TestService.txt").size() == 2);
	assert(strcmp(s.get("TestService.txt")[0].getNume(), "Facebook") == 0);
	assert(s.get("TestService.txt")[0].getMemorie() == 40);
	assert(strcmp(s.get("TestService.txt")[0].getStatus(), "ram") == 0);
	assert(swap == 60);
	

}