/*
 * Component.h
 *
 *  Created on: Sep 1, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#pragma once
#include <cstdint>
#ifndef COMPONENT_H_
#define COMPONENT_H_

class Component
{
public:
    // Constructor
    Component(class GameObject *owner, int updateOrder = 100);
    // Destructor
    virtual ~Component();
    // Update this component by deltaTime
    virtual void Update(float deltaTime);
    // Process input for this component
    virtual void ProcessInput(const uint8_t *keyState)
    {
    }
    int GetUpdateOrder() const
    {
        return this->updateOrder;
    }

protected:
    // Owning GameObject
    class GameObject *owner;
    // Update order of component
    int updateOrder;
};

#endif /* COMPONENT_H_ */
