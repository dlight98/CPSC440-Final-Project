/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>

#include "Enemy.h"

Enemy::Enemy() {
	death = NULL;
}

void Enemy::init(int width, int height, char* file_name, char* samp) {
	enemy.InitSprites(width, height, file_name, al_map_rgb(147,187,236));
	death = al_load_sample(samp);
}

Enemy::~Enemy() {
	enemy.~Sprite();
	al_destroy_sample(death);
}