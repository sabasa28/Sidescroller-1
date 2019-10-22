//Gradius logic:
/*
	Space ship going left to right
	Capability of shooting oncoming obstacles
	Free movement

*/
#include "raylib.h"
#include "glfw3.h"

const int screen_width = 1000;
const int screen_height = 400;
const int cant_meteor = 5;
float aux;

//Structs/Classes i prefer to do this way with {} simply because that's the easiest
//way for me to identify them on a quick read
struct Player {
	Rectangle rec;
	int score;
	float speed;
	Color color;
	Texture2D texture;
	Image img;
};
Player player;

struct Meteor {
	Rectangle rec;
	Color color;
	Texture2D texture;
	Image img;
	float speed;
	bool active; //This is when the player shoots it, it desapears for a moment
};

Meteor meteor[cant_meteor];
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

	InitWindow(screen_width, screen_height, "This ain't a Gradius clone, it's a ripoff");

	while (!WindowShouldClose() && !game_over)
	{
		input();
		update();
		draw();
	}
}

float posX_player;
float posY_player;

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


	//Player Texture
}

void draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawRectangleRec(player.rec, player.color);
	for (int i = 0; i < cant_meteor; i++)
	{
		if (meteor[i].active)
			DrawRectangleRec(meteor[i].rec, meteor[i].color);
	}
	EndDrawing();
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
	if (IsKeyPressed(KEY_ESCAPE)) game_over = true;

}
void update()
{
	for (int i = 0; i < cant_meteor; i++)
	{
		if (meteor[i].active)
			meteor[i].rec.x -= meteor[i].speed * GetFrameTime();
		if (meteor[i].rec.x <= 0)
		{
			aux = screen_height - meteor[i].rec.width;
			meteor[i].rec.x = screen_width - meteor[i].rec.width;
			meteor[i].rec.y = GetRandomValue(0, aux);
		}

	}
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
		aux = GetRandomValue(0,screen_height);
		meteor[i].rec.y = aux;

		meteor[i].color = RED;
		meteor[i].active = true;
	}
}

void init()
{
	game_over = false;
	init_player();
	init_meteor();
}