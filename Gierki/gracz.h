
#ifndef gracz_h
#define gracz_h
#include <iostream>
#include<string>
#include <fstream>
#include<vector>
#include <windows.h> // funk. Sleep()
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Struktury.h"
using namespace std;


class Gracz
{
public:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* kolejka;

protected:
	
	List* pList;
	
public:
	string nick;
	int punkty;
	string nazwa;
	Gracz();
	~Gracz();
	void ReadList();
	void MakeAList(List*& pList, string nick);
	void Formularz();
	void ZarejestrujSie();
	void ZalogujSie();
	bool SprawdzamNick(string nick, List*& pList);
	void SaveNick(string nick);
	bool UserMenu();
	void wypiszPunkty();
	void popfrontList();
	
};




#endif
