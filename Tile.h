/*
 * Tile.h
 *
 *  Created on: Sep 3, 2020
 *      Author: Jordan "Heroic" Hunt
 */
#pragma once
#include "GameObject.h"

#ifndef TILE_H_
#define TILE_H_

class Tile : public GameObject
{
public:
    friend class Grid;
    enum TileState
    {
        DEFAULT,
        PATH,
        START,
        END
    };
    Tile(class Game *game);
    void ToggleSelect();
    void SetTileState(TileState state);
    TileState GetTileState() const
    {
        return this->tileState;
    }
    const Tile *GetParent() const
    {
        return this->parent;
    }

private:
    // Pathfinding
    std::vector<Tile *> adjacentTiles;
    Tile *parent;
    float f;
    float g;
    float h;
    bool isInOpenSet;
    bool isInClosedSet;
    bool isBlocked;
    void UpdateTexture();
    class SpriteComponent *sprite;
    TileState tileState;
    bool isSelected;
};

#endif /* TILE_H_ */
