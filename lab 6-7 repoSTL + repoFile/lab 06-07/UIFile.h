#ifndef UIFILE_H
#define UIFILE_H
#include "ServiceFile.h"

class UIFile {
private:
	ServiceFile s;
public:
	UIFile();
	~UIFile();
	void setService(const ServiceFile& service);
	bool verificare(const char* nume, int memorie, const char* status, const char* fileName);
	void add(const char* fileName);
	void remove(const char* fileName);
	void update(const char* fileName);
	void getAll(const char* fileName);
	void run(const char* fileName);
};
void printMenu1();

#endif // !UIFILE_H
