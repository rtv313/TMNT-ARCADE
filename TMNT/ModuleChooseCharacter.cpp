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
	selectPlayer = App->textures->Load("Assets/TMNTSprites/SelectPlayer.png");
	App->renderer->camera.x = App->renderer->camera.y = 0;
	startGameFx = App->audio->LoadFx("Assets/explosion.wav");
	
	//Play Menu Music
	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

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
	firstPlayer = Animation();

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
	firstPlayer.frames.push_back({ 2,3,26,27 });
	
	startTime = SDL_GetTicks();

	return true;
}

update_status ModuleChooseCharacter::Update()
{
	
	//Start Game

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && startGame == false) 
	{
		startGame = true;
		App->audio->PlayFx(startGameFx, 0);
		App->player->SetCharacter(selectedCharacter);
		App->fade->FadeToBlack((Module*)App->stageOne, this, 1.8f);
	}

	App->renderer->Blit(graphics, 125, 36, &(selectTurtle.GetCurrentFrame()), 0.0f);

	//Leonardo Sprite
	App->renderer->Blit(graphics, 110, 50, &(selectFramework.GetCurrentFrame()), 0.0f);
	if(selectedCharacter != Character::Leonardo)
		App->renderer->Blit(graphics, 119, 59, &(nonSelectedLeonardo.GetCurrentFrame()), 0.0f);

	//MichaelAngello Sprite
	App->renderer->Blit(graphics, 205, 50, &(selectFramework.GetCurrentFrame()), 0.0f);
	if (selectedCharacter != Character::MichaelAngello)
		App->renderer->Blit(graphics, 214, 59, &(nonSelectedMichaelAngello.GetCurrentFrame()), 0.0f);

	//Donatello Sprite
	App->renderer->Blit(graphics, 110, 150, &(selectFramework.GetCurrentFrame()), 0.0f);
	if (selectedCharacter != Character::Donatello)
		App->renderer->Blit(graphics, 119, 159, &(nonSelectedDonatello.GetCurrentFrame()), 0.0f);

	//Rafael Sprite 
	App->renderer->Blit(graphics, 205, 150, &(selectFramework.GetCurrentFrame()), 0.0f);
	if (selectedCharacter != Character::Rafael)
		App->renderer->Blit(graphics, 214, 159, &(nonSelectedRafael.GetCurrentFrame()), 0.0f);

	//Select Character to play
	ChooseCharacter();


	return UPDATE_CONTINUE;
}

bool ModuleChooseCharacter::CleanUp()
{
	LOG("Unloading License Scene");
	App->textures->Unload(graphics);
	App->textures->Unload(selectPlayer);
	return true;
}


void ModuleChooseCharacter::ChooseCharacter()
{	
	int showFirstPlayerPosX = 0;
	int showFirstPlayerPosY = 0;
	
	if (SDL_GetTicks() - startTime >= interval) // Produce appear disapear effect 
	{
		startTime = SDL_GetTicks();
		showFirstPlayer = !showFirstPlayer;
	}

	if (SDL_GetTicks() - startTimeBlink >= intervalBlinkCharacter)
	{
		startTimeBlink = SDL_GetTicks();
		showSelectedPlayer = !showSelectedPlayer;
	}

	// Selection changes for Leonardo
	switch (selectedCharacter) {

		case Character::Leonardo:

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN )
			{
				selectedCharacter = Character::Leonardo;
			}

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && startGame == false)
			{
				selectedCharacter = Character::MichaelAngello;
			}

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && startGame == false)
			{
				selectedCharacter = Character::Donatello;
			}

			if(startGame == false )
				App->renderer->Blit(graphics, 119, 59, &(leonardo.GetCurrentFrame()), 0.0f);
			else if (startGame == true && showSelectedPlayer == true) 
				App->renderer->Blit(graphics, 119, 59, &(leonardo.GetCurrentFrame()), 0.0f);			
			
			showFirstPlayerPosX = 110;
			showFirstPlayerPosY = 44;
			LOG("Leonardo");
			break;


			//Selection changes for MichaelAngelo

		case Character::MichaelAngello:

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				selectedCharacter = Character::MichaelAngello;
			}

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN && startGame == false)
			{
				selectedCharacter = Character::Rafael;
			}

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN && startGame == false)
			{
				selectedCharacter = Character::Leonardo;
			}

			if (startGame == false)
				App->renderer->Blit(graphics, 214, 59, &(michaelAngello.GetCurrentFrame()), 0.0f);
			else if (startGame == true && showSelectedPlayer == true)
				App->renderer->Blit(graphics, 214, 59, &(michaelAngello.GetCurrentFrame()), 0.0f);

			showFirstPlayerPosX = 205;
			showFirstPlayerPosY = 44;
			LOG("MichaelAngello");

			break;
			//Selection changes for Donatello
		case Character::Donatello:
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			{
				selectedCharacter = Character::Donatello;
			}

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN && startGame == false)
			{
				selectedCharacter = Character::Rafael;
			}

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && startGame == false)
			{
				selectedCharacter = Character::Leonardo;
			}

			if (startGame == false)
				App->renderer->Blit(graphics, 119, 159, &(donatello.GetCurrentFrame()), 0.0f);
			else if (startGame == true && showSelectedPlayer == true)
				App->renderer->Blit(graphics, 119, 159, &(donatello.GetCurrentFrame()), 0.0f);

			showFirstPlayerPosX = 110;
			showFirstPlayerPosY = 144;
				
			
			LOG("Donatello");

			break;

			//Selection changes for Rafael
		case Character::Rafael:

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				selectedCharacter = Character::Rafael;
			}

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && startGame == false)
			{
				selectedCharacter = Character::MichaelAngello;
			}

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN && startGame == false)
			{
				selectedCharacter = Character::Donatello;
			}

			if (startGame == false)
				App->renderer->Blit(graphics, 214, 159, &(rafael.GetCurrentFrame()), 0.0f);
			else if (startGame == true && showSelectedPlayer == true)
				App->renderer->Blit(graphics, 214, 159, &(rafael.GetCurrentFrame()), 0.0f);

			showFirstPlayerPosX = 205;
			showFirstPlayerPosY = 145;
			
			LOG("Rafael");

			break;
		}

		if (showFirstPlayer == true)
			App->renderer->Blit(selectPlayer, showFirstPlayerPosX, showFirstPlayerPosY, &(firstPlayer.GetCurrentFrame())); 
}
