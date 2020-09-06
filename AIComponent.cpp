/*
 * AIComponent.cpp
 *
 *  Created on: Sep 1, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#include "AIComponent.h"
#include "AIState.h"
#include "GameObject.h"
#include <SDL2/SDL_log.h>

AIComponent::AIComponent(class GameObject *owner) : Component(owner), currentState(nullptr)
{
}

void AIComponent::Update(float deltaTime)
{
    if (this->currentState)
    {
        this->currentState->Update(deltaTime);
    }
}

void AIComponent::ChangeState(const std::string &name)
{
    // Exit the current state
    if (this->currentState)
    {
        this->currentState->OnExit();
    }
    // Find the new state from the map
    auto iter = this->stateMap.find(name);
    if (iter != this->stateMap.end())
    {
        this->currentState = iter->second;
        // Enter the new state
        this->currentState->OnEnter();
    }
    else
    {
        SDL_Log("Could not find AIState %s in state map", name.c_str());
        this->currentState = nullptr;
    }
}
void AIComponent::AddState(AIState *state)
{
    this->stateMap.emplace(state->GetName(), state);
}
