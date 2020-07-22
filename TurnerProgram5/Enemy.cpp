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
	health = 1;	//temp setting
	live = false;
}

Enemy::~Enemy() {
	enemy.~Sprite();
	al_destroy_sample(death);
}

void Enemy::init(int width, int height, int max_health, char* file_name, char* samp) {
	enemy.InitEnemySprites(width, height, file_name, al_map_rgb(147, 187, 236));
	death = al_load_sample(samp);
	health = max_health;
}

void Enemy::hit() {
	health -= 1;
}