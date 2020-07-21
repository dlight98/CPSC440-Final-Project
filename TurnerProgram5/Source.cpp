/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "SpriteSheet.h"
#include "mappy_A5.h"
 
int collided(int x, int y);  //Tile Collision
bool endValue(int x, int y); //End Block with the User Value = 8
void drawStatus(ALLEGRO_FONT* font, int counter, int width, int height);

int main(int argc, char **argv){
 
   ALLEGRO_DISPLAY *display = NULL;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   display = al_create_display(640, 480);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }
 
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_rest(10.0);
 
   al_destroy_display(display);
   system("pause");
 
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