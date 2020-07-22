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
	ouch = NULL;
}

Player::~Player() {
	hero.~Sprite();
	al_destroy_sample(ouch);
}

void Player::init(int width, int height, char* file_name, char* samp) {
	hero.InitHeroSprites(width, height, file_name, al_map_rgb(255, 255, 255));
	ouch = al_load_sample(samp);

}

void Player::movePlayer(int width, int height, int dir, int ani_dir) {
	hero.UpdateSprites(width, height, dir, ani_dir);
}


bool Player::Collision() {
	return hero.CollisionEndBlock();
}
void Player::DrawSprites(int xoffset, int yoffset) {
	hero.DrawSprites(xoffset, yoffset);
}
float Player::getX() {
	return hero.getX();
}
float Player::getY() {
	return hero.getY();
}
void Player::setX(float sx) {
	hero.setX(sx);
}
void Player::setY(float sy) {
	hero.setY(sy);
}
int Player::getWidth() {
	return hero.getWidth();
}
int Player::getHeight() {
	return hero.getHeight();
}