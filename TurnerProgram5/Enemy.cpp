/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include <allegro5/allegro.h>
#include "Enemy.h"
#include "SpriteSheet.h"


Enemy::Enemy(int width, int height, char* file_name) {
	enemy.InitSprites(width, height, file_name);
}

Enemy::~Enemy() {
	enemy.~Sprite();
}