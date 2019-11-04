//Gradius logic:
/*
	Space ship going left to right
	Capability of shooting oncoming obstacles
	Free movement

*/

#include <iostream>
#include <cmath>

#include "raylib.h"

const int screen_width = 1000;
const int screen_height = 400;
const int cant_meteor = 5;
const static int max_bullets = 50;
const static int max_bombs = 50;
static int chosenBullet;
static int chosenBomb;
float aux;

void init_meteor();
void drawBullets();
void shootBullet();
void moveBullets();

void initBomb();
void drawBombs();
void shootBomb();
void moveBomb();

//Structs/Classes i prefer to do this way with {} simply because that's the easiest
//way for me to identify them on a quick read

struct Player {
	Rectangle rec;
	bool invincibility_frames;
	int score;
	int life;
	float speed;
	Color color;
	Texture2D texture;
};
Player player;

struct Bullet {
	Vector2 pos;
	Vector2 speed;
	float radius;
	bool active;
	Color color;
};
Bullet bullet[max_bullets];

struct Bomb {
	Vector2 pos;
	Vector2 speed;
	float radius;
	bool active;
	Color color;
};
Bomb bomb[max_bombs];

struct Meteor {
	Rectangle rec;
	Color color;
	Texture2D texture;
	Image img;
	float speed;
	bool active;
};
Meteor meteor[cant_meteor];

enum  Game_screens {
	MENU,
	GAME,
	END
};
Game_screens game_screen;


void init_player();

void play();

void input();
void update();
void draw();
void init();

void draw_menu();
void draw_game();
void draw_end();

int main()
{
	play();
	return 0;
}

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

float posX_player;
float posY_player;



//Init
void draw()
{
	BeginDrawing();
	switch (game_screen)
	{
	case MENU:
	{
		draw_menu();
	}
		break;
	case GAME:
	{
		draw_game();
	}
		break;
	case END:
	{
		draw_end();
	}
		break;
	default:
		break;
	}
	EndDrawing();
}

void draw_menu()
{
	int posX = GetScreenWidth() / 4, posY = 10, size = 40;
	ClearBackground(BLACK);
	DrawText("Gradius", posX, posY, size, RAYWHITE);
	posY += 50;
	size = 20;
	DrawText("Press ENTER to begin", posX, posY, size, RAYWHITE);

	size = 25;
	posX = GetScreenWidth() / 10;
	posY = GetScreenHeight() / 4;
	DrawText("Controls", posX, posY, size, RAYWHITE);
	size = 20;
	posY += 25;
	DrawText("Arrow Keys: movement", posX, posY, size, RAYWHITE);
	posY += 25;
	DrawText("Space: shoot", posX, posY, size, RAYWHITE);
}

void draw_game()
{
	ClearBackground(BLACK);
	DrawRectangleRec(player.rec, player.color);
	drawBullets();
	drawBombs();
	for (int i = 0; i < cant_meteor; i++)
	{
		if (meteor[i].active)
			DrawRectangleRec(meteor[i].rec, meteor[i].color);
	}
}

void draw_end()
{
	ClearBackground(BLACK);
	int posX = GetScreenWidth() / 4, posY = 10, size = 40;

	DrawText("You suck", posX, posY, size, RAYWHITE);
}

void update()
{
	for (int i = 0; i < cant_meteor; i++)
	{
		if (player.rec.y <= 0) player.rec.y = 0;
		if (player.rec.y >= screen_height - player.rec.height) player.rec.y = screen_height - player.rec.height;
		meteor[i].rec.x -= meteor[i].speed * GetFrameTime();
		if (meteor[i].rec.x <= 0)
		{
			aux = screen_height - meteor[i].rec.width;
			meteor[i].rec.x = static_cast<float>(screen_width - meteor[i].rec.width);
			meteor[i].rec.y = static_cast<float>(GetRandomValue(0, aux));
			meteor[i].active = true;
		}
		for (int j = 0; j < max_bullets; j++)
		{
			if (CheckCollisionCircleRec(bullet[j].pos,bullet[j].radius,meteor[i].rec)&&meteor[i].active&&bullet[j].active)
			{
				meteor[i].active = false;
				bullet[j].active = false;
			}
		}

		if (CheckCollisionRecs(player.rec, meteor[i].rec)&&meteor[i].active)
		{
			meteor[i].active = false;
			player.life--;
			if (player.life <= 0)
				game_screen = END;
		}
	}
	moveBullets();
	moveBomb();
}

