#include "EntityManager.h"

#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Asteroid.h"

#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager() : Module()
{
	name.Create("entitymanager");
}

// Destructor
EntityManager::~EntityManager()
{}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	if (!active) return true;
	ListItem<Entity*>* entity = entities.start;
	while (entity != nullptr)
	{
		if (!entity->data->active)
			DestroyEntity(entity->data);

		entity = entity->next;
	}
	entities.Clear();
	return true;
}

Entity* EntityManager::CreateEntity(EntityType type)
{
	Entity* ret = nullptr;

	switch (type)
	{
		// L13: Create the corresponding type entity
		case EntityType::PLAYER: ret = new Player();
			break;
		case EntityType::ASTEROID: ret = new Asteroid();
			break;
		default:
			break;
	}

	// Created entities are added to the list
	if (ret != nullptr) entities.Add(ret);

	return ret;
}

bool EntityManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}

bool EntityManager::UpdateAll(float dt, bool doLogic)
{
	if (doLogic)
	{
		ListItem<Entity*>* entity = entities.start;
		while (entity != nullptr)
		{

			if (!entity->data->active)
				DestroyEntity(entity->data);

			entity = entity->next;
		}
	}

	return true;
}
void EntityManager::DestroyEntity(Entity* entity)
{
	ListItem<Entity*>* item = entities.At(entities.Find(entity));
	item->data->CleanUp();
	RELEASE(entity);

	entities.Del(item);
}
