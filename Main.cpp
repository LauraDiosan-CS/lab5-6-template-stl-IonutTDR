#include "UISTL.h"
#include "UIFile.h"
#include "Tests.h"
#include "UISQL.h"

/*MYSQL* conn = mysql_init(NULL);

void sql_connect()
{
	if (!conn)
		cout << "Failed";

	conn = mysql_real_connect(conn, "localhost", "root", "", "mydatabase", 0, NULL, 0);

	if (!conn)
		cout << "Error";
}*/

int main()
{
	myTests();

	/*
	UIFile console;
	console.run("Aplicatii.txt");
	*/

	UISTL console;
	console.run();
	
	
	return 0;
}