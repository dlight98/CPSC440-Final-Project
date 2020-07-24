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
	speed = 3;
	//FIXME change angles to dir
	radian_angle = 257.6;
	orig_angle = 257.6;

	image = NULL;
	fire = al_load_sample("fire1.wav");
}

Attack::~Attack() {
	//al_destroy_bitmap(image);
	al_destroy_sample(fire);
}

void Attack::DrawAttack(int xoff, int yoff) {
	if (live) {
		al_draw_scaled_bitmap(image, 0,0,
			al_get_bitmap_width(image), al_get_bitmap_height(image),
			x - xoff, y - yoff,32,32, 0);
	}
}

void Attack::FireAttack(Player player, int dire, int startx, int starty) {
	if (!live) {
		al_play_sample(fire, .25, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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
			y += speed;
		}
		else if (dir == 1) {
			x -= speed;
		}
		else if (dir == 2) {
			x += speed;
		}
		else if (dir == 3) {
			y -= speed;
		}

		if (y <= 0 || x <= 0 || y >= h || x >= w) {
			live = false;
		}
	}
}
void Attack::CollideAttack(Enemy enemy[], int cSize, int& score, int &num_beat) {
	if (live) {
		for (int i = 0; i < cSize; i++) {
			
			int ex = enemy[i].getBad().getX();	//enemy x
			int ebx = enemy[i].getBad().getBoundX(); //enemy bound x
			int ey = enemy[i].getBad().getY();
			int eby = enemy[i].getBad().getBoundY();
			int hx = x;
			int hy = y;
			int hbx = x + 32;	//the frame width & height is 32
			int hby = y + 32;

			if (((ex < hx && ebx > hx) || (ex > hx && ebx < hx) ||
				(ex < hbx && ebx > hbx) || (ex > hbx && ebx < hbx)) &&
				((ey < hy && eby > hy) || (eby > hby && ey < hby)
					))
			{
				//cout << "hit enemy" << endl;	//DEBUG
				if (enemy[i].getHealth() != 0 && enemy[i].getLive() == true) {
					enemy[i].hit();
					live = false;
					num_beat++;
					score++;
				}
			}
		}
	}
}

ALLEGRO_BITMAP* Attack::debugDraw(int gx, int gy) {	//DEBUG for seeing that it draws correctly
	return image;
}

