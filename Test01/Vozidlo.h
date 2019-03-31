#include <iostream>
#include <string>
#include "Objednavka.h"

#pragma once

using namespace std;
class Vozidlo
{
	string aSpz;
	int aNosnost;
	int aPrevadzkoveNaklady;
	int aCelkovePrevadzkoveNaklady = 0;
	int aZostavajucaNosnost = 0;
	int aPocetRegionov = 0;
public:
	Vozidlo(const string pSpz, const int pNosnost, const int pPrevadzkoveNaklady) {
		aSpz = pSpz;
		aNosnost = pNosnost;
		aPrevadzkoveNaklady = pPrevadzkoveNaklady;
		aZostavajucaNosnost = aNosnost;
	}
	~Vozidlo() {}
	string getSpz() { return aSpz; }
	int getNosnost() { return aNosnost; }
	int getZostavajucuNosnost() { return aZostavajucaNosnost; }
	int getCelkovePrevadzkoveNaklady() { return aCelkovePrevadzkoveNaklady; }
	string toString();
	string ulozit();
	void uberNosnost(int pGramy) { aZostavajucaNosnost = aZostavajucaNosnost - pGramy; }
	void pridajRegion() { aPocetRegionov++; }
	void koniecDna();
	void vyloz() { aZostavajucaNosnost = aNosnost; };
};

