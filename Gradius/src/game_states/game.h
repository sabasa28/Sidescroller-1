#ifndef GAME_H
#define GAME_H

enum  Game_states {
	MENU,
	GAME,
	END
};
extern Game_states game_state;

void play();
void init();
void input();
void update();
void draw();

#endif