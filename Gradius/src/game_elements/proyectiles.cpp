#include "proyectiles.h"

#include "raylib.h"

#include "general/console.h"
#include "game_elements/player.h"
#include "game_elements/enemies.h"

const int cant_meteor = 5;
const int max_bullets = 50;
const int max_bombs = 50;

Bullet bullet[max_bullets];
Bomb player_bomb[max_bombs];
Bomb enemy_bomb[max_bombs];
Meteor meteor[cant_meteor];

static int chosen_bullet;
static int chosen_player_bomb;
static int chosen_enemy_bomb;

void init_meteor()
{
	for (int i = 0; i < cant_meteor; i++)
	{
		meteor[i].rec.height = 10.0f;
		meteor[i].rec.width = 20.0f;

		meteor[i].speed = -450.0f;

		meteor[i].rec.x =screen_width;
		meteor[i].rec.y = static_cast<float>(GetRandomValue(0, screen_height- meteor[i].rec.height));

		meteor[i].color = RED;
		meteor[i].active = true;
	}
}

void init_player_bombs()
{
	for (int i = 0; i < max_bombs; i++)
	{
		player_bomb[i].active = false;
		player_bomb[i].color = WHITE;
		player_bomb[i].radius = 10.0f;
		player_bomb[i].speed.x = 200.0f;
		player_bomb[i].speed.y = 150.0f;
	}
}

void init_enemy_bombs()
{
	for (int i = 0; i < max_bombs; i++)
	{
		enemy_bomb[i].active = false;
		enemy_bomb[i].color = ORANGE;
		enemy_bomb[i].radius = 10.0f;
		enemy_bomb[i].speed.x = -200.0f;
		enemy_bomb[i].speed.y = -100.0f;
	}
}

void init_bullet()
{
	for (int i = 0; i < max_bullets; i++)
	{
		bullet[i].speed.y = 0.0f;
		bullet[i].speed.x = 200.0f;
		bullet[i].radius = 2.5f;
		bullet[i].active = false;
		bullet[i].color = YELLOW;
	}
}

void shoot_player_bomb()
{
	for (int i = 0; i < max_bombs; i++)
	{
		if (!player_bomb[i].active)
		{
			chosen_player_bomb = i;
			break;
		}
	}
	player_bomb[chosen_player_bomb].active = true;
	player_bomb[chosen_player_bomb].pos.x = player.rec.x+player.rec.width;
	player_bomb[chosen_player_bomb].pos.y = player.rec.y+player.rec.height;
}

void shoot_enemy_bomb()
{
	if (enemy.active)
	{
		for (int i = 0; i < max_bombs; i++)
		{
			if (!enemy_bomb[i].active)
			{
				chosen_enemy_bomb = i;
				break;
			}
		}
		enemy_bomb[chosen_enemy_bomb].active = true;
		enemy_bomb[chosen_enemy_bomb].pos.x = enemy.rec.x;
		enemy_bomb[chosen_enemy_bomb].pos.y = enemy.rec.y;
	}
}

void shoot_bullet()
{
	for (int i = 0; i < max_bullets; i++)
	{
		if (!bullet[i].active)
		{
			chosen_bullet = i;
			break;
		}
	}
	bullet[chosen_bullet].active = true;
	bullet[chosen_bullet].pos.x = player.rec.x + player.rec.width;
	bullet[chosen_bullet].pos.y = player.rec.y + player.rec.height / 2;
}

void update_player_bomb()
{
	for (int i = 0; i < max_bombs; i++)
	{
		player_bomb[i].pos.x += player_bomb[i].speed.x*GetFrameTime();
		player_bomb[i].pos.y += player_bomb[i].speed.y*GetFrameTime();
		if (player_bomb[i].pos.y >= screen_height - player_bomb[i].radius)
		{
			player_bomb[i].active = false;
		}
	}
}

void update_enemy_bomb()
{
	for (int i = 0; i < max_bombs; i++)
	{
		if (enemy_bomb[i].active)
		{
			enemy_bomb[i].pos.x += enemy_bomb[i].speed.x*GetFrameTime();
			enemy_bomb[i].pos.y += enemy_bomb[i].speed.y*GetFrameTime();
			if (enemy_bomb[i].pos.y <= 0 + enemy_bomb[i].radius || enemy_bomb[i].pos.x <= 0 + enemy_bomb[i].radius)
			{
				enemy_bomb[i].active = false;
			}
			if (CheckCollisionCircleRec(enemy_bomb[i].pos, enemy_bomb[i].radius, player.rec))
			{
				enemy_bomb[i].active = false;
				player.life -= 1;
			}
		}
	}
}

void update_bullets()
{
	for (int i = 0; i < max_bullets; i++)
	{
		bullet[i].pos.x += bullet[i].speed.x*GetFrameTime();
		if (bullet[i].pos.x > screen_width)
		{
			bullet[i].active = false;
		}
	}
}

void draw_bombs()
{
	for (int i = 0; i < max_bombs; i++)
	{
		if (player_bomb[i].active)
		{
			DrawCircle(player_bomb[i].pos.x, player_bomb[i].pos.y, player_bomb[i].radius, player_bomb[i].color);
		}
		if (enemy_bomb[i].active)
		{
			DrawCircle(enemy_bomb[i].pos.x, enemy_bomb[i].pos.y, enemy_bomb[i].radius, enemy_bomb[i].color);
		}
	}
}

void draw_bullets()
{
	for (int i = 0; i < max_bullets; i++)
	{
		if (bullet[i].active)
		{
			DrawCircle(bullet[i].pos.x, bullet[i].pos.y, bullet[i].radius, bullet[i].color);
		}
	}
}