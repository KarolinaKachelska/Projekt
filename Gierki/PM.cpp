#include <sstream> 
#include <time.h>
#include"PM.h"


void PM::StworzRanking()
{
	string ss;
	fstream plik;
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

PM::PM()
{
	this->nick = "gosc";
	this->punkty = 0;
	this->NazwaPliku = "PM/PM_ranking.txt";
	this->pList = nullptr;
	this->pHead = nullptr;
	this->pHead2 = nullptr;
	this->pRanking = nullptr;
	ALLEGRO_DISPLAY* display =Gracz::display;
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;


}

PM::~PM()
{

	while (pHead) popfrontTree();

	while (pHead2) popfrontTree2();

	while (pList) popfrontList();

	while (pRanking) popfrontRanking(this->pRanking);
	al_destroy_event_queue(kolejka);

}

void PM::graj()
{
	
	
	bool done = false;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue();
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	bool check = false;
	bool czyGrac = true;
	int punkty = 0;
	string nazwaPliku = "PM/panstwa.txt";
	czytajPlik(pHead, nazwaPliku);
	string nazwaPliku2 = "PM/miasta.txt";
	czytajPlik(pHead2, nazwaPliku2);
	char litera;
	string pkt;
	srand((unsigned)time(NULL));

	do
	{
		litera = rand() % 26 + 65;
		if (litera == 'Q' || litera == 'X' || litera == 'Y' || litera == 'V') litera = 'Z';
		ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wylosowana litera: ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, &litera);
		al_flip_display();
		wpiszNazweP(litera);
		check = sprawdzP(pHead, litera);

		if (check == false)
		{
			al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Smutne, nie udalo ci sie ;c ");
			al_flip_display();
			al_rest(1);
			al_clear_to_color(al_map_rgb(20, 75, 80));
			al_flip_display();
			czyGrac = false;
		}
		else {
			al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wylosowana litera: ");
			al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, &litera);
			al_flip_display();
			wpiszNazweM(litera);
			check = sprawdzM(pHead2, litera);
			
			if (check == false)
			{
				pkt = to_string(punkty);
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Smutne, nie udalo ci sie ;c ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4)+40, ALLEGRO_ALIGN_LEFT, "Twoje punkty : ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4)+80, ALLEGRO_ALIGN_LEFT, pkt.c_str() );
				al_flip_display();
				al_rest(2);
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				czyGrac = false;
			}
			else
			{
				punkty++;
				pkt = to_string(punkty);
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Jej, dales rade <3 ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, "Twoje punkty : ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 80, ALLEGRO_ALIGN_LEFT, pkt.c_str());
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4)+120, ALLEGRO_ALIGN_LEFT, "Czy chcesz dalej grac? ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 160, ALLEGRO_ALIGN_LEFT, "1 - TAK ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 200, ALLEGRO_ALIGN_LEFT, "2 - NIE ");
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
						if (ev1.keyboard.keycode == ALLEGRO_KEY_1)
						{
							al_clear_to_color(al_map_rgb(20, 75, 80));
							al_flip_display();
							czyGrac = true; break;
							done = true;
						}
						else if (ev1.keyboard.keycode == ALLEGRO_KEY_2)
						{
							if (czyGrac == false) break; else  czyGrac = false; break;
							
						}


					}
				}
				
			}
		}





	} while (czyGrac);

	this->punkty = punkty;
	if (nick != "gosc")
	{
		zapiszPunkty();
	}

	TheEnd(this->nick, this->punkty, this->pRanking, this->NazwaPliku);
}

void PM::czytajPlik(Tree*& pHead, string nazwaPliku)
{
	string ss;
	fstream plik;
	string linia;
	plik.open(nazwaPliku, std::ios::in | std::ios::out);
	try {
		if (plik.good() == true)
		{


			while (!plik.eof())
			{
				getline(plik, linia);

				dodajDrzewo(pHead, linia);

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

void PM::dodajDrzewo(Tree*& pHead, string slowo)
{
	if (!pHead) pHead = new Tree{ nullptr, slowo };
	else {
		return dodajDrzewo(pHead->pNext, slowo);

	}
}

bool PM::sprawdzP(Tree* pHead, char litera)
{
	while (pHead)
	{
		if (pHead->nazwa_P_M == this->nazwa && nazwa[0] == litera)
		{
			return true;
		}
		else pHead = pHead->pNext;
	}

	return false;
}

bool PM::sprawdzM(Tree* pHead, char litera)
{
	while (pHead)
	{
		if (pHead->nazwa_P_M == this->nazwa && nazwa[0] == litera)
		{
			return true;
		}
		else pHead = pHead->pNext;
	}


	return false;
}

void PM::wpiszNazweM(char literka)
{
	bool done = false;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue();
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4)+120, ALLEGRO_ALIGN_LEFT, "Wpisz nazwe wybranej Stolicy :  ");

	al_flip_display();
	
	string nazwa="";
	while (!done)
	{
		al_wait_for_event(kolejka, &ev1);

		if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev1.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
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
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wylosowana litera: ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, &literka);
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 120, ALLEGRO_ALIGN_LEFT, "Wpisz nazwe wybranej Stolicy :  ");

				al_flip_display();
				nazwa = "";
				done = false;
			}


			else {

				nazwa.push_back(ev1.keyboard.keycode + 96);
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 160, ALLEGRO_ALIGN_LEFT, nazwa.c_str());
				al_flip_display();
			}
		}
	}

	al_clear_to_color(al_map_rgb(20, 75, 80));
	al_flip_display();
	
	nazwa = ZmienZnak(nazwa);
	this->nazwa = nazwa;

}

void PM::wpiszNazweP(char literka)
{
	bool done = false;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue();
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 120, ALLEGRO_ALIGN_LEFT, "Wpisz nazwe Panstwa : ");
    al_flip_display();
	
	string nazwa = "";
	while (!done)
	{
		al_wait_for_event(kolejka, &ev1);

		if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev1.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
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
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wylosowana litera: ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, &literka);
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 120, ALLEGRO_ALIGN_LEFT, "Wpisz nazwe Panstwa : ");

				al_flip_display();
				nazwa = "";
				done = false;
			}


			else {

				nazwa.push_back(ev1.keyboard.keycode + 96);
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 160, ALLEGRO_ALIGN_LEFT, nazwa.c_str());
				al_flip_display();
			}
		}
	}

	al_clear_to_color(al_map_rgb(20, 75, 80));
	al_flip_display();

	nazwa = ZmienZnak(nazwa);
	this->nazwa = nazwa;


}

void PM::zapiszPunkty()
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
			plik << linia2 + " " + to_string(this->punkty) << endl;
			plik << linia3 << endl;
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

void PM::popfrontTree()
{
	Tree* p = pHead;
	if (p)
	{
		pHead = p->pNext;
		delete p;
	}

}

void PM::popfrontTree2()
{
	Tree* p = pHead2;
	if (p)
	{
		pHead2 = p->pNext;
		delete p;
	}
}
