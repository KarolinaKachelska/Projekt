#ifndef end_h
#define end_h
#include <iostream>
#include<string>
#include"Gracz.h"
using namespace std;


class End {

public:
	void DodajDoRankingu(Ranking*& pRanking, string nick, int punkty);
	void ZapiszRanking(Ranking* Helper, string NazwaPliku);
	void TheEnd(string nick, int punkty, Ranking* pRanking, string NazwaPliku);
	void RekrutacjaDoRankingu(Ranking*& pRanking, int i, int punkty, string nick);
	void popfrontRanking(Ranking*& pRanking);
	string ZmienZnak(string znak);

};

#endif

