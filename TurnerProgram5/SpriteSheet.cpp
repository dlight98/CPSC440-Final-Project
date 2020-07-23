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
	//al_destroy_bitmap(image);
}
void Sprite::InitHeroSprites(int width, int height, char* name, ALLEGRO_COLOR color)
{
	x = width / 2;
	y = height / 2;

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

void Sprite::InitEnemySprites(int width, int height, int fw, int fh, int max, int col, char* name, ALLEGRO_COLOR color)
{
	//x = width / 2;
	//y = height / 2;
	y = 0;
	x = 0;

	WIDTH = width;
	HEIGHT = height;

	maxFrame = max;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 3;
	frameWidth = fw;	//normally 50
	frameHeight = fh;	//normally 70
	//cout << "frameWidth: " << frameWidth << endl;	//DEBUG
	//cout << "frameHeight: " << frameHeight << endl;	//DEBUG
	animationColumns = col;
	animationRows = 1;
	//animationDirection = 2;
	//0 = down, 1 = left, 2 = right, 3 = up

	image = al_load_bitmap(name);
	al_convert_mask_to_alpha(image, color);
	boundx = frameWidth + x;
	boundy = frameHeight + x;
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
		if (x <= 0) {
			x = oldx;
		}
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
		if (y + frameHeight >= height) {
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
		if (y <= 0) {
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
		if (y+frameHeight > height||collided(x, y + frameHeight) || collided(x + frameWidth, y + frameHeight)) {	
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
		if (collided(x, y) || collided(x + frameWidth, y) || y < 0) {	
			x = oldx;
			y = oldy;
		}
	}
	boundx = x + frameWidth;
	boundy = y + frameHeight;

}

void Sprite::UpdateEnemySprites(int width, int height, int xp, int yp, int health, int &loop, bool &live) {
	int oldx = x;
	int oldy = y;

	boundx = x + frameWidth; // *.9;	//the *.9 makes the hitbox accurate
	boundy = y + frameHeight; // *.9;	//to the scaled bitmap

	//xp and yp are the players
	//x and y coordinates
	if (health <= 0) {
		if (loop < 3) {
			if (++frameCount > frameDelay) {
				frameCount = 0;
				if (++curFrame > maxFrame) {
					curFrame = 0;
					loop++;
				}
			}
		}
		else {
			live = false;
		}
	}
	else {
		//move towards ness at 1 per frame (ness moves at 2 per frame)
		//this allows ness to outrun them
		if (xp > x) {
			x++;
		}
		else if (xp < x) {
			x--;
		}
		if (yp > y) {
			y++;
		}
		else if (yp < y) {
			y--;
		}

		//check collision with foreground tiles
		//repurposed from UpdateSprites
		if (y > oldy) {
			if (boundy > height || collided(x, boundy) || collided(boundx, boundy)) {
				//collision down
				//x = oldx;
				y = oldy;
			}
		}
		else if (y < oldy) {
			if (collided(x, y) || collided(boundx, y) || y < 0) {
				//collision up
				//x = oldx;
				y = oldy;
			}
		}
		if (x < oldx) {

			if (collided(x, boundy) || collided(x, y) || collided(x, boundy) ||
				collided(x, boundy / 2)) {
				//collision detection to the left
				x = oldx;
				//y = oldy;
			}
		}
		else if (x > oldx) {
			if (collided(boundx, boundy) || collided(boundx, y) || 
				collided(boundx, boundy / 2) || collided(boundx, boundy / 3) ||
				collided(boundx, oldy + 10) || collided(boundx, boundy - 25)) {
				//collision detection to the right
				x = oldx;
				//y = oldy;
			}
		}
		
	}

	boundx = x + frameWidth; //*.9;	//this updates the bound boxes
	boundy = y + frameHeight;// *.9;	//to check for collision
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

void Sprite::DrawEnemySprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	//al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
	
	
	
	al_draw_tinted_scaled_rotated_bitmap_region(
		image,								//bitmap
		fx, fy, frameWidth, frameHeight,	//source region
		al_map_rgb(255,255,255),			//tint (white means none)
		0, 0,								//center of rotation
		x - xoffset,y - yoffset,			//destination
		.9, .9,								//scale
		0,0);								//angle & flags
}

void Sprite::EnemyDie(int xoffset, int yoffset, bool &l) {
	curFrame = 0;
	for (int i = 0; i < 30; i++) {
		frameCount = 0;
		while (curFrame < maxFrame) {
			if (++frameCount > frameDelay) {
				curFrame++;
				int fx = (curFrame % animationColumns) * frameWidth;
				int fy = (curFrame / animationColumns) * frameHeight;
				al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
				frameCount = 0;
			}
		}
		curFrame = 0;
	}
	l = false;
}