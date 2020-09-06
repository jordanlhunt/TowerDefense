/*
 * NavigationComponent.h
 *
 *  Created on: Sep 3, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#pragma once
#include "Math.h"
#include "MoveComponent.h"
#ifndef NAVIGATIONCOMPONENT_H_
#define NAVIGATIONCOMPONENT_H_

class NavigationComponent : public MoveComponent
{
public:
    // Lower update order to update first
    NavigationComponent(class GameObject *owningGameObject, int updateOrder = 10);
    void Update(float deltaTime) override;
    void StartPath(const class Tile *start);
    void TurnTo(const Vector2 &position);

private:
    const class Tile *nextNode;
};

#endif /* NAVIGATIONCOMPONENT_H_ */
