/*
 * GameObject.cpp
 *
 *  Created on: Aug 31, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#include "GameObject.h"
#include "Component.h"
#include "Game.h"
#include <algorithm>
GameObject::GameObject(Game *game) : state(ACTIVE), position(Vector2::Zero), scale(1.0f), rotation(0.0f), game(game)
{
    this->game->AddGameObject(this);
}
GameObject::~GameObject()
{
    this->game->RemoveGameObject(this);
    // Delete the components of this gameObject
    while (!this->components.empty())
    {
        delete this->components.back();
    }
}
void GameObject::Update(float deltaTime)
{
    if (this->state == ACTIVE)
    {
        UpdateComponents(deltaTime);
        UpdateGameObject(deltaTime);
    }
}
void GameObject::UpdateComponents(float deltaTime)
{
    for (auto gameComponent : this->components)
    {
        gameComponent->Update(deltaTime);
    }
}
void GameObject::UpdateGameObject(float deltaTime)
{
}
void GameObject::ProcessInput(const uint8_t *keyState)
{
    if (this->state == ACTIVE)
    {
        // Process input for each component
        for (auto gameComponent : this->components)
        {
            gameComponent->ProcessInput(keyState);
        }
        GameObjectInput(keyState);
    }
}
void GameObject::GameObjectInput(const uint8_t *keyState)
{
}
void GameObject::AddComponent(Component *component)
{
    // Find the insertion point in the sorted vector
    // which will be the first element with a higher order than this gameObject
    int gameObjectOrder = component->GetUpdateOrder();
    auto iter = this->components.begin();
    for (; iter != this->components.end(); iter++)
    {
        if (gameObjectOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    // Insert the component before position of iterator
    this->components.insert(iter, component);
}
void GameObject::RemoveComponent(Component *component)
{
    auto iter = std::find(this->components.begin(), this->components.end(), component);
    if (iter != this->components.end())
    {
        this->components.erase(iter);
    }
}
