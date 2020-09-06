/*
 * Bullet.h
 *
 *  Created on: Sep 2, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#pragma once
#include "GameObject.h"
#ifndef BULLET_H_
#define BULLET_H_

class Bullet : public GameObject
{
public:
    Bullet(class Game *game);
    void UpdateGameObject(float deltaTime) override;

private:
    class CircleComponent *circle;
    float lifeSpan;
};

#endif /* BULLET_H_ */
