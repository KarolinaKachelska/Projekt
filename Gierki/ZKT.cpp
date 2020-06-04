#include <iostream>
#include<string>
#include <fstream>
#include <sstream> 
#include <windows.h> // funk. Sleep()
#include <time.h>
#include"ZKT.h"



ZKT::ZKT()
{

	this->nick = "gosc";
	this->punkty = 0;
	this->odpA = "";
	this->odpB = "";
	this->odpC = "";
	for (int n = 0; n < 33; n++)
		this->tablica[n] = "";
	this->NazwaPliku = "ZKT/ZKT_ranking.txt";
	this->pList = nullptr;
	this->pRanking = nullptr;
	ALLEGRO_DISPLAY* display = Gracz::display;
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;


}

ZKT::~ZKT()
{

	while (pList) popfrontList();

	while (pRanking) popfrontRanking(this->pRanking);


}

void ZKT::graj()
{
	int los;
	int los2;
	int los3;
	string ss;
	char pyt=' ';
	char pyt2[2] = { ' ',' ' };
	int punkty = 16;

	int int_pyt;
	string string_pyt="";
	bool done = false;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 22, NULL);
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue();
	al_register_event_source(kolejka, al_get_keyboard_event_source());

	srand((unsigned)time(NULL));

	bool czyLitera = false;
	los = rand() % 16 + 1;
	los2 = rand() % 16 + 1;
	while (los == los2) los2 = rand() % 16 + 1;
	los3 = rand() % 16 + 1;
	while (los == los3 || los2 == los3) los3 = rand() % 16 + 1;

	tablica[0] = "";
	WybierzPostac(los);
	string odp2 = WybierzDodatkowa(los2);
	string odp3 = WybierzDodatkowa(los3);
	losujKolejnoscOdpowiedzi(odp2, odp3);

	WyswietlPytania();
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, 10, ALLEGRO_ALIGN_LEFT, "Wybierz numer pytania lub wybierz litere Twojej odpowiedzi ! ");
	al_flip_display();
	int i = 0;
	do {
		
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

				else {
					
					
					pyt2[i]=ev1.keyboard.keycode+21;
					pyt = ev1.keyboard.keycode + 96;
					i++;
				
				}


			}
		}

		string_pyt.push_back(pyt2[0]);
		if(i==2)  string_pyt.push_back(pyt2[1]);
		
		int_pyt = atoi(string_pyt.c_str());
		cout << string_pyt << endl;
		

		try {
			if (pyt >= 65 && pyt <= 122)
			{
				done = true;
				czyLitera = true;
				string Poprodpowiedz = "";
				Poprodpowiedz = ZmienZnak(Poprodpowiedz + pyt);

				if (Poprodpowiedz == "A")Poprodpowiedz = this->odpA;
				else if (Poprodpowiedz == "B") Poprodpowiedz = this->odpB;
				else if (Poprodpowiedz == "C") Poprodpowiedz = this->odpC;

				if (Poprodpowiedz == this->nazwa) {
					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_flip_display();

					al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, 50, ALLEGRO_ALIGN_LEFT, "jej <3");
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, 90, ALLEGRO_ALIGN_LEFT, "Twoje punkty :  ");
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 140, ALLEGRO_ALIGN_LEFT, to_string(punkty).c_str());
					al_flip_display();
					al_rest(1);


					this->punkty = punkty;
					if (nick != "gosc")
					{
						zapiszPunkty();
					}
					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_flip_display();
					czyLitera = false;
					TheEnd(this->nick, this->punkty, this->pRanking, this->NazwaPliku);


				}
				else {
					punkty = 0;
					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_flip_display();

					al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, 50, ALLEGRO_ALIGN_LEFT, "smutne, nie udalo ci sie ;c");
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 90, ALLEGRO_ALIGN_LEFT, "Twoje punkty :  ");
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), 120, 150, ALLEGRO_ALIGN_LEFT, to_string(punkty).c_str());
					al_flip_display();
					al_rest(1);
					czyLitera = false;


				}

			}
			else if (int_pyt >= 1 && int_pyt <= 16)
			{
				punkty--;
				WybierzPytanie(int_pyt);
				done = false;
				czyLitera = false;
			}
			else throw ss;
		}
		catch (string)
		{
			cout << "Blad! nie wpisales ani odpowiedzi, ani numeru pytania !" << endl;
			Sleep(1000);
			system("cls");
			exit(5);
		}


		string_pyt = "";
		int_pyt = 0;
		pyt2[0] = ' ';
		pyt2[1] = ' ';
		pyt = ' ';
		i = 0;


	} while (czyLitera == false);




}

