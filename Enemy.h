/*
 * Enemy.h
 *
 *  Created on: Sep 2, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#pragma once
#include "GameObject.h"
#ifndef ENEMY_H_
#define ENEMY_H_
class Enemy : public GameObject
{
public:
    Enemy(class Game *game);
    ~Enemy();
    void UpdateGameObject(float deltaTime) override;
    class CircleComponent *GetCircle()
    {
        return this->circle;
    }

private:
    class CircleComponent *circle;
};
#endif /* ENEMY_H_ */
