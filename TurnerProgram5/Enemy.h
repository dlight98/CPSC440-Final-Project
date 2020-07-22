/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#ifndef ENEMY_H
#define ENEMY_H
#include "SpriteSheet.h"

class Enemy {

public:
	Enemy() {};
	Enemy(int width, int height, char* file_name);
	~Enemy();
private:
	Sprite enemy;

};

#endif