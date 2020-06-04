
#include "gracz.h"
#include "PM.h"
#include"ZKT.h"
#include"F.h"


Gracz::Gracz()
{
	this->nick = "gosc";
	this->nazwa = "";
	this->punkty = 0;
	this->pList = nullptr;
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	


}

Gracz::~Gracz()
{

	while (pList) popfrontList();
	al_destroy_event_queue(kolejka);

}

void Gracz::popfrontList()
{
	List* p = pList;
	if (p)
	{
		pList = p->pNext;
		delete p;
	}


}

void Gracz::wypiszPunkty()
{
	string ss;
	
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, (0), ALLEGRO_ALIGN_LEFT, "Wyswietlane 5 sekund");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 40), ALLEGRO_ALIGN_LEFT, "HISTORIA TWOICH GIER :");
	al_flip_display();
	fstream plik;
	string nazwaPliku = "Users/nick/" + this->nick + ".txt";
	string linia;
	int wys = 60;
	int szer =80;
	
	try {
		plik.open(nazwaPliku, std::ios::in);
		if (plik.good() == true)
		{


			while (!plik.eof())
			{

				getline(plik, linia);
				al_draw_text(Myfont, al_map_rgb(255, 255, 200),wys, szer, ALLEGRO_ALIGN_LEFT, linia.c_str());
				szer=szer +50;


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
	al_flip_display();
	al_rest(5);


}

void Gracz::ReadList()
{
	string ss;
	fstream plik;
	string linia;
	int punkty = 0;
	string nazwaPliku = "Users/lista.txt";
	plik.open(nazwaPliku, std::ios::in | std::ios::out);
	try {
		if (plik.good() == true)
		{


			while (!plik.eof())
			{

				getline(plik, linia);
				MakeAList(this->pList, linia);


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

void Gracz::MakeAList(List*& pList, string nick)
{
	if (!pList) pList = new List{ nick,nullptr };
	else
		return MakeAList(pList->pNext, nick);


}

void Gracz::Formularz()
{
	bool done = 0;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Czy posiadasz juz konto ?");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100, (480 / 4 + 40), ALLEGRO_ALIGN_LEFT, "1 - TAK ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100, (480 / 4 + 80), ALLEGRO_ALIGN_LEFT, " 2 - NIE");
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
				this->ZalogujSie();


			}
			if (ev1.keyboard.keycode == ALLEGRO_KEY_2)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				this->ZarejestrujSie();


			}
		}
	}	
}

void Gracz::ZarejestrujSie()
{
	bool h = true;
	bool done = 0;
	string nick="";
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wpisz nick : ");
	
	al_flip_display();
	while (h)
	{

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
				if (ev1.keyboard.keycode == ALLEGRO_KEY_ENTER )
				{
					done = true;
				}
				else if (ev1.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
				{
					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wpisz nick : ");

					al_flip_display();
					nick = "";
					done = false;
				}


			else {
					nick.push_back(ev1.keyboard.keycode + 96);
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 80, ALLEGRO_ALIGN_LEFT, nick.c_str());
					al_flip_display();
			}
			}
		}
		
		al_clear_to_color(al_map_rgb(20, 75, 80));
		al_flip_display();
	
		if (SprawdzamNick(nick, this->pList) == true)
		{
			
			al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "wybrany nick istnieje, wybierz inny  ");

			al_flip_display();
			nick = "";
			done = false;

		}
		else
		{
			al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Udalo sie, nick jest twoj! ");

			al_flip_display();
			
			h = false;
			SaveNick(nick);
			MakeAList(this->pList, nick);
			this->nick = nick;
			UserMenu();

		}

	}


}

