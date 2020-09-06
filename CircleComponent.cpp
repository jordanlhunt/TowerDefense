/*
 * CircleComponent.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#include "CircleComponent.h"
#include "GameObject.h"
CircleComponent::CircleComponent(class GameObject *owningGameObject) : Component(owningGameObject), radius(0.0f)
{
}
const Vector2 &CircleComponent::GetCenter() const
{
    return this->owner->GetPosition();
}
float CircleComponent::GetRadius() const
{
    return this->owner->GetScale() * this->radius;
}
bool Intersect(const CircleComponent &self, const CircleComponent &target)
{
    // Calculate distance squared
    Vector2 difference = self.GetCenter() - target.GetCenter();
    float distanceSquared = difference.LengthSquared();
    // Calculate sum of radii squared
    float radiiSquared = self.GetRadius() + target.GetRadius();
    radiiSquared *= radiiSquared;
    return distanceSquared <= radiiSquared;
}