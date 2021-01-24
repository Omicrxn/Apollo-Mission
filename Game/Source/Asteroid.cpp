#include "Asteroid.h"
#include "Collision.h"
#include "App.h"
#include "Render.h"
#include "Window.h"

Asteroid::Asteroid() : Entity(EntityType::ASTEROID)
{
    texture = NULL;
    rect = { 0,0,800,800 };
    width = rect.w;
    height = rect.h;
}

bool Asteroid::Update(float dt)
{
    return true;
}

bool Asteroid::Draw()
{
    app->render->DrawTexture(texture, position.x, position.y, &rect);
    return true;
}

void Asteroid::SetTexture(SDL_Texture* tex)
{
    texture = tex;
}

void Asteroid::SetPosition(Vec2i pos)
{
    position = pos;
    collider = new CircleCollision(pos.x + width/2, pos.y + height/2, 200);
}

bool Asteroid::CleanUp() {
    RELEASE(collider);
    return true;
}