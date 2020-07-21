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
using namespace std;
class Sprite
{
	friend int collided(int x, int y);
	friend bool endValue( int x, int y );
public:
	Sprite();
	~Sprite();
	void InitSprites(int width, int height);
	void UpdateSprites(int width, int height, int dir, int ani_dir); //dir 1 = right, 0 = left, 2 = Standing Still
	void DrawSprites(int xoffset, int yoffset);
	float getX() {return x;}
	float getY() {return y;}
	void setX(float sx) { x = sx; }
	void setY(float sy) { y = sy; }
	int getWidth() {return frameWidth;}
	int getHeight() {return frameHeight;}
	bool CollisionEndBlock();

private:
	float x;
	float y;

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