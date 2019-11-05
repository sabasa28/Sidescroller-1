#ifndef PROYECTILES_H
#define PROYECTILES_H

#include "raylib.h"

extern const int cant_meteor;
extern const int max_bullets;
extern const int max_bombs;

struct Bullet {
	Vector2 pos;
	Vector2 speed;
	float radius;
	bool active;
	Color color;
};
extern Bullet bullet[];

struct Bomb {
	Vector2 pos;
	Vector2 speed;
	float radius;
	bool active;
	Color color;
};
extern Bomb player_bomb[];
extern Bomb enemy_bomb[];

struct Meteor {
	Rectangle rec;
	Color color;
	Texture2D texture;
	Image img;
	float speed;
	bool active;
};
extern Meteor meteor[];

void init_meteor();
void init_player_bombs();
void init_enemy_bombs();
void init_bullet();
void shoot_player_bomb();
void shoot_enemy_bomb();
void shoot_bullet();
void update_player_bomb();
void update_enemy_bomb();
void update_bullets();
void draw_bombs();
void draw_bullets();

#endif