#include "VozovyPark.h"



VozovyPark::VozovyPark()
{
	
}


VozovyPark::~VozovyPark()
{
	for (size_t i = (*aVozidla).size(); i > 0; i--)
	{
		delete (*aVozidla)[i - 1];
	}
	delete aVozidla;
}

void VozovyPark::pridatVozidlo(const int pNosnost, const int pPrevNakl)
{
	string spz = "DT";
	if ((*aVozidla).size() < 10)
	{
		spz += "00";
	}
	else if ((*aVozidla).size() >= 10 && (*aVozidla).size() < 100)
	{
		spz += "0";
	}
	spz += to_string((*aVozidla).size()) + "AA";
	(*aVozidla).add(new Vozidlo(spz, pNosnost, pPrevNakl));
}

void VozovyPark::vypisatVozidla()
{
	for (size_t i = 0; i < (*aVozidla).size(); i++)
	{
		cout << (*aVozidla)[i]->toString() << endl;
	}
}
