/*
 * Grid.h
 *
 *  Created on: Sep 3, 2020
 *      Author: Jordan "Heroic" Hunt
 */

#pragma once
#include "GameObject.h"
#include <vector>
#ifndef GRID_H_
#define GRID_H_

class Grid : public GameObject
{
public:
    Grid(class Game *game);
    // Handle a mouse click on a x/y location
    void ProcessClick(int x, int y);
    // Use A* to find a path;
    bool FindAStarPath(class Tile *start, class Tile *goal);
    // Build a tower on a location
    void BuildTower();
    // Get the start and end tiel
    class Tile *GetStartTile();
    class Tile *GetEndTile();
    void UpdateGameObject(float deltaTime) override;

private:
    // Select a specific tile
    void SelectTile(size_t row, size_t col);
    // Update textures for tiles on path
    void UpdatePathTiles(class Tile *start);
    // Create Tiles
    void CreateTiles();
    // Create Rows and Columns
    void CreateRowsAndColumns();
    // Create Adjacency Lists
    void CreateAdjacencyLists();
    // Currently selected tile
    class Tile *selectedTile;
    // 2D Vector of tiles in grid
    std::vector<std::vector<class Tile *>> tiles;
    // Time until next enemy
    float nextEnemySpawnTime;
    // Rows and Columns in grid
    const size_t NUMROWS = 7;
    const size_t NUMCOLS = 16;
    // Starting y position of the top left corner
    const float STARTY = 192.0f;
    // Width and height of each tile
    const float TILESIZE = 64.0f;
    // Time between enemies
    const float ENEMYSPAWNTIME = 1.5f;
};

#endif /* GRID_H_ */
