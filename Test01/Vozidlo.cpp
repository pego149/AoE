#include "Vozidlo.h"


string Vozidlo::toString()
{
	return "SPZ:" + aSpz + ", nosnost:" + to_string(aNosnost) + ", celkove pr. naklady:" + to_string(aCelkovePrevadzkoveNaklady);
}

string Vozidlo::ulozit()
{
	return to_string(aNosnost) + " " + to_string(aPrevadzkoveNaklady);
}

void Vozidlo::koniecDna()
{
	aCelkovePrevadzkoveNaklady += 2 * aPrevadzkoveNaklady * aPocetRegionov;
	aPocetRegionov = 0;
	aZostavajucaNosnost = aNosnost;
}
