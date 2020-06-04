#ifndef struktury_h
#define struktury_h
#include <iostream>
#include<string>

using namespace std;




struct List {


	string nick;
	List* pNext;
};

struct Tree {  //beda tu zapisane nazwy panst i miast

	Tree* pNext;

	string nazwa_P_M;

};

struct Ranking { // trzyma ranking z WSZYSTKICH GIER tych list  bedzie tyle ile gier

	string nick;
	int punkty;

	Ranking* pNext;


};

#endif

