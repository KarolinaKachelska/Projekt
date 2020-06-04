#ifndef pm_h
#define pm_h
#include <iostream>
#include<string>
#include "Wirtualna.h"
using namespace std;


class PM : public Wirtualna
{
private:
	Tree* pHead;
	Tree* pHead2;


public:

	PM();
	~PM();

	////////////////////////
	void StworzRanking();
	void graj();
	void zapiszPunkty();
	/////////////////////

	void czytajPlik(Tree*& pHead, string nazwaPliku);
	void dodajDrzewo(Tree*& pHead, string slowo);
	bool sprawdzP(Tree* pHead, char litera);
	bool sprawdzM(Tree* pHead, char litera);
	void wpiszNazweM(char literka);
	void wpiszNazweP(char literka);
	void popfrontTree();
	void popfrontTree2();
};






#endif
