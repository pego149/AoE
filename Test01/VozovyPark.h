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
};

