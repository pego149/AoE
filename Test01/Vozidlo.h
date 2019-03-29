#include <iostream>
#include <string>

#pragma once

using namespace std;
class Vozidlo
{
	string aSpz;
	int aNosnost;
	int aPrevadzkoveNaklady;
	int aCelkovePrevadzkoveNaklady = 0;
public:
	Vozidlo(const string pSpz, const int pNosnost, const int pPrevadzkoveNaklady) {
		aSpz = pSpz;
		aNosnost = pNosnost;
		aPrevadzkoveNaklady = pPrevadzkoveNaklady;
	}
	~Vozidlo() {}
	string getSpz() { return aSpz; }
	int getNosnost() { return aNosnost; }
	int getCelkovePrevadzkoveNaklady() { return aCelkovePrevadzkoveNaklady; }
	string toString();
};

