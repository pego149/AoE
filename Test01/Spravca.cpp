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
	for (size_t i = 0; i < 3600; i++)
	{
		aAktualnyCas++;
		for (Sklad *sklad : (*aSklady))
		{
			sklad->tik();
		}
	}
	if ((aAktualnyCas - 75600) % 75600 == 0)
	{
		aAktualnyCas += 36000;
		zvozZasielok();
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
	(*aObjednavky).add(new Objednavka(pGramy, pOdkial, pVzdialenostOdos, pKam, pVzdialenostPrijmatela, aAktualnyCas, (*aObjednavky).size()));
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
		if ((*aSklady)[indexOdkial]->getVozidlo() == nullptr)
		{
			(*aSklady)[indexOdkial]->priraditVozidlo(*aVp->vyberVozidlo());
		}
		if ((*aSklady)[indexOdkial]->pridatObjednavku((*aObjednavky)[(*aObjednavky).size() - 1], 0, aAktualnyCas) && (*aSklady)[indexKam]->pridatObjednavku((*aObjednavky)[(*aObjednavky).size() - 1], 1, aAktualnyCas))
		{
			cout << "Objednavka prijata na spracovanie" << endl;
		}
		else
		{
			cout << "Objednavka nemohla byt spracovana" << endl;
			(*aObjednavky).removeAt(aObjednavky->size() - 1);
		}
	}
	else
	{
		cout << "Zadali ste zle udaje" << endl;
		(*aObjednavky).removeAt(aObjednavky->size() - 1);
	}
	//int casVyzdvihnutia =

	return false;
}

void Spravca::ulozNacitaj(string pTyp, string pMenoSuboru)
{
	if (pTyp == "u")
	{
		ofstream vystup(pMenoSuboru);
		vystup << aVp->ulozVozidla();
		for (Sklad *sklad : (*aSklady))
		{
			vystup << sklad->ulozDrony() << endl;
		}
		vystup.close();
	}
	else if (pTyp == "n") 
	{
		ifstream vstup(pMenoSuboru);
		string word;
		string pom1;
		string pom2;
		string pom3;
		if (vstup.is_open())
		{
			while (vstup >> word)
			{
				if (word == "0")
				{
					vstup >> pom1;
					vstup >> pom2;
					pridatVozidlo(stoi(pom1), stoi(pom2));
				}
				else 
				{
					vstup >> pom1;
					vstup >> pom2;
					vstup >> pom3;
					for (size_t i = 0; i < stoi(pom2); i++)
					{
						pridatDrona(pom1, 1);
					}
					for (size_t i = 0; i < stoi(pom3); i++)
					{
						pridatDrona(pom1, 2);
					}
				}
			}
		}
		else cout << "Subor sa nenasiel." << endl;
	}
}

void Spravca::zvozZasielok()
{
	aVp->koniecDna();
	for (Sklad *sklad : (*aSklady))
	{
		sklad->odobratVozidlo();
	}
	for (Objednavka * objednavka : (*aObjednavky))
	{
		if (objednavka->getStav() == "vLokalnomPrekladisku")
		{
			objednavka->setStav("vCentralnomSklade");
		}
	}
	aVp->sortVozidla();
	for (Objednavka * objednavka : (*aObjednavky))
	{
		if (objednavka->getStav() == "vCentralnomSklade")
		{
			for (size_t i = 0; i < aVp->getPocetVozidiel() - 1; i++)
			{
				if (aVp->vyberVozidloNaRozvoz(i)->getZostavajucuNosnost() - objednavka->getHmotnost() >= 0)
				{
					aVp->vyberVozidloNaRozvoz(i)->uberNosnost(objednavka->getHmotnost());
					objednavka->setStav("zasielkaCakaNaDorucenie");
					for (size_t j = 0; j < (*aSklady).size(); j++) {
						if ((*aSklady)[j]->getId() == objednavka->getKam())
						{
							(*aSklady)[j]->priraditVozidlo(*aVp->vyberVozidloNaRozvoz(i));
							(*aSklady)[j]->pridatObjednavku(objednavka, 1, aAktualnyCas);
						}
					}
					break;
				}
			}
		}
	}
	aVp->vylozAuta();
}
