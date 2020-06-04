#ifndef zkt_h
#define zkt_h
#include <iostream>
#include<string>
#include"Gracz.h"
#include "Wirtualna.h"
using namespace std;


class ZKT : public Wirtualna
{
private:

	string odpA;
	string odpB;
	string odpC;
	string tablica[33];

public:

	ZKT();
	~ZKT();

	/////////////////
	void StworzRanking();
	void graj();
	void zapiszPunkty();
	/////////////////

	void WybierzPostac(int los);
	string WybierzDodatkowa(int los2);
	void losujKolejnoscOdpowiedzi(string odp2, string odp3);
	void WyswietlPytania();
	void WybierzPytanie(int pyt);

};




#endif

