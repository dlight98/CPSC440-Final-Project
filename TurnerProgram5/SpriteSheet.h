/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#ifndef SPRITESHEET_H
#define SPRITESHEET_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <fstream>

using namespace std;
class Sprite
{
	friend int collided(int x, int y);
	friend bool endValue( int x, int y );
public:
	Sprite();
	~Sprite();
	void InitHeroSprites(int width, int height, char* name, ALLEGRO_COLOR color);
	void InitEnemySprites(int width, int height, int fw, int fh, int max, int col, char* name, ALLEGRO_COLOR color);
	void UpdateSprites(int width, int height, int dir, int ani_dir); //dir 0 = down, 1 = left, 2 = right, 3 = left
	void UpdateEnemySprites(int width, int height, int dir, int ani_dir);
	void DrawSprites(int xoffset, int yoffset);
	void DrawEnemySprites(int xoffset, int yoffset);
	void EnemyDie();
	int getWidth() { return frameWidth; }
	int getHeight() { return frameHeight; }
	void setX(int sx) { x = sx; }
	void setY(int sy) { y = sy; }
	int getX() { return x; }
	int getY() { return y; }
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	bool CollisionEndBlock();

private:
	int x;
	int y;

	int boundx;
	int boundy;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationRows;
	int animationDirection;
	int WIDTH;
	int HEIGHT;

	ALLEGRO_BITMAP *image;
};

#endif