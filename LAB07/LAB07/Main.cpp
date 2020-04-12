#include "Tests.h"
#include "UIFile.h"
int main()
{
	test_aplicatie();
	test_repositorySTL();
	test_repositoryFile();
	test_service();

	UIFile console;
	console.run("Aplicatii.txt");

	return 0;
}