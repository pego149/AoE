#include "structures/heap_monitor.h"
#include "Spravca.h"

Spravca spravca = Spravca();

void subMenu1() {
	int nosnost;
	int prevNakl;
	cout << "Zvolte nosnost:";
	cin >> nosnost;
	cout << "Zvolte prevadzkove naklady:";
	cin >> prevNakl;
	spravca.pridatVozidlo(nosnost, prevNakl);
}

void subMenu3() {
	string prekladisko;
	int typ;
	cout << "Zvolte prekladisko:";
	cin >> prekladisko;
	cout << "Zvolte typ:";
	cin >> typ;
	cout << endl;
	spravca.pridatDrona(prekladisko, typ);
}

void subMenu4() {
	string prekladisko;
	cout << "Zvolte prekladisko:";
	cin >> prekladisko;
	cout << endl;
	spravca.vypisatDronovPodlaPrekladiska(prekladisko);
}

void subMenu5() {
	int gramy;
	string odkial;
	string kam;
	int odialm;
	int kamm;
	cout << "Hmotnost v g:";
	cin >> gramy;
	cout << "Zvolte odkial prekladisko:";
	cin >> odkial;
	cout << "Zvolte vzdialenost od prekladiska na odoslanie:";
	cin >> odialm;
	cout << "Zvolte kam prekladisko:";
	cin >> kam;
	cout << "Zvolte vzdialenost od prekladiska na prijatie:";
	cin >> kamm;
	cout << endl;
	spravca.pridatObjednavku(gramy, odkial, odialm, kam, kamm);
}

int main() {
	initHeapMonitor();
	spravca.pridatVozidlo(1, 2);
	spravca.pridatVozidlo(1, 5);
	spravca.pridatVozidlo(1, 1);
	spravca.pridatVozidlo(2, 8);
	spravca.pridatVozidlo(1, 2);
	spravca.pridatVozidlo(1, 2);
	spravca.pridatVozidlo(1, 2);
	spravca.pridatDrona("ZA", 1);
	spravca.pridatDrona("BB", 1);
	spravca.pridatDrona("CA", 1);
	spravca.pridatDrona("KA", 1);

	string in = "";
	while (spravca.getAktivne())
	{
		cout << "a-zobrazit cas, b-posun casu, c-zatial nic, e-koniec" << endl
			<< "1-pridat vozidlo, 2-vypisat vozidla, 3-pridat drona do prekladiska, 4-vypisat drony v prekladisku," << endl 
			<< "5-pridat objednavku" << endl;
		cin >> in;
		if (in == "1")
		{
			subMenu1();
		}
		else if (in == "2") 
		{
			spravca.vypisatVozidla();
		}
		else if (in == "3")
		{
			subMenu3();
		}
		else if (in == "4")
		{
			subMenu4();
		}
		else if (in == "a")
		{
			spravca.vypisatCas();
		}
		else if (in == "b")
		{
			spravca.plus1hodina();
		}
		else if (in == "e")
		{
			spravca.koniec();
		}
		else if (in == "5")
		{
			subMenu5();
		}
	}
	return 0;
}