#include <iostream>

#pragma once

using namespace std;

class Objednavka
{
	int aHmotnostVGramoch;
	string aOdkial = "";
	int aVzdialenostOdosielatela;
	string aKam = "";
	int aVzdialenostAdresata;
	int aCasVyzdvihnutia = 0;
	int aCasDorucenia = 0;
	int aCasPridania = 0;
	string aStav = "naVyzdvihnutie";
	int aId = 0;
public:
	Objednavka(int pHmotnost, string pOdkial, int pVzdialenostOdos, string pKam, int pVzdialenostPrijmatela, int pCasPridania, int pId);
	~Objednavka();
	int getVzdialenostOdosielatela() { return aVzdialenostOdosielatela; }
	int getVzdialenostAdresata() { return aVzdialenostAdresata; }
	int getCasVyzdvihnutia() { return aCasVyzdvihnutia; }
	int getCasDorucenia() { return aVzdialenostAdresata; }
	void setCasVyzdvihnutia(int pInput) { aCasVyzdvihnutia = pInput; }
	void setCasDorucenia(int pInput) { aCasDorucenia = pInput; }
	string getStav() { return aStav; }
	int getHmotnost() { return aHmotnostVGramoch; }
	void setStav(string pInput) { aStav = pInput; }
	int getId() { return aId; }
	string getOdkial() { return aOdkial; }
	string getKam() { return aKam; }
};

