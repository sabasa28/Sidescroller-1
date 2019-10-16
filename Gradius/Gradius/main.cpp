//Gradius logic:
/*
	Space ship going left to right
	Capability of shooting oncoming obstacles
	Free movement

*/
#include "raylib.h"
#include "glfw3.h"

struct Player {
	Rectangle rec;
	Vector2 size;
	int score;
	Color color;
	Texture2D texture;
	Image img;
};

Player player;

struct Meteor {
	Rectangle rec;
	Vector2 size;
	Color color;
	Texture2D texture;
	Image img;
	bool active; //This is when the player shoots it, it desapears for a moment
};

Meteor meteor;
bool game_over;


void init_player();
void play();

void input();
void update();
void draw();
void init();

void main()
{
	play();
}

void play()
{
	init();

	InitWindow(1000, 440, "This ain't a Gradius clone, it's a ripoff");

	while (!game_over)
	{
		input();
		update();
		draw();
	}
}

float posX_player;
float posY_player;
float vel_player = 385.0f;

void init_player()
{
	posX_player =(GetScreenWidth() / 14);
	posY_player =(GetScreenHeight() / 2);
	//Players Creation
	player.size.x = 30.0f;
	player.size.y = 30.0f;

	player.rec.x = posX_player;
	player.rec.y = posY_player;

	player.rec.width = player.size.x;
	player.rec.height = player.size.y;
	player.color = BLUE;
	//Player Texture
}

void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawRectangle(player.rec.x, player.rec.y, player.rec.height, player.rec.width, player.color);
	//DrawTriangle({punta 1 x y},{punta 2 x y},{punta 3 x y},color);
	EndDrawing();
}

void input()
{
	if (IsKeyDown(KEY_DOWN))
	{
		player.rec.y += vel_player * GetFrameTime();
	}
	if (IsKeyDown(KEY_UP))
	{
		player.rec.y -= vel_player * GetFrameTime();
	}
}
void update()
{
	if (CheckCollisionRecs(player.rec, meteor.rec))
	{
		game_over = true;
	}
}

void init_meteor()
{
	meteor.size.x = 10.0f;
	meteor.size.y = 10.0f;

	meteor.rec.x = GetScreenWidth();
	meteor.rec.y = GetScreenHeight() / 2;

	meteor.rec.width = meteor.size.x;
	meteor.rec.height = meteor.size.y;
	meteor.color = RED;
}

void init()
{
	game_over = false;
	init_player();
	init_meteor();
}