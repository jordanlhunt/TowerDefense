/*
 * Bullet.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#include "Bullet.h"
#include "CircleComponent.h"
#include "Enemy.h"
#include "Game.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
Bullet::Bullet(class Game *game) : GameObject(game)
{
    SpriteComponent *spriteComponent = new SpriteComponent(this);
    spriteComponent->SetTexture(game->GetTexture("Assets/Projectile.png"));
    MoveComponent *moveComponent = new MoveComponent(this);
    moveComponent->SetForwardSpeed(400.0f);
    this->circle = new CircleComponent(this);
    this->circle->SetRadius(5.0f);
    this->lifeSpan = 1.0f;
}
void Bullet::UpdateGameObject(float deltaTime)
{
    GameObject::UpdateGameObject(deltaTime);

    // Check for collision
    for (Enemy *enemy : GetGame()->GetEnemies())
    {
        if (Intersect(*this->circle, *(enemy->GetCircle())))
        {
            // Delete bullet and enemy on collision
            enemy->SetState(DEAD);
            SetState(DEAD);
            break;
        }
    }
    this->lifeSpan -= deltaTime;
    if (this->lifeSpan <= 0.0f)
    {
        // when the time let expires, die
        SetState(DEAD);
    }
}
