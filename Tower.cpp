/*
 * Tower.cpp
 *
 *  Created on: Sep 4, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Tower.h"
Tower::Tower(class Game *game) : GameObject(game)
{
    SpriteComponent *spriteComponent = new SpriteComponent(this, 200);
    spriteComponent->SetTexture(game->GetTexture("Assets/Tower.png"));
    this->move = new MoveComponent(this);
    this->nextAttack = ATTACKTIME;
}
void Tower::UpdateGameObject(float deltaTime)
{
    GameObject::UpdateGameObject(deltaTime);
    this->nextAttack -= deltaTime;
    if (this->nextAttack <= 0.0f)
    {
        Enemy *enemy = GetGame()->GetNearestEnemy(GetPosition());
        if (enemy != nullptr)
        {
            // Vector from face enemy
            Vector2 direction = enemy->GetPosition() - GetPosition();
            float distance = direction.Length();
            if (distance < ATTACKRANGE)
            {
                // Rotate to face enemy
                SetRotation(Math::Arctangent2(-direction.y, direction.x));
                // Spawn a bullet at tower position face enemy
                Bullet *bullet = new Bullet(GetGame());
                bullet->SetRotation(GetRotation());
                bullet->SetPosition(GetPosition());
            }
        }
        this->nextAttack += ATTACKTIME;
    }
}
