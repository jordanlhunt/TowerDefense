/*
 * NavigationComponent.cpp
 *
 *  Created on: Sep 3, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#include "NavigationComponent.h"
#include "Tile.h"

NavigationComponent::NavigationComponent(class GameObject *owner, int updateOrder) : MoveComponent(owner, updateOrder), nextNode(nullptr)
{
}
void NavigationComponent::Update(float deltaTime)
{
    if (this->nextNode)
    {
        // If currently at the next node, advance along the path
        Vector2 difference = this->owner->GetPosition() - this->nextNode->GetPosition();
        if (Math::IsNearZero(difference.Length(), 2.0f))
        {
            this->nextNode = this->nextNode->GetParent();
            TurnTo(this->nextNode->GetPosition());
        }
    }
    MoveComponent::Update(deltaTime);
}
void NavigationComponent::StartPath(const Tile *start)
{
    this->nextNode = start->GetParent();
    TurnTo(this->nextNode->GetPosition());
}
void NavigationComponent::TurnTo(const Vector2 &position)
{
    // Vector from origin to position
    Vector2 direction = position - this->owner->GetPosition();
    // New is arcTanget2 of the directon vector
    // Negate y because +y is down on the screen
    float angle = Math::Arctangent2(-direction.y, direction.x);
    this->owner->SetRotation(angle);
}
