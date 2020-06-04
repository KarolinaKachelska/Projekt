#ifndef wirtualna_h
#define wirtualna_h
#include <iostream>
#include<string>
#include"Gracz.h"
#include "end.h"
#include "Struktury.h"
using namespace std;



class Wirtualna : public End, public Gracz {
public:
	string NazwaPliku;
	Ranking* pRanking;

	Wirtualna();
	~Wirtualna();

	virtual void StworzRanking() {};
	virtual void zapiszPunkty() {};
	virtual void graj() {};
};


#endif
