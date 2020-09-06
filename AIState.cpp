/*
 * AIState.cpp
 *
 *  Created on: Sep 1, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#include "AIState.h"
#include "AIComponent.h"
#include "SDL2/SDL.h"
void AIPatrol::Update(float deltaTime)
{
    SDL_Log("Update %s state", GetName());
    bool isDead = true;
    if (isDead)
    {
        this->owner->ChangeState("Death");
    }
}
void AIPatrol::OnEnter()
{
    SDL_Log("Entering %s state", GetName());
}
void AIPatrol::OnExit()
{
    SDL_Log("Exiting %s state", GetName());
}
void AIDeath::Update(float deltaTime)
{
    SDL_Log("Updating %s state", GetName());
}
void AIDeath::OnEnter()
{
    SDL_Log("Entering %s state", GetName());
}

void AIDeath::OnExit()
{
    SDL_Log("Exiting %s state", GetName());
}
void AIAttack::Update(float deltaTime)
{
    SDL_Log("Updating %s state", GetName());
}

void AIAttack::OnEnter()
{
    SDL_Log("Entering %s state", GetName());
}

void AIAttack::OnExit()
{
    SDL_Log("Exiting %s state", GetName());
}
