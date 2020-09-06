/*
 * MoveComponent.h
 *
 *  Created on: Sep 2, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#pragma once
#include "Component.h"
#ifndef MOVECOMPONENT_H_
#define MOVECOMPONENT_H_

class MoveComponent : public Component
{
public:
    // Lower update order to update first
    MoveComponent(class GameObject *owningGameObject, int updateOrder = 10);
    void Update(float deltaTime) override;
    float GetAngularSpeed() const
    {
        return this->angularSpeed;
    }
    float GetForwardSpeed() const
    {
        return this->forwardSpeed;
    }
    void SetAngularSpeed(float speed)
    {
        this->angularSpeed = speed;
    }
    void SetForwardSpeed(float speed)
    {
        this->forwardSpeed = speed;
    }

private:
    float angularSpeed;
    float forwardSpeed;
};

#endif /* MOVECOMPONENT_H_ */
