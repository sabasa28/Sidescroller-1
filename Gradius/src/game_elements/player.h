#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

struct Player {
	Rectangle rec;
	bool invincibility_frames;
	int score;
	int life;
	float speed;
	Color color;
	Texture2D texture;
};
extern Player player;

void init_player();

#endif