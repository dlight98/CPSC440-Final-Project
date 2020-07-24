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
	Sprite getBad() { return badGuy; }
	void init(int width, int height, int max_health, int fw, int fh, int max, int col, char* file_name, char* samp);
	void hit();
	bool getLive() { return live; }
	void setLive(bool l) { live = l; }
	void CollideHero(Player player, Sprite hero, int xoffset, int yoffset, int& life);

	void startEnemy(int sx, int sy);
	void moveEnemy(int width, int height, int xp, int yp);
	void DrawSprites(int xoffset, int yoffset);
	bool Collision();
	void printDebug(int num);
	void Die();
	int getHealth() { return health; }
	void setHealth(int h) { health = h; }
	//the following are used in getting and setting
	//information related to the enemy sprite
	int getX();
	int getY();
	void setX(int sx);
	void setY(int sy);
	int getWidth();
	int getHeight();
private:
	Sprite badGuy;
	ALLEGRO_SAMPLE* death;
	int health;
	int MAX_HEALTH;
	int death_loop;
	bool live;
};

#endif