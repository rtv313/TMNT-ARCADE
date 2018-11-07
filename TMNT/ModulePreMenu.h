#ifndef  _MODULEPREMENU_H_
#define  _MODULEPREMENU_H_

#include "Module.h"

struct SDL_Texture;

class ModulePreMenu :public Module
{

private:
	int startGameFx = 0;
	bool startGame = false;
	float startTime = 0;
	float interval = 250;

public:
	ModulePreMenu(bool active = true);
	~ModulePreMenu();
	bool Start();
	update_status Update();
	bool CleanUp();
	
public:
	SDL_Texture * graphics = nullptr;
	Animation ultraGames;
	Animation games;
	Animation rCopyRight;
	Animation theArcadeGame;
	Animation konami;
	Animation turtle;
	Animation turtlesLetters;

};
#endif //_MODULEPREMENU_H_

