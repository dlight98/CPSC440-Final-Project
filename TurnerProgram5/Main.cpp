/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include "SpriteSheet.h"
#include "Enemy.h"
#include "Player.h"
#include "Attack.h"
#include "mappy_A5.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <iostream>



/*
HOW TO PLAY
arrow keys move
space to shoot
the goal is to shoot the starmen approaching
each level increases the number to be defeated by 10
*/




using namespace std;
 
int collided(int x, int y);  //Tile Collision
bool endValue(int x, int y); //End Block with the User Value = 8
void drawStatus(ALLEGRO_FONT* font, int level, int remaining, int lives, int width, int height);
void drawIntro();
void drawEnd();

int main(int argc, char **argv){
 
	//Constants
	const int WIDTH = 900;
	const int HEIGHT = 480;
	const int TRUE_HEIGHT = 580;	//gives space for the status bar
	const int TIME_PER_LEVEL = 60;	//seconds
	const int FPS = 60;
	const int MAX_LIVES = 3;
	const int NUM_BAD1 = 5;	//the weaker enemy starman
	const int NUM_BAD2 = 2;		//the stronger enemy starman deluxe
	const int NUM_SHOOT = 10;	//number of shots allowed out
	bool keys[] = { false, false, false, false, false };
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

	//Variables
	bool gameOver = false;
	bool levelOver = false;
	bool render = true;
	int level = 1;	//level starts at 1 not 0
	int score = 0;
	int lvl_defeat1 = 0;		//the number of starmen defeated this level
	int lvl_defeat2 = 0;		//the number of deluxe beaten this level
	int lvl_need1 = NUM_BAD1 * 2;	//starmen needed to be defeated this level
	int lvl_need2 = NUM_BAD2 * 2;	//deluxe needed to be defeated this level
	int ani_dir = 5; //the direction the character should be facing
	int dirs = 0;	//the direction the shot goes
	int xOff = 0;	//used in determining if map should scroll
	int yOff = 0;	//used in determining if map should scroll
	int count = 0;	//used to see when to shoot again
	int h_lives = MAX_LIVES;	//lives for player

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
 
   display = al_create_display(WIDTH, TRUE_HEIGHT);
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
   ALLEGRO_FONT* font = al_load_font("Bleeding_Cowboys.ttf", 18, 0);

   bgm = al_load_sample("battle against a clueless foe.wav");
   //this sound is taken royalty-free from the unused 
   //soundtrack of the unrealeased game "Oddity"
   //previously know as "Mother 4"
   //a fangame based on Earthbound
   if (!bgm) {
	   exit(9);
   }

   //Player, Enemy, Attack Variables
   //Player hero("wow.wav");	//Ness
   Player hero("wow.wav", "ness_spritesheet.bmp", al_map_rgb(255, 255, 255));	//Ness

   /*Enemy starman[NUM_BAD1] = { Enemy("starman_sheet.png", al_map_rgb(147, 187, 236)),
		Enemy("starman_sheet.png", al_map_rgb(147, 187, 236)), Enemy("starman_sheet.png", al_map_rgb(147, 187, 236)) ,
		Enemy("starman_sheet.png", al_map_rgb(147, 187, 236)), Enemy("starman_sheet.png", al_map_rgb(147, 187, 236)) };	//starman
	*/   
   Enemy starman[NUM_BAD1];		//DEBUG BREAK
	//Enemy deluxe[NUM_BAD2];	//starman deluxe	FIXME multiple of these
   Attack shoot[NUM_SHOOT];	//number 

   //this is where I init sprites & audio
   hero.init(WIDTH, HEIGHT, "ness_spritesheet.bmp", "wow.wav");
   /*for (int i = 0; i < NUM_BAD1; i++) {
	   starman[i].init(WIDTH, HEIGHT, 1, 50, 70, 3, 3, "starman_sheet.png", "enemydie.wav");

   }*/
   //deluxe.init(WIDTH, HEIGHT, 3, 50, 70, 2, 2, "starman_deluxe_sheet.png", "enemydie.wav");	//TODO init this



   if (MapLoad("area1.FMP", 1))
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
   hero.setX(WIDTH /2);
   hero.setY(HEIGHT / 2);
   hero.DrawSprites(WIDTH / 2, HEIGHT / 2);
   al_play_sample(bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);	
   //background music is outside while loop so it doesn't reset

   while (!gameOver) {

	   if (levelOver == true) {
		   al_clear_to_color(al_map_rgb(0, 0, 0));
		   level++;
		   lvl_defeat1 = 0;
		   //lvl_defeat2 = 0;
		   lvl_need1 = (NUM_BAD1 * 2) + (10 * level);
		   //lvl_need2 = (NUM_BAD2 * 2) * (level / 2);
		   MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
		   hero.setX(WIDTH / 2);
		   hero.setY(HEIGHT / 2);
		   hero.DrawSprites(WIDTH / 2, HEIGHT / 2);
		   for (int i = 0; i < NUM_BAD1; i++) {
			   starman[i].setLive(false);
			   starman[i].setHealth(-1);
		   }
		   al_flip_display();
		   levelOver = false;
		   //al_rest(3.0);
	   }

	   ALLEGRO_EVENT ev;
	   al_wait_for_event(event_queue, &ev);
	   if (ev.type == ALLEGRO_EVENT_TIMER)
	   {
		   render = true;
		   //Updates the hero character
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
		   else {
			   hero.movePlayer(WIDTH, HEIGHT, 5, ani_dir);
			}
		   if(ani_dir != 5)
			   dirs = ani_dir;	//this determines the way the attacks fly

			//update attack
		   for (int i = 0; i < NUM_SHOOT; i++) {
			   if (shoot[i].getLive() == true) {
				   shoot[i].UpdateAttack(WIDTH, HEIGHT);
			   }
		   }

		   //spawn enemies
		   if (count % 60 == 0 && lvl_defeat1 < lvl_need1) {	//FIXME should be &&
				for (int i = 0; i < NUM_BAD1; i++) {
				   if (starman[i].getLive() == false && starman[i].getHealth() <= 0) {
					   int num = rand() % 4;	//0 = top, 1 = bottom, 2 = left, 3 = right
					   int xspot = -1;
					   int yspot = -1;
					   if (num == 0) {
						   //top
						   xspot = (rand() % 140) + 384 + 32;
						   yspot = 75;
					   }
					   else if (num == 1) {
						   //bottom
						   xspot = (rand() % 140) + 384 + 32;
						   yspot = HEIGHT - 75;
					   }
					   else if (num == 2) {
						   //left
						   xspot = 55;
						   yspot = (rand() % 26) + 224 + 32;
					   }
					   else if (num == 3) {
						   //right
						   xspot = WIDTH - 55;
						   yspot = (rand() % 26) + 224 + 32;
					   }
					   if (xspot != -1) {
						   starman[i].init(WIDTH, HEIGHT, 1, 50, 70, 3, 3, "starman_sheet.png", "enemydie.wav");
						   starman[i].startEnemy(xspot, yspot);
					   }
					   //break;
				   }
			   }
		   }

		   //update enemies
		   for (int i = 0; i < NUM_BAD1; i++) {	//DEBUG
				starman[i].moveEnemy(WIDTH, HEIGHT, hero.getHero().getX(), hero.getHero().getY());
				   /*if (!(starman[i].getLive() == true && starman[i].getHealth() >= 0)) {
					   break;
				   }*/
		   }

		   //check attack collision with enemy
		   for (int i = 0; i < NUM_BAD1; i++) {
			   shoot[i].CollideAttack(starman, lvl_need1, score, lvl_defeat1);
		   }

		   //check BOTH enemy collision with hero
		   for (int i = 0; i < NUM_BAD1; i++) {
			   starman[i].CollideHero(hero, hero.getHero(), xOff, yOff, h_lives);
		   }

		   //spawn attack
		   if (keys[SPACE]) {
			   if (count % 20 == 0) {
				   for (int i = 0; i < NUM_SHOOT; i++) {
					   if (shoot[i].getLive() == false) {
						   shoot[i].FireAttack(hero, dirs, hero.getHero().getX(), hero.getHero().getY());
						   break;
					   }
				   }
			   }
		   }

		   if (lvl_defeat1 >= lvl_need1) {
			   levelOver = true;
		   }

		   render = true;
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
			   if (ani_dir == 3) {
				   ani_dir = 5;
			   }
			   keys[UP] = false;
			   break;
		   case ALLEGRO_KEY_DOWN:
			   if (ani_dir == 0) {
				   //ani_dir = 5;
			   }
			   keys[DOWN] = false;
			   break;
		   case ALLEGRO_KEY_LEFT:
			   if (ani_dir == 1) {
				   ani_dir = 5;
			   }
			   keys[LEFT] = false;
			   break;
		   case ALLEGRO_KEY_RIGHT:
			   if (ani_dir == 2) {
				   ani_dir = 5;
			   }
			   keys[RIGHT] = false;
			   break;
		   case ALLEGRO_KEY_SPACE:
			   keys[SPACE] = false;
			   for (int i = 0; i < NUM_SHOOT; i++) {
				   if (shoot[i].getLive() == false) {
					   shoot[i].FireAttack(hero, dirs, hero.getHero().getX(), hero.getHero().getY());
					   break;
				   }
			   }
			   break;
		   case ALLEGRO_KEY_E:	//DEBUG printed
			   starman[0].printDebug(0);
			   break;
		   case ALLEGRO_KEY_D:	//DEBUG printed
			   hero.printDebug();
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

		   //draw foreground tiles and hero
		   MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
		   hero.DrawSprites(xOff, yOff);

		   //Draws enemies
		   for (int i = 0; i < NUM_BAD1; i++) {	//FIXME should be changing based on level
			   if (starman[i].getLive() == true) {	//DEBUG
				   starman[i].DrawSprites(xOff, yOff);
			   }
		   }

		   //Draws attacks
		   for (int i = 0; i < NUM_SHOOT; i++) {
			   if (shoot[i].getLive() == true) {
				   shoot[i].DrawAttack(xOff, yOff);
			   }
		   }
		   if (h_lives == 0) {
			   gameOver = true;
		   }
		   count++;
		   drawStatus(font, level, lvl_need1-lvl_defeat1, h_lives, WIDTH, TRUE_HEIGHT);
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

void drawStatus(ALLEGRO_FONT* font, int level, int remaining, int lives, int width, int height) {
	//TODO make it have 
	//lives bar

	al_draw_line(0, height - 100, width, height - 100, al_map_rgb(255, 255, 0), 2);
	for (int i = 0; i < 5; i++) {
		if (lives > i) {
			al_draw_filled_circle(20 + 20 * i, height - (height - (height - 100)) / 2, 10, al_map_rgb(219, 79, 144));
		}
	}
	al_draw_textf(font, al_map_rgb(255, 255, 255), 75, height - 75, 0, "Level: %i", level);
	al_draw_textf(font, al_map_rgb(255, 255, 255), width - 100, height - 75, 0, "Left: %i", remaining);
	//al_draw_filled_rectangle(width - 76, 0, width, 20, al_map_rgb(255, 255, 255));
	//al_draw_textf(font, al_map_rgb(0, 0, 0), width - 75, 0, 0, "Time: %i", counter);

}

void drawIntro() {
	//TODO
	//add warning for flashing lights
}

void drawEnd() {
	//TODO
}
