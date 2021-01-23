#include "SceneGameplay.h"

#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Audio.h"
#include "Textures.h"

#include "EntityManager.h"

SceneGameplay::SceneGameplay()
{
}

SceneGameplay::~SceneGameplay()
{}

bool SceneGameplay::Load() /*EntityManager entityManager)*/
{
	// Load music
	app->audio->PlayMusic("Assets/Audio/Music/music_space.wav");
	space = app->tex->Load("Assets/Textures/space.png");

	// Load game entities
	//Player* player = (Player*)entityManager->CreateEntity(EntityType::PLAYER);
	//player->SetTexture(tex->Load("Assets/Textures/player.png"));
	//entityManager->CreateEntity(EntityType::ENEMY);
	//entityManager->CreateEntity(EntityType::ENEMY);
	//entityManager->CreateEntity(EntityType::ITEM);
	//entityManager->CreateEntity(EntityType::ITEM);
	//entityManager->CreateEntity(EntityType::ITEM);

	// Initialize player
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	player->SetTexture(app->tex->Load("Assets/Textures/space_spritesheet.png"));
	world = new World();
	world->AddBody(player->body);

	groundCollision = new RectCollision({ 0,3600,1280,60 });
    return false;
}

bool SceneGameplay::Update(float dt)
{
	//if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	//	TransitionToScene(SceneType::TITLE);


	player->Update(dt);
	world->Update(dt);
	CheckAllColisions();
	return true;
}

bool SceneGameplay::Draw()
{
	app->render->DrawTexture(space, 0, 0, &spaceRect);

	player->Draw();

    return false;
}

void SceneGameplay::CheckAllColisions() {
	if (groundCollision->Intersects(player->body->rectCollision->collider)) {
		player->body->AddNormalForce(Vec2f(0.0f, -600.0f));
		player->body->velocity.y = 0;
	}


}

bool SceneGameplay::Unload()
{
	// TODO: Unload all resources
	app->tex->UnLoad(space);

    return false;
}