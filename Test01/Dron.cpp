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
	aTypZasielky = pTypObj;
	if (aAktualnaObjednavka->getStav() == "zasielkaCakaNaDorucenie")
	{
		aAktualnaObjednavka->setStav("dronDorucujeZasielku"); 
		cout << "Dron dorucuje zasielku c." << aAktualnaObjednavka->getId() << endl;
	}
	else
	{
		aAktualnaObjednavka->setStav("dronIdePoZasielku"); 
		cout << "Dron ide po zasielku c." << aAktualnaObjednavka->getId() << endl;
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
		if (aNavratDronuZCesty < aTrvanieCestyVSek / 2 && aAktualnaObjednavka->getStav() == "dronIdePoZasielku")
		{
			aAktualnaObjednavka->setStav("DronVezieZasielkuDoPrekladiska");
			cout << "Dron vezie zasielku c." << aAktualnaObjednavka->getId() << " do prekladiska." << endl;
		}
		else if (aNavratDronuZCesty < aTrvanieCestyVSek / 2 && aAktualnaObjednavka->getStav() == "dronDorucujeZasielku")
		{
			aAktualnaObjednavka->setStav("Dorucena");
			cout << "Zasielka c." << aAktualnaObjednavka->getId() << " bola dorucena." << endl;
		}
		if (aNavratDronuZCesty == 0 && aTypZasielky == 0)
		{
			aAktualnaObjednavka->setStav("vLokalnomPrekladisku");
			cout << "Zasielka c." << aAktualnaObjednavka->getId() << " bola dorucena do lokalneho prekladiska: " << aAktualnaObjednavka->getOdkial() << endl;
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

int Dron::getCasPotrebnyPreNabitieNaDoletDoMetrovPoDolete(int pMetre)
{
	if (aAktualnaObjednavka != nullptr)
	{
		int iter = 0;
		int pocetPercPoDolete = (aMaxDobaLetu - aTrvanieCestyVSek) / aMaxDobaLetu * 100;
		for (size_t i = 0; i < aCasPotrebnyNa10Percent * 10; i++)
		{
			if (aTyp == 1 && iter == 180)
			{
				if (pocetPercPoDolete < 100)
				{
					pocetPercPoDolete += 10;
				}
				if (pocetPercPoDolete > 100)
				{
					pocetPercPoDolete = 100;
				}
				iter = 0;
			}
			else if (aTyp == 2 && iter == 300)
			{
				if (pocetPercPoDolete < 100)
				{
					pocetPercPoDolete += 10;
				}
				if (pocetPercPoDolete > 100)
				{
					pocetPercPoDolete = 100;
				}
				iter = 0;
			}
			if (pMetre <= aMaxDoletVMetroch / 100 * pocetPercPoDolete)
			{
				return i;
			}
			iter++;
		}
	}
	return 0;
}

int Dron::getCasLetu1Cesta(int pMetre)
{
	return pMetre / aPriemernaRychlost;
}
