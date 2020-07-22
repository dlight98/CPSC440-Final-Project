/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include "Attack.h"

Attack::Attack() {
	image = NULL;
	hit = NULL;
}
Attack::~Attack() {
	al_destroy_bitmap(image);
	al_destroy_sample(hit);
}