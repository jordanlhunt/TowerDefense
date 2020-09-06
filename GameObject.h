/*
 * GameObject.h
 *
 *  Created on: Aug 31, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#pragma once
#include "Math.h"
#include <cstdint>
#include <vector>

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

class GameObject
{
public:
    enum State
    {
        ACTIVE,
        PAUSED,
        DEAD
    };
    GameObject(class Game *game);
    virtual ~GameObject();
    // Update function called from Game (not overridable)
    void Update(float deltaTime);
    // Update all the components attached to the gameObject (not overridable)
    void UpdateComponents(float deltaTime);
    // Any gameObject-specific update code (overridable)
    virtual void UpdateGameObject(float deltaTime);
    // ProcessInput function called from Game(not overridable)
    void ProcessInput(const uint8_t *keyState);
    // Any gameObject-specific input (overridable)
    virtual void GameObjectInput(const uint8_t *keyState);

    // Getter/Setter
    const Vector2 &GetPosition() const
    {
        return this->position;
    }
    void SetPosition(const Vector2 &position)
    {
        this->position = position;
    }
    float GetScale() const
    {
        return this->scale;
    }
    void SetScale(float scale)
    {
        this->scale = scale;
    }
    float GetRotation() const
    {
        return this->rotation;
    }
    void SetRotation(float rotation)
    {
        this->rotation = rotation;
    }
    Vector2 GetForward() const
    {
        return Vector2(Math::Cosine(this->rotation), -Math::Sine(this->rotation));
    }
    State GetState() const
    {
        return this->state;
    }
    void SetState(State state)
    {
        this->state = state;
    }
    class Game *GetGame()
    {
        return this->game;
    }
    void AddComponent(class Component *component);
    void RemoveComponent(class Component *component);

private:
    // GameObject's current state
    State state;
    // Transform
    Vector2 position;
    float scale;
    float rotation;
    std::vector<class Component *> components;
    class Game *game;
};

#endif /* GAMEOBJECT_H_ */
