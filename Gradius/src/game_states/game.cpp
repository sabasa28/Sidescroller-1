#include "game.h"

#include <ctime>

#include "raylib.h"

#include "general/console.h"
#include "game_elements/player.h"
#include "game_elements/proyectiles.h"
#include "game_states/menu.h"
#include "game_states/gameplay.h"
#include "game_states/gameOver.h"
#include "game_elements/enemies.h"

Game_states game_state;

static int timer;
static int enemy_shot = 0;
void init();
void input();
void update();
void draw();

void play()
{
	init();
	while (!WindowShouldClose())
	{
		input();
		update();
		draw();
	}
}

void init()
{
	InitWindow(screen_width, screen_height, "This ain't a Gradius clone, it's a ripoff");
	game_state = MENU;
	init_gameplay();
}

void input()
{
	switch (game_state)
	{
	case MENU:
		if (IsKeyPressed(KEY_ENTER))
		{
			game_state = GAME;
		}
		break;
	case GAME:
		if (IsKeyDown(KEY_DOWN))
		{
			player.rec.y += player.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP))
		{
			player.rec.y -= player.speed * GetFrameTime();
		}
		if (IsKeyPressed('Z'))
		{
			shoot_bullet();
		}
		if (IsKeyPressed('X'))
		{
			shoot_player_bomb();
		}
		break;
	case END:
		if (IsKeyPressed(KEY_ENTER))
		{
			init_meteor();
			init_player_bombs();
			init_bullet();
			init_player();
			init_enemy_bombs();
			init_enemies();
			game_state = GAME;
		}
		break;
	}
}

void update()
{
	timer = static_cast<int>(clock() / 1000);
	if (timer>=enemy_shot)
	{
		shoot_enemy_bomb();
		enemy_shot = timer + enemy.cadence;
	}
	switch (game_state)
	{
	case MENU:
		break;
	case GAME:
		for (int i = 0; i < cant_meteor; i++)
		{
			if (player.rec.y <= 0) player.rec.y = 0;
			if (player.rec.y >= screen_height - player.rec.height) player.rec.y = screen_height - player.rec.height;
			meteor[i].rec.x += meteor[i].speed * GetFrameTime();
			if (meteor[i].rec.x <= 0)
			{
				meteor[i].rec.x = static_cast<float>(screen_width - meteor[i].rec.width);
				meteor[i].rec.y = static_cast<float>(GetRandomValue(0, screen_height - meteor[i].rec.height));
				meteor[i].active = true;
			}
			for (int j = 0; j < max_bullets; j++)
			{
				if (CheckCollisionCircleRec(bullet[j].pos, bullet[j].radius, meteor[i].rec) && meteor[i].active&&bullet[j].active)
				{
					meteor[i].active = false;
					bullet[j].active = false;
				}
			}

			if (CheckCollisionRecs(player.rec, meteor[i].rec) && meteor[i].active)
			{
				meteor[i].active = false;
				player.life--;
			}
			for (int i = 0; i < max_bombs; i++)
			{
				if (CheckCollisionCircleRec(player_bomb[i].pos,player_bomb[i].radius,enemy.rec)&&enemy.active)
				{
					enemy.active = false;
				}
			}

			if (player.life <= 0)
			{
				game_state = END;
			}
		}
		update_bullets();
		update_player_bomb();
		update_enemies();
		update_enemy_bomb();
		break;
	case END:
		break;
	}
	
}

void draw()
{
	BeginDrawing();
	switch (game_state)
	{
	case MENU:
		draw_menu();
		break;
	case GAME:
		draw_gameplay();
		break;
	case END:
		draw_gameover();
		break;
	}
	EndDrawing();
}