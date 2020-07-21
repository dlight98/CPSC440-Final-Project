/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "SpriteSheet.h"
#include "mappy_A5.h"
 
int collided(int x, int y);  //Tile Collision
bool endValue(int x, int y); //End Block with the User Value = 8
void drawStatus(ALLEGRO_FONT* font, int counter, int width, int height);

int main(int argc, char **argv){
 
	//Constants
	const int WIDTH = 640;	//FIXME?
	const int HEIGHT = 480;
	bool keys[] = { false, false, false, false, false };
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	//Variables
	//todo?

	//Player Variable
	Sprite player;

	//Allegro Variables
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE* event_queue = NULL;
   ALLEGRO_TIMER* timer;

   //Program Init
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   display = al_create_display(WIDTH, HEIGHT);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }

   //addon init
   al_install_keyboard();
   al_init_image_addon();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
 
   //TODO initialize the font
   //ALLEGRO_FONT* font = al_load_font("college.ttf", 18, 0);

   //TODO this is where I init sprites & audio

   event_queue = al_create_event_queue();
   timer = al_create_timer(1.0 / 60);

   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_start_timer(timer);

   /*al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_rest(10.0);
	*/

   system("pause");
   al_destroy_timer(timer);
   al_destroy_event_queue(event_queue);

   al_destroy_display(display);
 
   return 0;
}

int collided(int x, int y)
{
	BLKSTR* blockdata;
	blockdata = MapGetBlock(x / mapblockwidth, y / mapblockheight);
	return blockdata->tl;
}

bool endValue(int x, int y)
{

	BLKSTR* data;
	data = MapGetBlock(x / mapblockwidth, y / mapblockheight);

	if (data->user1 == 8)
	{
		return true;
	}
	else
		return false;
}

void drawStatus(ALLEGRO_FONT* font, int counter, int width, int height) {
	al_draw_filled_rectangle(width - 76, 0, width, 20, al_map_rgb(255, 255, 255));
	al_draw_textf(font, al_map_rgb(0, 0, 0), width - 75, 0, 0, "Time: %i", counter);
}