#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
using namespace std;

struct mov
{
    int pos_x;
    int pos_y;
    bool teclas[4];
};

enum Teclas{UP, DOWN, LEFT, RIGTH};

mov *Preecher_array(mov *movs)
{
    for (int i = 0; i < 4; i++)
    {
        movs->teclas[i] = false;
    }
    return movs;
    
}

bool Tela(ALLEGRO_EVENT_QUEUE *fila, ALLEGRO_EVENT ev, mov *movimentos)
{
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return true;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return true;
        }
        switch (ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_UP:

            movimentos->teclas[UP] = true;
            break;
        
        case ALLEGRO_KEY_DOWN:

            movimentos->teclas[DOWN] = true;  
            break;

        case ALLEGRO_KEY_LEFT:

            movimentos->teclas[LEFT] = true;
            break;

        case ALLEGRO_KEY_RIGHT:

            movimentos->teclas[RIGTH] = true;
            break;
        }
        

        return false;
    }
    else if (ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        switch (ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_UP:

            movimentos->teclas[UP] = false;
            break;
        
        case ALLEGRO_KEY_DOWN:

            movimentos->teclas[DOWN] = false;  
            break;

        case ALLEGRO_KEY_LEFT:

            movimentos->teclas[LEFT] = false;
            break;

        case ALLEGRO_KEY_RIGHT:

            movimentos->teclas[RIGTH] = false;
            break;
        }

        return false;
    }
    return false;
    
    
}
void sem_bordas(mov *movs)
{
    if (movs->pos_x >= 1280)
    {
        if (movs->pos_y > 0 && movs->pos_y < 720)
        {
            movs->pos_x = 0;
        }
        else
        {
            if (movs->pos_y > 720)
            {
                movs->pos_y = 0;
            }
            else
            {
                movs->pos_y = 720;
            }
            
        }
        
    }
    else if (movs->pos_x < 0)
    {
        if (movs->pos_y > 0 && movs->pos_y < 720)
        {
            movs->pos_x = 1280;
        }
        else
        {
            if (movs->pos_y >= 720)
            {
                movs->pos_y = 0;
            }
            else
            {
                movs->pos_y = 720;
            }
            
        }
    }
    else
    {
        if (movs->pos_y > 720)
        {
            movs->pos_y = 0;
        }
        else if (movs->pos_y < 0)
        {
            movs->pos_y = 720;
        }
    }

    
}
int main(){
    ALLEGRO_DISPLAY *display=NULL;
    bool fim = false;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

    mov *movimentos = NULL;

    movimentos = (mov*)malloc(sizeof(mov));

    movimentos->pos_x = 100;
    movimentos->pos_y = 100;

    Preecher_array(movimentos);


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

    //Inicialização de addons e etc.
    al_install_keyboard();
    al_install_mouse();


    fila_eventos = al_create_event_queue();
    al_init_primitives_addon();

    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(display));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());


    //Lógica da tela
    while (!fim)
    {
        ALLEGRO_EVENT ev;

        al_wait_for_event(fila_eventos, &ev);

        fim = Tela(fila_eventos, ev, movimentos);

        movimentos->pos_x -= 10 * movimentos->teclas[LEFT];
        movimentos->pos_x += 10 * movimentos->teclas[RIGTH];
        movimentos->pos_y -= 10 * movimentos->teclas[UP];
        movimentos->pos_y += 10 * movimentos->teclas[DOWN];

        sem_bordas(movimentos);

        al_draw_filled_rectangle(movimentos->pos_x, movimentos->pos_y,movimentos->pos_x + 30, movimentos->pos_y + 30, al_map_rgb(255, 0, 0));
        al_flip_display();
        al_clear_to_color(al_map_rgb(225, 225, 225));
    }

    //Fim do programa
    al_destroy_display(display);
    al_destroy_event_queue(fila_eventos);
   
    return 0;
}
