#include "VozovyPark.h"
#include <fstream>

#pragma once
class Spravca
{
	structures::ArrayList<Sklad*> *aSklady = new structures::ArrayList<Sklad*>();
	structures::ArrayList<Objednavka*> *aObjednavky = new structures::ArrayList<Objednavka*>();
	VozovyPark *aVp = new VozovyPark();
	int aPocetDronov = 0;
	int aAktualnyCas = 25200;
	boolean aAktivne;
public:
	Spravca();
	~Spravca();
	void pridatVozidlo(const int pNosnost, const int pPrevNakl) { aVp->pridatVozidlo(pNosnost, pPrevNakl); }
	void vypisatVozidla() { aVp->vypisatVozidla(); }
	void pridatDrona(string pPrekladisko, int pTyp);
	void vypisatCas();
	void vypisatDronovPodlaPrekladiska(const string pPrekladisko);
	void plus1hodina();
	void koniec();
	boolean pridatObjednavku(int pGramy, string pOdkial, int pVzdialenostOdos, string pKam, int pVzdialenostPrijmatela);
	boolean getAktivne() { return aAktivne; }
	void ulozNacitaj(string pTyp, string pMenoSuboru);
	void zvozZasielok();
};

