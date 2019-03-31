#include "Sklad.h"
#include "Vozidlo.h"
#include <iostream>

#pragma once
class VozovyPark
{
	structures::ArrayList<Vozidlo*> *aVozidla = new structures::ArrayList<Vozidlo*>();
public:
	VozovyPark();
	~VozovyPark();
	void pridatVozidlo(const int pNosnost, const int pPrevNakl);
	void vypisatVozidla();
	string ulozVozidla();
	void sortVozidla();
	//structures::ArrayList<Vozidlo*> getVozidla() { return *aVozidla; };
	boolean pridatObjednavku() {}
	Vozidlo* vyberVozidlo() { sortVozidla(); return *&(*aVozidla)[0]; }
	Vozidlo* vyberVozidloNaRozvoz(int pIndex) { return *&(*aVozidla)[pIndex]; }
	void koniecDna();
	int getPocetVozidiel() { return (*aVozidla).size(); }
	void vylozAuta();
};

