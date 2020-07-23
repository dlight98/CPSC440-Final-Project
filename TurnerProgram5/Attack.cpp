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

	//image = NULL;
	//hit = NULL;

	hit = al_load_sample("fire1.wav");
	//image = resize_bitmap("PK_fire_air.png", 32, 32);
}

Attack::~Attack() {
	//al_destroy_bitmap(image);
	al_destroy_sample(hit);
}

void Attack::initAttack() {
	//hit = al_load_sample("fire1.wav");
	image = resize_bitmap("PK_fire_air.png", 32, 32);
	//image = al_load_bitmap("PK_fire_air.png");
}

void Attack::DrawAttack(int xoff, int yoff) {
	if (live) {
		al_draw_bitmap(image, x - xoff, y - yoff, 0);
	}
}

void Attack::FireAttack(Player player, int dire, int startx, int starty) {
	if (!live) {
		/*this->dir = dir;
		x = player->getX();
		y = player->getY();*/
		//initAttack();

		//image = resize_bitmap("PK_fire_air.png", 32, 32);
		image = al_load_bitmap("PK_fire_air.png");
		dir = dire;
		x = player.getX();
		y = player.getY();
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

ALLEGRO_BITMAP* resize_bitmap(const char* name, int target_width, int target_height) {
	//this simplifies scaling the bitmap to the size we want

	ALLEGRO_BITMAP* temp, * ret_val;    //temporary and return value

	ret_val = al_create_bitmap(target_width, target_height); //this is set up at the correct size
	temp = al_load_bitmap(name);


	al_set_target_bitmap(ret_val);
	al_draw_scaled_bitmap(temp, 0, 0,
		al_get_bitmap_width(temp), al_get_bitmap_height(temp),
		0, 0, target_width, target_height, 0);
	if (temp == NULL) {
		cout << "resize_bitmap temp is null" << endl;
		return NULL;
	}
	al_destroy_bitmap(temp);

	return ret_val;
}