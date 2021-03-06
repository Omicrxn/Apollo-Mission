#include "SceneGameplay.h"

#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Audio.h"
#include "Textures.h"

#include "EntityManager.h"
#include "SceneManager.h"

SceneGameplay::SceneGameplay()
{
}

SceneGameplay::~SceneGameplay()
{}

bool SceneGameplay::Load() /*EntityManager entityManager)*/
{
	// Load music & sprites
	app->audio->PlayMusic("Assets/Audio/Music/music_space.wav");
	fxDie = app->audio->LoadFx("Assets/Audio/Fx/explosion_crunch.ogg");

	space = app->tex->Load("Assets/Textures/space.png");
	spaceRect = { 0,0,1280,3600 };

	smallFighter = app->tex->Load("Assets/Textures/small_fighter.png");
	fire = app->tex->Load("Assets/Textures/fire.png");
	explosion = app->tex->Load("Assets/Textures/explosion.png");
	asteroidTexture = app->tex->Load("Assets/Textures/asteroid.png");

	font = new Font("Assets/Fonts/future_font.xml");

	// Initialize player
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	player->SetTextures(smallFighter, fire, explosion);
	player->SetFont(font);

	// Adding asteroids
	asteroid1 = (Asteroid*)app->entityManager->CreateEntity(EntityType::ASTEROID);
	asteroid1->SetTexture(asteroidTexture);
	asteroid1->SetPosition(Vec2i{ 0,500 });

	asteroid2 = (Asteroid*)app->entityManager->CreateEntity(EntityType::ASTEROID);
	asteroid2->SetTexture(asteroidTexture);
	asteroid2->SetPosition(Vec2i{ 480,1000 });

	asteroid3 = (Asteroid*)app->entityManager->CreateEntity(EntityType::ASTEROID);
	asteroid3->SetTexture(asteroidTexture);
	asteroid3->SetPosition(Vec2i{ 0,1500 });

	asteroid4 = (Asteroid*)app->entityManager->CreateEntity(EntityType::ASTEROID);
	asteroid4->SetTexture(asteroidTexture);
	asteroid4->SetPosition(Vec2i{ 480,2000 });
	
	// Initialize world
	world = new World();
	world->AddBody(player->body);

	// Initialize game colliders
	earthBottomCollision = new RectCollision({ 0,3555,1280,45 });
	earthWaterCollision = new RectCollision({ 0,3257,1280,343 });
	earthGroundCollision = new RectCollision({ 538,3222,480,10 });
	earthIslandCollision = new RectCollision({ 538,3232,490,110 });
	moonGroundCollision = new RectCollision({ 0,0,1280,223 });

	// Initialize Physics factors
	fluidDensity = 0.75;
	volumeSubmerged = 25;
	buoyancyStart = 3153;
	buoyancyEnd = 3600;

	player->explode = false;
	player->propulsion = false;
	player->hasTouchedMoon = false;

	app->sceneManager->win = false;

    return false;
}

bool SceneGameplay::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		TransitionToScene(SceneType::TITLE);

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		TransitionToScene(SceneType::ENDING);

	if (app->sceneManager->win)
		TransitionToScene(SceneType::ENDING);

	if (player->explode)
	{
		app->audio->PlayFx(fxDie);
		TransitionToScene(SceneType::ENDING);
	}

	player->Update(dt);

	world->Update(dt);

	CheckAllColisions();

	return true;
}

bool SceneGameplay::Draw()
{
	app->render->DrawTexture(space, 0, 0, &spaceRect);

	asteroid1->Draw();
	asteroid2->Draw();
	asteroid3->Draw();
	asteroid4->Draw();

	player->Draw();

    return false;
}

void SceneGameplay::CheckAllColisions() 
{
	if (earthGroundCollision->Intersects(player->body->rectCollision->collider)) 
	{
		player->currentLocation = Location::GROUND;

		if (player->angle > 30 && player->angle < 330 || player->body->velocity.y > 200)
		{
			player->explode = true;
		}

		player->body->AddNormalForce(Vec2f(0.0f, (player->earthGravity.y * -1.0f)));
		player->propulsion = false;
		player->body->velocity = { 0,0 };

		if (player->hasTouchedMoon && !player->explode)
		{
			app->sceneManager->win = true;
		}
	}
	else if (earthWaterCollision->Intersects(player->body->rectCollision->collider))
	{
		player->body->AddBuoyancy(fluidDensity, player->GetGravity(), volumeSubmerged, player->body->GetBuoyancyHeight(player->body->position, buoyancyStart, buoyancyEnd));
		player->currentLocation = Location::WATER;
	}
	else if (moonGroundCollision->Intersects(player->body->rectCollision->collider))
	{
		player->currentLocation = Location::MOON;

		if ((player->angle >= 0 && player->angle < 150) || (player->angle > 210 && player->angle <= 360) || player->body->velocity.y < -200)
		{
			player->explode = true;
		}

		player->body->AddNormalForce(Vec2f(0.0f, (player->moonGravity.y * -1.0f)));
		player->propulsion = false;
		player->body->velocity = { 0,0 };

		player->hasTouchedMoon = true;
	}
	else
	{
		player->currentLocation = Location::SPACE;
	}

	if (earthIslandCollision->Intersects(player->body->rectCollision->collider))
	{
		player->explode = true;
	}

	if (earthBottomCollision->Intersects(player->body->rectCollision->collider))
	{
		player->explode = true;
	}

	if (asteroid1->collider->Intersects(player->body->rectCollision->collider) ||
		asteroid2->collider->Intersects(player->body->rectCollision->collider) ||
		asteroid3->collider->Intersects(player->body->rectCollision->collider) ||
		asteroid4->collider->Intersects(player->body->rectCollision->collider))
	{
		player->explode = true;
	}
}

bool SceneGameplay::Unload()
{
	// TODO: Unload all resources
	app->tex->UnLoad(space);
	app->tex->UnLoad(smallFighter);
	app->tex->UnLoad(fire);
	app->tex->UnLoad(explosion);
	app->tex->UnLoad(asteroidTexture);

	player->active = false;
	asteroid1->active = false;
	asteroid2->active = false;
	asteroid3->active = false;
	asteroid4->active = false;
	
	RELEASE(font);

	world->CleanUp();
	RELEASE(world);
	RELEASE(earthBottomCollision);
	RELEASE(earthWaterCollision);
	RELEASE(earthGroundCollision);
	RELEASE(earthIslandCollision);
	RELEASE(moonGroundCollision);

    return false;
}