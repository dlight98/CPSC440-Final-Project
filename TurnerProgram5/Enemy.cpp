/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>

#include "Enemy.h"

Enemy::Enemy() {
	death = NULL;
	health = 1;	//temp setting
	live = false;
}

Enemy::~Enemy() {
	badGuy.~Sprite();
	al_destroy_sample(death);
}

void Enemy::init(int width, int height, int max_health, int fw, int fh, int max, int col, char* file_name, char* samp) {
	badGuy.InitEnemySprites(width, height, fw, fh, max, col, file_name, al_map_rgb(147, 187, 236));
	death = al_load_sample(samp);
	health = max_health;
}

void Enemy::hit() {
	health -= 1;
}

//FIXME
void Enemy::moveEnemy(int width, int height, int dir, int ani_dir) {
	
	//should move automatically towards Ness
	badGuy.UpdateSprites(width, height, dir, ani_dir);

}

void Enemy::CollideEnemy(Player& player, Sprite hero) {
	if (live)
	{
		if (badGuy.getX() - badGuy.getBoundX() < hero.getX() + hero.getBoundX() &&
			badGuy.getX() + badGuy.getBoundX() > hero.getX() - hero.getBoundX() &&
			badGuy.getY() - badGuy.getBoundY() < hero.getY() + hero.getBoundY() &&
			badGuy.getY() + badGuy.getBoundY() > hero.getY() - hero.getBoundY())
		{
			//TODO remove player life
			live = false;
			al_play_sample(death, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		else if (badGuy.getX() < 0)
		{
			live = false;
		}
	}
}

void Enemy::DrawSprites(int xoffset, int yoffset) {
	badGuy.DrawSprites(xoffset, yoffset);
}

bool Enemy::Collision() {
	return badGuy.CollisionEndBlock();
}
float Enemy::getX() {
	return badGuy.getX();
}
float Enemy::getY() {
	return badGuy.getY();
}
void Enemy::setX(float sx) {
	badGuy.setX(sx);
}
void Enemy::setY(float sy) {
	badGuy.setY(sy);
}
int Enemy::getWidth() {
	return badGuy.getWidth();
}
int Enemy::getHeight() {
	return badGuy.getHeight();
}