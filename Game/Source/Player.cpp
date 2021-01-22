#include "Player.h"
#include "Body.h"
#include "CircleShape.h"
#include "App.h"
#include "Render.h"
#include "Render.h"
#include "Window.h"
#include "Input.h"
#include "Physics.h"

Player::Player() : Entity(EntityType::PLAYER)
{
    texture = NULL;
    rect = { 917,531,42,42 };
    width = 42;
    height = 42;

    // Define Player animations

    // Player collider

    Shape* circle = (Shape*)new CircleShape(2.0f);
    body = new Body(5.0f,circle,0.007f);
    body->position = Vec2f(600.0f, 400.0f);
    collider = app->collisions->AddCollider({ (int)body->position.x,(int)body->position.y,width,height }, Collider::Type::PLAYER, (Module*)app->entityManager);
}

bool Player::Update(float dt)
{

    tempPosition = body->position;

    if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) HorizontalMove(true);
    if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) HorizontalMove(false);
    if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) Propulsion();
    
    // Update collider position
    if (collider != nullptr)
    {
        collider->SetPos(body->position.x, body->position.y);
    }
    //follow if over the ground
    if (body->position.y < 357)
    app->render->CameraFollow(body->position);
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

void Player::Propulsion()
{
    body->AddImpulse(Vec2f(0, -0.20f), Vec2f(0.0f, 0.0f));
}


void Player::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

SDL_Rect Player::GetBounds()
{
    return { (int)body->position.x, (int)body->position.y, width, height };
}

void Player::OnCollision(Collider* collider) 
{
    body->position = tempPosition;
    body->velocity.y = 0;
}