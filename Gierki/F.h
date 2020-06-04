#ifndef f_h
#define f_h
#include <iostream>
#include<string>
#include"Gracz.h"
#include "Wirtualna.h"
using namespace std;


class F : public Wirtualna
{
private:

	string odp;


public:
	string tablica[5];
	F();
	~F();

	////////////
	void graj();
	void StworzRanking();
	void zapiszPunkty();
	///////////////

	void losuj();
	void Sprawdz();


};

#endif

