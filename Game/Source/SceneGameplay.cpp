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
	// Load music & image
	app->audio->PlayMusic("Assets/Audio/Music/music_space.wav");
	space = app->tex->Load("Assets/Textures/space.png");
	spaceRect = { 0,0,1280,3600 };

	// Initialize player
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	player->SetTexture(app->tex->Load("Assets/Textures/space_spritesheet.png"));
	
	// Initialize world
	world = new World();
	world->AddBody(player->body);

	// Initialize game colliders
	earthBottomCollision = new RectCollision({ 0,3555,1280,45 });
	earthWaterCollision = new RectCollision({ 0,3257,1280,343 });
	earthGroundCollision = new RectCollision({ 538,3222,490,35 });
	moonGroundCollision = new RectCollision({ 0,0,1280,223 });

    return false;
}

bool SceneGameplay::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		TransitionToScene(SceneType::TITLE);

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

void SceneGameplay::CheckAllColisions() 
{
	if (earthGroundCollision->Intersects(player->body->rectCollision->collider)) 
	{
		player->body->AddNormalForce(Vec2f(0.0f, (player->earthGravity.y * -1.0f)));
		player->body->velocity = { 0,0 };
		player->currentLocation = Location::GROUND;
	}
	else if (earthWaterCollision->Intersects(player->body->rectCollision->collider))
	{
		player->currentLocation = Location::WATER;
	}
	else if (moonGroundCollision->Intersects(player->body->rectCollision->collider))
	{
		player->body->AddNormalForce(Vec2f(0.0f, (player->moonGravity.y * -1.0f)));
		player->body->velocity = { 0,0 };
		player->currentLocation = Location::MOON;
	}
	else
	{
		player->currentLocation = Location::SPACE;
	}

	if (earthBottomCollision->Intersects(player->body->rectCollision->collider))
	{
		player->body->AddNormalForce(Vec2f(0.0f, (player->earthGravity.y * -1.0f)));
		player->body->velocity = { 0,0 };
	}

}

bool SceneGameplay::Unload()
{
	// TODO: Unload all resources
	app->tex->UnLoad(space);

    return false;
}