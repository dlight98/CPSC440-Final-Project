/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#ifndef ENEMY_H
#define ENEMY_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "SpriteSheet.h"

class Enemy {

public:
	Enemy();
	~Enemy();
	void init(int width, int height, int max_health, char* file_name, char* samp);
	void hit();
	bool getLive() { return live; }
	void setLive(bool l) { live = l; }

private:
	Sprite enemy;
	ALLEGRO_SAMPLE* death;
	int health;
	bool live;
};

#endif