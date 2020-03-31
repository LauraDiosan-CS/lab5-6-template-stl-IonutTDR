#include <iostream>
#include <cstring>
#include "UISTL.h"
#include "Aplicatie.h"
#include "RepositorySTL.h"
#include "UIFile.h"
#include "ServiceSTL.h"
#include "Tests.h"
using namespace std;

int main()
{
	myTests();

	UIFile console;
	console.run("Aplicatii.txt");

	/*UISTL console;
	console.run();*/
	return 0;
}