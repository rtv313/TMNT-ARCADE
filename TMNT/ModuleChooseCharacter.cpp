#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleChooseCharacter.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleChooseCharacter::ModuleChooseCharacter(bool active) :Module(active)
{
}


ModuleChooseCharacter::~ModuleChooseCharacter()
{
}

bool ModuleChooseCharacter::Start()
{
	LOG("Loading PreMenuModule");
	graphics = App->textures->Load("Assets/TMNTSprites/SelectCharacter.png");
	App->renderer->camera.x = App->renderer->camera.y = 0;
	startGameFx = App->audio->LoadFx("Assets/explosion.wav");


	selectTurtle = Animation();
	leonardo = Animation();
	michaelAngello = Animation();
	donatello = Animation();
	rafael = Animation();
	nonSelectedLeonardo = Animation();
	nonSelectedMichaelAngello = Animation();
	nonSelectedDonatello = Animation();
	nonSelectedRafael = Animation();
	selectFramework = Animation();

	selectTurtle.frames.push_back({ 70, 4, 146, 10 });

	leonardo.frames.push_back({ 9, 18, 64, 64 });
	michaelAngello.frames.push_back({ 76, 18, 64, 64 });
	donatello.frames.push_back({ 143, 18, 64, 64 });
	rafael.frames.push_back({ 210, 18, 64, 64 });

	nonSelectedLeonardo.frames.push_back({ 9, 85, 64, 64 });
	nonSelectedMichaelAngello.frames.push_back({ 76, 85, 64, 64 });
	nonSelectedDonatello.frames.push_back({ 143, 85, 64, 64 });
	nonSelectedRafael.frames.push_back({ 210, 85, 64, 64 });

	selectFramework.frames.push_back({ 279, 66, 81, 81 });
	
	startTime = SDL_GetTicks();

	return true;
}

update_status ModuleChooseCharacter::Update()
{
	
	App->renderer->Blit(graphics, 125, 36, &(selectTurtle.GetCurrentFrame()), 0.0f);

	//Leonardo Sprite
	App->renderer->Blit(graphics, 110, 50, &(selectFramework.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphics, 119, 59, &(nonSelectedLeonardo.GetCurrentFrame()), 0.0f);

	//MichaelAngello Sprite
	App->renderer->Blit(graphics, 205, 50, &(selectFramework.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphics, 214, 59, &(nonSelectedMichaelAngello.GetCurrentFrame()), 0.0f);

	//Donatello Sprite
	App->renderer->Blit(graphics, 110, 150, &(selectFramework.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphics, 119, 159, &(nonSelectedDonatello.GetCurrentFrame()), 0.0f);

	//Rafael Sprite 
	App->renderer->Blit(graphics, 205, 150, &(selectFramework.GetCurrentFrame()), 0.0f);
	App->renderer->Blit(graphics, 214, 159, &(nonSelectedRafael.GetCurrentFrame()), 0.0f);

	//Select Character to play
	ChooseCharacter();

	


	//Once Selected start blinking
	if (startGame == false)
	{
		//App->renderer->Blit(graphics, 156, 204, &(leonardo.GetCurrentFrame()), 0.0f);
	}
	else
	{
		if (SDL_GetTicks() - startTime >= interval) // Produce appear disapear effect 
		{
			App->renderer->Blit(graphics, 156, 204, &(leonardo.GetCurrentFrame()), 0.0f);
			startTime = SDL_GetTicks();
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleChooseCharacter::CleanUp()
{
	LOG("Unloading License Scene");
	App->textures->Unload(graphics);
	return true;
}


void ModuleChooseCharacter::ChooseCharacter()
{
	// Selection changes for Leonardo
	switch (selectedCharacter) {

		case Character::Leonardo:

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			{
				selectedCharacter = Character::Leonardo;
			}

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				selectedCharacter = Character::MichaelAngello;
			}

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			{
				selectedCharacter = Character::Donatello;
			}

			App->renderer->Blit(graphics, 119, 59, &(leonardo.GetCurrentFrame()), 0.0f);
			LOG("Leonardo");

			break;


			//Selection changes for MichaelAngelo

		case Character::MichaelAngello:

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				selectedCharacter = Character::MichaelAngello;
			}

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			{
				selectedCharacter = Character::Rafael;
			}

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			{
				selectedCharacter = Character::Leonardo;
			}

			App->renderer->Blit(graphics, 214, 59, &(michaelAngello.GetCurrentFrame()), 0.0f);
			LOG("MichaelAngello");

			break;
			//Selection changes for Donatello
		case Character::Donatello:
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			{
				selectedCharacter = Character::Donatello;
			}

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				selectedCharacter = Character::Rafael;
			}

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
			{
				selectedCharacter = Character::Leonardo;
			}

			App->renderer->Blit(graphics, 119, 159, &(donatello.GetCurrentFrame()), 0.0f);
			LOG("Donatello");

			break;

			//Selection changes for Rafael
		case Character::Rafael:

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				selectedCharacter = Character::Rafael;
			}

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
			{
				selectedCharacter = Character::MichaelAngello;
			}

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			{
				selectedCharacter = Character::Donatello;
			}

			App->renderer->Blit(graphics, 214, 159, &(rafael.GetCurrentFrame()), 0.0f);
			LOG("Rafael");

			break;
		}

}
