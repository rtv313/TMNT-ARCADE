#ifndef  _MODULE_CHOOSE_CHARACTER_H_
#define  _MODULE_CHOOSE_CHARACTER_H_

#include "Module.h"

struct SDL_Texture;

class ModuleChooseCharacter :public Module
{

private:
	int startGameFx = 0;
	bool startGame = false;
	float startTime = 0;
	float interval = 250;
	enum class Character { Leonardo, MichaelAngello, Donatello, Rafael };
	Character selectedCharacter = Character::Leonardo;
	void ChooseCharacter();

public:
	ModuleChooseCharacter(bool active = true);
	~ModuleChooseCharacter();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture * graphics = nullptr;
	Animation selectTurtle;
	Animation leonardo;
	Animation michaelAngello;
	Animation donatello;
	Animation rafael;
	Animation nonSelectedLeonardo;
	Animation nonSelectedMichaelAngello;
	Animation nonSelectedDonatello;
	Animation nonSelectedRafael;
	Animation selectFramework;
};
#endif //_MODULE_CHOOSE_CHARACTER_H_

