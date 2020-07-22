/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#ifndef PLAYER_H
#define PLAYER_H
#include "SpriteSheet.h"

class Player {

public:
	//todo
	Player();
	Player(int width, int height, char* file_name);
	~Player();
	void movePlayer(int width, int height, int dir, int ani_dir);
private:
	Sprite hero;

};

#endif