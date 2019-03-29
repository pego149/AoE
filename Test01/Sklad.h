#include "structures/list/array_list.h"
#include "Dron.h"
#include <iostream>
#include "structures/queue/implicit_queue.h"
#include "structures/ds_routines.h"

#pragma once
class Sklad
{
	string aId;
	structures::ArrayList<Dron*> *aDrony = new structures::ArrayList<Dron*>();
	structures::ImplicitQueue<Objednavka*> *aObjednavkyVyzdvihnutie = new structures::ImplicitQueue<Objednavka*>();
	structures::ImplicitQueue<Objednavka*> *aObjednavkyDorucenie = new structures::ImplicitQueue<Objednavka*>();
public:
	Sklad(const string pId) {
		aId = pId;
	}
	~Sklad();
	void pridatDrona(int pCas, int pTyp, int pSerioveCislo);
	string getId() { return aId; }
	void vypisatDrony();
	boolean pridatObjednavku(Objednavka *&pObj, int pTyp);
	int vyberDronaPreObjednavkuZDostupnych(int pGramy, int pVzdialenost);
	void sortDrony();
	void tik();
	boolean overObjednavku(int pGramy, int pVzdialenost);
};

