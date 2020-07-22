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
#include <iostream>
#include "SpriteSheet.h"
#include "Enemy.h"
#include "Player.h"
#include "mappy_A5.h"

using namespace std;
 
int collided(int x, int y);  //Tile Collision
bool endValue(int x, int y); //End Block with the User Value = 8
void drawStatus(ALLEGRO_FONT* font, int counter, int width, int height);
void drawIntro();
void drawEnd();

int main(int argc, char **argv){
 
	//Constants
	const int WIDTH = 900;	//FIXME screen size?
	const int HEIGHT = 480;
	const int TIME_PER_LEVEL = 60;	//seconds
	const int FPS = 60;
	bool keys[] = { false, false, false, false, false };
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	//Variables
	bool gameOver = false;
	bool levelOver = false;
	bool render = true;
	int level = 1;	//FIXME? level starts at 1 not 0
	int ani_dir = 5; //the direction the character should be facing
	int xOff = 0;	//used in determining if map should scroll
	int yOff = 0;	//used in determining if map should scroll


	//Player & Enemy Variables
	Player hero;	//Ness
	Enemy starman;	//starman	FIXME multiple of these
	Enemy deluxe;	//starman deluxe

	//Allegro Variables
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE* event_queue = NULL;
   ALLEGRO_SAMPLE* bgm = NULL;	//background music
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
   if (!al_install_audio()) {
	   return -1;
   }
   if (!al_init_acodec_addon()) {
	   return -1;
   }
   if (!al_reserve_samples(5)) {	//TODO FIXME
	   return -1;	//IMPORTANT without this only 1 sound will play --> need to put the number of audio files
   }

   //addon init
   al_install_keyboard();
   al_init_image_addon();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
 
   //TODO initialize the font
   //ALLEGRO_FONT* font = al_load_font("college.ttf", 18, 0);

   bgm = al_load_sample("battle against a clueless foe.wav");
   //this sound is taken royalty-free from the unused 
   //soundtrack of the unrealeased game "Oddity"
   //previously know as "Mother 4"
   //a fangame based on Earthbound
   if (!bgm) {
	   exit(9);
   }

   //TODO this is where I init sprites & audio
   hero.init(WIDTH, HEIGHT, "ness_spritesheet.bmp", "wow.wav");
   starman.init(WIDTH, HEIGHT, 1, 50, 70, 3, 3, "starman_sheet.png", "enemydie.wav");
   //deluxe.init(WIDTH, HEIGHT, 3, 50, 70, 2, 2, "starman_deluxe_sheet.png", "enemydie.wav");	//TODO init this

   if (MapLoad("temp.FMP", 1))
	   return -5;

   event_queue = al_create_event_queue();
   timer = al_create_timer(1.0 / FPS);

   srand(time(NULL));

   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_start_timer(timer);
   //draw the background tiles
   MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);

   //draw foreground tiles
   MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
   hero.DrawSprites(50, 50);
   hero.setX(50);
   hero.setY(50);
   al_play_sample(bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);	
   //background music is outside while loop so it doesn't reset

   starman.setLive(true);
   starman.setX(50);
   starman.setY(50);
   starman.DrawSprites(WIDTH / 2, HEIGHT / 2);


   while (!gameOver) {
	   ALLEGRO_EVENT ev;
	   al_wait_for_event(event_queue, &ev);
	   if (ev.type == ALLEGRO_EVENT_TIMER)
	   {
		   render = true;
		   if (keys[UP]) {
			   if (ani_dir == 5)
				   ani_dir = 3;
			   hero.movePlayer(WIDTH, HEIGHT, 3, ani_dir);
		   }
		   if (keys[DOWN]) {
			   if (ani_dir == 5)
				   ani_dir = 0;
			   hero.movePlayer(WIDTH, HEIGHT, 0, ani_dir);
		   }
		   if (keys[LEFT]) {
			   if (ani_dir == 5)
				   ani_dir = 1;
			   hero.movePlayer(WIDTH, HEIGHT, 1, ani_dir);
		   }
		   if (keys[RIGHT]) {
			   if (ani_dir == 5)
				   ani_dir = 2;
			   hero.movePlayer(WIDTH, HEIGHT, 2, ani_dir);
		   }
		   else
			   hero.movePlayer(WIDTH, HEIGHT, 5, ani_dir);
		   if (hero.Collision()) {	//FIXME ???
		   }
		   ani_dir = 5;

	   }
	   else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	   {
		   gameOver = true;
	   }
	   else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	   {
		   switch (ev.keyboard.keycode)
		   {
		   case ALLEGRO_KEY_ESCAPE:
			   gameOver = true;
			   break;
		   case ALLEGRO_KEY_UP:
			   keys[UP] = true;
			   break;
		   case ALLEGRO_KEY_DOWN:
			   keys[DOWN] = true;
			   break;
		   case ALLEGRO_KEY_LEFT:
			   keys[LEFT] = true;
			   break;
		   case ALLEGRO_KEY_RIGHT:
			   keys[RIGHT] = true;
			   break;
		   case ALLEGRO_KEY_SPACE:
			   keys[SPACE] = true;
			   break;

		   }
	   }
	   else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	   {
		   switch (ev.keyboard.keycode)
		   {
		   case ALLEGRO_KEY_ESCAPE:
			   gameOver = true;
			   break;
		   case ALLEGRO_KEY_UP:
			   keys[UP] = false;
			   break;
		   case ALLEGRO_KEY_DOWN:
			   keys[DOWN] = false;
			   break;
		   case ALLEGRO_KEY_LEFT:
			   keys[LEFT] = false;
			   break;
		   case ALLEGRO_KEY_RIGHT:
			   keys[RIGHT] = false;
			   break;
		   case ALLEGRO_KEY_SPACE:
			   keys[SPACE] = false;
			   break;
		   }
	   }
	   if (render && al_is_event_queue_empty(event_queue))
	   {
		   render = false;
		   
		   //update the map scroll position
		   xOff = hero.getX() + hero.getWidth() - WIDTH / 2;
		   yOff = hero.getY() + hero.getHeight() - HEIGHT / 2;

		   //avoid moving beyond the map edge
		   if (xOff < 0) xOff = 0;

		   if (xOff > (mapwidth * mapblockwidth - WIDTH))
			   xOff = mapwidth * mapblockwidth - WIDTH;
		   if (yOff < 0)
			   yOff = 0;
		   if (yOff > (mapheight * mapblockheight - HEIGHT))
			   yOff = mapheight * mapblockheight - HEIGHT;

		   //draw the background tiles
		   MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);

		   //draw foreground tiles
		   MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
		   hero.DrawSprites(xOff, yOff);
		   if (starman.getLive()) {	//DEBUG
			   starman.DrawSprites(WIDTH / 2, HEIGHT / 2);
		   }
		   levelOver = hero.Collision();
		   if (levelOver && level >= 3) {	//checks if game is over
			   gameOver = true;
		   }
		   //counter = al_get_time() - start_time - 1;	//-1 to offset the loading time

		   /*drawStatus(font, counter, WIDTH, HEIGHT);*/
		   al_flip_display();
		   al_clear_to_color(al_map_rgb(0, 0, 0));

	   }
	   if (gameOver == true)
		   break;
   } 	

   //FIXME don't know order around the system("pause") for deallocating memory
   al_destroy_event_queue(event_queue);
   al_destroy_timer(timer);
   al_destroy_sample(bgm);
   system("pause");
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

void drawIntro() {
	//TODO
}

void drawEnd() {
	//TODO
}
