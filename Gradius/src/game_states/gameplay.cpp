#include "gameplay.h"

#include "raylib.h"

#include "game_elements/proyectiles.h"
#include "game_elements/player.h"
#include "game_elements/enemies.h"

void init_gameplay() 
{
	init_player();
	init_meteor();
	init_player_bombs();
	init_enemy_bombs();
	init_bullet();
	init_enemies();
}

void draw_gameplay()
{
	ClearBackground(BLACK);
	DrawRectangleRec(player.rec, player.color);
	draw_bullets();
	draw_bombs();
	draw_enemies();
	for (int i = 0; i < cant_meteor; i++)
	{
		if (meteor[i].active)
			DrawRectangleRec(meteor[i].rec, meteor[i].color);
	}
}