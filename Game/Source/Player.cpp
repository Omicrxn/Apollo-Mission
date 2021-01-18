#include "Player.h"

#include "App.h"
#include "Render.h"
#include "Render.h"
#include "Window.h"
#include "Input.h"
#include "Physics.h"

Player::Player() : Entity(EntityType::PLAYER)
{
    texture = NULL;
    position = iPoint(12 * 16, 27 * 16);
    velocity.y = 200.0f;
    rect = { 917,531,42,42 };
    width = 42;
    height = 42;

    // Define Player animations

    // Player collider
    collider = app->collisions->AddCollider({ position.x,position.y,width,height }, Collider::Type::PLAYER, (Module*)app->entityManager);
}

bool Player::Update(float dt)
{

    tempPosition = position;

    if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) HorizontalMove(true);
    if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) HorizontalMove(false);
    if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) Propulsion();
    
    // Calculate gravity acceleration
    Physics::GetInsance()->UpdateVelocity(position, velocity, acceleration, dt);
    // Update collider position
    if (collider != nullptr)
    {
        collider->SetPos(position.x, position.y);
    }
    app->render->CameraFollow(position);

    return true;
}

bool Player::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    app->render->DrawTexture(texture, position.x, position.y, &rect);
   
    

    return false;
}

void Player::HorizontalMove(bool isLeft)
{
    if (position.x <= 0)
    {
        position.x = 0;
    }
    else if (position.x >= 1280 - 16)
    {
        position.x = 1280 - 16;
    }
    isLeft ? velocity.x = -200.0f : velocity.x = 250.0f;
}

void Player::Propulsion()
{
    velocity.y = -400.0f;
}


void Player::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

SDL_Rect Player::GetBounds()
{
    return { position.x, position.y, width, height };
}

void Player::OnCollision(Collider* collider) 
{
    position = tempPosition;
    velocity.y = 0;
}