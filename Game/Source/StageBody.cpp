#include "StageBody.h"
#include "Body.h"
#include "Shape.h"
#include "App.h"
#include "Render.h"
#include "Render.h"
#include "Window.h"


StageBody::StageBody() : Entity(EntityType::PLAYER)
{
    texture = NULL;
    rect = { 917,531,42,42 };
    width = 42;
    height = 42;
    Circle* c = new Circle(3.0f);
    body = new Body(Vec2f(600.0f, 550.0f), 5.0f, c, 0.009f);
    body->AddCollision({ 600,400,width,height }, ColliderType::RECTANGLE);
}

bool StageBody::Update(float dt)
{
    body->AddGravity(Vec2f(0.0f, 600.0f));


    //follow if over the ground
    //if (body->position.y < (3600 - app->win->GetWindowHeight() / 2) && body->position.y > app->win->GetWindowHeight() / 2)
    //    app->render->CameraFollow(body->position);

    body->rectCollision->SetPosition(body->position);

    return true;
}

bool StageBody::Draw()
{
    // TODO: Calculate the corresponding rectangle depending on the
    // animation state and animation frame
    app->render->DrawTexture(texture, body->position.x, body->position.y, &rect);
    return false;
}

void StageBody::SetTexture(SDL_Texture* tex)
{
    texture = tex;
}

SDL_Rect StageBody::GetBounds()
{
    return { (int)body->position.x, (int)body->position.y, width, height };
}
