/*
 * AIState.h
 *
 *  Created on: Sep 1, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#pragma once
#ifndef AISTATE_H_
#define AISTATE_H_
class AIState
{
public:
    AIState(class AIComponent *owningAIComponent) : owner(owningAIComponent)
    {
    }
    // State-specific behavior
    virtual void Update(float deltaTime) = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    // Getter
    virtual const char *GetName() const = 0;

protected:
    class AIComponent *owner;
};
class AIPatrol : public AIState
{
public:
    AIPatrol(class AIComponent *owningAIComponent) : AIState(owningAIComponent)
    {
    }
    // Override default behaviors for this state
    void Update(float deltaTime) override;
    void OnEnter() override;
    void OnExit() override;
    const char *GetName() const override
    {
        return "Patrol";
    }
};
class AIDeath : public AIState
{
public:
    AIDeath(class AIComponent *owningAIComponent) : AIState(owningAIComponent)
    {
    }
    // Override default behaviors for this state
    void Update(float deltaTime) override;
    void OnEnter() override;
    void OnExit() override;
    const char *GetName() const override
    {
        return "Death";
    }
};
class AIAttack : public AIState
{
public:
    AIAttack(class AIComponent *owningAIComponent) : AIState(owningAIComponent)
    {
    }
    // Override default behaviors for this state
    void Update(float deltaTime) override;
    void OnEnter() override;
    void OnExit() override;
    const char *GetName() const override
    {
        return "Attack";
    }
};
#endif /* AISTATE_H_ */