void ZKT::WybierzPostac(int los)
{

	string ss;
	fstream plik;
	string linia;
	string nazwaPliku = "ZKT/Postac" + to_string(los) + ".txt";
	plik.open(nazwaPliku, std::ios::in);
	try {
		if (plik.good() == true)
		{


			while (!plik.eof())
			{
				getline(plik, linia);

				this->nazwa = linia;

				for (int i = 1; i < 17; i++)
				{
					getline(plik, linia);
					tablica[i] = linia;
					getline(plik, linia);
					tablica[i + 16] = linia;
				}





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

string ZKT::WybierzDodatkowa(int los2)
{

	string ss;
	fstream plik;
	string linia;
	string nazwaPliku = "ZKT/Postacie.txt";
	plik.open(nazwaPliku, std::ios::in);
	try {
		if (plik.good() == true)
		{

			for (int i = 1; i < los2 + 1; i++) // tu moze byc +/- zla linia brana
			{

				getline(plik, linia);


			}

			return linia;
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


	return "";
}

void ZKT::losujKolejnoscOdpowiedzi(string odp2, string odp3)
{

	int Kolejnosc = rand() % 6 + 1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 12, NULL);
	switch (Kolejnosc)
	{
	case 1:
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 50, ALLEGRO_ALIGN_LEFT, "Mozliwe Odpowiedzi: ");

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 70, ALLEGRO_ALIGN_LEFT, "A. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 70, ALLEGRO_ALIGN_LEFT, this->nazwa.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 110, ALLEGRO_ALIGN_LEFT, "B. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 110, ALLEGRO_ALIGN_LEFT, odp2.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 150, ALLEGRO_ALIGN_LEFT, "C. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 150, ALLEGRO_ALIGN_LEFT, odp3.c_str());
		al_flip_display();
		this->odpA = this->nazwa;
		this->odpB = odp2;
		this->odpC = odp3;
		break;

	case 2:
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 50, ALLEGRO_ALIGN_LEFT, "Mozliwe Odpowiedzi: ");

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 70, ALLEGRO_ALIGN_LEFT, "A. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 70, ALLEGRO_ALIGN_LEFT, odp2.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 110, ALLEGRO_ALIGN_LEFT, "B. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 110, ALLEGRO_ALIGN_LEFT, this->nazwa.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 150, ALLEGRO_ALIGN_LEFT, "C. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 150, ALLEGRO_ALIGN_LEFT, odp3.c_str());
		al_flip_display();
		this->odpA = odp2;
		this->odpB = this->nazwa;
		this->odpC = odp3;

		break;
	case 3:
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 50, ALLEGRO_ALIGN_LEFT, "Mozliwe Odpowiedzi: ");

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 70, ALLEGRO_ALIGN_LEFT, "A. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 70, ALLEGRO_ALIGN_LEFT, odp3.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 110, ALLEGRO_ALIGN_LEFT, "B. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 110, ALLEGRO_ALIGN_LEFT, odp2.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 150, ALLEGRO_ALIGN_LEFT, "C. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 150, ALLEGRO_ALIGN_LEFT, this->nazwa.c_str());
		al_flip_display();
		this->odpA = odp3;
		this->odpB = odp2;
		this->odpC = this->nazwa;

		break;



	case 4:
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 50, ALLEGRO_ALIGN_LEFT, "Mozliwe Odpowiedzi: ");

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 70, ALLEGRO_ALIGN_LEFT, "A. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 70, ALLEGRO_ALIGN_LEFT, odp2.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 110, ALLEGRO_ALIGN_LEFT, "B. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 110, ALLEGRO_ALIGN_LEFT, odp3.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 150, ALLEGRO_ALIGN_LEFT, "C. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 150, ALLEGRO_ALIGN_LEFT, this->nazwa.c_str());
		al_flip_display();
		this->odpA = odp2;
		this->odpB = odp3;
		this->odpC = this->nazwa;

		break;
	case 5:
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 50, ALLEGRO_ALIGN_LEFT, "Mozliwe Odpowiedzi: ");

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 70, ALLEGRO_ALIGN_LEFT, "A. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 70, ALLEGRO_ALIGN_LEFT, odp3.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 110, ALLEGRO_ALIGN_LEFT, "B. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 110, ALLEGRO_ALIGN_LEFT, this->nazwa.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 150, ALLEGRO_ALIGN_LEFT, "C. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 150, ALLEGRO_ALIGN_LEFT, odp2.c_str());
		al_flip_display();
		this->odpA = odp3;
		this->odpB = this->nazwa;
		this->odpC = odp2;

		break;
	case 6:
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 50, ALLEGRO_ALIGN_LEFT, "Mozliwe Odpowiedzi: ");

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 70, ALLEGRO_ALIGN_LEFT, "A. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 70, ALLEGRO_ALIGN_LEFT, this->nazwa.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 110, ALLEGRO_ALIGN_LEFT, "B. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 110, ALLEGRO_ALIGN_LEFT, odp3.c_str());

		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 150, ALLEGRO_ALIGN_LEFT, "C. ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 150, ALLEGRO_ALIGN_LEFT, odp2.c_str());
		al_flip_display();
		this->odpA = this->nazwa;
		this->odpB = odp3;
		this->odpC = odp2;
		break;

	}
}

void ZKT::WyswietlPytania()
{
	int wys=10;
	int szer=70;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 12, NULL);
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, 45, ALLEGRO_ALIGN_LEFT, "Pytania: ");

	for (int i = 1; i < 17; i++)
	{
		
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), wys, szer, ALLEGRO_ALIGN_LEFT, tablica[i].c_str());
		szer = szer + 15;
	}
	al_flip_display();

}

void ZKT::WybierzPytanie(int pyt)
{
	int wys = 350;
	int szer = 55 +15*pyt; //+15
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 12, NULL);
	
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), wys, szer, ALLEGRO_ALIGN_LEFT, tablica[pyt+16].c_str());
	al_flip_display();
}

void ZKT::zapiszPunkty()
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
	try
	{
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
			plik << linia3 + " " + to_string(this->punkty) << endl;
			plik << linia4 << endl;

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

void ZKT::StworzRanking()
{

	fstream plik;
	string ss;
	string NickView;
	int PointView;
	string linia;
	string nazwaPliku = this->NazwaPliku;
	plik.open(nazwaPliku, std::ios::in);
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
				DodajDoRankingu(this->pRanking, NickView, PointView);


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


