/*
 * CircleComponent.h
 *
 *  Created on: Sep 2, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#pragma once
#include "Component.h"
#include "Math.h"

#ifndef CIRCLECOMPONENT_H_
#define CIRCLECOMPONENT_H_

class CircleComponent : public Component
{
public:
    CircleComponent(class GameObject *owningGameObject);
    void SetRadius(float radius)
    {
        this->radius = radius;
    }
    float GetRadius() const;
    const Vector2 &GetCenter() const;

private:
    float radius;
};

bool Intersect(const CircleComponent &a, const CircleComponent &b);

#endif /* CIRCLECOMPONENT_H_ */