void input()
{
	if (IsKeyDown(KEY_DOWN))
	{
		player.rec.y += player.speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_UP))
	{
		player.rec.y -= player.speed * GetFrameTime();
	}
	if (IsKeyPressed(KEY_ENTER)&&(game_screen==END||game_screen==MENU))
	{
		init_meteor();
		player.life = 3;
		game_screen = GAME;
	}
	if (IsKeyPressed(KEY_SPACE))
	{
		shootBullet();
	}
	if (IsKeyPressed('Z'))
	{
		shootBomb();
	}
}

void init_player()
{
	posX_player = 0.0f;
	posY_player = 200.0f;

	player.speed = 385.0f;
	player.rec.width = 30.0f;
	player.rec.height = 30.0f;

	player.color = BLUE;

	player.rec.x = posX_player + player.rec.width;
	player.rec.y = posY_player;

	player.invincibility_frames = false;

	player.life = 3;

}

void init_meteor()
{
	for (int i = 0; i < cant_meteor; i++)
	{
		meteor[i].rec.height = 10.0f;
		meteor[i].rec.width = 20.0f;

		meteor[i].speed = 450.0f;

		aux = screen_width - meteor[i].rec.height;
		meteor[i].rec.x = aux;
		aux = static_cast<float>(GetRandomValue(0,screen_height));
		meteor[i].rec.y = aux;

		meteor[i].color = RED;
		meteor[i].active = true;
	}
}

void initBomb()
{
	for (int i = 0; i < max_bombs; i++)
	{
		bomb[i].active = false;
		bomb[i].color = WHITE;
		bomb[i].radius = 10.0f;
		bomb[i].speed.x = 200.0f;
		bomb[i].speed.y = 150.0f;
	}
}

void drawBombs()
{
	for (int i = 0; i < max_bombs; i++)
	{
		if (bomb[i].active)
		{
			DrawCircle(bomb[i].pos.x, bomb[i].pos.y, bomb[i].radius, bomb[i].color);
		}
	}
}

void shootBomb()
{
	for (int i = 0; i < max_bombs; i++)
	{
		if (!bomb[i].active)
		{
			chosenBomb = i;
			break;
		}
	}
	bomb[chosenBomb].active = true;
	bomb[chosenBomb].pos.x = player.rec.x ;
	bomb[chosenBomb].pos.y = player.rec.y ;
}

void moveBomb()
{
	for (int i = 0; i < max_bombs; i++)
	{
		bomb[i].pos.x += bomb[i].speed.x*GetFrameTime();
		bomb[i].pos.y += bomb[i].speed.y*GetFrameTime();
		if (/*CheckCollisionCircleRec(bomb[i].pos,bomb[i].radius,floor)*/bomb[i].pos.y >= screen_height-bomb[i].radius)
		{
			bomb[i].active = false;
		}
	}
}

void initBullet() 
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

void drawBullets()
{
	for (int i = 0; i < max_bullets; i++)
	{
		if (bullet[i].active)
		{
			DrawCircle(bullet[i].pos.x, bullet[i].pos.y, bullet[i].radius, bullet[i].color);
		}
	}
}

void shootBullet()
{
	for (int i = 0; i < max_bullets; i++)
	{
		if (!bullet[i].active)
		{
			chosenBullet = i;
			break;
		}
	}
	bullet[chosenBullet].active = true;
	bullet[chosenBullet].pos.x = player.rec.x+player.rec.width;
	bullet[chosenBullet].pos.y = player.rec.y+player.rec.height/2;
}

void moveBullets()
{
	for (int i = 0; i < max_bullets; i++)
	{
		bullet[i].pos.x += bullet[i].speed.x*GetFrameTime();
		if (bullet[i].pos.x>screen_width)
		{
			bullet[i].active = false;
		}
	}
}

void init()
{
	game_screen = MENU;
	InitWindow(screen_width, screen_height, "This ain't a Gradius clone, it's a ripoff");
	init_player();
	init_meteor();
	initBomb();
	initBullet();
}