/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>

#include "Player.h"

Player::Player() {
	hit = NULL;
}

void Player::init(int width, int height, char* file_name, char* samp) {
	hero.InitSprites(width, height, file_name, al_map_rgb(255,255,255));
	hit = al_load_sample(samp);
	
}

Player::~Player() {
	hero.~Sprite();
	al_destroy_sample(hit);
}

void Player::movePlayer(int width, int height, int dir, int ani_dir) {
	hero.UpdateSprites(width, height, dir, ani_dir);
}