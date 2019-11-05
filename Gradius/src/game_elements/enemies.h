#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"

struct Enemy {
	Rectangle rec;
	Color color;
	Vector2 speed;
	bool active;
	int cadence;
};
extern Enemy enemy;

void init_enemies();
void update_enemies();
void draw_enemies();

#endif