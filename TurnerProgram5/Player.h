/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#ifndef PLAYER_H
#define PLAYER_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "SpriteSheet.h"

class Player {

public:
	//todo
	Player();
	~Player();
	void init(int width, int height, char* file_name, char* samp);
	void movePlayer(int width, int height, int dir, int ani_dir);
private:
	Sprite hero;
	ALLEGRO_SAMPLE* hit;
};

#endif