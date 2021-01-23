#include "Player.h"
#include "Body.h"
#include "Shape.h"
#include "App.h"
#include "Render.h"
#include "Render.h"
#include "Window.h"
#include "Input.h"


Player::Player() : Entity(EntityType::PLAYER)
{
    texture = NULL;
    rect = { 917,531,42,42 };
    width = 42;
    height = 42;
    Circle* c = new Circle(3.0f);
    body = new Body(Vec2f(600.0f,550.0f),5.0f,c,0.009f);
    body->AddCollision({ 600,400,width,height }, ColliderType::RECTANGLE);

    earthMaxGravity = { 0.0f,600.0f };
    earthGravity = { 0.0f,0.0f };
    earthGravityStart = 2160;
    earthGravityEnd = 3600;

    moonMaxGravity = { 0.0f,-600.0f };
    moonGravity = { 0.0f,0.0f };
    moonGravityStart = 0;
    moonGravityEnd = 1440;
}

bool Player::Update(float dt)
{
    tempPosition = body->position;

    earthGravity = body->GetGravity(earthMaxGravity, body->position, earthGravityStart, earthGravityEnd, false);
    body->AddGravity(earthGravity);
    moonGravity = body->GetGravity(moonMaxGravity, body->position, moonGravityStart, moonGravityEnd, true);
    body->AddGravity(moonGravity);

    printf("Earth gravity: %f | Moon gravity: %f\n", earthGravity.y, moonGravity.y);
    if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) HorizontalMove(true);
    if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) HorizontalMove(false);
    if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) Propulsion(true);
    if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) Propulsion(false);

    //follow if over the ground
    if (body->position.y < (3600 - app->win->GetWindowHeight() / 2) && body->position.y > app->win->GetWindowHeight() / 2)
        app->render->CameraFollow(body->position);

    body->rectCollision->SetPosition(body->position);
    return true;
}

bool Player::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
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


void Player::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

SDL_Rect Player::GetBounds()
{
    return { (int)body->position.x, (int)body->position.y, width, height };
}
