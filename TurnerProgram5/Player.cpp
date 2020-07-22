/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include <allegro5/allegro.h>

#include "Player.h"
#include "SpriteSheet.h"


Player::Player(int width, int height, char* file_name) {
	hero.InitSprites(width, height, file_name);
}

Player::~Player() {
	hero.~Sprite();
}

void Player::movePlayer(int width, int height, int dir, int ani_dir) {
	hero.UpdateSprites(width, height, dir, ani_dir);
}