/*
 * MoveComponent.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#include "MoveComponent.h"
#include "GameObject.h"
MoveComponent::MoveComponent(class GameObject *owner, int updateOrder) : Component(owner, updateOrder), angularSpeed(0.0f), forwardSpeed(0.0f)
{
}
void MoveComponent::Update(float deltaTime)
{
    if (!Math::IsNearZero(this->angularSpeed))
    {
        float rotation = this->owner->GetRotation();
        rotation += this->angularSpeed * deltaTime;
        this->owner->SetRotation(rotation);
    }
    if (!Math::IsNearZero(forwardSpeed))
    {
        Vector2 position = this->owner->GetPosition();
        position += this->owner->GetForward() * this->forwardSpeed * deltaTime;
        this->owner->SetPosition(position);
    }
}
