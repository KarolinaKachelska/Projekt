#include <iostream>
#include<string>
#include <fstream>
#include <iomanip>
#include <windows.h> // funk. Sleep()
#include "end.h"


void End::DodajDoRankingu(Ranking*& pRanking, string nick, int punkty)
{
	if (!pRanking) pRanking = new Ranking{ nick,punkty,nullptr };
	else
	{
		return DodajDoRankingu(pRanking->pNext, nick, punkty);
	}

}

string End::ZmienZnak(string znak)
{
	if (znak[0] > 95) // zmieniamy mala litere na duza
	{
		znak[0] = znak[0] - 32;
	}

	return znak;
}

void End::ZapiszRanking(Ranking* View, string NazwaPliku)
{

	string ss;


	ofstream zapis;
	zapis.open(NazwaPliku, ios::out | ios::trunc);
	try {
		if (zapis.good() == true)
		{


			while (View != nullptr && View->nick != "")
			{
				zapis << View->nick << " " << View->punkty << endl;
				View = View->pNext;

			}

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

}

void End::TheEnd(string nick, int punkty, Ranking* pRanking, string NazwaPliku)
{
	bool done = false;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 22, NULL);
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue();
	string pkt = to_string(punkty);
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 50, 50, ALLEGRO_ALIGN_LEFT, "Liczba uzyskanych punktow : " );
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 50, ALLEGRO_ALIGN_LEFT, pkt.c_str());
	al_flip_display();
	
	int k = 1;
	RekrutacjaDoRankingu(pRanking, k, punkty, nick);
	Ranking* View = pRanking;
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 50, 90, ALLEGRO_ALIGN_LEFT, " -----------RANKING------------------");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 120, ALLEGRO_ALIGN_LEFT, "#1 ---");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 140, 120, ALLEGRO_ALIGN_LEFT, View->nick.c_str());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 190, 120, ALLEGRO_ALIGN_LEFT, "   ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 230, 120, ALLEGRO_ALIGN_LEFT,to_string(View->punkty).c_str());
	View = View->pNext;

	
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 160, ALLEGRO_ALIGN_LEFT, "#2 ---");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200),140, 160, ALLEGRO_ALIGN_LEFT, View->nick.c_str());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 190, 160, ALLEGRO_ALIGN_LEFT, "   ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 230, 160, ALLEGRO_ALIGN_LEFT, to_string(View->punkty).c_str());
	View = View->pNext;

	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 200, ALLEGRO_ALIGN_LEFT, "#3 ---");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 140, 200, ALLEGRO_ALIGN_LEFT, View->nick.c_str());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 190, 200, ALLEGRO_ALIGN_LEFT, "   ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 230, 200, ALLEGRO_ALIGN_LEFT, to_string(View->punkty).c_str());
	View = View->pNext;

	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 240, ALLEGRO_ALIGN_LEFT, "#4 ---");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 140, 240, ALLEGRO_ALIGN_LEFT, View->nick.c_str());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 190, 240, ALLEGRO_ALIGN_LEFT, "   ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 230, 240, ALLEGRO_ALIGN_LEFT, to_string(View->punkty).c_str());
	View = View->pNext;

	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 280, ALLEGRO_ALIGN_LEFT, "#5 ---");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 140, 280, ALLEGRO_ALIGN_LEFT, View->nick.c_str());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 190, 280, ALLEGRO_ALIGN_LEFT, "   ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 230, 280, ALLEGRO_ALIGN_LEFT, to_string(View->punkty).c_str());
	al_flip_display();
	al_rest(3);
	al_clear_to_color(al_map_rgb(20, 75, 80));
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 50, 90, ALLEGRO_ALIGN_LEFT, "1 - PanelGracza");
	al_flip_display();

	ZapiszRanking(pRanking, NazwaPliku);
	
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
				Gracz G1;
				
				G1.nick = nick;
				G1.UserMenu();


			}

			
			
		}
	}

		
	

	 
}

void End::RekrutacjaDoRankingu(Ranking*& pRanking, int i, int punkty, string nick)
{
	if (pRanking)
	{
		if (pRanking->punkty < punkty)
		{
			pRanking = new Ranking{ nick,punkty,pRanking };
			cout << "Twoje miejsce :  " << i << endl;
		}

		else {
			i = i + 1;
			return RekrutacjaDoRankingu(pRanking->pNext, i, punkty, nick);

		}
	}
	else {
		pRanking = new Ranking{ nick,punkty,nullptr };
	}
}

void End::popfrontRanking(Ranking*& pRanking)
{
	Ranking* p = pRanking;
	if (p)
	{
		pRanking = p->pNext;
		delete p;
	}


}
