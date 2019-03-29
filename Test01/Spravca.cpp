#include "Spravca.h"


Spravca::Spravca()
{
	aAktivne = true;
	(*aSklady).add(new Sklad("MA"));
	(*aSklady).add(new Sklad("BA"));
	(*aSklady).add(new Sklad("TT"));
	(*aSklady).add(new Sklad("KN"));
	(*aSklady).add(new Sklad("NR"));
	(*aSklady).add(new Sklad("TN"));
	(*aSklady).add(new Sklad("PD"));
	(*aSklady).add(new Sklad("KA"));
	(*aSklady).add(new Sklad("ZV"));
	(*aSklady).add(new Sklad("BB"));
	(*aSklady).add(new Sklad("MT"));
	(*aSklady).add(new Sklad("CA"));
	(*aSklady).add(new Sklad("ZA"));
	(*aSklady).add(new Sklad("NO"));
	(*aSklady).add(new Sklad("LM"));
	(*aSklady).add(new Sklad("LC"));
	(*aSklady).add(new Sklad("RA"));
	(*aSklady).add(new Sklad("PP"));
	(*aSklady).add(new Sklad("SL"));
	(*aSklady).add(new Sklad("SN"));
	(*aSklady).add(new Sklad("KE"));
	(*aSklady).add(new Sklad("PO"));
	(*aSklady).add(new Sklad("HE"));
	(*aSklady).add(new Sklad("MI"));
}


Spravca::~Spravca()
{
	for (size_t i = (*aObjednavky).size(); i > 0; i--)
	{
		delete (*aObjednavky)[i - 1];
		(*aObjednavky)[i - 1] = nullptr;
	}
	delete aObjednavky;
	aObjednavky = nullptr;
	for (size_t i = (*aSklady).size(); i > 0; i--)
	{
		delete (*aSklady)[i - 1];
		(*aSklady)[i - 1] = nullptr;
	}
	delete aSklady;
	aSklady = nullptr;
	delete aVp;
	aVp = nullptr;
}

void Spravca::pridatDrona(string pPrekladisko, int pTyp)
{
	for (size_t i = 0; i < (*aSklady).size(); i++) {
		if (!(*aSklady)[i]->getId().compare(pPrekladisko))
		{
			(*aSklady)[i]->pridatDrona(aAktualnyCas, pTyp, aPocetDronov);
			aPocetDronov++;
		}
	}
}

void Spravca::vypisatCas()
{
	int dni = aAktualnyCas / 60 / 60 / 24;
	int hodiny = (aAktualnyCas / 60 / 60) % 24;
	int minuty = (aAktualnyCas / 60) % 60;
	int sekundy = aAktualnyCas % 60;
	cout << "Cas:" << to_string(dni) << "d " << to_string(hodiny) 
		<< ":" + to_string(minuty) << ":" << to_string(sekundy) << endl;
}

void Spravca::vypisatDronovPodlaPrekladiska(const string pPrekladisko)
{
	for (size_t i = 0; i < (*aSklady).size(); i++) {
		if (!(*aSklady)[i]->getId().compare(pPrekladisko))
		{
			(*aSklady)[i]->vypisatDrony();
		}
	}
}

void Spravca::plus1hodina()
{
	for (size_t i = 0; i < 600; i++)
	{
		aAktualnyCas++;
		for (size_t i = 0; i < aSklady->size(); i++)
		{
			(*aSklady)[i]->tik();
		}
	}
}

void Spravca::koniec()
{
	aAktivne = false;
}

boolean Spravca::pridatObjednavku(int pGramy, string pOdkial, int pVzdialenostOdos, string pKam, int pVzdialenostPrijmatela)
{
	int indexOdkial = -1;
	int indexKam = -1;
	(*aObjednavky).add(new Objednavka(pGramy, pOdkial, pVzdialenostOdos, pKam, pVzdialenostPrijmatela, aAktualnyCas));
	for (size_t i = 0; i < (*aSklady).size(); i++) {
		if (!(*aSklady)[i]->getId().compare(pOdkial))
			indexOdkial = i;
	}
	for (size_t i = 0; i < (*aSklady).size(); i++) {
		if (!(*aSklady)[i]->getId().compare(pKam))
			indexKam = i;
	}
	if (indexOdkial >= 0 && indexKam >= 0)
	{
		if ((*aSklady)[indexOdkial]->pridatObjednavku((*aObjednavky)[(*aObjednavky).size() - 1], 0) && (*aSklady)[indexKam]->pridatObjednavku((*aObjednavky)[(*aObjednavky).size() - 1], 1))
		{
			cout << "Objednavka prijata na spracovanie" << endl;
		}
		else
		{
			cout << "Objednavka nemohla byt spracovana" << endl;
		}
	}
	else
	{
		cout << "Zadali ste zle udaje" << endl;
	}
	//int casVyzdvihnutia =

	return false;
}
