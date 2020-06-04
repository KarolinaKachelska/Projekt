#include <iostream>
#include<string>
#include "Wirtualna.h"

Wirtualna::Wirtualna()
{
	this->NazwaPliku = "nieinterere.txt";
	this->pRanking = nullptr;
	ALLEGRO_DISPLAY* display = Gracz::display;
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
}

Wirtualna::~Wirtualna()
{
	while (pList) popfrontList();

	while (pRanking) popfrontRanking(this->pRanking);
}
