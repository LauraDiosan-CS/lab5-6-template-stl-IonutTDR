#ifndef UIFILE_H
#define UIFILE_H
#include "Service.h"

class UIFile {
private:
	Service<Aplicatie> s;
	int ram;
	int swap;
public:
	UIFile();
	~UIFile();
	void getMemory(const char* fileName);
	void updateStatusAfterX(const char* fileName, int X);
	void add(const char* fileName, int X);
	void remove(const char* fileName, int X);
	void update(const char* fileName, int X);
	void getAll(const char* fileName);
	void run(const char* fileName);
};
void addStatusByX(Service<Aplicatie>& s, map<int, Aplicatie> elems, int& ram, int& swap, const char* nume, int memorie, const char* fileName, int X, int& gasit);
void removeByX(Service<Aplicatie>& s, map<int, Aplicatie> apps, int& ram, int& swap, const char* fileName, int X, int index);
void updateStatusByX(Service<Aplicatie>& s, map<int, Aplicatie> apps, int& ram, int& swap, const char* nume, int memorie, const char* fileName, int X, int& gasit, int index);
void printMenu1();

#endif // !UIFILE_H
