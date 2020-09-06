/*
 * Enemy.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#include "Enemy.h"
#include "CircleComponent.h"
#include "Game.h"
#include "Grid.h"
#include "NavigationComponent.h"
#include "SpriteComponent.h"
#include "Tile.h"
#include <algorithm>

Enemy::Enemy(class Game *game)
    : GameObject(game)
{
    // Add to enemy vector
    game->GetEnemies().emplace_back(this);
    SpriteComponent *spriteComponent = new SpriteComponent(this);
    spriteComponent->SetTexture(game->GetTexture("Assets/Airplane.png"));
    // Set Position at starting tile
    SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
    NavigationComponent *navigationComponent = new NavigationComponent(this);
    navigationComponent->SetForwardSpeed(150.0f);
    navigationComponent->StartPath(GetGame()->GetGrid()->GetStartTile());
    this->circle = new CircleComponent(this);
    this->circle->SetRadius(25.0f);
}

Enemy::~Enemy()
{
    // Remove from the enemy vector
    auto iter = std::find(GetGame()->GetEnemies().begin(), GetGame()->GetEnemies().end(), this);
    GetGame()->GetEnemies().erase(iter);
}
void Enemy::UpdateGameObject(float deltaTime)
{
    GameObject::UpdateGameObject(deltaTime);
    // Check if at the end of tile
    Vector2 difference = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
    if (Math::IsNearZero(difference.Length(), 10.0f))
    {
        SetState(DEAD);
    }
}
