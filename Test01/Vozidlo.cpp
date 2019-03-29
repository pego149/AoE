#include "Vozidlo.h"


string Vozidlo::toString()
{
	return "SPZ:" + aSpz + ", nosnost:" + to_string(aNosnost) + ", celkove pr. naklady:" + to_string(aCelkovePrevadzkoveNaklady);
}
