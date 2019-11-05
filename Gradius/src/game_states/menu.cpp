#include "menu.h"

#include "raylib.h"

static const int text1PosX = 250;
static const int text1PosY = 10;
static const int text1Size = 40;
static const int text2PosX = 250;
static const int text2PosY = 60;
static const int text2Size = 20;
static const int text3PosX = 100;
static const int text3PosY = 100;
static const int text3Size = 25;
static const int text4PosX = 100;
static const int text4PosY = 125;
static const int text4Size = 20;
static const int text5PosX = 100;
static const int text5PosY = 150;
static const int text5Size = 20;
static const int text6PosX = 100;
static const int text6PosY = 175;
static const int text6Size = 20;
static const int text7PosX = 100;
static const int text7PosY = 220;
static const int text7Size = 25;
static const int text8PosX = 100;
static const int text8PosY = 245;
static const int text8Size = 20;
static const int text9PosX = 100;
static const int text9PosY = 270;
static const int text9Size = 20;

void draw_menu()
{
	ClearBackground(BLACK);

	DrawText("Gradius", text1PosX, text1PosY, text1Size, RAYWHITE);

	DrawText("Press ENTER to begin", text2PosX, text2PosY, text2Size, RAYWHITE);

	DrawText("Controls", text3PosX, text3PosY, text3Size, RAYWHITE);

	DrawText("Arrow Keys: movement", text4PosX, text4PosY, text4Size, RAYWHITE);

	DrawText("Z: shoot bullet", text5PosX, text5PosY, text5Size, RAYWHITE);

	DrawText("X: shoot bomb", text6PosX, text6PosY, text6Size, RAYWHITE);

	DrawText("Credits", text7PosX, text7PosY, text7Size, RAYWHITE);

	DrawText("Original developer - Felix Godziela", text8PosX, text8PosY, text8Size, RAYWHITE);

	DrawText("Fork developer - Inaki Diez Galarza", text9PosX, text9PosY, text9Size, RAYWHITE);
}