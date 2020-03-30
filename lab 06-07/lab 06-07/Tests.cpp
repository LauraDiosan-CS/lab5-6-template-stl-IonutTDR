#include "Tests.h"
#include "Repository.cpp"
#include "Aplicatie.h"
#include <assert.h>

void test_repository()
{
	const Aplicatie a1("Poker", 60, "ram");
	const Aplicatie a2("AppStore", 30, "swap");
	const Aplicatie a3("Zynga", 80, "ram");

	Repository <Aplicatie> repo;

	repo.addElem(a1);
	repo.addElem(a2);
	repo.addElem(a3);

	Aplicatie* elems = repo.getAll();

	assert(elems[0] == a1);
	assert(elems[1] == a2);
	assert(elems[2] == a3);

}

void test_aplicatie()
{
	Aplicatie a1("AppStore", 30, "ram");
	Aplicatie a2;

	assert(strcmp(a1.getNume(),"AppStore") == 0);
	assert(a1.getMemorie() == 30);
	assert(strcmp(a1.getStatus(),"ram") == 0);

	a2 = a1;
	assert(a1.getMemorie() == 30);
	assert(a1 == a2);
}