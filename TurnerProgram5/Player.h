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
	void DrawSprites(int xoffset, int yoffset);
	//void removeLife()
	bool Collision();

	//the following are used in getting and setting
	//information related to the hero sprite
	float getX();
	float getY();
	void setX(float sx);
	void setY(float sy);
	int getWidth();
	int getHeight();
private:
	Sprite hero;
	ALLEGRO_SAMPLE* ouch;
};

#endif