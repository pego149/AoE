#include <iostream>
#include <string>
#include "Objednavka.h"

using namespace std;

#pragma once
class Dron
{
	int aCasZaradenia;
	int aSerioveCislo;
	int aTyp;
	int aNosnost;
	int aPriemernaRychlost;
	int aMaxDobaLetu;
	int aCasPotrebnyNa10Percent;
	int aNalietaneSekundy = 0;
	int aPrepraveneZasielky = 0;
	int aMaxDoletVMetroch;
	int aAktualnyMaxDoletVMetroch;
	int aPocetPercentBaterky = 100;
	int aNavratDronuZCesty = 0;
	int aTrvanieCestyVSek = 0;
	int aIter = 0;
	Objednavka* aAktualnaObjednavka = nullptr;
public:
	Dron(const int pCasZaradenia, const int pSerioveCislo, const int pTyp,
		const int pNosnost, const int pPriemernaRychlost,
		const int pMaxDobaLetu, const int pCasPotrebnyNa10Percent);
	~Dron() {};
	int getCasZaradenia() { return aCasZaradenia; }
	int getSerioveCislo() { return aSerioveCislo; }
	int getTyp() { return aTyp; }
	int getNosnost() { return aNosnost; }
	int getPriemernaRychlost() { return aPriemernaRychlost; }
	int getMaxDobaLetu() { return aMaxDobaLetu; }
	int getCasPotrebnyNa10Percent() { return aCasPotrebnyNa10Percent; }
	int getMaxDoletVMetroch() { return aMaxDoletVMetroch; }
	int getAktualnyDoletVMetroch();
	int getPocetPercentBaterky() { return aPocetPercentBaterky; }
	string toString();
	void priraditObjednavku(Objednavka &pObj, int pTypObj); //typ: ak 0 odoslanie,1 dorucenie
	void odobratObjednavku() { aAktualnaObjednavka = nullptr; };
	void tik();
	int getNavratDronuZCesty() { return aNavratDronuZCesty; }
};

