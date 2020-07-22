/*
Nick Turner
7/21/2020
CPSC 440J
Turner Program 5
*/
#ifndef ATTACK_H
#define ATTACK_H

#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Attack {
public:
	Attack();
	~Attack();

private:
	ALLEGRO_BITMAP* image;
	ALLEGRO_SAMPLE* hit;
};

#endif