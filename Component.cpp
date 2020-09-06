/*
 * Component.cpp
 *
 *  Created on: Sep 1, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject *owningGameObject, int componentUpdateOrder) : owner(owningGameObject), updateOrder(componentUpdateOrder)
{
    // Add to gameObject's vector of components
    this->owner->AddComponent(this);
}

Component::~Component()
{
    this->owner->RemoveComponent(this);
}
void Component::Update(float deltaTime)
{
}
