#include "player.h"

Player player;

void init_player()
{
	player.speed = 385.0f;

	player.rec.width = 30.0f;
	player.rec.height = 30.0f;
	player.rec.x = 30.0f;
	player.rec.y = 200.0f;

	player.color = BLUE;

	player.invincibility_frames = false;

	player.life = 3;
}