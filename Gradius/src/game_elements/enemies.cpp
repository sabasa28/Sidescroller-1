#include "enemies.h"
#include "general/console.h"
#include "player.h"

Enemy enemy;


void init_enemies() 
{
	enemy.active = true;
	enemy.color = RED;
	enemy.speed = { -100.0f,0.0f };
	enemy.rec.width = 30.0;
	enemy.rec.height = 30.0f;
	enemy.rec.x = screen_width;
	enemy.rec.y = screen_height-enemy.rec.height;
	enemy.cadence = 1;
}

void update_enemies() 
{
	enemy.rec.x += enemy.speed.x*GetFrameTime();
	if (enemy.rec.x <= 0)
	{
		enemy.rec.x = screen_width;
		enemy.active = true;
	}
}

void draw_enemies()
{
	if (enemy.active)
	{
		DrawRectangle(enemy.rec.x, enemy.rec.y, enemy.rec.width, enemy.rec.height, enemy.color);
	}
}