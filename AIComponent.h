/*
 * AIComponent.h
 *
 *  Created on: Sep 1, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#ifndef AICOMPONENT_H_
#define AICOMPONENT_H_
#pragma once
#include "Component.h"
#include <string>
#include <unordered_map>

class AIComponent : public Component
{
public:
    AIComponent(class GameObject *owner);
    void Update(float deltaTime) override;
    void ChangeState(const std::string &name);
    void AddState(class AIState *state);

private:
    // Maps name of state to AIState instance
    std::unordered_map<std::string, class AIState *> stateMap;
    // Current state
    class AIState *currentState;
};

#endif /* AICOMPONENT_H_ */
