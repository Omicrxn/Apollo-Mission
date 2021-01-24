#include "Player.h"
#include "Body.h"
#include "Shape.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Font.h"

#include "math.h"
#define PI 3.14159265359

Player::Player() : Entity(EntityType::PLAYER)
{
    texture = NULL;

    for (int i = 5; i >= 0; i--)
    {
        smallFighterTurnLeft.PushBack(SDL_Rect{ i * 95, 0, 95, 151 });
    }
    for (int i = 0; i < 6; i++)
    {
        smallFighterTurnLeft.PushBack(SDL_Rect{ i * 95, 0, 95, 151 });
    }
    smallFighterTurnLeft.loop = false;
    smallFighterTurnLeft.speed = 0.1;

    for (int i = 0; i < 5; i++)
    {
        smallFighterTurnRight.PushBack(SDL_Rect{ i * 95, 151, 95, 151 });
    }
    for (int i = 4; i >= 0; i--)
    {
        smallFighterTurnRight.PushBack(SDL_Rect{ i * 95, 151, 95, 151 });
    }
    smallFighterTurnRight.loop = false;
    smallFighterTurnRight.speed = 0.1;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            explosion.PushBack(SDL_Rect{ j * 240, i * 240, 240, 240 });
        }
    }
    explosion.loop = false;

    explosion.PushBack(SDL_Rect{ 1920, 1440, 240, 240 });

    rect = { 20,12,55,135 };
    fireRect = { 0,0,95,382 };
    width = rect.w;
    height = rect.h;

    c = new Circle(3.0f);
    body = new Body(Vec2f(595.0f, 3071), 5.0f, c, 0.009f);
    body->AddCollision({ 600,400,width,height }, ColliderType::RECTANGLE);

    earthMaxGravity = { 0.0f,600.0f };
    earthGravity = { 0.0f,0.0f };
    earthGravityStart = 2160;
    earthGravityEnd = 3600;

    moonMaxGravity = { 0.0f,-earthMaxGravity.y/6 };
    moonGravity = { 0.0f,0.0f };
    moonGravityStart = 0;
    moonGravityEnd = 1440;

    angle = 0;

    currentLocation = Location::SPACE;

    fxDie = app->audio->LoadFx("Assets/Audio/Fx/explosion_crunch.ogg");
}

