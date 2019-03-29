#include "Sklad.h"

Sklad::~Sklad()
{
	for (size_t i = (*aDrony).size(); i > 0; i--)
	{
		delete (*aDrony)[i - 1];
		(*aDrony)[i - 1] = nullptr;
	}
	delete aDrony;
	aDrony = nullptr;
	delete aObjednavkyDorucenie;
	delete aObjednavkyVyzdvihnutie;
}

void Sklad::pridatDrona(int pCas,int pTyp, int pSerioveCislo)
{
	if (pTyp == 1)
	{
		(*aDrony).add(new Dron(pCas, pSerioveCislo, 1, 2000, 80 / 3.6, 40 * 60, 3));
	}
	else
	{
		(*aDrony).add(new Dron(pCas, pSerioveCislo, 2, 5000, 40 / 3.6, 60 * 60, 5));
	}
}

void Sklad::vypisatDrony()
{
	for (size_t i = 0; i < (*aDrony).size(); i++)
	{
		cout << (*aDrony)[i]->toString() << endl;
	}
}

boolean Sklad::pridatObjednavku(Objednavka *&pObj, int pTyp)
{
	sortDrony();
	if (pTyp == 0 && pObj->getStav() == "naVyzdvihnutie") {
		int i = vyberDronaPreObjednavkuZDostupnych(pObj->getHmotnost(), pObj->getVzdialenostOdosielatela());
		if (i >= 0)
		{
			(*aDrony)[i]->priraditObjednavku(*pObj, 0);
			return true;
		}
		else if (overObjednavku(pObj->getHmotnost(), pObj->getVzdialenostOdosielatela()))
		{
			(*aObjednavkyVyzdvihnutie).push(pObj);
			return true;
		}
	}
	else if (pTyp == 1 && overObjednavku(pObj->getHmotnost(), pObj->getVzdialenostOdosielatela()))
	{
		(*aObjednavkyDorucenie).push(pObj);
		return true;
	}
	/*if (pTyp == 0)
	{
		for (size_t i = 0; i < (*aDrony).size(); i++)
		{
			if ((*aDrony)[i]->getAktualnyDoletVMetroch() >= pObj->getVzdialenostOdosielatela() && (*aDrony)[i]->getNosnost() >= pObj->getHmotnost() && (*aDrony)[i]->getNavratDronuZCesty() == 0)
			{
				(*aDrony)[i]->priraditObjednavku(*pObj, 0);
				return true;
			}
			else if ((*aDrony)[i]->getMaxDoletVMetroch() >= pObj->getVzdialenostOdosielatela() && (*aDrony)[i]->getNosnost() >= pObj->getHmotnost())
			{
				(*aObjednavkyVyzdvihnutie).push(pObj);
				return true;
			}
		}
	}*/
	return false;
}

int Sklad::vyberDronaPreObjednavkuZDostupnych(int pGramy, int pVzdialenost)
{
	for (int i = 0; i < aDrony->size(); i++)
	{
		if ((*aDrony)[i]->getNosnost() >= pGramy && (*aDrony)[i]->getAktualnyDoletVMetroch() >= pVzdialenost && (*aDrony)[i]->getNavratDronuZCesty() == 0)
		{
			return i;
		}
	}
	return -1;
}

void Sklad::sortDrony()
{
	for (int i = 0; i < aDrony->size(); i++)
	{
		for (int j = i + 1; j < aDrony->size(); j++)
		{
			if ((*aDrony)[i]->getNosnost() > (*aDrony)[j]->getNosnost())
			{
				structures::DSRoutines::swap((*aDrony)[i], (*aDrony)[j]);
			}
			else if ((*aDrony)[i]->getNosnost() == (*aDrony)[j]->getNosnost() && (*aDrony)[i]->getPocetPercentBaterky() < (*aDrony)[j]->getPocetPercentBaterky())
			{
				structures::DSRoutines::swap((*aDrony)[i], (*aDrony)[j]);
			}
		}
	}
}

void Sklad::tik()
{
	for (Dron *dron : (*aDrony))
	{
		dron->tik();
	}
}

boolean Sklad::overObjednavku(int pGramy, int pVzdialenost)
{
	for (int i = 0; i < aDrony->size(); i++)
	{
		if ((*aDrony)[i]->getNosnost() >= pGramy && (*aDrony)[i]->getAktualnyDoletVMetroch() >= pVzdialenost)
		{
			return true;
		}
	}
	return false;
}
