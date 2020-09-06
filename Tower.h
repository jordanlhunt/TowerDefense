/*
 * Tower.h
 *
 *  Created on: Sep 4, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#include "GameObject.h"
#ifndef TOWER_H_
#define TOWER_H_

class Tower : public GameObject
{
public:
    Tower(class Game *game);
    void UpdateGameObject(float deltaTime) override;

private:
    class MoveComponent *move;
    float nextAttack;
    const float ATTACKTIME = 2.5f;
    const float ATTACKRANGE = 100.0f;
};

#endif /* TOWER_H_ */
