/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#ifndef ATTACK_H
#define ATTACK_H
#include "Enemy.h"
#include "Player.h"

#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Attack {
public:
	Attack();
	~Attack();

	void DrawAttack(int xoff, int yoff);
	void FireAttack(Player player, int dire, int startx, int starty);
	void UpdateAttack(int w, int h);
	void initAttack();
	void CollideAttack(Enemy enemy[], int cSize, int& score);
	bool getLive() { return live; }
	ALLEGRO_BITMAP* debugDraw(int gx, int gy);
private:
	int pi;
	float x;
	float y;
	bool live;
	int speed;
	float radian_angle;
	float orig_angle; //the angle it was fired from
	int dir;	//
	ALLEGRO_BITMAP* image;
	ALLEGRO_SAMPLE* hit;
};

#endif