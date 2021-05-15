#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
using namespace std;

enum TECLAS{UP, DOWN, LEFT, RIGTH};


int main(){
    ALLEGRO_DISPLAY *display=NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    bool fim = false;
    bool teclas[]= {false, false, false, false};

    int pos_x = 100;
    int pos_y = 100;

    if(!al_init()){
        fprintf(stderr, "ERRO!");
        return -1;
    }

    display=al_create_display(1280,720);

    if(!display) {
        fprintf(stderr, "ERRO!");
        return -1;
    }
    al_clear_to_color(al_map_rgb(225,225,225));

    
    al_install_keyboard();
    al_install_mouse();


    fila_eventos = al_create_event_queue();
    al_init_primitives_addon();

    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(display));


    while (!fim)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(fila_eventos, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                fim =  true;
            }   
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:

                    teclas[UP] = true;
                    break;
            
                case ALLEGRO_KEY_DOWN:

                    teclas[DOWN] = true;  
                    break;

                case ALLEGRO_KEY_LEFT:

                    teclas[LEFT] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:

                    teclas[RIGTH] = true;
                    break;
            }

            
        } 
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:

                teclas[UP] = false;
                break;
            
            case ALLEGRO_KEY_DOWN:

                teclas[DOWN] = false;  
                break;

            case ALLEGRO_KEY_LEFT:

                teclas[LEFT] = false;
                break;

            case ALLEGRO_KEY_RIGHT:

                teclas[RIGTH] = false;
                break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            fim = true;
        }

        pos_x -= 10 * teclas[LEFT];
        pos_x += 10 * teclas[RIGTH];
        pos_y -= 10 * teclas[UP];
        pos_y += 10 * teclas[DOWN];

        al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 0));
        al_flip_display();
        al_clear_to_color(al_map_rgb(225, 225, 225));
    }
    al_destroy_display(display);
    al_destroy_event_queue(fila_eventos);
   
    return 0;
}
