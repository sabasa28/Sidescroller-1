#include "gameOver.h"

#include "raylib.h"

static const int text1PosX = 380;
static const int text1PosY = 180;
static const int text1Size = 50;
static const int text2PosX = 10;
static const int text2PosY = 370;
static const int text2Size = 20;


void draw_gameover()
{
	ClearBackground(BLACK);

	DrawText("You suck", text1PosX, text1PosY, text1Size, RED);

	DrawText("ENTER to play again", text2PosX, text2PosY, text2Size, RAYWHITE);
}