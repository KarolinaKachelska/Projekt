#include <iostream>
#include<string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Gracz.h"


using namespace std;



int main()
{
   
    ALLEGRO_EVENT ev1;
    Gracz G1;
    ALLEGRO_SAMPLE* sample = NULL;
    ALLEGRO_BITMAP* icon;
    
    ALLEGRO_SAMPLE_INSTANCE* sampleInstance = NULL;
    
    G1.ReadList();  // czytamy liste nick'ow
    

    if (!al_init())
    {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return -1;
    }
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_audio();////////////////////////
    al_init_acodec_addon(); ///////////////////
    al_reserve_samples(5);/////////////////
    sample = al_load_sample("mjusik.ogg");///////////////
    sampleInstance = al_create_sample_instance(sample);///
    al_set_sample_instance_playmode(sampleInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sampleInstance, al_get_default_mixer());

    /* Allokujemy pamiêæ dla kolejki i sprawdzamy czy funkcja nie zwróci³a b³êdu */
    G1.kolejka = al_create_event_queue();
    

    if (G1.kolejka == NULL)
    {
        fprintf(stderr, "Failed to create event queue!\n");
        return -1;
    }
    
    G1.display = al_create_display(640, 480);
    if (G1.display == NULL)
    {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    if (!al_install_keyboard()) ///setup the keyboard
    {
        al_show_native_message_box(NULL, "Error!", "Failed to install keyboard.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    icon = al_load_bitmap("icon.bmp");
    al_set_window_title(G1.display, "ORDI Game");
    al_set_display_icon(G1.display, icon);
   
    al_register_event_source(G1.kolejka, al_get_display_event_source(G1.display));
    al_register_event_source(G1.kolejka, al_get_keyboard_event_source());
    ALLEGRO_BITMAP* obrazek = al_load_bitmap("logo.png");
    al_draw_bitmap(obrazek, 0, 0, 0);  // wyœwietlenie bitmapy "obrazek" na "Backbuffer" (bufor ekranu)
    al_flip_display(); // wyœwietlenie aktualnego bufora na ekran
   //al_play_sample_instance(sampleInstance);
   al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
   al_rest(4);
    al_clear_to_color(al_map_rgb(20, 75, 80));
    al_flip_display();
    //al_stop_sample_instance(sampleInstance);
    string write= "";
    ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);

    bool done = 0;
    al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) -220 , (480 / 4), ALLEGRO_ALIGN_LEFT, "----------- Panel Gry ------------");
    al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100, (480 / 4 + 40), ALLEGRO_ALIGN_LEFT, "Wybierz:");
    al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100 , (480 / 4 +80), ALLEGRO_ALIGN_LEFT, "1.Zaloguj sie");
    al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100, (480 / 4 +120), ALLEGRO_ALIGN_LEFT, "2.Graj jako gosc");
    al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100, (480 / 4 +160), ALLEGRO_ALIGN_LEFT, "3.Wyjdz");

    al_flip_display();
    while (!done)
    {
        
        
        al_wait_for_event(G1.kolejka, &ev1);
        
        if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
        
        done = true;
        exit(1);

        }
        else  if(ev1.type == ALLEGRO_EVENT_KEY_DOWN) 
        {
            if (ev1.keyboard.keycode == ALLEGRO_KEY_1 )
            {
                al_clear_to_color(al_map_rgb(20, 75, 80));
                al_flip_display();
                G1.Formularz();
                done = true;
               
               
            }
            if (ev1.keyboard.keycode == ALLEGRO_KEY_2)
            {
                al_clear_to_color(al_map_rgb(20, 75, 80));
                al_flip_display();
                G1.UserMenu();
                done = true;
             

            }
            if (ev1.keyboard.keycode == ALLEGRO_KEY_3)
            {
               
                done = true;
               

            }
        }

            
       
    }
    
    al_destroy_bitmap(obrazek);
    al_destroy_bitmap(icon);
    al_destroy_sample(sample);
    al_destroy_sample_instance(sampleInstance);
    al_destroy_display(G1.display);

       
    return 0;
}
