#include "Player.h"
#include "Body.h"
#include "Shape.h"
#include "App.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"

Player::Player() : Entity(EntityType::PLAYER)
{
    texture = NULL;

    rect = { 567,191,100,94 };
    width = rect.w;
    height = rect.h;

    Circle* c = new Circle(3.0f);
    body = new Body(Vec2f(595.0f, 3000.0f), 5.0f, c, 0.009f);
    body->AddCollision({ 600,400,width,height }, ColliderType::RECTANGLE);

    earthMaxGravity = { 0.0f,600.0f };
    earthGravity = { 0.0f,0.0f };
    earthGravityStart = 2160;
    earthGravityEnd = 3600;

    moonMaxGravity = { 0.0f,-600.0f };
    moonGravity = { 0.0f,0.0f };
    moonGravityStart = 0;
    moonGravityEnd = 1440;

    currentLocation = Location::SPACE;

    fxPropulsion = app->audio->LoadFx("Assets/Audio/Fx/thruster_fire.ogg");
    fxDie = app->audio->LoadFx("Assets/Audio/Fx/explosion_crunch.ogg");
}

bool Player::Update(float dt)
{
    earthGravity = body->GetGravity(earthMaxGravity, body->position, earthGravityStart, earthGravityEnd, false);
    body->AddGravity(earthGravity);
    moonGravity = body->GetGravity(moonMaxGravity, body->position, moonGravityStart, moonGravityEnd, true);
    body->AddGravity(moonGravity);

    if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && (currentLocation == Location::SPACE || currentLocation == Location::WATER)) HorizontalMove(true);
    if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && (currentLocation == Location::SPACE || currentLocation == Location::WATER)) HorizontalMove(false);
    if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
    {
        Propulsion(true);
        //app->audio->PlayFx(fxPropulsion);
    }
    if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
    {
        Propulsion(false);
        //app->audio->PlayFx(fxPropulsion);
    }

    if (!app->debug)
    {
        static char titleDebug[256];
        sprintf_s(titleDebug, 256, 
            "| Player velocity: %.3f,%.3f | Player position: %.1f,%.1f | Player mass: %.3f | Earth gravity: %.3f | Moon gravity: %.3f | Location: %d |", 
            body->velocity.x, body->velocity.y, body->position.x, body->position.y, body->mass, earthGravity.y, moonGravity.y, currentLocation
        );
        app->win->SetTitle(titleDebug);
    }

    // Follow if in bounds
    if (body->position.y < (3600 - app->win->GetWindowHeight() / 2) && body->position.y > app->win->GetWindowHeight() / 2)
        app->render->CameraFollow(body->position);

    body->rectCollision->SetPosition(body->position);



    return true;
}

bool Player::Draw()
{
    app->render->DrawTexture(texture, body->position.x, body->position.y, &rect);

    return false;
}

void Player::HorizontalMove(bool isLeft)
{
    isLeft ? body->AddImpulse(Vec2f(-0.250f,0.0f), Vec2f(0.0f, 0.0f)) : body->AddImpulse(Vec2f(0.250f, 0.0f), Vec2f(0.0f, 0.0f));
}

void Player::Propulsion(bool isUp)
{
    isUp ? body->AddImpulse(Vec2f(0, -0.20f), Vec2f(0.0f, 0.0f)) : body->AddImpulse(Vec2f(0, 0.20f), Vec2f(0.0f, 0.0f));
}

void Player::SetTexture(SDL_Texture* tex)
{
    texture = tex;
}

SDL_Rect Player::GetBounds()
{
    return { (int)body->position.x, (int)body->position.y, width, height };
}