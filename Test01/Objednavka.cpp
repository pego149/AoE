#include "Objednavka.h"



Objednavka::Objednavka(int pHmotnost, string pOdkial, int pVzdialenostOdos, string pKam, int pVzdialenostPrijmatela, int pCasPridania, int pId)
{
	aHmotnostVGramoch = pHmotnost;
	aOdkial = pOdkial;
	aVzdialenostOdosielatela = pVzdialenostOdos;
	aKam = pKam;
	aVzdialenostAdresata = pVzdialenostPrijmatela;
	aCasPridania = pCasPridania;
	aId = pId;
}


Objednavka::~Objednavka()
{
}
