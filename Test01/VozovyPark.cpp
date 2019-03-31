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

string VozovyPark::ulozVozidla()
{
	string str = "";
	for (size_t i = 0; i < (*aVozidla).size(); i++)
	{
		str += "0 " + (*aVozidla)[i]->ulozit() + "\n";
	}
	return str;
}

void VozovyPark::sortVozidla()
{
	for (int i = 0; i < aVozidla->size(); i++)
	{
		for (int j = i + 1; j < aVozidla->size(); j++)
		{
			if ((*aVozidla)[i]->getCelkovePrevadzkoveNaklady() > (*aVozidla)[j]->getCelkovePrevadzkoveNaklady())
			{
				structures::DSRoutines::swap((*aVozidla)[i], (*aVozidla)[j]);
			}
			else if ((*aVozidla)[i]->getCelkovePrevadzkoveNaklady() == (*aVozidla)[j]->getCelkovePrevadzkoveNaklady() && (*aVozidla)[i]->getZostavajucuNosnost() < (*aVozidla)[j]->getZostavajucuNosnost())
			{
				structures::DSRoutines::swap((*aVozidla)[i], (*aVozidla)[j]);
			}
		}
	}
}

void VozovyPark::koniecDna()
{
	for(Vozidlo* vozidlo : (*aVozidla))
	{
		vozidlo->koniecDna();
	}
}

void VozovyPark::vylozAuta()
{
	for (Vozidlo* vozidlo : (*aVozidla))
	{
		vozidlo->vyloz();
	}
}
