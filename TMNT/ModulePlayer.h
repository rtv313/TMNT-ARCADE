#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Observer.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class ModulePlayer : public Module ,Observer
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void onNotify(GameEvent event);
	void Jump(int const &speed);

	
public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	iPoint position;
	bool destroyed = false;
	Collider *collider;
	bool flipHorinzontal = false;
	// Walk
	Animation forward;
	Animation backward;
	Animation up;
	Animation down;
	//idle
	Animation idle;
	// jump
	Animation jump;
	bool jumping;
	bool goingUp;
	int startJumpPosition;
	int jumpHeight;
	//Punch
	/*Animation beforePunch;*/
	Animation rightPunch;
	Animation leftPunch;
	Animation finalPunch;
	bool punching;

};

#endif