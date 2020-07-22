/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include "SpriteSheet.h"

Sprite::Sprite()
{
	image=NULL;
}
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}
void Sprite::InitHeroSprites(int width, int height, char* name, ALLEGRO_COLOR color)
{
	x = 80;
	y = -10;

	WIDTH = width;
	HEIGHT = height;

	maxFrame = 16;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 30;
	frameHeight = 40;
	animationColumns = 4;
	animationRows = 4;
	animationDirection = 2;
	//0 = down, 1 = left, 2 = right, 3 = up

	image = al_load_bitmap(name);
	al_convert_mask_to_alpha(image, color);
}

void Sprite::InitEnemySprites(int width, int height, char* name, ALLEGRO_COLOR color)
{
	x = 0;
	y = -0;

	WIDTH = width;
	HEIGHT = height;

	/*maxFrame = 16;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 30;
	frameHeight = 40;
	animationColumns = 4;
	animationRows = 4;
	animationDirection = 2;*/
	//0 = down, 1 = left, 2 = right, 3 = up

	image = al_load_bitmap(name);
	al_convert_mask_to_alpha(image, color);
}


void Sprite::UpdateSprites(int width, int height, int dir, int ani_dir)
{
	int oldx = x;
	int oldy = y;
	animationDirection = ani_dir;

	if (dir == 2) { //right key
		x += 2;
		if (++frameCount > frameDelay && ani_dir == 2)
		{
			if (curFrame < 8) //Ness is facing right in frames 8 to 11
				curFrame = 8;
			frameCount = 0;
			if (++curFrame > 11)
				curFrame = 8;
		}
		animationDirection = 2;
	}
	else if (dir == 1) { //left key
		x -= 2;
		if(++frameCount > frameDelay && ani_dir == 1)
		{
			if (curFrame < 4) //Ness is facing left in frames 4 to 7
				curFrame = 4;
			frameCount = 0;
			if (++curFrame > 7)
				curFrame = 4;
		}
		animationDirection = 1;
	}
	else if (dir == 0) {	//down key
		y += 2;
		if (y + frameHeight >= HEIGHT) {
			y = oldy;
		}
		if (++frameCount > frameDelay) {
			if (curFrame < 0) //Ness is facing doown in frames 0 to 3
				curFrame = 0;
			frameCount = 0;
			if (++curFrame > 3)
				curFrame = 0;
		}
		animationDirection = 0;

	}
	else if (dir == 3) {	//up key
		y -= 2;
		if (y < 0) {
			y = oldy;
		}

		if (++frameCount > frameDelay) {
			if (curFrame < 12) //Ness is facing up in frames 12 to 15
				curFrame = 12;
			frameCount = 0;
			if (++curFrame > 15)
				curFrame = 12;
		}
		animationDirection = 3;
	}
	else //represent that they hit the space bar and that mean direction = 0
		animationDirection = 5;

	//check for collided with foreground tiles
	if (animationDirection == 0) {//collision down
		if (collided(x, y + frameHeight) || collided(x + frameWidth, y + frameHeight)) {	
			x = oldx;
			y = oldy;
		}
	}
	else if (animationDirection == 1)//collision detection to the left
	{ 
		if (collided(x, y + frameHeight) || collided(x,y)|| collided(x, y + frameHeight / 2)) { 
			x = oldx; 
			y= oldy;
		}

	}
	else if (animationDirection == 2)//collision detection to the right
	{ 
		if (collided(x + frameWidth, y + frameHeight) || collided(x+frameWidth, y) || collided(x+frameWidth, y + frameHeight/2)) {
			x = oldx; 
			y= oldy;
		}
	}
	else if (animationDirection == 3) {//collision up
		if (collided(x, y) || collided(x + frameWidth, y)) {	
			x = oldx;
			y = oldy;
		}
	}

}

bool Sprite::CollisionEndBlock()
{
	if (endValue(x + frameWidth/2, y + frameHeight + 5))
		return true;
	else
		return false;
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
}