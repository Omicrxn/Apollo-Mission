#include "SceneGameplay.h"

#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Audio.h"
#include "Textures.h"
#include "Collisions.h"

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
    return false;
}

inline bool CheckCollision(SDL_Rect rec1, SDL_Rect rec2)
{
	if ((rec1.x < (rec2.x + rec2.w) && (rec1.x + rec1.w) > rec2.x) &&
		(rec1.y < (rec2.y + rec2.h) && (rec1.y + rec1.h) > rec2.y)) return true;
	else return false;
}

bool SceneGameplay::Update(float dt)
{
	//if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	//	TransitionToScene(SceneType::TITLE);
	world->Update(dt);
	//app->collisions->AddCollider({ 0,0,1280,50 }, Collider::Type::WALL, nullptr);
	app->collisions->AddCollider({ 0,670,1280,50 }, Collider::Type::WALL, (Module*)app->entityManager);
	app->collisions->debug = true;

	player->Update(dt);

	

	return true;
}

bool SceneGameplay::Draw()
{
	app->render->DrawTexture(space, 0, -1440, &spaceRect);

	player->Draw();

    return false;
}

bool SceneGameplay::Unload()
{
	// TODO: Unload all resources
	app->tex->UnLoad(space);

    return false;
}