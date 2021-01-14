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
    #define GRAVITY 400.0f
    #define PLAYER_MOVE_SPEED 200.0f
    #define PLAYER_JUMP_SPEED 350.0f

    if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) position.y += (PLAYER_MOVE_SPEED * dt);
    if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) position.y -= (PLAYER_MOVE_SPEED * dt);
    if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) position.x -= (PLAYER_MOVE_SPEED * dt);
    if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) position.x += (PLAYER_MOVE_SPEED * dt);

    if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) position.y -= (PLAYER_JUMP_SPEED * dt);

    // Calculate gravity acceleration
    Physics::GetInsance()->UpdateVelocity(position,velocity,dt);
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

void Player::SetTexture(SDL_Texture *tex)
{
    texture = tex;
}

SDL_Rect Player::GetBounds()
{
    return { position.x, position.y, width, height };
}