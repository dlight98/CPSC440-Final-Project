/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include "Enemy.h"

#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>


Enemy::Enemy() {
	death = NULL;
	health = -3;	//FIXME temp
	live = false;
	death_loop = 0;
	//badGuy;
}

Enemy::Enemy(char* name, ALLEGRO_COLOR color) {
	death = NULL;
	live = false;
	death_loop = 0;
	health = -3;
	//badGuy(name, color);
}

Enemy::~Enemy() {
	badGuy.~Sprite();
	//al_destroy_sample(death);
}

void Enemy::init(int width, int height, int max_health, int fw, int fh, int max, int col, char* file_name, char* samp) {
	badGuy.InitEnemySprites(width, height, fw, fh, max, col, file_name, al_map_rgb(147, 187, 236));
	live = true;
	death = al_load_sample(samp);
	MAX_HEALTH = max_health;
	health = -3;
}

void Enemy::startEnemy(int sx, int sy) {
	health = MAX_HEALTH;
	live = true;
	death_loop = 0;
	badGuy.setX(sx);
	badGuy.setY(sy);
}

void Enemy::hit() {
	if (health > 0) {
		health--;
	}
	else if(health == 0) {
		
		al_play_sample(death, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

void Enemy::moveEnemy(int width, int height, int xp, int yp) {
	//xp and yp are the players
	//x and y coordinates
	/*if (live == false && health == 0) {
		badGuy.~Sprite();
	}
	else */if (live) {	//DEBUG BREAK
		//should move automatically towards Ness
		badGuy.UpdateEnemySprites(width, height, xp, yp, health, death_loop, live);	//TEMP
	}


}

void Enemy::CollideHero(Player player, Sprite hero, int xoffset, int yoffset, int &life) {
	if (live && health > 0)
	{
		int ex = badGuy.getX();	//enemy x
		int ebx = badGuy.getBoundX(); //enemy bound x
		int ey = badGuy.getY();
		int eby = badGuy.getBoundY();
		int hx = hero.getX();
		int hbx = hero.getBoundX();
		int hy = hero.getY();
		int hby = hero.getBoundY();
		
		if (((ex < hx && ebx > hx) || (ex > hx && ebx < hx) ||
			(ex < hbx && ebx > hbx)|| (ex > hbx && ebx < hbx)) &&
			((ey < hy && eby > hy) || (eby > hby && ey < hby)
			))
		{
			life--;
			player.playOuch();
			health = 0;
		}
		
	}
}

void Enemy::Die() {
	al_play_sample(death, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

}

void Enemy::DrawSprites(int xoffset, int yoffset) {
	badGuy.DrawEnemySprites(xoffset, yoffset);
}

bool Enemy::Collision() {
	return badGuy.CollisionEndBlock();
}
int Enemy::getX() {
	return badGuy.getX();
}
int Enemy::getY() {
	return badGuy.getY();
}
void Enemy::setX(int sx) {
	badGuy.setX(sx);
}
void Enemy::setY(int sy) {
	badGuy.setY(sy);
}
int Enemy::getWidth() {
	return badGuy.getWidth();
}
int Enemy::getHeight() {
	return badGuy.getHeight();
}

void Enemy::printDebug(int num) {
	printf("enemy #%i x and bx: %i, %i\n", num, badGuy.getX(), badGuy.getBoundX());
	printf("enemy #%i y and by: %i, %i\n", num, badGuy.getY(), badGuy.getBoundY());

}

int Enemy::getHealth() { return health; }

bool Enemy::getLive() { return live; }