bool Player::Update(float dt)
{
    earthGravity = body->GetGravity(earthMaxGravity, body->position, earthGravityStart, earthGravityEnd, false);
    body->AddGravity(earthGravity);

    moonGravity = body->GetGravity(moonMaxGravity, body->position, moonGravityStart, moonGravityEnd, true);
    body->AddGravity(moonGravity);

    if(earthGravity.y > 0.0f)
        body->AddDrag();

    if (body->position.x <= 0)
    {
        body->position.x = 0;
    }

    if (body->position.x >= 1220)
    {
        body->position.x = 1220;
    }

    //if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && (currentLocation == Location::SPACE || currentLocation == Location::WATER)) HorizontalMove(true);
    //if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && (currentLocation == Location::SPACE || currentLocation == Location::WATER)) HorizontalMove(false);
    if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
    {
        propulsion = true;
        fireDraw = true;
        Propulsion(true, angle);
    }
    if (app->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
        fireDraw = false;
    
    if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
        Propulsion(false, angle);

    if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
    {
        smallFighterTurnLeft.Reset();
        animLeft = true;
        animRight = false;
    }
    if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
    {
        angle += 3;
    }

    if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
    {
        smallFighterTurnRight.Reset();
        animRight = true;
        animLeft = false;
    }
    if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
    {
        angle += 360 - 3;
    }

    if (angle > 360)
    {
        angle = angle - 360;
    }

    // Follow if in bounds
    if (body->position.y < (3600 - app->win->GetWindowHeight() / 2) && body->position.y > app->win->GetWindowHeight() / 2)
        app->render->CameraFollow(body->position);

    body->rectCollision->SetPosition(body->position);

    return true;
}

bool Player::Draw()
{
    SDL_Rect currentAnim;
    if (animLeft == true)
    {
        currentAnim = smallFighterTurnLeft.GetCurrentFrame();
    }
    else if (animRight == true)
    {
        currentAnim = smallFighterTurnRight.GetCurrentFrame();
    }
    else
    {
        currentAnim = smallFighterTurnLeft.GetFrame(0);
    }

    if (smallFighterTurnLeft.Finished() == true)
    {
        animLeft = false;
    }
    if (smallFighterTurnRight.Finished() == true)
    {
        animRight = false;
    }

    if (!explode)
    {
        app->render->DrawTexture(texture, body->position.x, body->position.y, &currentAnim, 1.0f, angle);

        if (fireDraw) 
            app->render->DrawTexture(fireTexture, body->position.x, body->position.y, &fireRect, 1.0f, angle, 47, 75);

        // UI Draw
        static char textUI[50];

        sprintf_s(textUI, 40, "Position: %.0f,%.0f", body->position.x, body->position.y);
        app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 + 325, app->win->GetWindowHeight() / 2 - 350, 18, 4, { 255,255,255,255 });
        
        Uint8 r = 255, g = 255, b = 255;

        if (earthGravity.y > 0.0f)
        {
            if (body->velocity.y > 200)
            {
                sprintf_s(textUI, 40, "! Velocity: %.3f,%.3f", body->velocity.x, body->velocity.y * -1);
                g = b = 0;
            }
            else sprintf_s(textUI, 40, "Velocity: %.3f,%.3f", body->velocity.x, body->velocity.y * -1);

            app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 + 325, app->win->GetWindowHeight() / 2 - 330, 18, 4, { r,g,b,255 });
            Uint8 r = 255, g = 255, b = 255;

            if (angle > 30 && angle < 330)
            {
                sprintf_s(textUI, 30, "! Angle: %d", angle);
                g = b = 0;
            }
            else sprintf_s(textUI, 30, "Angle: %d", angle);

            app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 + 325, app->win->GetWindowHeight() / 2 - 310, 18, 4, { r,g,b,255 });
        }
        else if (moonGravity.y < 0.0f)
        {
            if (body->velocity.y < -200)
            {
                sprintf_s(textUI, 40, "! Velocity: %.3f,%.3f", body->velocity.x, body->velocity.y * -1);
                g = b = 0;
            }
            else sprintf_s(textUI, 40, "Velocity: %.3f,%.3f", body->velocity.x, body->velocity.y * -1);

            app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 + 325, app->win->GetWindowHeight() / 2 - 330, 18, 4, { r,g,b,255 });
            Uint8 r = 255, g = 255, b = 255;

            if ((angle >= 0 && angle < 150) || (angle > 210 && angle <= 360))
            {
                sprintf_s(textUI, 30, "! Angle: %d", angle);
                g = b = 0;
            }
            else sprintf_s(textUI, 30, "Angle: %d", angle);

            app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 + 325, app->win->GetWindowHeight() / 2 - 310, 18, 4, { r,g,b,255 });
        }
        else if (earthGravity.y == 0.0f && moonGravity.y == 0.0f)
        {
            sprintf_s(textUI, 40, "Velocity: %.3f,%.3f", body->velocity.x, body->velocity.y * -1);
            app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 + 325, app->win->GetWindowHeight() / 2 - 330, 18, 4, { 255,255,255,255 });
            sprintf_s(textUI, 30, "Angle: %d", angle);
            app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 + 325, app->win->GetWindowHeight() / 2 - 310, 18, 4, { 255,255,255,255 });
        }
        
        sprintf_s(textUI, 30, "Earth's Gravity: %.3f", earthGravity.y);
        app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 + 325, app->win->GetWindowHeight() / 2 - 290, 18, 4, { 255,255,255,255 });
        sprintf_s(textUI, 30, "Moon's Gravity: %.3f", moonGravity.y);
        app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 + 325, app->win->GetWindowHeight() / 2 - 270, 18, 4, { 255,255,255,255 });

        sprintf_s(textUI, 20, "Mass: %.3f", body->mass);
        app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 + 325, app->win->GetWindowHeight() / 2 - 250, 18, 4, { 255,255,255,255 });

        if (currentLocation == Location::WATER) sprintf_s(textUI, 35, "Location: Underwater (+Buoyancy)");
        else if (currentLocation == Location::MOON) sprintf_s(textUI, 35, "Location: Moon");
        else if (currentLocation == Location::GROUND) sprintf_s(textUI, 35, "Location: Ground");
        else if (currentLocation == Location::SPACE && earthGravity.y == 0.0f && moonGravity.y == 0.0f) sprintf_s(textUI, 35, "Location: Outer Space");
        else if (currentLocation == Location::SPACE && earthGravity.y > 0.0f) sprintf_s(textUI, 60, "Location: Earth's Gravitational Field (+Drag)");
        else if (currentLocation == Location::SPACE && moonGravity.y < 0.0f) sprintf_s(textUI, 60, "Location: Moon's Gravitational Field");
        app->render->DrawText(fontUI, textUI, app->win->GetWindowWidth() / 2 - 610, app->win->GetWindowHeight() / 2 - 350, 18, 4, { 255,255,255,255 });
    }

    if (explode)
    {
        app->render->DrawTexture(explosionTexture, body->position.x - 47.5f, body->position.y - 75.5f, &explosion.GetCurrentFrame(), 1.0f, angle);
    }

    return false;
}

void Player::HorizontalMove(bool isLeft)
{
    isLeft ? body->AddImpulse(Vec2f(-0.25f,0.0f), Vec2f(0.0f, 0.0f)) : body->AddImpulse(Vec2f(0.25f, 0.0f), Vec2f(0.0f, 0.0f));
}

void Player::Propulsion(bool isUp, uint angle)
{
    float angleRad = ((float)angle * PI) / 180.0f;
    if (!isUp) 
    {
        if (propulsion)
            body->AddImpulse(Vec2f(-0.1f * cos(PI / 2 - angleRad), 0.1f * sin(PI / 2 - angleRad)), Vec2f(0.0f, 0.0f));
    }
    else
        body->AddImpulse(Vec2f(0.1f * cos(PI / 2 - angleRad), -0.1f * sin(PI / 2 - angleRad)), Vec2f(0.0f, 0.0f));
}

void Player::SetTextures(SDL_Texture* tex, SDL_Texture* tex2, SDL_Texture* tex3)
{
    texture = tex;
    fireTexture = tex2;
    explosionTexture = tex3;
}

void Player::SetFont(Font* font)
{
    fontUI = font;
}

SDL_Rect Player::GetBounds()
{
    return { (int)body->position.x, (int)body->position.y, width, height };
}

Vec2f Player::GetGravity()
{
    return earthGravity;
}

bool Player::CleanUp()
{
    //body->CleanUp();

    return true;
}