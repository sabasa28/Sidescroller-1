//Gradius logic:
/*
	Space ship going left to right
	Capability of shooting oncoming obstacles
	Free movement

*/
#include <fstream>
#include <iostream>
#include <cmath>

#include "raylib.h"
#include "glfw3.h"

const int screen_width = 1000;
const int screen_height = 400;
const int cant_meteor = 5;
const int max_bullets = 10;
float aux;

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
	float rotation;
	int life_spawn;
	bool active;
	Color color;
	//Texture2D texture;
};

Bullet bullet[max_bullets];

struct Meteor {
	Rectangle rec;
	Color color;
	Texture2D texture;
	Image img;
	float speed;
	bool active; //This is when the player shoots it, it desapears for a moment
};

enum  Game_screens {
	MENU,
	GAME,
	END
};

Game_screens game_screen;


Meteor meteor[cant_meteor];


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

//Game manager
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
	ClearBackground(BLACK);
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
	DrawRectangleRec(player.rec, player.color);
	for (int i = 0; i < cant_meteor; i++)
	{
		if (meteor[i].active)
			DrawRectangleRec(meteor[i].rec, meteor[i].color);
	}
}
void draw_end()
{
	int posX = GetScreenWidth() / 4, posY = 10, size = 40;

	DrawText("You suck", posX, posY, size, RAYWHITE);
}

void update()
{
	for (int i = 0; i < cant_meteor; i++)
	{
		if (player.rec.y <= 0) player.rec.y = 0;
		if (player.rec.y >= screen_height - player.rec.height) player.rec.y = screen_height - player.rec.height;
		if (meteor[i].active)
			meteor[i].rec.x -= meteor[i].speed * GetFrameTime();
		if (meteor[i].rec.x <= 0)
		{
			aux = screen_height - meteor[i].rec.width;
			meteor[i].rec.x = static_cast<float>(screen_width - meteor[i].rec.width);
			meteor[i].rec.y = static_cast<float>(GetRandomValue(0, aux));
		}

		if (CheckCollisionRecs(player.rec, meteor[i].rec))
		{
			meteor[i].rec.x = static_cast<float>(screen_width - meteor[i].rec.height);
			meteor[i].rec.y = static_cast<float>(GetRandomValue(0,screen_height));
			player.life--;
			if (player.life <= 0)
				game_screen = END;
		}
	}

}
//Input
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
	if (IsKeyPressed(KEY_ENTER))
	{
		game_screen = GAME;
	}
}

//Init
void init_player()
{
	posX_player = 0.0f;
	posY_player = 200.0f;
	//Players Creation

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

void init()
{
	game_screen = MENU;
	InitWindow(screen_width, screen_height, "This ain't a Gradius clone, it's a ripoff");
	init_player();
	init_meteor();
}