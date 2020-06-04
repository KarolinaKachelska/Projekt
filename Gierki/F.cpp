#include <iostream>
#include<string>
#include <fstream>
#include <sstream> 
#include <windows.h> // funk. Sleep()
#include <time.h>
#include"F.h"



F::F()
{
	this->nick = "gosc";
	this->punkty = 0;
	this->odp = "";
	//for (int n = 0; n < 5; n++)
	//	this->tablica[n] = "";
	this->NazwaPliku = "F/F_ranking.txt";
	this->pList = nullptr;
	this->pRanking = nullptr;
	ALLEGRO_DISPLAY* display = Gracz::display;
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;

}

F::~F()
{

	while (pList) popfrontList();

	while (pRanking) popfrontRanking(this->pRanking);

	al_destroy_event_queue(kolejka);
}

void F::graj()
{

	bool czyGrac = true;
	bool done = false;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue();
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	this->odp = "";


	for (int i = 0; i < 5; i++)
	{
		losuj();
		al_draw_text(Myfont, al_map_rgb(255, 255, 200),50, 50, ALLEGRO_ALIGN_LEFT,this->nazwa.c_str());
		al_flip_display();

		while (!done)
		{
			al_wait_for_event(kolejka, &ev1);

			if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{

				done = true;
				exit(1);

			}
			else  if (ev1.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (ev1.keyboard.keycode == ALLEGRO_KEY_ENTER)
				{
					done = true;
				}
				else if (ev1.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
				{
					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), 50, 50, ALLEGRO_ALIGN_LEFT, this->nazwa.c_str());
					al_flip_display();
					odp = "";
					done = false;
				}


				else {

					this->odp.push_back(ev1.keyboard.keycode + 96);
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 120, ALLEGRO_ALIGN_LEFT, this->odp.c_str());
					al_flip_display();
				}


			}
		}


		this->odp = ZmienZnak(this->odp);
		Sprawdz();
		al_clear_to_color(al_map_rgb(20, 75, 80));
		al_flip_display();
		done = false;
		this->odp = "";


	}
	al_clear_to_color(al_map_rgb(20, 75, 80));
	al_flip_display();
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, "Twoje punkty :  ");

	string pkt = to_string(punkty);
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 120, ALLEGRO_ALIGN_LEFT, pkt.c_str());
	al_flip_display();
	al_rest(2);


	if (nick != "gosc")
	{
		zapiszPunkty();
	}

	TheEnd(this->nick, this->punkty, this->pRanking, this->NazwaPliku);
}

void F::losuj()
{
	srand((unsigned)time(NULL));
	int los = rand() % 17 + 1;
	string ss;
	fstream plik;
	string linia;
	string nazwaPliku = "F/Pytanie" + to_string(los) + ".txt";
	plik.open(nazwaPliku, ios::in);
	try {
		if (plik.good() == true)
		{



			getline(plik, linia);

			this->nazwa = linia;

			for (int i = 0; i < 5; i++)
			{
				getline(plik, linia);

				this->tablica[i] = linia;

			}



			plik.close();


		}

		else
		{
			throw ss;
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl;
		Sleep(1000);
		system("cls");
		exit(5);

	}


}

void F::Sprawdz()
{
	bool check = false;
	for (int i = 0; i < 5; i++)
	{
		if (this->odp == tablica[i])
		{
			this->punkty += 20 - i * 4;
			check = true;
			i = 10;
		}


	}

	if (check == false) this->punkty += 0;

}

void F::StworzRanking()
{
	string ss;
	fstream plik;
	string NickView;
	int PointView;
	string linia;
	plik.open(this->NazwaPliku, std::ios::in);
	try {
		if (plik.good() == true)
		{


			while (!plik.eof())
			{

				getline(plik, linia);

				istringstream iss(linia);
				iss >> linia;
				NickView = linia;
				iss >> linia;
				PointView = atoi(linia.c_str());
				DodajDoRankingu(pRanking, NickView, PointView);


			}
			plik.close();
		}


		else
		{
			throw ss;
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl;
		Sleep(1000);
		system("cls");
		exit(5);
	}

}

void F::zapiszPunkty()
{
	string ss;
	string sss;
	string linia;
	fstream plik;
	string linia1;
	string linia2;
	string linia3;
	string linia4;
	string nazwaPliku = "Users/nick/" + this->nick + ".txt";
	plik.open(nazwaPliku, ios::in);
	try {
		if (plik.good() == true)
		{

			getline(plik, linia1);
			getline(plik, linia2);
			getline(plik, linia3);
			getline(plik, linia4);



			plik.close();
		}

		else
		{
			throw ss;
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl;
		Sleep(1000);
		system("cls");
		exit(5);

	}
	plik.open(nazwaPliku, ios::out);
	try {
		if (plik.good() == true)
		{

			plik << linia1 << endl;
			plik << linia2 << endl;
			plik << linia3 << endl;
			plik << linia4 + " " + to_string(this->punkty);

			plik.close();
		}

		else
		{
			throw sss;
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl;
		Sleep(1000);
		system("cls");
		exit(5);

	}



}
