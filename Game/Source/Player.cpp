#include "Player.h"

#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Physics.h"
Player::Player() : Entity(EntityType::PLAYER)
{
    texture = NULL;
    position = iPoint(12 * 16, 27 * 16);
    velocity.y = 200.0f;

    width = 16;
    height = 32;

    // Define Player animations
}

bool Player::Update(float dt)
{
    tempPosition = position;
    if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) HorizontalMove(true);
    if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) HorizontalMove(false);
    if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) Propulsion();
    // Calculate gravity acceleration
    Physics::GetInsance()->UpdateVelocity(position, velocity, acceleration, dt);
    //Temporal floor until coliders are added
    if (position.y >= 600) position.y = 600;
    return true;
}

bool Player::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    SDL_Rect rec = { 0 };
    app->render->DrawTexture(texture, position.x, position.y, &rec);

    app->render->DrawRectangle(GetBounds(), { 255, 0, 0, 255 });

    return false;
}

void Player::HorizontalMove(bool isLeft)
{
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