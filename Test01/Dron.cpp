#include "Dron.h"

Dron::Dron(const int pCasZaradenia, const int pSerioveCislo, const int pTyp, 
	const int pNosnost, const int pPriemernaRychlost, 
	const int pMaxDobaLetu, const int pCasPotrebnyNa10Percent)
{
	aCasZaradenia = pCasZaradenia;
	aSerioveCislo = pSerioveCislo;
	aTyp = pTyp;
	aNosnost = pNosnost;
	aPriemernaRychlost = pPriemernaRychlost;
	aMaxDobaLetu = pMaxDobaLetu;
	aCasPotrebnyNa10Percent = pCasPotrebnyNa10Percent;
	if (pTyp == 1)
	{
		aMaxDoletVMetroch = 53333;
	}
	else
	{
		aMaxDoletVMetroch = 40000;
	}
	aAktualnyMaxDoletVMetroch = aMaxDoletVMetroch / 100 * aPocetPercentBaterky;
	//cout << aAktualnyMaxDoletVMetroch;
}

int Dron::getAktualnyDoletVMetroch()
{
	return aAktualnyMaxDoletVMetroch;
}

string Dron::toString()
{
	int dni = aCasZaradenia / 60 / 60 / 24;
	int hodiny = (aCasZaradenia / 60 / 60) % 24;
	int minuty = (aCasZaradenia / 60) % 60;
	int sekundy = aCasZaradenia % 60;
	int nalHodiny = aNalietaneSekundy / 60 / 60;
	int nalMinuty = (aNalietaneSekundy / 60) % 60;
	int nalSekundy = aNalietaneSekundy % 60;
	return "Cas zaradenia:" + to_string(dni) + "d " + to_string(hodiny) + ":" + to_string(minuty) + ":"
		+ to_string(sekundy) + ", typ:" + to_string(aTyp) + ", celkovy pocet nalietanych hodin" + to_string(nalHodiny) + ":"
		+ to_string(nalMinuty) + ":" + to_string(nalSekundy) + ", celkovy pocet prepravenych zasielok:" + to_string(aPrepraveneZasielky);
}

void Dron::priraditObjednavku(Objednavka & pObj, int pTypObj) //typ: ak 0 odoslanie,1 dorucenie
{
	aAktualnaObjednavka = &pObj;
	if (aAktualnaObjednavka->getStav() == "naDorucenie")
	{
		aAktualnaObjednavka->setStav("dronDorucujeZasielku");
	}
	else
	{
		aAktualnaObjednavka->setStav("dronIdePoZasielku");
	}
	if (pTypObj == 0)
	{
		aNavratDronuZCesty = aAktualnaObjednavka->getVzdialenostOdosielatela() * 2 / aPriemernaRychlost;
	}
	else
	{
		aNavratDronuZCesty = aAktualnaObjednavka->getVzdialenostAdresata() * 2 / aPriemernaRychlost;
	}
	aTrvanieCestyVSek = aNavratDronuZCesty;
}

void Dron::tik()
{
	aAktualnyMaxDoletVMetroch = aMaxDoletVMetroch / 100 * aPocetPercentBaterky;
	if (aNavratDronuZCesty > 0)
	{
		aNavratDronuZCesty--;
		aNalietaneSekundy++;
		if (aTyp == 1 && aIter == 240)
		{
			aPocetPercentBaterky--;
			aIter = 0;
		}
		else if (aTyp == 2 && aIter == 360)
		{
			aPocetPercentBaterky--;
			aIter = 0;
		}
		if (aNavratDronuZCesty < aTrvanieCestyVSek / 2 && aAktualnaObjednavka->getStav().compare("dronIdePoZasielku"))
		{
			aAktualnaObjednavka->setStav("DronVezieZasielkuDoPrekladiska");
		}
		else if (aNavratDronuZCesty < aTrvanieCestyVSek / 2 && aAktualnaObjednavka->getStav().compare("zasielkaCakaNaDorucenie"))
		{
			aAktualnaObjednavka->setStav("Dorucena");
		}
		if (aNavratDronuZCesty == 0)
		{
			aAktualnaObjednavka->setStav("vLokalnomPrekladisku");
			odobratObjednavku();
		}
	}
	else if (aNavratDronuZCesty == 0)
	{
		if (aTyp == 1 && aIter == 180)
		{
			if (aPocetPercentBaterky < 100)
			{
				aPocetPercentBaterky += 10;
			}
			if (aPocetPercentBaterky > 100)
			{
				aPocetPercentBaterky = 100;
			}
			aIter = 0;
		} 
		else if (aTyp == 2 && aIter == 300)
		{
			if (aPocetPercentBaterky < 100)
			{
				aPocetPercentBaterky += 10;
			}
			if (aPocetPercentBaterky > 100)
			{
				aPocetPercentBaterky = 100;
			}
			aIter = 0;
		}
	}
	aIter++;
}
