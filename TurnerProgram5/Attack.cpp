/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include "Attack.h"

#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include <iostream>

Attack::Attack() {
	pi = 3.14;
	x = 350;
	y = 400;
	live = false;
	speed = 5;
	//FIXME change angles to dir
	radian_angle = 257.6;
	orig_angle = 257.6;

	image = NULL;
	hit = NULL;
}
Attack::~Attack() {
	//al_destroy_bitmap(image);
	al_destroy_sample(hit);
}

void Attack::DrawAttack() {

}

void Attack::FireAttack(Player* player, int dir, int startx, int starty) {
	if (!live) {
		/*this->dir = dir;
		x = player->getX();
		y = player->getY();*/
		this->dir = player->getDir();
		x = player->getX();
		y = player->getY();
		live = true;
	}
}
void Attack::UpdateAttack(int w, int h) {
	if (live) {
		if (dir == 0) {
			x += 2;
		}
		else if (dir == 1) {
			y -= 2;
		}
		else if (dir == 2) {
			x += 2;
		}
		else if (dir == 3) {
			y += 2;
		}

		if (y <= 0 || x <= 0 || y >= h || x >= w) {
			live = false;
		}
	}
}
void Attack::CollideAttack(Enemy enemy[], int cSize, int& score) {

}

ALLEGRO_BITMAP* Attack::debugDraw(int gx, int gy) {	//DEBUG for seeing that it draws correctly
	return image;
}