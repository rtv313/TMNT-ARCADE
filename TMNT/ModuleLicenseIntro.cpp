#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLicenseIntro.h"

ModuleLicenseIntro::ModuleLicenseIntro(bool active) :Module(active)
{
}


ModuleLicenseIntro::~ModuleLicenseIntro()
{
}

bool ModuleLicenseIntro::Start() 
{
	LOG("Loading LicenseModule");
	graphics = App->textures->Load("Assets/TMNTSprites/TitleScreens.png");
	background = Animation();
	App->renderer->camera.x = App->renderer->camera.y = 0;
	background.frames.push_back({ 287, 43, 217, 132 }); //w,h

	return true;
}

update_status ModuleLicenseIntro::Update()
{
	App->renderer->Blit(graphics,100,80,&(background.GetCurrentFrame()), 0.0f);

	if ( App->fade->isFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->stageOne, this, 1.0f);
	}

	return UPDATE_CONTINUE;
}

bool ModuleLicenseIntro::CleanUp()
{
	LOG("Unloading License Scene");
	App->textures->Unload(graphics);
	return true;
}