void Gracz::ZalogujSie()
{
	ALLEGRO_EVENT ev1;
	bool done = 0;
	string nick = "";

	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wpisz nick : ");

	al_flip_display();
	bool sprawdz = false;
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
			else if (ev1.keyboard.keycode == ALLEGRO_KEY_BACKSPACE )
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wpisz nick : ");

				al_flip_display();
				nick = "";
				done = false;
			}

			else {
				
				nick.push_back(ev1.keyboard.keycode + 96);
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 80, ALLEGRO_ALIGN_LEFT, nick.c_str());
				al_flip_display();
			}
		}
	}


	done = false;
	al_clear_to_color(al_map_rgb(20, 75, 80));
	al_flip_display();
	sprawdz = SprawdzamNick(nick, this->pList);
	if (sprawdz == true)
	{
		this->nick = nick;

		UserMenu();

	}
	else
	{
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Nie istnieje gracz o takiej nazwie ! ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4)+40, ALLEGRO_ALIGN_LEFT, "1 - Zarejestruj sie ! ");
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4)+80, ALLEGRO_ALIGN_LEFT, "2 - wyjdz ");
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
					ZarejestrujSie();
					done = true;
				}
				else if (ev1.keyboard.keycode == ALLEGRO_KEY_2)
				{
					done = true;
					exit(1);
				}


			}
		}


	}

}

bool Gracz::SprawdzamNick(string nick, List*& pList)
{
	if (pList)
	{
		if (pList->nick == nick) return true; // true - czyli istnieje
		else return SprawdzamNick(nick, pList->pNext);

	}

	return false;

}

void Gracz::SaveNick(string nick)
{
	string ss;
	string sss;
	ofstream zapis;
	zapis.open("Users/lista.txt", ios::out | ios::app);
	try {
		if (zapis.good() == true)
		{
			zapis << nick << endl;

			zapis.close();
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
	
	string plik = "Users/nick/" + nick + ".txt";
	ofstream stworz;

	stworz.open(plik, ios::out | ios::app);
	try {
		if (stworz.good() == true)
		{
			stworz << nick << endl;
			stworz << "Panstwa-Miasta" << endl;
			stworz << "Zgadnij-Kto-To?" << endl;
			stworz << "Familiada" << endl;
			stworz.close();
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

bool Gracz::UserMenu()
{
	al_clear_to_color(al_map_rgb(20, 75, 80));
	al_flip_display();
	vector< Wirtualna*> Wir;
	ALLEGRO_EVENT ev1;
	PM* pm1 = new PM;
	Wir.push_back(pm1);
	ZKT* zkt1 = new ZKT;
	Wir.push_back(zkt1);
	F* f1 = new F;
	Wir.push_back(f1);
	int s = Wir.size(); 
	for (int i = 0; i < s; i++)
	{

		Wir[i]->StworzRanking();
		Wir[i]->nick = this->nick;

	}

	string ss;
	bool done = false;
	
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 22, NULL);
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue();
	
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, (0), ALLEGRO_ALIGN_LEFT, "-----------Panel Gracza -----------------");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 40), ALLEGRO_ALIGN_LEFT, "Wybierz:");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 80), ALLEGRO_ALIGN_LEFT, " 1.Zagraj w Panstwa-Miasta");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 +120), ALLEGRO_ALIGN_LEFT, "2.Zagraj w Zgadnij Kto To?");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 160), ALLEGRO_ALIGN_LEFT, "3.Zagraj w Familiade");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 200), ALLEGRO_ALIGN_LEFT, " 4.Wyswietl Historie Gier");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 240), ALLEGRO_ALIGN_LEFT, "5.Wyjdz");
	al_flip_display();

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
			if (ev1.keyboard.keycode == ALLEGRO_KEY_1)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				pm1->graj();
				done = true;


			}
			if (ev1.keyboard.keycode == ALLEGRO_KEY_2)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				zkt1->graj();
				done = true;


			}
			if (ev1.keyboard.keycode == ALLEGRO_KEY_3)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				al_destroy_event_queue(kolejka);
				f1->graj();
				done = true;


			}
			if (ev1.keyboard.keycode == ALLEGRO_KEY_4)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				if (this->nick != "gosc")
				{
					wypiszPunkty();

					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_flip_display();
					UserMenu();
					done = true;
				}
				else
				{
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, (480 / 4 + 40), ALLEGRO_ALIGN_LEFT, "Grasz jako gosc, nie masz histori gier! ");
					al_flip_display();
					al_rest(2);
					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_flip_display();
					UserMenu();
					done = true;

				}

			}
			if (ev1.keyboard.keycode == ALLEGRO_KEY_5)
			{
				done = true;
				exit(1);


			}
		}
	}
	


	return false;
}
