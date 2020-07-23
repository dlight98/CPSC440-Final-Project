/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include "Player.h"

#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>

Player::Player() {
	ouch = NULL;
	dir = 5;
}

Player::Player(char* samp) {
	ouch = al_load_sample(samp);
	dir = 5;
}

Player::~Player() {
	hero.~Sprite();
	//al_destroy_sample(ouch);
}

void Player::init(int width, int height, char* file_name, char* samp) {
	ouch = al_load_sample(samp);
	hero.InitHeroSprites(width, height, file_name, al_map_rgb(255, 255, 255));

}

void Player::movePlayer(int width, int height, int dir, int ani_dir) {
	hero.UpdateSprites(width, height, dir, ani_dir);
	dir = ani_dir;	//use dir with which way the attack fires
					//FIXME might want to use dir instead?
}

void Player::playOuch() {
	al_play_sample(ouch, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

bool Player::Collision() {
	return hero.CollisionEndBlock();
}
void Player::DrawSprites(int xoffset, int yoffset) {
	hero.DrawSprites(xoffset, yoffset);
}
int Player::getX() {
	return hero.getX();
}
int Player::getY() {
	return hero.getY();
}
void Player::setX(int sx) {
	hero.setX(sx);
}
void Player::setY(int sy) {
	hero.setY(sy);
}
int Player::getWidth() {
	return hero.getWidth();
}
int Player::getHeight() {
	return hero.getHeight();
}

void Player::printDebug() {
	printf("hero x and bx: %i, %i\n", hero.getX(), hero.getBoundX());
	printf("hero y and by: %i, %i\n", hero.getY(), hero.getBoundY());
}
