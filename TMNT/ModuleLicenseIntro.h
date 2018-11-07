#ifndef  _MODULELICENSEINTRO_H_
#define  _MODULELICENSEINTRO_H_

#include "Module.h"

struct SDL_Texture;

class ModuleLicenseIntro :public Module
{
public:
	ModuleLicenseIntro(bool active = true);
	~ModuleLicenseIntro();
	bool Start();
	update_status Update();
	bool CleanUp();
public:
	SDL_Texture* graphics = nullptr;
	Animation  background;
};
#endif //_MODULELICENSEINTRO_H_
