#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModulePreMenu.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModulePreMenu::ModulePreMenu(bool active) :Module(active)
{
}


ModulePreMenu::~ModulePreMenu()
{
}

bool ModulePreMenu::Start()
{
	LOG("Loading PreMenuModule");
	graphics = App->textures->Load("Assets/TMNTSprites/TitleScreens.png");
	App->renderer->camera.x = App->renderer->camera.y = 0;
	startGameFx = App->audio->LoadFx("Assets/explosion.wav");


	ultraGames = Animation();
	games = Animation();
	rCopyRight = Animation();
	theArcadeGame = Animation();
	konami = Animation();
	turtle = Animation();
	turtlesLetters = Animation();

	ultraGames.frames.push_back({ 159, 114, 104, 22 });
	games.frames.push_back({ 211, 183, 35, 7 });
	rCopyRight.frames.push_back({ 261, 138, 10, 10 });
	theArcadeGame.frames.push_back({6, 180, 179, 64 });
	konami.frames.push_back({ 136, 137, 110, 12 });
	turtle.frames.push_back({ 226, 164, 16, 17 });
	turtlesLetters.frames.push_back({ 146, 151, 63, 10 });

	startTime = SDL_GetTicks();

	return true;
}

update_status ModulePreMenu::Update()
{
	
	App->renderer->Blit(graphics, 140, 60, &(ultraGames.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphics, 187, 80, &(games.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphics, 237, 72, &(rCopyRight.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphics, 100, 90, &(theArcadeGame.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphics, 140, 170, &(konami.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphics, 130, 200, &(turtle.GetCurrentFrame()), 0.0f);
	
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && startGame == false)
	{	
		startGame = true;
		App->audio->PlayFx(startGameFx,0);
		App->fade->FadeToBlack((Module*)App->stageOne, this, 1.5f);
	}

	if(startGame == false)
	{
		App->renderer->Blit(graphics, 156, 204, &(turtlesLetters.GetCurrentFrame()), 0.0f);
	}
	else 
	{
		if (SDL_GetTicks() - startTime >= interval) // Produce appear disapear effect 
		{
			App->renderer->Blit(graphics, 156, 204, &(turtlesLetters.GetCurrentFrame()), 0.0f);
			startTime = SDL_GetTicks();
		}
	}

	return UPDATE_CONTINUE;
}

bool ModulePreMenu::CleanUp()
{
	LOG("Unloading License Scene");
	App->textures->Unload(graphics);
	return true;
}

