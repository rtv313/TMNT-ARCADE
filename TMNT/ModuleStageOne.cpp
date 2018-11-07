#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleStageOne.h"



ModuleStageOne::ModuleStageOne(bool active):Module(active)
{
}


ModuleStageOne::~ModuleStageOne()
{
}

bool ModuleStageOne::Start() {

	LOG("Loading Stage 1");

	levelOne = App->textures->Load("Assets/TMNTSprites/Scenes/Scene1.png");
	background = Animation();
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->audio->CleanUp(); //Clear Audio
	//App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	background.frames.push_back({ 518, 7, 1404, 357 });
	background.speed = 0.0f;

	return true;
}

update_status ModuleStageOne::Update()
{
	App->renderer->Blit(levelOne, 0, 0, &(background.GetCurrentFrame()),1.0f);
	
	return UPDATE_CONTINUE;
}

bool ModuleStageOne::CleanUp()
{
	LOG("Unloading battletoad stage one scene");

	return true;
}