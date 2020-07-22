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
#include "Player.h"

class Enemy {

public:
	Enemy();
	~Enemy();
	void init(int width, int height, int max_health, int fw, int fh, int max, int col, char* file_name, char* samp);
	void hit();
	bool getLive() { return live; }
	void setLive(bool l) { live = l; }
	void CollideEnemy(Player& player, Sprite hero);

	void moveEnemy(int width, int height, int dir, int ani_dir);
	void DrawSprites(int xoffset, int yoffset);
	bool Collision();

	//the following are used in getting and setting
	//information related to the enemy sprite
	float getX();
	float getY();
	void setX(float sx);
	void setY(float sy);
	int getWidth();
	int getHeight();
private:
	Sprite badGuy;
	ALLEGRO_SAMPLE* death;
	int health;
	bool live;
};

#endif